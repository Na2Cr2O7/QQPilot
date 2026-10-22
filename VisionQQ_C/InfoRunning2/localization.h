#pragma once

#include <string>

namespace localization
{
	/// 按"当前系统语言 -> 兜底语言(zh-CN)"的顺序读取翻译文件。
	///
	/// 文件是 UTF-8 编码的 JSON，读取时不会做代码页转换 —— 拿到什么字节就是什么字节，
	/// 界面上要显示时再统一用 CP_UTF8 转成 UTF-16。
	void load();

	/// 取一条文案（UTF-8）。找不到时返回 `X<key>`，与 qqpilot5 的行为一致。
	std::string get(const std::string& src);

	/// 这条文案是否存在。
	bool has(const std::string& src);

	/// 当前系统语言是不是中文，用于没有翻译文件时的兜底文案。
	bool is_chinese();
}
