import threading
from time import sleep
loading=False
def load(color,text):
    l=['|','/','-','\\']
    while loading:
        for i in l:
            print(color+i+'\t'+text,end='\r')
            sleep(0.1)
        
def startLoading(color,text):
    global loading
    loading=True
    t=threading.Thread(target=load,args=(color,text))
    t.start()

def stopLoading():
    global loading
    loading=False
    print('\n')
    