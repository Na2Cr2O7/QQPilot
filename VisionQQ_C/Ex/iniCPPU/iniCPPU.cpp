// iniCPPU.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<fstream>
#include <string>
#include<vector>
#include<unordered_map>
#include "inicpp.hpp"
std::u8string trim(const std::u8string& str) {
    if (str.empty()) return str;
    size_t start = 0;
    size_t end = str.size();

    // 跳过前导空白（U+0020 SPACE, U+0009 TAB, U+000D CR, U+000A LF）
    while (start < end && (str[start] == u8' ' || str[start] == u8'\t' ||
        str[start] == u8'\r' || str[start] == u8'\n')) {
        ++start;
    }
    // 跳过尾部空白
    while (end > start && (str[end - 1] == u8' ' || str[end - 1] == u8'\t' ||
        str[end - 1] == u8'\r' || str[end - 1] == u8'\n')) {
        --end;
    }
    return str.substr(start, end - start);
}
std::u8string readUtf8File(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary); // 以二进制模式避免文本转换
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + filename);
    }

    // 读取全部字节
    std::vector<char> buffer(std::istreambuf_iterator<char>(file), {});

    return std::u8string(reinterpret_cast<const char8_t*>(buffer.data()), buffer.size());
}
template<typename T>
int replaceAll(
    std::basic_string<T>& src,
    const std::basic_string<T>& from,
    const std::basic_string<T>& to)
{
    if (from.empty()) {
        return 0;
    }

    //std::basic_string<T> result = src;
    int count = 0;
    size_t start_pos = 0;


    while ((start_pos = src.find(from, start_pos)) != std::basic_string<T>::npos) {
        src.replace(start_pos, from.length(), to);
        start_pos += to.length();
        ++count;
    }

    return count;
    //return result;
}
std::vector<std::u8string> splitLines(const std::u8string& text) {
    std::vector<std::u8string> lines;
    size_t start = 0;
    size_t pos = 0;

    while (pos < text.size()) {
        if (text[pos] == u8'\n') {
            lines.push_back(text.substr(start, pos - start));
            start = pos + 1;
            // 处理 \r\n
            if (start > 0 && text[start - 2] == u8'\r') {
                lines.back().resize(lines.back().size() - 1);
            }
        }
        else if (text[pos] == u8'\r') {
            // 单独 \r（Mac 风格）
            lines.push_back(text.substr(start, pos - start));
            start = pos + 1;
        }
        ++pos;
    }
    // 处理最后一行（无换行符）
    if (start < text.size()) {
        lines.push_back(text.substr(start));
    }
    return lines;
}
std::unordered_map<std::u8string, std::unordered_map<std::u8string, std::u8string>>
parseIniU8(const std::u8string& content) {
    auto lines = splitLines(content);
    std::unordered_map<std::u8string, std::unordered_map<std::u8string, std::u8string>> ini;
    std::u8string currentSection = u8""; // 全局节（无 [section] 的键值对）

    for (auto& line : lines) {
        auto trimmed = trim(line);
        if (trimmed.empty()) continue;

        // 跳过注释
        if (trimmed[0] == u8';' || trimmed[0] == u8'#') continue;

        // [section]
        if (trimmed.front() == u8'[' && trimmed.back() == u8']') {
            currentSection = trim(trimmed.substr(1, trimmed.size() - 2));
            if (currentSection.empty()) continue;
            ini[currentSection]; // 确保存在
            continue;
        }

        // key = value
        size_t eq = trimmed.find(u8'=');
        if (eq == std::u8string::npos) continue;

        std::u8string key = trim(trimmed.substr(0, eq));
        std::u8string value = trim(trimmed.substr(eq + 1));

        // 去除引号（可选）
        if (value.size() >= 2) {
            if ((value.front() == u8'"' && value.back() == u8'"') ||
                (value.front() == u8'\'' && value.back() == u8'\'')) {
                value = value.substr(1, value.size() - 2);
            }
        }

        if (!key.empty()) {
            ini[currentSection][key] = value;
        }
    }
    return ini;
}
int main() {
    try {
        auto content = readUtf8File("config.ini");
        // 可选：预处理空格（如你最初的需求）
        replaceAll(content, std::u8string(u8" = "), std::u8string(u8"="));

        auto ini = parseIniU8(content);

        // 输出（需 cast 回 char* 才能打印）
        for (const auto& [sec, kv] : ini) {
            std::cout << "[" << reinterpret_cast<const char*>(sec.c_str()) << "]\n";
            for (const auto& [k, v] : kv) {
                std::cout << reinterpret_cast<const char*>(k.c_str())
                    << " = "
                    << reinterpret_cast<const char*>(v.c_str()) << "\n";
            }
            std::cout << "\n";
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    return 0;
}
template<typename T>
unsigned find(const std::basic_string<T>& src, const std::basic_string<T>& target)
{
    return src.find(target);
}

unsigned GetPrivateProfileString(
    const char8_t*  lpAppName,
    const char8_t*  lpKeyName,
    const char8_t*  lpDefault,
    char8_t *       lpReturnedString ,
    unsigned        size     ,
    const char8_t* lpFileName
    )
{

    return 1;
}



