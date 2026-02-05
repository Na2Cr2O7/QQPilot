import json
import os 
if not os.path.exists('datasetTiny.json'):
    import prepareData
    
# with open('tokenizer.json','r',encoding='utf8') as f:
#     char_to_idx = json.load(f)
with open('datasetTiny.json','r',encoding='utf8') as f:
    pair = json.load(f)
questions=list(pair.keys())
answers=list(pair.values())
def jaccard_similarity(s1, s2):

    """计算两个字符串的Jaccard相似度"""
    # 将字符串转换为集合
    set1 = set(s1)
    set2 = set(s2)
    
    # 计算交集和并集
    intersection = len(set1.intersection(set2))
    union = len(set1.union(set2))
    
    # 计算Jaccard相似度
    jaccard_sim = intersection / union
    return jaccard_sim


def answer(question):
    max_similarity = -1
    best_match = None
    for i in questions:
        similarity = jaccard_similarity(question, i)

        if similarity > max_similarity:
            max_similarity = similarity
            best_match = i
    print(pair[best_match])
    return pair[best_match]
if __name__ == '__main__':
    print('TinyLangJaccard 测试')
    print('数据集:https://www.modelscope.cn/datasets/Moemuu/Muice-Dataset/files')
    while True:
        answer(input('请输入问题: '))
    # print(answer("啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊"))