#encoding:utf-8
import os


# remove the title and on-alphabetic character of each mail, and make vocabulary

train = "/Users/janechen/Desktop/课程/机器学习/HW3/hw3-nb/train-mails"
target_train = "/Users/janechen/Desktop/课程/机器学习/HW3/hw3-nb/prossesed_train"
train_files = os.listdir(train)
test = "/Users/janechen/Desktop/课程/机器学习/HW3/hw3-nb/test-mails"
target_test = "/Users/janechen/Desktop/课程/机器学习/HW3/hw3-nb/prossesed_test"
test_files = os.listdir(test)
vocabulary = []

for file in train_files:
    f_s = open(train + "/" + file)
    f_t = open(target_train + "/" + file, "a")
    lines = f_s.readlines()
    for line in lines[2:]:
        words = line.split(' ')
        for word in words:
            if word.isalpha():
                if word not in vocabulary:
                    vocabulary.append(word)
                f_t.write(word+' ')

for file in test_files:
    f_s = open(test + "/" + file)
    f_t = open(target_test + "/" + file, "a")
    lines = f_s.readlines()
    for line in lines[2:]:
        words = line.split(' ')
        for word in words:
            if word.isalpha():
                f_t.write(word+' ')

f_v =open('/Users/janechen/Desktop/课程/机器学习/HW3/hw3-nb/vocabulary.txt', "a")
for word in vocabulary:
    f_v.write(word+' ')







