//
//  main.cpp
//  test1
//
//  Created by apple on 2020/4/26.
//  Copyright © 2020 apple. All rights reserved.
//

#include <iostream>
#include "math.h"
//using namespace std;

#include <vector>

int main(int argc, const char * argv[]) {
    //数组
    //================================================
    int n[10]; // n 是一个包含 10 个整数的数组
    
    // 初始化数组元素
    for ( int i = 0; i < 10; i++ )
    {
        n[i] = i + 100; // 设置元素 i 为 i + 100
    }
    
    double balance[5] = {1000.0, 2.0, 3.4, 7.0, 50.0};
    double balance1[] = {1000.0, 2.0, 3.4, 7.0, 50.0};
    //================================================

    
    //Vector
    //================================================

//    std::vector<double> values;
    std::vector<double> values(4);//这个容器开始时有 4 个元素，它们的默认初始值都为 0。
    values[0] = 3.14159;
    values[1] = 5.0;
    values[2] = 2.0*values[0]*values[1];
    
    //添加
    values.push_back(555);//在序列的末尾添加一个元素
    
    for (int i = 0; i < values.size(); i++) {
        std::cout<<values[i]<<std::endl;
    }
    //———————————————
    
    //插入：emplace，insert
    std::vector<std::string> words {"first", "second"};
    
    auto iter = words.emplace(++std::begin(words),5,'A');//插入AAAAA到第二个元素的位置
    words.emplace(++iter, "$$$$");//插入$$$到第三个元素的位置
    
    words.insert(std::end(words), "words end");//在 vector 的末尾插入一个元素
    
    for (int i = 0; i < words.size(); i++) {
        std::cout<<words[i]<<std::endl;
    }
    //———————————————
    
    
    
    //================================================

}
