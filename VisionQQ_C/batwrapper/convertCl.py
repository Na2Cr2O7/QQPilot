import sys
import os
import subprocess

def escape_c_string(s):
    return s.replace('\\', '\\\\').replace('"', '\\"')

if len(sys.argv) == 1:
    print(f"用法: {sys.argv[0]} [cmd文件1] [cmd文件2] ...")
    sys.exit(1)

with open('basic.c', 'r', encoding='utf8') as f:
    basic = f.read()

marker = '//REPLACE_START'
l = basic.find(marker)


basic_left = basic[:l]
basic_right = basic[l + len(marker):]

exe_ext = '.exe' if os.name == 'nt' else ''

for arg in sys.argv[1:]:
    with open(arg, 'r', encoding='utf8') as f:
        lines = [line.rstrip('\n\r') for line in f if line.strip()]

    code = basic_left
    for line in lines:
        escaped = escape_c_string(line)
        code += f'\tsystem("{escaped}");\n'
    code += basic_right

    base_name = os.path.splitext(os.path.basename(arg))[0]
    c_file = base_name + '.c'
    exe_file = base_name + exe_ext

    with open(c_file, 'w', encoding='utf8') as f:
        f.write(code)

    # 尝试编译
    try:
        subprocess.run(['gcc', c_file, '-o', exe_file], check=True)
    except FileNotFoundError:
        print("gcc 未找到，尝试使用 tcc...")
        try:
            subprocess.run(['tcc/tcc.exe', c_file, '-o', exe_file], check=True)
        except (FileNotFoundError, subprocess.CalledProcessError):
            print("错误：gcc 和 tcc 均不可用或编译失败。")
            sys.exit(1)
    except subprocess.CalledProcessError:
        print(f"编译 {c_file} 失败。")
        sys.exit(1)

    print(f"已生成: {exe_file}")