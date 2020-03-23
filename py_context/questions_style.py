#coding=utf-8
'''
写来批量导入！
格式见questions.txt文件
'''
import sys
import os
import re
'''
1—5：ADDBD 6—10：BDBCC 10—15：CBCDB 16—20： ABDCC 21-25:DBDCD 26-30:ADDCB 31-35:ABDBD 36-40:CCAAB 41-45:DBADD46-50： DBABB 51—55：CCBAA 56—60 BAAAC 
61-65：DBCDD 66-70：ABADD 71-75：DADBD 76-70：BBBCA 80-85：CDADA 86-90：BDABD 90-95：ADBCC 96-100:CCACA 
'''


def his_stdanswer():
    history_answers = "1—5：ADDBD 6—10：BDBCC 10—15：CBCDB 16—20：ABDCC 21-25:DBDCD 26-30:ADDCB 31-35:ABDBD 36-40:CCAAB \
        41-45:DBADD 46-50：DBABB 51—55：CCBAA 56—60：BAAAC 61-65：DBCDD 66-70：ABADD 71-75：DADBD 76-70：BBBCA 80-85：CDADA 86-90：BDABD 90-95：ADBCC 96-100:CBCCD"

    std_histort_ans = []

    for i in range(len(history_answers)):
        if history_answers[i] == 'A' or history_answers[i] == 'B' or history_answers[i] == 'C' or history_answers[i] == 'D':
            std_histort_ans.append(history_answers[i])

    print (len(std_histort_ans),std_histort_ans)


# std_histort_ans = []

# history_answers = history_answers.split("：")
# for i , h in enumerate(history_answers):
#     h = h.split(" ")
#     print(len(h))
#     if len(h) >= 2:

#         std_histort_ans.append(h[0])
# print (std_histort_ans)

def read_his_question():
    question = []
    result_a = []
    result_b = []
    result_c = []
    result_d = []
    f = open('/home/jiang/Repositories/项目-2020接/答题app/lishi .txt','r')
    # all_lines = f.readlines()
    # for i,line in enumerate(all_lines):
    #     if len(line.split('A.')) > 1:
    #         question.append
    all_context = f.read()
    f.close()


    fw = open('history_my.txt','w')

    SPL_A = all_context.split('A')
    for i,spla in enumerate(SPL_A):
        print (i)
        if i == 0:
            question.append(spla)
            fw.write(spla )
            continue
        splb = spla.split('B')
        a = splb[0]
        splc = splb[1].split('C')
        b = splc[0]
        spld = splc[1].split('D')
        c = spld[0]
        spl_q = spld[1].split(str(i+1))#'、'
        d = spl_q[0]
        q = ""
        for i in range(1,len(spl_q)):
            q += spl_q[i]
        

        question.append(q)
        result_a.append(a)
        result_b.append(b)
        result_c.append(c)
        result_d.append(d)
        
        line_context =  q+"**"+a+"**"+b+"**"+c+"**"+d+"###"+'\n'
        fw.write(line_context)
    
    print(len(result_a),len(result_b),len(result_c),len(result_d),len(question))
    fw.close()


def yuwen_():
    ans = "22321 14414 42212 13431 43413 22442 21423 44121 41144 41332 23344 34423 11222 11431 34142 41242 22224 41443 34232 23324"
    question_and_ans = []
    question = []
    result_a = []
    result_b = []
    result_c = []
    result_d = []
    f = open('/home/jiang/Repositories/项目-2020接/答题app/yuwen.txt','r')
    all_context = f.read()
    f.close()

    question_left = all_context

    fw = open('chinses_my.txt','w')

    test = question_left.split(str(12)+'.')
    print(len(test))

    for i in range(1,101):
        
        the_split0 = question_left.split(str(i)+'.')
        the_split1 = the_split0[0].split(str(i+1)+'.')
        print(i,len(the_split0),len(the_split1))
        question_i = the_split1[0]
        
        question_left = question_left[len(question_i):]#the_split1[1]
        question_and_ans.append(question_i)

        #分解成五部分
        q = question_i.split(str(i) + '.')[0]
        qq = q.split("aa")
        print (':',question_i)
        if len(qq) > 1:
            q = qq[0]
            a = qq[1]
            aa = a.split("bb")
            a = aa[0]
            b = aa[1]
            bb = b.split("cc")
            b = bb[0]
            c = bb[1]
            cc = c.split("dd")
            c = cc[0]
            d = cc[1]

            line_context = q +"**"+a+"**"+b+"**"+c+"**"+d+"###"+'\n'
            fw.write(line_context)
        # question.append(ques_)
        # result_a.append(a_)
        # result_b.append(b_)
        # result_c.append(c_)
        # result_d.append(d_)
    
    print(len(question_and_ans))
    fw.close()

def eng_my():
    ans = "22321 14414 42212 13431 43413 22442 21423 44121 41144 41332 23344 34423 11222 11431 34142 41242 22224 41443 34232 23324"
    question_and_ans = []
    question = []
    result_a = []
    result_b = []
    result_c = []
    result_d = []
    f = open('/home/jiang/Repositories/项目-2020接/答题app/yingyu.txt','r')
    all_context = f.read()
    f.close()

    question_left = all_context

    fw = open('eng_my.txt','w')

    test = question_left.split(str(12)+'.')
    print(len(test))

    for i in range(1,101):
        
        the_split0 = question_left.split(str(i)+'.')
        the_split1 = the_split0[0].split(str(i+1)+'.')
        print(i,len(the_split0),len(the_split1))
        question_i = the_split1[0]
        
        question_left = question_left[len(question_i):]#the_split1[1]
        question_and_ans.append(question_i)

        #分解成五部分
        qq = question_i.split("A.")
        print (':',question_i)
        if len(qq) > 1:
            q = qq[0]
            a = qq[1]
            aa = a.split("B.")
            a = aa[0]
            b = aa[1]
            bb = b.split("C.")
            b = bb[0]
            c = bb[1]
            cc = c.split("D.")
            c = cc[0]
            d = cc[1]

            line_context = q +"**"+a+"**"+b+"**"+c+"**"+d+"###"+'\n'
            fw.write(line_context)
        # question.append(ques_)
        # result_a.append(a_)
        # result_b.append(b_)
        # result_c.append(c_)
        # result_d.append(d_)
    
    print(len(question_and_ans))
    fw.close()

def std_ans_():
    chinese_ans = "22321 14414 42212 13431 43413 22442 21423 44121 41144 41332 23344 34423 11222 11431 34142 41242 22224 41443 \
        34232 23324"
    english_ans = ":1-5 BCDCB 6-10 ADCAC 11-15 DBCCD 16-20 DDCCC 21-25 ACBCB 26-30BBBAC31-35 AADAC 36-40 CDCBA 41-45 DDBBC \
        46-50ADDBB  51-55 CDDDD 56-60 BCACD 61-65 DADDB 66-70 ADCBC 71-75 BDBCD 76-80 ABDAC 81-85 BADBB 86-90 BDABC 91-95 DDABC 96-100 AACBC"
    history_answers = "1—5：ADDBD 6—10：BDBCC 10—15：CBCDB 16—20：ABDCC 21-25:DBDCD 26-30:ADDCB 31-35:ABDBD 36-40:CCAAB \
        41-45:DBADD 46-50：DBABB 51—55：CCBAA 56—60：BAAAC 61-65：DBCDD 66-70：ABADD 71-75：DADBD 76-70：BBBCA 80-85：CDADA 86-90：BDABD 90-95：ADBCC 96-100:CBCCD"


    std_histort_ans = []

    for i in range(len(chinese_ans)):
        if chinese_ans[i] == '1':
            std_histort_ans.append('A')
        elif chinese_ans[i] == '2':
            std_histort_ans.append('B')
        elif chinese_ans[i] == '3':
            std_histort_ans.append('C')
        elif chinese_ans[i] == '4':
            std_histort_ans.append('D')
    print (len(std_histort_ans))

    for i in range(len(english_ans)):
        if english_ans[i] == 'A' or english_ans[i] == 'B' or english_ans[i] == 'C' or english_ans[i] == 'D':
            std_histort_ans.append(english_ans[i])
    print (len(std_histort_ans))
    for i in range(len(history_answers)):
        if history_answers[i] == 'A' or history_answers[i] == 'B' or history_answers[i] == 'C' or history_answers[i] == 'D':
            std_histort_ans.append(history_answers[i])
    print (len(std_histort_ans))
    return std_histort_ans

def write_std_ques():
    f = open("ques.txt","r")
    context = f.read()
    f.close()

    std_ans = std_ans_()
    f = open("std_ques_ans.txt","w")
    list_ques = context.split("###")
    print("ques:",len(list_ques))
    for i,ques in  enumerate(list_ques):
        if i != 0:
            ques = "###" + std_ans[i-1] + "**" + ques +"\n"
        f.write(ques)
    f.close()

#eng_my()

#std_ans_()    
#read_his_question()
write_std_ques()
