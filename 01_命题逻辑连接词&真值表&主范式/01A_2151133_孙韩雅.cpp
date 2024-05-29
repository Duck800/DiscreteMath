/*2151133 孙韩雅*/
#include <stdio.h>
#include <iostream>
using namespace std;

int main() {
	bool p = false, q = false;
	char choice_continue;//用于存放是否继续运算的选择
	cout << "***************************************" << endl;  
	cout << "**                                   **" << endl;
	cout << "**        欢迎进入逻辑运算程序       **" << endl;
	cout << "**                                   **" << endl;
	cout << "***************************************" << endl << endl;
PART1:
	cout << "请输入P的值（0或1）:";
	cin >> p;  
	if (cin.fail()) {
		cout << "P的值输入有误,请重新输入!" << endl;
		cin.clear();
		cin.ignore(100, '\n');
		goto PART1;
	}
PART2:
	cout << "请输入Q的值（0或1）:";
	cin >> q; 
	if (cin.fail()){
		cout << "Q的值输入有误,请重新输入!" << endl;
		cin.clear();
		cin.ignore(100, '\n');
		goto PART2;
	}

	cout << endl;
	cout << "合取: P/\\Q =" << (p && q )<< endl; //输出合取结果
	cout << "析取: P\\/Q =" << (p || q )<< endl; //输出析取结果
	cout << "条件: P->Q =" <<((!p) || q) << endl; //输出条件结果
	cout << "双条件: P<->Q =" << (((!p) || q) && ((!q) || p))<< endl; //输出双条件结果

PART3:
	cout << endl << "是否继续运算?（y/n）";  //是否继续操作
	cin >> choice_continue;
	if (choice_continue == 'y' || choice_continue == 'n'|| choice_continue == 'Y'|| choice_continue == 'N'){
		if (choice_continue == 'y'|| choice_continue == 'Y')
			goto PART1;  //返回P值的输入
		else
			cout << "程序已退出!" << endl;  
	}
	else{
		cout << "输入错误,请重新输入!" << endl; 
		cin.clear();
		cin.ignore(100, '\n');
		goto PART3; //回到询问是否继续操作
	}
	return 0;
}