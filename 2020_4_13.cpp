//
//  main.cpp
//  test
//
//  Created by apple on 2020/4/3.
//  Copyright © 2020 apple. All rights reserved.


//#include <iostream>
//
//int main(int argc, const char * argv[]) {
//    // insert code here...
//    std::cout << "Hello, World!\n";
//    return 0;
//}


//1. 两数之和
//给定一个整数数组 nums 和一个目标值 target，请你在该数组中找出和为目标值的那 两个 整数，并返回他们的数组下标。
//
//你可以假设每种输入只会对应一个答案。但是，你不能重复利用这个数组中同样的元素。
//
//示例:
//
//给定 nums = [2, 7, 11, 15], target = 9
//
//因为 nums[0] + nums[1] = 2 + 7 = 9
//所以返回 [0, 1]

#include <iostream>
#include <vector>
#include<unordered_map>
using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        
        unordered_map<int,int> m;
        
        for(int i=0;i<nums.size();i++)
            m[nums[i]] = i;         //向map中添加元素
        
        for(int i=0;i<nums.size();i++)
        {
            if(m.find(target-nums[i]) != m.end() && m[target-nums[i]] != i)     //如果m中存在对应的键值，并且不为i
                return {i , m[target-nums[i]]};
        }
        return {};
    }
};
