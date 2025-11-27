import json
import os 
if not os.path.exists('tokenizer.json'):
    import prepareData
    
with open('tokenizer.json','r',encoding='utf8') as f:
    char_to_idx = json.load(f)
with open('datasetTiny.jsonl','r',encoding='utf8') as f:
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
def tokenize(text):
    """将文本转换为词ID"""
    return [char_to_idx[c] for c in text if c in char_to_idx]
def pad_tokens(token, seq_len=64):
    """填充序列，使其长度为seq_len"""
    if len(token) < seq_len:
        token = token + [0] * (seq_len - len(token))
    else:
        token = token[-seq_len:]
    return token
def pad_sequence(text, seq_len=64):
    """填充序列，使其长度为seq_len"""
    if len(text) < seq_len:
        text = text + ' ' * (seq_len - len(text))
    else:
        text = text[-seq_len:]
    return text

def answer(question):
    tokenized_question = pad_tokens(tokenize(pad_sequence(question)))
    max_similarity = -1
    best_match = None
    for i in questions:
        tokenized_i = tokenize(pad_sequence(i))
        similarity = jaccard_similarity(tokenized_question, tokenized_i)

        if similarity > max_similarity:
            max_similarity = similarity
            best_match = i
    print(pair[best_match])
    return pair[best_match]
if __name__ == '__main__':
    print('TinyLangJaccard 测试')
    print('数据集:https://www.modelscope.cn/datasets/Moemuu/Muice-Dataset/files')
    while True:
        print(answer(input('请输入问题: ')))
    # print(answer("啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊"))