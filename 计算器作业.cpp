#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <algorithm>
#include <cstring>
#include <stack>
#define MAXN 1010
using namespace std;

class Function_Calculator 
{
public:
	Function_Calculator() {
		while (!nums.empty())nums.pop();
		while (!ops.empty())ops.pop();
		str = new char[MAXN];
	}
	int Judge_Priority(char ch){
		if (ch == '(')return 1;
		else if (ch == '+' || ch == '-')return 2;
		else if (ch == '*' || ch == '/')return 3;
		else if (ch == ')')return 4;
		else throw("操作失败，运算符出现error!!");
	}
	int Math_Cal(int a, int b, char c) {
		switch (c) {
		case '+':
			return a + b;
		case '-':
			return a - b;
		case '*':
			return a * b;
		case '/':
			if (b == 0)throw("操作失败，除数不能为0 ! ! !");
			else return a / b;
		}
	}
	//输入操作字符串并计算
	void Input_string()
	{
		//字符数组s用于存放大于10的数字
		char ch,s[100] = {0};
		int index = 0;
		//用于存放操作数和结果
		int tempa, tempb,sum;
		int t = 0;
		//输入计算式子
		while ((ch = getchar()) != '\n')str[index++] = ch;
		//结束符号：
		str[index] = '@';
		for ( index = 0; str[index] != '@'; index++) {
			//首先判断初始是否为负号--->处理开头就是负数导致的情况
			if (index == 0 && str[index] == '-')s[t++] = str[index++];
			//判断括号中第一个数字是否为负数
			else if(str[index]=='('&&str[index+1]=='-') {
				index++;
				s[t++] = str[index++];
				while (str[index] >= '0' && str[index] <= '9') {
					s[t++] = str[index++];
				}
				//atoi函数用于将字符串转换为数值
				this->nums.push(atoi(s));
				while (t > 0) {
					s[t--] = 0;
				}
				if (str[index] != ')')this->ops.push('(');
			}
			else if (str[index] >= '0' && str[index] <= '9') {
				while (str[index] >= '0' && str[index] <= '9')s[t++] = str[index++];
				this->nums.push(atoi(s));
				while (t > 0) {
					s[t--] = 0;
				}
				index--;
			}
			else {
				if (ops.empty())this->ops.push(str[index]);
				else if (Judge_Priority(str[index]) == 1)this->ops.push(str[index]);
				else if (Judge_Priority(str[index]) == 2) {
					if (Judge_Priority(ops.top()) == 1)ops.push(str[index]);
					else if (Judge_Priority(ops.top()) >= 2) {
						while (!ops.empty() && nums.size() >= 2) {
							tempa = nums.top(); nums.pop();
							tempb = nums.top(); nums.pop();
							sum = Math_Cal(tempb, tempa, ops.top());
							ops.pop();
							nums.push(sum);
						}
						ops.push(str[index]);
					}
				}
				else if (Judge_Priority(str[index]) == 3) {
					if (Judge_Priority(ops.top())<3)ops.push(str[index]);
					else {
						while (ops.size() != 0 && nums.size() >= 2)
						{
							tempa = nums.top(); nums.pop();
							tempb = nums.top(); nums.pop();
							sum = Math_Cal(tempb, tempa, ops.top());
							ops.pop();
							nums.push(sum);
						}
						ops.push(str[index]);
					}
				}
				else
				{
					do { //循环出栈直到遇到'('
						tempa = nums.top(); nums.pop();
						tempb = nums.top(); nums.pop();
						sum = Math_Cal(tempb, tempa, ops.top());
						ops.pop();
						nums.push(sum);
					} while (ops.top() != '(');
					ops.pop();
				}
			}
		}
		while (!ops.empty())
		{
			tempa = nums.top(); nums.pop();
			tempb = nums.top(); nums.pop();
			sum = Math_Cal(tempb, tempa, ops.top());
			ops.pop();
			nums.push(sum);
		}
		cout << "计算结果为：" << nums.top() << endl;
		//清空内存，初始化
		while (!nums.empty())nums.pop();
		while (!ops.empty())ops.pop();
		str = new char[MAXN];
		while (t > 0) {
			s[t--] = 0;
		}
	}
protected:
	//如下属性用于存放操作数以及运算符
	char* str;
	stack<int>nums;
	stack<char>ops;
};

signed main()
{
	Function_Calculator cal;
	while (true)
	{
		cal.Input_string();
	}
}











/*
#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <algorithm>
#include <cstring>
#include <stack>
#define MAXN 1010
using namespace std;

class Function_Calculator
{
public:
	Function_Calculator() {
		while (!nums.empty())nums.pop();
		while (!ops.empty())ops.pop();
		str = new char[MAXN];
	}
	int Judge_Priority(char ch){
		if (ch == '(')return 1;
		else if (ch == '+' || ch == '-')return 2;
		else if (ch == '*' || ch == '/')return 3;
		else if (ch == ')')return 4;
		else throw("操作失败，运算符出现error!!");
	}
	int Math_Cal(int a, int b, char c) {
		switch (c) {
		case '+':
			return a + b;
		case '-':
			return a - b;
		case '*':
			return a * b;
		case '/':
			if (b == 0)throw("操作失败，除数不能为0 ! ! !");
			else return a / b;
		}
	}
	void Input_string()
	{
		//字符数组s用于存放大于10的数字
		char ch,s[100] = {0};
		int index = 0;
		int tempa, tempb,sum;
		int t = 0;
		while ((ch = getchar()) != '\n')str[index++] = ch;
		str[index] = '@';
		for ( index = 0; str[index] != '@'; index++) {
			//首先判断初始是否为负号--->处理开头就是负数导致的情况
			if (index == 0 && str[index] == '-')s[t++] = str[index++];
			else if(str[index]=='('&&str[index+1]=='-') {
				index++;
				s[t++] = str[index++];
				while (str[index] >= '0' && str[index] <= '9') {
					s[t++] = str[index++];
				}
				this->nums.push(atoi(s));
				while (t > 0) {
					s[t--] = 0;
				}
				if (str[index] != ')')this->ops.push('(');
			}
			else if (str[index] >= '0' && str[index] <= '9') {
				while (str[index] >= '0' && str[index] <= '9')s[t++] = str[index++];
				this->nums.push(atoi(s));
				while (t > 0) {
					s[t--] = 0;
				}
				index--;
			}
			else {
				if (ops.empty())this->ops.push(str[index]);
				else if (Judge_Priority(str[index]) == 1)this->ops.push(str[index]);
				else if (Judge_Priority(str[index]) == 2) {
					if (Judge_Priority(ops.top()) == 1)ops.push(str[index]);
					else if (Judge_Priority(ops.top()) == 2) {
						while (!ops.empty() && nums.size() >= 2) {
							tempa = nums.top(); nums.pop();
							tempb = nums.top(); nums.pop();
							sum = Math_Cal(tempb, tempa, ops.top());
							ops.pop();
							nums.push(sum);
						}
						ops.push(str[index]);
					}
					else if (Judge_Priority(ops.top()) == 3)
					{
						while (ops.size() != 0 && nums.size() >= 2)
						{
							tempa = nums.top(); nums.pop();
							tempb = nums.top(); nums.pop();
							sum = Math_Cal(tempb, tempa, ops.top());
							ops.pop();
							nums.push(sum);
						}
						ops.push(str[index]);
					}
				}
				else if (Judge_Priority(str[index]) == 3) {
					if (Judge_Priority(ops.top())<3)ops.push(str[index]);
					else {
						while (ops.size() != 0 && nums.size() >= 2)
						{
							tempa = nums.top(); nums.pop();
							tempb = nums.top(); nums.pop();
							sum = Math_Cal(tempb, tempa, ops.top());
							ops.pop();
							nums.push(sum);
						}
						ops.push(str[index]);
					}
				}
				else
				{
					do { //循环出栈直到遇到'('
						tempa = nums.top(); nums.pop();
						tempb = nums.top(); nums.pop();
						sum = Math_Cal(tempb, tempa, ops.top());
						ops.pop();
						nums.push(sum);
					} while (ops.top() != '(');
					ops.pop();
				}
			}
		}
		while (!ops.empty())
		{
			tempa = nums.top(); nums.pop();
			tempb = nums.top(); nums.pop();
			sum = Math_Cal(tempb, tempa, ops.top());
			ops.pop();
			nums.push(sum);
		}
		cout << "计算结果为：" << nums.top() << endl;
		//delete str;
		//str = new char;
		//nums.pop();
	}
protected:
	//如下属性用于存放操作数以及运算符
	char* str;
	stack<int>nums;
	stack<char>ops;
};

signed main()
{
	Function_Calculator cal;
	cal.Input_string();
}
*/