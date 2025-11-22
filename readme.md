
# VisionQQ - 基于纯视觉的 QQ 自动回复机器人

[![示例截图](./VisionQQ.jpeg)](./VisionQQ.jpeg)

> 使用纯图像识别技术实现 QQ 消息自动回复，**零 API 依赖、零注入、低封号风险**。仅支持 Windows 系统。

---

## 🌟 项目简介

VisionQQ 是一个基于计算机视觉（CV）与 OCR 技术的全自动 QQ 聊天机器人。它通过以下流程实现智能回复：

> **截图 → 图像处理 → OCR 识别 → LLM 生成回复 → 模拟输入发送**

全程不调用 QQ 内部接口、不 Hook 进程、不注入 DLL，极大降低账号安全风险。

---

## ✅ 核心优势

- **安全无痕**：纯视觉操作，零注入、零 Hook，几乎无封号风险  
- **隐私可控**：支持完全本地运行（OCR + LLM），数据不出设备  
- **灵活扩展**：可对接任意本地大模型（如 Ollama）或远程 API  
- **开箱即用**：提供完整打包环境，无需手动配置 Python

## ⚠️ 使用限制

- 仅支持 **Windows** 系统（需桌面 GUI 环境）  
- 对屏幕 **分辨率** 和 **DPI 缩放比例** 敏感（推荐 100% 或 125%）  
- OCR 准确率受 **字体、背景、聊天窗口布局** 影响  
- 需保持 QQ 主窗口 **可见且未最小化**

---

## 🔧 工作原理

1. **窗口置顶**  
   通过 `FocusqqWindow.dll`（Python ctypes 调用）强制将 QQ 主窗口置顶，确保截图一致性。

2. **DPI 自适应**  
   运行 `ScaleToINI.exe` 自动检测系统缩放比例，并写入 `config.ini` 用于坐标校准。

3. **未读消息检测**  
   在联系人列表区域扫描“小红点”，定位有新消息的会话。

4. **自动交互**  
   模拟鼠标点击红点位置，打开对应聊天窗口。

5. **内容识别**  
   - 截取聊天区域并进行 **对比度增强 + 二值化** 预处理  
   - 使用 [EasyOCR](https://github.com/JaidedAI/EasyOCR) 提取文本  
   - 通过监测 `nt_data/emoji` 和 `nt_data/picture` 目录变化，识别表情包

6. **智能回复生成**  
   将识别结果传入本地大模型（如 Ollama）或 HTTP API，生成自然语言回复。

7. **自动发送**  
   - 将回复文本粘贴至 QQ 输入框  
   - 随机插入 `.\Images` 中的表情包（可选）  
   - 模拟回车键发送消息

8. **会话清理**  
   发送完成后自动关闭当前聊天窗口，返回主界面继续监听。

---

## 📦 安装指南

### 步骤 1：下载项目
前往 [Releases](https://github.com/Na2Cr2O7/Visionqq/releases) 下载最新压缩包并解压。

### 步骤 2：安装依赖
双击运行 `install.cmd`（需联网）：
- 自动解压内置 Python 3.13 环境
- 安装依赖：`easyocr`, `pillow`, `pyautogui`, `pyperclip`, `requests`, `ollama`, `colorama` 等
- 总体积 ≤ 1GB

### 步骤 3：配置大模型（推荐）
安装 [Ollama](https://ollama.com/) 并拉取模型：

```bash
# 推荐主力模型（7B）
ollama pull huihui_ai/deepseek-r1-abliterated:7b

# 低配设备可选（1.5B）
ollama pull huihui_ai/deepseek-r1-abliterated:1.5b

# 视觉多模态模型（效果一般，慎用）
ollama pull huihui_ai/qwen3-vl-abliterated:latest
```


> 💡 **提示**：当前本地视觉模型效果较差，**强烈建议使用纯文本模型**。  
> 如需自定义 API，可在 `config.ini` 中设置。

### 步骤 4：初始化设置
运行 `设置.exe` 配置参数（如 QQ 窗口位置、表情包路径等）。

---

## ▶️ 使用方法

1. 将自定义表情包放入 `.\Images` 文件夹（可选）  
2. 打开 QQ 客户端并登录账号  
3. **确保 QQ 主窗口可见（不要最小化或遮挡）**  
4. 双击运行 `run.bat` 启动主程序  
5. 程序将自动监控未读消息并智能回复

> 📌 **重要**：保持 QQ 窗口始终在前台，避免被其他窗口覆盖！

---

## ⚙️ QQ 推荐设置（提升识别准确率）

| 设置项             | 推荐值                     |
|--------------------|---------------------------|
| 联系人面板宽度     | 调整窗口后拉到**最窄**     |
| 字体大小           | 设为“**最小**”            |
| 聊天背景           | 使用**默认白色背景**       |
| 系统显示缩放       | **100% 或 125%**（避免过高）|

> 📷 参考图示：[注意事项说明](./notice1.jpeg)

---

## 🛠️ 编译说明（开发者）

本项目基于 **Python 3.13** 开发，依赖见 `requirements.txt`。

还需编译以下原生组件：
- `FocusqqWindow2.dll`
- `ScaleToINI.exe`
- `uploadFile.dll`

它们都在`VisionQQ_C`目录下，使用 **Visual Studio 2022/2026** 编译。

使用 **Visual Studio 2022/2026** 编译解决方案：
- `Opt.sln`
- `update.sln`

---

## 🛡️ 免责声明

本软件**仅限技术学习与研究用途**，严禁用于：
- 自动骚扰、诈骗、刷屏
- 违反《QQ 软件许可协议》的行为
- 任何违法违规场景

使用者须自行承担因使用本软件引发的一切法律责任，作者概不负责。

---

## 📄 开源协议

本项目采用 [MIT License](LICENSE)。欢迎 Star ⭐、Fork 🍴 与贡献代码！

---

## 🙌 贡献与反馈

- 发现 Bug？→ 提交 [Issue](https://github.com/Na2Cr2O7/Visionqq/issues)  
- 想改进功能？→ 提交 Pull Request  
- 有新语言/模型建议？→ 欢迎讨论！

让我们一起打造更安全、智能的视觉自动化工具！
