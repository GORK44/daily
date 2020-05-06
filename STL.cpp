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
#include <map>
#include <unordered_map>

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

    
    //Map
    //================================================
    //创建
    std::map<std::string, size_t> people;//size_t 类型的值表示年龄，作为它保存的值，string 类型的值表示名称，作为它的键
    std::map<std::string, size_t> people1{{"Ann", 25}, {"Bill", 46},{"Jack", 32},{"Jill", 32}};
    
    std::map<std::string, size_t> people2{std::make_pair("Ann",25),std::make_pair("Bill", 46),std::make_pair("Jack", 32),std::make_pair("Jill", 32)};
    
    std::map<std::string, size_t> personnel {people}; // 复制 Duplicate people map
    std::cout<<people1["Jack"]<<std::endl;
    
    //插入 Create a pair element and insert it
    auto pr = std::make_pair("Fred",22); //pr 对象的类型是 pair<const char*,int>。在 insert() 操作中，这个对象会被隐式转换为容器元素类型。
    people1.insert(pr); //插入
    std::cout<<people1["Fred"]<<std::endl;
    
    //输出map元素。键值自动排序
    std::map<std::string, size_t>::iterator iterMap;
    iterMap = people1.begin();
//    iterMap->second = 22;//修改第一个键值对的值
//    people1["Bill"] = 43;//修改键值“Bill”对应的值
//    people1.erase("Jack"); //移除键和参数匹配的元素
//    people1.clear(); //清空
    while(iterMap != people1.end()) {
        std::cout << iterMap->first << " : " << iterMap->second << std::endl;
        //输出：Ann : 25， Bill : 46， Fred : 22， Jack : 32， Jill : 32
        iterMap++;
    }
    
    //pair：
    //make_pair<T1，T2> 函数模板是一个辅助函数，可以生成并返回一个 pair<T1，T2> 对象。 可以如下所示生成先前代码块中的 pair 对象：
    std::string s1{"test"};
    std::string s2{"that"};
    auto my_pair = std::make_pair(s1, s2);
    auto your_pair = std::make_pair(std::string {"test"},std::string {"that"});
    auto his_pair = std::make_pair<std::string, std::string>("test",std::string {"that"});
    auto her_pair = std::make_pair<std::string, std::string>("test", "that");
    
    //================================================

    
    //unordered_map
    //================================================
    std::unordered_map<std::string, size_t> people3;
    std::unordered_map<std::string, size_t> people4 { {"Jim", 33}, { "Joe", 99}};// Name,age
    std::cout<<people4.bucket_count()<<std::endl;//bucket_count() 个数
    //插入
    auto pr1 = people4.insert (std::pair<std::string, size_t> {"Jan", 44});
    std:: cout << "Element " << (pr1.second ? "was" : "was not") << " inserted." << std::endl;
    
    //获取元素
    people4["Jim"] = 22; //Set Jim's age to 22;
    people4["Jan"] = people4["Jim"]; //Set May's age to Jim's
    ++people4 ["Joe"] ; //Increment Joe's age
    people4 ["Kit"] = people4 ["Joe"]; // 如果容器中不存在”Kit”，上面最后一条语句会生成一个以“kit”为键、年龄值为 0 的元素；最后"Joe”所关联的对象会被复制到"Kit"。
    for(const auto& person4 : people4)//循环取出people4中元素。当你只想要读取range里面的元素时，使用const auto&
        std::cout << person4.first << " is "<< person4.second <<std::endl;

    //删除元素
    auto n4 = people4.erase ("Jim");// 当参数是键时，erase() 会返回一个整数，它是移除元素的个数，所以 0 表示没有找到匹配的元素。
    auto iter4 = people4.find ("May") ; // 如果不存在，返回end()指针
    if(iter4 != people4.end())
        iter4 = people4.erase (iter4) ;// 参数是迭代器时，返回的迭代器指向被移除元素后的元素。
    
    //================================================
}
