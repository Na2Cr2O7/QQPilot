#include "localization.h"

#include <windows.h>

#include <fstream>
#include <sstream>
#include <vector>

#include "json.hpp"

namespace localization
{
	namespace
	{
		nlohmann::json data = nlohmann::json::object();
		std::wstring current_locale;

		std::string ToUtf8(const std::wstring& text)
		{
			if (text.empty())
			{
				return {};
			}
			const int length = WideCharToMultiByte(CP_UTF8, 0, text.data(), static_cast<int>(text.size()),
				nullptr, 0, nullptr, nullptr);
			if (length <= 0)
			{
				return {};
			}
			std::string result(static_cast<size_t>(length), '\0');
			WideCharToMultiByte(CP_UTF8, 0, text.data(), static_cast<int>(text.size()),
				result.data(), length, nullptr, nullptr);
			return result;
		}

		std::wstring CurrentDirectory()
		{
			const DWORD length = GetCurrentDirectoryW(0, nullptr);
			if (length == 0)
			{
				return {};
			}
			std::wstring path(length, L'\0');
			const DWORD written = GetCurrentDirectoryW(length, path.data());
			if (written == 0 || written >= length)
			{
				return {};
			}
			path.resize(written);
			return path;
		}

		std::wstring ModuleDirectory()
		{
			std::wstring path(MAX_PATH, L'\0');
			for (;;)
			{
				const DWORD written = GetModuleFileNameW(nullptr, path.data(), static_cast<DWORD>(path.size()));
				if (written == 0)
				{
					return {};
				}
				if (written < path.size())
				{
					path.resize(written);
					break;
				}
				path.resize(path.size() * 2);
			}

			const size_t slash = path.find_last_of(L"\\/");
			if (slash == std::wstring::npos)
			{
				return {};
			}
			path.erase(slash);
			return path;
		}

		bool EqualsIgnoreCase(const std::wstring& left, const wchar_t* right)
		{
			return _wcsicmp(left.c_str(), right) == 0;
		}

		/// 读一个 JSON 文件。BOM、空文件、半截文件都当作"没有这个文件"，
		/// 这样"建了个空文件占位"也能正确回退到兜底语言，而不是把界面变成一片 X。
		bool ReadJson(const std::wstring& path, nlohmann::json& out)
		{
			std::ifstream file(path, std::ios::binary);
			if (!file)
			{
				return false;
			}
			std::ostringstream buffer;
			buffer << file.rdbuf();
			std::string text = buffer.str();

			// UTF-8 BOM：nlohmann 不认，先去掉。
			if (text.size() >= 3 &&
				static_cast<unsigned char>(text[0]) == 0xEF &&
				static_cast<unsigned char>(text[1]) == 0xBB &&
				static_cast<unsigned char>(text[2]) == 0xBF)
			{
				text.erase(0, 3);
			}
			if (text.empty())
			{
				return false;
			}

			const nlohmann::json parsed = nlohmann::json::parse(text, nullptr, false);
			if (parsed.is_discarded() || !parsed.is_object() || parsed.empty())
			{
				return false;
			}
			out = parsed;
			return true;
		}
	}

	void load()
	{
		data = nlohmann::json::object();

		wchar_t locale_buffer[LOCALE_NAME_MAX_LENGTH] = {};
		if (GetUserDefaultLocaleName(locale_buffer, LOCALE_NAME_MAX_LENGTH) > 0)
		{
			current_locale = locale_buffer;
		}
		else
		{
			current_locale.clear();
		}

		// 与 qqpilot5 的 LOCALES/FALLBACK_LOCALE 保持一致。
		std::vector<std::wstring> candidates;
		for (const wchar_t* name : { L"zh-CN", L"en-US" })
		{
			if (EqualsIgnoreCase(current_locale, name))
			{
				candidates.emplace_back(name);
			}
		}
		candidates.emplace_back(L"zh-CN");

		// 先找自己所在的目录，再找工作目录：两种启动方式都能读到翻译。
		std::vector<std::wstring> directories;
		const std::wstring module_directory = ModuleDirectory();
		if (!module_directory.empty())
		{
			directories.push_back(module_directory);
		}
		const std::wstring current_directory = CurrentDirectory();
		if (!current_directory.empty() && current_directory != module_directory)
		{
			directories.push_back(current_directory);
		}

		for (const std::wstring& locale : candidates)
		{
			for (const std::wstring& directory : directories)
			{
				nlohmann::json parsed;
				if (ReadJson(directory + L"\\" + locale + L".json", parsed))
				{
					data = std::move(parsed);
					return;
				}
			}
		}
	}

	std::string get(const std::string& src)
	{
		const auto it = data.find(src);
		if (it != data.end() && it->is_string())
		{
			return it->get<std::string>();
		}
		return std::string("X") + src;
	}

	bool has(const std::string& src)
	{
		const auto it = data.find(src);
		return it != data.end() && it->is_string();
	}

	bool is_chinese()
	{
		return EqualsIgnoreCase(current_locale, L"zh-CN");
	}
}
