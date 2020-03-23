#coding=utf-8
import sys
import os
import numpy as np 
'''
功能：生成模拟题库 questions.txt
格式：类别 问题 选项A 选项B 选项C 选项D 答案
如：
2 问题 A.qwer B.萨达大多 C.对的 D.WODS 1
'''
char_ = []
for j in range(65,91):
    str_a = str(chr(j))
    char_.append(str_a)
for j in range(97,123):
    str_a = str(chr(j))
    char_.append(str_a)
for j in range(10):
    str_a = str(j)
    char_.append(str_a)

index = np.random.randint(0,255,size=1)

def get_random_str(lenthmax):
    question = ""
    qlenth = np.random.randint(1,lenthmax,size=1)[0]
    while qlenth:
        index = np.random.randint(0,len(char_),size=1)[0]
        question +=  char_[index]
        qlenth -= 1
    return question

f = open("questions.txt","a")

for i in range(300):#三百道题
    str_write = ''

    question = get_random_str(30)
    a_ = '.'+ get_random_str(10)
    b_ = '.'+ get_random_str(10)
    c_ = '.'+ get_random_str(10)
    d_ = '.'+ get_random_str(10)
    r_ = np.random.randint(1,5,size=1)[0]

    if i <100:
        str_write = str(1)+' '+question+' '+a_ +' '+b_+' '+c_ +' '+d_ +' '+str(r_)+'\n'
    elif  100<= i<200:
        str_write = str(2)+' '+question+' '+a_ +' '+b_+' '+c_ +' '+d_ +' '+str(r_)+'\n'
    else:
        str_write = str(3)+' '+question+' '+a_ +' '+b_+' '+c_ +' '+d_ +' '+str(r_)+'\n'
    
    f.write(str_write)
f.close()



    