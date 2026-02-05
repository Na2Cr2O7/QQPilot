// ini_parser.hpp
#pragma once
#include <string>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <vector>

class IniParser {
public:
    using Section = std::unordered_map<std::wstring, std::wstring>;
    using Sections = std::unordered_map<std::wstring, Section>;

    // 构造函数：从文件加载
    explicit IniParser(const std::wstring& filename) {
        load(filename);
    }

    // 默认构造（空配置）
    IniParser() = default;

    // 加载 INI 文件（UTF-8 编码）
    bool load(const std:: wstring& filename) {
        std::ifstream file(filename, std::ios::binary);
        if (!file.is_open()) return false;

        // 读取整个文件内容（支持跨平台换行）
        std::wstring content((std::istreambuf_iterator<char>(file)),
                            std::istreambuf_iterator<char>());
        file.close();
        content;
        parse(content);
        m_filename = filename;
        return true;
    }

    // 保存到文件（UTF-8 编码）
    bool save(const std::wstring& filename = L"") const {
        std::wstring out_file = filename.empty() ? m_filename : filename;
        if (out_file.empty()) return false;

        std::ofstream file(out_file, std::ios::binary);
        if (!file.is_open()) return false;

        // 可选：写入 UTF-8 BOM（Windows 记事本友好）
        // file.write("\xEF\xBB\xBF", 3);

        for (const auto& sec_pair : m_sections) {
            file << "[" << sec_pair.first << "]\n";
            for (const auto& kv : sec_pair.second) {
                file << kv.first << "=" << kv.second << "\n";
            }
            file << "\n";
        }
        file.close();
        return true;
    }

    // 获取字符串值
    std::wstring getString(const std::wstring& section, const std::wstring& key,
                          const std::wstring& default_value = L"") const {
        auto sec_it = m_sections.find(section);
        if (sec_it != m_sections.end()) {
            auto key_it = sec_it->second.find(key);
            if (key_it != sec_it->second.end()) {
                return key_it->second;
            }
        }
        return default_value;
    }

    // 设置字符串值
    void setString(const std::wstring& section, const std::wstring& key, const std::wstring& value) {
        m_sections[section][key] = value;
    }

    // 获取整数
    int getInt(const std::wstring& section, const std::wstring& key, int default_value = 0) const {
        std::wstring val = getString(section, key);
        if (val.empty()) return default_value;
        try {
            size_t pos;
            int result = std::stoi(val, &pos);
            if (pos == 0) return default_value; // 无效数字
            return result;
        } catch (...) {
            return default_value;
        }
    }

    // 设置整数
    void setInt(const std::wstring& section, const std::wstring& key, int value) {
        setString(section, key, std::to_wstring(value));
    }

    // 获取布尔值（支持 true/false, 1/0, yes/no, on/off，不区分大小写）
    bool getBool(const std::wstring& section, const std::wstring& key, bool default_value = false) const {
        std::wstring val = getString(section, key);
        if (val.empty()) return default_value;

        // 转为小写
        std::wstring lower;
        std::transform(val.begin(), val.end(), std::back_inserter(lower),
                       [](unsigned char c) { return std::tolower(c); });

        if (lower == "true" || lower == "1" || lower == "yes" || lower == "on") return true;
        if (lower == "false" || lower == "0" || lower == "no" || lower == "off") return false;
        return default_value;
    }

    // 设置布尔值（输出为 "true"/"false"）
    void setBool(const std::wstring& section, const std::wstring& key, bool value) {
        setString(section, key, value ? L"true" : L"false");
    }

    // 删除键
    bool removeKey(const std::wstring& section, const std::wstring& key) {
        auto sec_it = m_sections.find(section);
        if (sec_it != m_sections.end()) {
            return sec_it->second.erase(key) > 0;
        }
        return false;
    }

    // 删除整个节
    bool removeSection(const std::wstring& section) {
        return m_sections.erase(section) > 0;
    }

private:
    std::wstring m_filename;
    Sections m_sections;

    void parse(const std::wstring& content) {
        m_sections.clear();
        std::wistringstream stream(content);
        std::wstring line;
        std::wstring current_section = L"";

        while (std::getline(stream, line)) {
            // 移除行尾 \r（兼容 Windows 换行）
            if (!line.empty() && line.back() == '\r') {
                line.pop_back();
            }

            // 跳过空行和注释
            if (line.empty() || line[0] == ';' || line[0] == '#') {
                continue;
            }

            // 检查是否是节 [section]
            if (line.front() == '[' && line.back() == ']') {
                current_section = line.substr(1, line.size() - 2);
                trim(current_section);
                continue;
            }

            // 查找 '=' 分隔符
            size_t eq_pos = line.find('=');
            if (eq_pos == std::wstring::npos) {
                continue; // 无效行
            }

            std::wstring key = line.substr(0, eq_pos);
            std::wstring value = line.substr(eq_pos + 1);

            trim(key);
            trim(value);

            if (!key.empty()) {
                m_sections[current_section][key] = value;
            }
        }
    }

    // 去除字符串首尾空白（支持 UTF-8 安全的空格：仅 ASCII 空白）
    static void trim(std::wstring& s) {
        return;
        // 注意：UTF-8 中文字符不会被误删，因为空格是 ASCII 0x20
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
            return !std::isspace(ch);
        }));
        s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
            return !std::isspace(ch);
        }).base(), s.end());
    }
};