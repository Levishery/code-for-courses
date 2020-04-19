import os
import json
import numpy


test = "hw3-nb/prossesed_test"
test_files = os.listdir(test)
vocabulary_path = "hw3-nb/vocabulary.txt"
train_result_path = "hw3-nb/train_result.json"

# load result
with open(train_result_path, 'r') as load_f:
    result_dict = json.load(load_f)
P_spam = result_dict['P_spam']
P_legal = 1-P_spam
P_w_spam = result_dict['P_word_spam']
P_w_legal = result_dict['P_word_legal']

# load vocabulary
vocabulary = []
v = 0
f_v = open(vocabulary_path, "r")
for word in f_v.readline().split(' '):
    vocabulary.append(word)
    v = v+1

tp = 0
fn = 0
fp = 0
tn = 0
for file in test_files:
    I = []
    index = -1
    P_p_spam = numpy.float128(P_spam)
    P_p_legal = numpy.float128(P_legal)
    f_s = open(test + "/" + file)
    content = f_s.readline().split(' ')
    for word in content:
        try:
            index = vocabulary.index(word)
        except ValueError:
            index = -1
        if index != -1 and index not in I:
            I.append(index)
    for word in I:
        P_p_spam = P_p_spam * P_w_spam[word]
        P_p_legal = P_p_legal * P_w_legal[word]
    if P_p_legal < P_p_spam:    # predict to be spam
        if 'spm' in file:
            tp = tp+1
        else:
            fp = fp+1
    else:
        if 'spm' in file:
            fn = fn+1
        else:
            tn = tn+1

print('tp:', tp, 'fp:', fp, 'fn', fn, 'tn', tn)











