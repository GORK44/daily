//最小栈
//设计一个支持 push ，pop ，top 操作，并能在常数时间内检索到最小元素的栈。
//
//push(x) —— 将元素 x 推入栈中。
//pop() —— 删除栈顶的元素。
//top() —— 获取栈顶元素。
//getMin() —— 检索栈中的最小元素。
//示例:
//
//MinStack minStack = new MinStack();
//minStack.push(-2);
//minStack.push(0);
//minStack.push(-3);
//minStack.getMin();   --> 返回 -3.
//minStack.pop();
//minStack.top();      --> 返回 0.
//minStack.getMin();   --> 返回 -2.

#include <iostream>
#include <vector>
#include<unordered_map>
#include<stack>
#include<queue>
using namespace std;



class MinStack {
public:
    stack<int> s;//数据栈
    stack<int> min;//辅助栈（栈顶元素最小）
    /** initialize your data structure here. */
    MinStack() {
        
    }
    
    void push(int x) {
        s.push(x);  //压s栈
        if(min.empty()||x<=min.top())   //如果x小于min栈顶
            min.push(x);                //压x入min栈
    }
    
    void pop() {
        if(s.top()==min.top())  //如果两栈栈顶元素相等（最小）
            min.pop();          //删min栈顶
        s.pop();    //删s栈顶元素
    }
    
    int top() {
        return s.top();
    }
    int getMin() {
        return min.top();   //min栈顶元素为最小
    }
};
