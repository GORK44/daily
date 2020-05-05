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

#include <string>
#include <vector>
#include <list>

int main(int argc, const char * argv[]) {
    
    //字符串
    //================================================
    std::string stuff;
//    std::cin >> stuff;
//    getline(std::cin, stuff);
    //上述三行代码，第一行是声明 string 类的对象 stuff，第二行是从屏幕读入输入的字符串，第三行同样实现第二行代码的功能。
    
    std::string a; //定义一个空字符串
    
    std::string str ("12345678");//构造
    std::string str_1 (str); //构造函数，全部复制
    std::string str_2 (str, 2, 5); //构造函数，从字符串str的第2个元素(3)开始，复制5个元素，赋值给str_2
    std::cout << str_2 << std::endl;//输出“34567”
    std::string str_4 (5,'X'); //将 5 个 'X' 组成的字符串 "XXXXX" 赋值给 str_4
    std::string str_5 (str.begin(), str.end()); //复制字符串 str 的所有元素，并赋值给 str_5
    
    char ch[] = "abcdefgh";
    std::string str_3 (ch, 5); //将字符串ch的前5个元素赋值给str_3
    
    //长度
    unsigned long size = str.size(); //8
    unsigned long length = str.length();  //8
//    int length = str.length();  //8
    std::cout<<size<<" "<<length<<std::endl;
    
    
    //访问元素
    str[3] = '6'; //改元素
    std::cout<<str<<std::endl; //12365678
    
    
    //find查找元素下标
    std::string::size_type m = str.find ('7', 0);//find()函数的第1个参数是被搜索的字符、第2个参数是在源串中开始搜索的下标位置
    std::cout<<(int)m<<std::endl; //输出6（下标）str[6] = '7'
    //================================================
    
    
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

    //插入：emplace()，insert()
    std::vector<std::string> words {"first", "second"};

    auto iter = words.emplace(++std::begin(words),5,'A');//插入AAAAA到第二个元素的位置
    words.emplace(++iter, "$$$$");//插入$$$到第三个元素的位置

    words.insert(std::end(words), "words end");//在 vector 的末尾插入一个元素

    for (int i = 0; i < words.size(); i++) {
        std::cout<<words[i]<<std::endl;
    }
    //———————————————
    
    
    //删除元素：clear()，pop_back()
    std::vector<int> data(100, 99); //大小和容量都是 100；所有元素的初始值都是 99。
    data.clear(); //删除所有的元素
    data.pop_back(); //删除最后一个元素，因此 data 的大小变为 99，容量还是 100

    data.shrink_to_fit();//去掉容器中多余的容量，不再向容器中添加新元素
    
    //================================================
    
    
    //List
    //================================================
    std::list<std::string> words1;
    std::list<std::string> sayings {20}; // A list of 20 empty strings
    std::list<double> values1(50, 3.14159265);//生成了一个具有 50 个 double 型值的列表，并且每一个值都等于 π
    std::list<double> save_values {values1}; // 拷贝构造函数，可以生成一个现有 list 容器的副本

    //添加元素
    std::list<std::string> names { "Jane", "Jim", "Jules", "Janet"};
    names.push_front("Ian"); // 在它的头部添加一个元素"Ian"
    names.push_back("Kitty"); // 在 list 容器的末尾添加一个元素"Kitty"
    
    //插入元素
    std::list<int> data1(10, 55); // 10个55
    data1.insert(++begin(data1), 66); // 插入66到第二个位置。data1: 55 66 55 55 55 55 55 55 55 55 55（11个元素）
    
    auto iter1 = begin(data1); //iter 是 list<int>::iterator 类型（迭代器，是确使用户可在容器对象上遍访的对象）
    std::advance(iter1, 9); // iter + 9 ，为了得到第10个元素
    data1.insert(iter1, 3, 88);// 从第10个元素处开始插入3个88，得到55 66 55 55 55 55 55 55 55 88 88 88 55 55
                                                    //元素位置：1  2  3  4  5  6  7  8  9  10 11 12 13 14
    
    //删除元素
    std::list<int> numbers { 2, 5, 2, 3, 6, 7, 8, 2, 9};
    numbers.remove(2); // List is now 5 3 6 7 8 9（移除了 numbers 中出现的所有值等于 2 的元素。）
//    numbers.clear(); //清空
    numbers.remove_if([](int n){return n%2 == 0;});//断言返回 true 的所有元素都会被移除。（结果：5 3 7 9）
    
    std::list<std::string> words2 { "one", "two", "two", "two","three", "four", "four"};
    words2.unique () ; // Now contains "one" "two" "three" "four"
    //unique ()移除连续的重复元素，只留下其中的第一个。
    
    
    
    //================================================
    
    
    

}
