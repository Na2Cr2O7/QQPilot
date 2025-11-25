import threading
from time import sleep,time

loading=False
startTime=0
def load(color,text):
    l=['|','/','-','\\']
    while loading:
        for i in l:
            print(color+i+'\t'+text,end='\r')
            sleep(0.1)
        
def startLoading(color,text):
    global loading,startTime
    startTime=time()

    loading=True
    t=threading.Thread(target=load,args=(color,text))
    t.start()

def stopLoading():
    global loading,startTime
    loading=False
    print(f'\n用时:{time()-startTime:.2f}s')
    print('\n')
    