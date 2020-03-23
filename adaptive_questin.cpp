#include "adaptive_questin.h"
#include<iostream>
#include<math.h>
#include <cstdlib>
#include <ctime>

#include "sql.h"

using namespace std;
//输入各类别的分数，返回这次各类别出的题数
std::vector<int> adaptive_questin(int *scores)
{
    int CLASSES = 3;
    int TOTAL_NUM = 15;
    int step = 10;//自己改这个参数以达到最好效果
    std::vector<int> out_nums(3);//[] = {5,5,5};
    int total_this = 0;

    //init out
    for(int i = 0;i < CLASSES;i++){
        out_nums[i] = 5;
    }

    for(int i = 0;i < CLASSES;i++){
        if (scores[i] < 0){
            return out_nums;
        }
    }
    for (int i = 0;i < CLASSES; i++){
        out_nums[i] += int((100 - scores[i])/step);
        total_this += out_nums[i];
    }
    cout << total_this <<endl;

    //按比例归一到总数15
    float radio = float(TOTAL_NUM/float(total_this));
    cout << "radio = "<<radio <<endl;
    total_this = 0;
    for (int i = 0;i < CLASSES; i++){
        out_nums[i] =  int(out_nums[i] * radio);
        total_this += out_nums[i];
    }
    if (total_this < TOTAL_NUM){
        uint8_t dd = TOTAL_NUM - total_this;

        if (out_nums[0] > out_nums[1] && out_nums[0] > out_nums[2]){
            out_nums[0] += dd;
        }
        else if (out_nums[1] > out_nums[0] && out_nums[1] > out_nums[2]){
            out_nums[1] += dd;
        }
        else if (out_nums[2] > out_nums[0] && out_nums[2] > out_nums[1]){
            out_nums[2] += dd;
        }
        else{
            //random
            srand((int)time(0)); // 产生随机种子  把0换成NULL也行
            int index_rand =  rand()%3;
            out_nums[index_rand] += dd;
        }
    }
    else if (total_this > TOTAL_NUM){
        uint8_t dd = total_this -TOTAL_NUM;

        if (out_nums[0] < out_nums[1] && out_nums[0] < out_nums[2]){
            out_nums[0] -= dd;
        }
        else if (out_nums[1] < out_nums[0] && out_nums[1] < out_nums[2]){
            out_nums[1] -= dd;
        }
        else if (out_nums[2] < out_nums[0] && out_nums[2] < out_nums[1]){
            out_nums[2] -= dd;
        }
        else{
            //random
            srand((int)time(0)); // 产生随机种子  把0换成NULL也行
            int index_rand =  rand()%3;
            out_nums[index_rand] -= dd;
        }
    }
    for(int i = 0 ; i < 3; i ++)
        cout << out_nums[i] <<"  in:" << scores[i] <<endl;
    return  out_nums;
}

