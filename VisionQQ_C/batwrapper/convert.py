#########################
# 批量编译cmd文件
# 建议安装gcc 编译
import sys
import os
import subprocess

argv=sys.argv
if len(argv)==1:
    print(f"用法 : {argv[0]} [cmd文件]")
    raise SystemExit
with open('basic.c','r',encoding='utf8') as f:
    basic=f.read()
l=basic.find('//REPLACE_START')




for arg in argv[1:]:
    basic_L=basic[:l]
    basic_R=basic[l+len('//REPLACE_START'):]
    with open(arg,'r',encoding='utf8') as f:
        cmd=f.read().split('\n')
    for line in cmd:
        basic_L+=f'\tsystem("{line.replace('\\','\\\\')}");\n'
    _,fn=os.path.split(arg)
    with open(os.path.splitext(fn)[0]+'.c','w',encoding='utf8') as f:
        f.write(basic_L+basic_R)
    try:
        subprocess.run(['gcc',os.path.splitext(fn)[0]+'.c','-o',os.path.splitext(fn)[0]+'.exe'])
    except:
        print('gcc未找到，使用tcc')
        subprocess.run(['tcc/tcc.exe',os.path.splitext(fn)[0]+'.c','-o',os.path.splitext(fn)[0]+'.exe'])
    
