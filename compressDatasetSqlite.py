# ini_to_sqlite.py
import sqlite3
import sys
import os
import json
import configparser
config = configparser.ConfigParser()
# config.read('datasetINI.ini','w')
config.add_section('g')
with open('datasetTiny.json','r',encoding='utf8') as f:
    data=json.load(f)
for key,value in data.items():
    try:

        config.set('g',key,value)
    except Exception as e:
        print(e)
with open('datasetINI.ini','w',encoding='utf8') as f:
    config.write(f)

def parse_ini_simple(ini_path):
    """
    极简 INI 解析器：只处理 [g] 下的 key = value 行
    - 忽略空行、注释（以 # 或 ; 开头）
    - 遇到 [xxx] 且不是 [g] 则停止（假设 [g] 是唯一 section）
    """
    in_g_section = False
    kv_pairs = []

    with open(ini_path, 'r', encoding='utf-8') as f:
        for line in f:
            line = line.strip()
            if not line or line.startswith(('#', ';')):
                continue

            if line == '[g]':
                in_g_section = True
                continue
            elif line.startswith('[') and line.endswith(']'):
                # 遇到其他 section，提前结束（因你只有 [g]）
                break

            if in_g_section:
                if ' = ' in line:
                    key, value = line.split(' = ', 1)
                    kv_pairs.append((key, value))
                # 可选：跳过格式错误的行（或报错）
    return kv_pairs


def convert(ini_path, db_path):
    print(f"正在解析: {ini_path}")
    pairs = parse_ini_simple(ini_path)
    print(f"共读取 {len(pairs)} 条问答对")

    print(f"正在写入 SQLite: {db_path}")
    conn = sqlite3.connect(db_path)
    cur = conn.cursor()
    cur.execute('''
        CREATE TABLE g (
            question TEXT PRIMARY KEY,
            answer TEXT NOT NULL
        )
    ''')
    cur.executemany('INSERT INTO g (question, answer) VALUES (?, ?)', pairs)
    conn.commit()
    conn.close()

    ini_size = os.path.getsize(ini_path)
    db_size = os.path.getsize(db_path)
    print(f"✅ 完成！体积从 {ini_size / 1024 / 1024:.1f} MB → {db_size / 1024 / 1024:.1f} MB")


def query_example(db_path, question):
    """示例：如何查询"""
    conn = sqlite3.connect(db_path)
    cur = conn.cursor()
    cur.execute("SELECT answer FROM g WHERE question = ?", (question,))
    row = cur.fetchone()
    conn.close()
    return row[0] if row else None


if __name__ == '__main__':

    ini_file = 'datasetINI.ini'
    db_file = 'dataset.db'
    convert(ini_file, db_file)

    # 可选：测试查询
    # ans = query_example(db_file, "你好，最近怎么样？")
    # print("测试查询结果:", ans)