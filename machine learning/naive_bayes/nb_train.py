import os
import numpy as np
import json


train = "hw3-nb/prossesed_train"
train_files = os.listdir(train)
vocabulary_path = "hw3-nb/vocabulary.txt"
# concat all the spam words to this txt
spam_path = "hw3-nb/spam.txt"
f_spam = open(spam_path, "a")
# concat all legal words to this txt
legal_path = "hw3-nb/legal.txt"
f_legal = open(legal_path, "a")
f_v = open(vocabulary_path)
vocabulary = []
v = 0  # length of vocabulary
spam_count = 0
legal_count = 0
spam_words = 0
legal_words = 0

for word in f_v.readline().split(' '):
    vocabulary.append(word)
    v = v+1

for file in train_files:
    f_s = open(train + "/" + file)
    if "spm" in file:
        spam_count = spam_count + 1
        for word in f_s.readline().split(' '):
            spam_words = spam_words + 1
            f_spam.write(word + ' ')
        f_spam.write('\n')
    else:
        legal_count = legal_count + 1
        for word in f_s.readline().split(' '):
            legal_words = legal_words + 1
            f_legal.write(word + ' ')
        f_legal.write('\n')

P_spam = float(spam_count) / float(spam_count + legal_count)
P_legal = 1 - P_spam

P_w_spam = np.zeros(v)
P_w_legal = np.zeros(v)
count = 0
f_spam = open(spam_path, "r")
f_legal = open(legal_path, "r")
lines_spam = f_spam.readlines()
lines_legal = f_legal.readlines()
for word in vocabulary:
    word_count = 0
    for line in lines_spam:
        for item in line.split(' '):   # compute P_w_spam
            if item == word:
                word_count = word_count + 1
    P_w_spam[count]=float(word_count+1)/float(spam_words+v)

    word_count=0
    for line in lines_legal:
        for item in line.split(' '):  # compute P_w_legal
            if item == word:
                word_count = word_count + 1
    P_w_legal[count] = float(word_count + 1) / float(legal_words + v)

    count = count+1
    if count % 1000 == 0:
        print(float(count)/float(v))

st_path = "hw3-nb/train_result.json"
P_w_legal = P_w_legal.tolist()
P_w_spam = P_w_spam.tolist()
result_dic = {'P_spam': P_spam, 'P_legal': P_legal, 'P_word_spam': P_w_spam, 'P_word_legal': P_w_legal}
with open(st_path, "w") as dump_f:
    json.dump(result_dic, dump_f)