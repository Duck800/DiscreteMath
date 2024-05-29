/*2151133 孙韩雅*/
#include <iostream>
#include <string>
#include <map>//利用map容器反映的符号向优先级的映射
#include <stack>//栈的头文件
using namespace std;

typedef map<char, int> M_ci;//为map<char, int>起别名为Map_ci
typedef map<int, char> M_ic;//为map<int, char>起别名为Map_ic
typedef map<int, int> M_ii;//为map<int, int>起别名为Map_ii

M_ci priority;//首先定义一个运算符优先级map,类型是map<char, int>

bool check_fomula (string a) {//检查输入公式的正确性
	/*检查左右括号是否成对、运算符非法相连*/
	int left = 0, right = 0;
	for (unsigned int i = 0; i < a.length(); i++) {//对式子进行遍历
		if (left < right) //右括号数不能多于左括号数
			return false;
		if (a[i] == '(') {
			left++;
			if (a[i + 1] == '&' || a[i + 1] == '|' || a[i + 1] == '^') 
				//不能存在‘(&’‘(|’‘(^’的情况
				return false;
		}
		else if (a[i] == ')') {
			right++;
			if (a[i - 1] == '&' || a[i - 1] == '|' || a[i - 1] == '^') 
				//不能存在‘&)’‘|)’‘^)’的情况
				return false;
		}
	}
	if (left != right) //左右括号是否成对
		return false;
	if (a[a.length() - 1] == '&' || a[a.length() - 1] == '|' || a[a.length() - 1] == '!' || a[a.length() - 1] == '~' || a[a.length() - 1] == '^')
		//检查表达式的最后一位
		return false;
	return true;//若上述都没问题，则返回真值
}
int find_proposition(M_ic pSet, char p){//计算不同命题变项的个数
	M_ic::iterator it = pSet.begin();//map迭代器it指向map的开头
	while (it != pSet.end()) {
		if (it->second == p) //判断it指向的vaule是否为p
			return it->first;//若为p，则返回指定命题变项的下标
		it++;//迭代器it右移
	}
	return -1;//遍历完，没有找到，则返回-1
}
M_ic get_proposition(string formula) //该函数返回所输入公式中的命题变项(不包括运算符)
{
	M_ic proposition;
	int n_proposition = 0;//记录不同命题变项的个数
	for (unsigned int i = 0; i < formula.length(); i++){//逐个字符遍历式子
		char c = formula[i];//将遍历到的字符存在字符型变量c中
		if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {//判断是否是英文大小写字母
			if (find_proposition(proposition, c) == -1) //该命题变项尚未在式子中出现过
				proposition[n_proposition++] = c;
		}
		else if (!priority.count(c)) { //c在priority中不存在，即不是运算符
			cout << c << " is undefined!" << endl;//即既不是字母，又不是运算符。则输出该字符未定义的提示
			exit(2);//退出程序
		}
	}
	return proposition;
}
M_ii translate(int n_proposition, int value)  //该函数返回命题变项的二进制取值
{
	M_ii result;
	for (int i = 0; i < n_proposition; i++) {
		result[n_proposition - 1 - i] = value % 2;
		value = value / 2;
	}
	return result;
}
int power(int n) {//返回2^n的值
	if (n == 0)
		return 1;
	else
		return 2 * power(n - 1);//递归n-1次
}
void stack_pop(int& p, int& q,stack<bool>value) {//为了后续函数遍历，将出栈操作放入一个函数
	p = value.top();//取整数栈栈顶元素
	value.pop();//出栈
	q = value.top();//取整数栈栈顶元素
	value.pop();//出栈
}
void check(stack<bool>& value, stack<char>& opter) {//返回两个命题变项分别取0或1时的各种组合运算结果
	int p, q, result;
	char opt = opter.top();//字符栈的栈顶运算符
	switch (opt) {
	case '&':
		stack_pop(p, q, value);
		result = p && q;//与运算
		value.push(result);//将结果进栈
		opter.pop();//符号栈栈顶元素出栈
		break;
	case '|':
		stack_pop(p, q, value);
		result = p || q;//或运算
		value.push(result);//将结果进栈
		opter.pop();//符号栈栈顶元素出栈
		break;
	case '!':
		p = value.top();//取整数栈栈顶元素
		value.pop();//出栈
		result = !p;//非运算
		value.push(result);//将结果进栈
		opter.pop();//符号栈栈顶元素出栈
		break;
	case '^':
		stack_pop(p, q, value);
		result = !p || q;//蕴含运算，等价为~p∪q
		value.push(result);//将结果进栈
		opter.pop();//符号栈栈顶元素出栈
		break;
	case '~':
		stack_pop(p, q, value);
		result = (!p || q) && (p || !q);//等值运算，p蕴含q且q蕴含p。
		value.push(result);//将结果进栈
		opter.pop();//符号栈栈顶元素出栈
		break;
	case ')':
		opter.pop();
		while (opter.top() != '(')
			check(value, opter);//递归
		if (opter.top() == '(')
			opter.pop();//出栈
		break;
	default:
		break;
	}
}
int calculate(string formula, M_ic pSet, M_ii value) { //返回给定整体命题变项组合的运算结果
	stack<char> opter;//字符栈
	stack<bool> num;//整数栈
	opter.push('#');//压入栈底元素标识
	formula = formula + "#";//公式结尾标识符
	for (unsigned int i = 0; i < formula.length(); i++) {
		char c = formula[i];//将遍历到的字符存在c中
		if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) //若是英文大小写字母
			num.push(value[find_proposition(pSet, c)]);
		else {
			char tmp = opter.top();
			if (priority[tmp] > priority[c]) {//若栈顶元素优先级大于遍历到的符号的优先级
				while (priority[tmp] > priority[c] && tmp != '(') {
					check(num, opter); //返回两个命题变项(取值0或1)的各种运算结果
					tmp = opter.top();
					if (tmp == '#' && c == '#') //若为#，即栈底或式子结尾
						return num.top();//返回整数栈的栈顶元素
				}
				opter.push(c);//符号入栈
			}
			else
				opter.push(c);//符号入栈
		}
	}
	return -1;
}

int main() {
	//运用map<char, int> 的类型，将符号和优先级对应起来
	priority['('] = 6;
	priority[')'] = 6;
	priority['!'] = 5;
	priority['&'] = 4;
	priority['|'] = 3;
	priority['^'] = 2;
	priority['~'] = 1;
	priority['#'] = 0;
	//菜单显示
	cout << "***************************************\n";
	cout << "**                                   **\n";
	cout << "**         欢迎进入逻辑运算软件      **\n";
	cout << "**   (可运算真值表,主范式,支持括号)  **\n";
	cout << "**                                   **\n";
	cout << "**              用!表示非            **\n";
	cout << "**              用&表示与            **\n";
	cout << "**              用|表示或            **\n";
	cout << "**             用^表示蕴含           **\n";
	cout << "**             用~表示等值           **\n";
	cout << "**                                   **\n";
	cout << "***************************************\n\n";
	cout << "Please enter a legitimate proposition formula: " << endl;

	string formula;//将式子用string存储
	while (1) {
		cin >> formula;//输入公式
		if (check_fomula(formula)) //检查式子是否合法
			break;//合法，则跳出循环
		else
			cout << "表达式有误，请重新输入！" << endl;
	}

	M_ic proposition_set = get_proposition(formula);//获取包含所输入公式中的命题变项的map(不包括运算符)
	//输出该式子中的变量个数
	cout << "该式子中的变量个数为：" << proposition_set.size() << endl;
	cout << endl;//空行
	cout << "输出真值表如下：" << endl;
	/*打印表头*/
	for (unsigned int i = 0; i < proposition_set.size(); i++)
		cout << proposition_set[i] << "       ";
	cout << formula << endl;//输出公式

	int* p=NULL;
	p = (int*)malloc(sizeof(int) * power(proposition_set.size()));   //该数组依次存放命题公式的各行(0或1)的运算结果的值
	for (int i = 0; i < power(proposition_set.size()); i++) {//循环2的命题个数的次方次，因为有这么多种二进制组合方式
		M_ii bina_set = translate(proposition_set.size(), i);//返回命题变项的二进制取值
		for (unsigned int j = 0; j < bina_set.size(); j++)
			cout << bina_set[j] << endl;//输出一组命题变项0、1的组合
		int result = calculate(formula, proposition_set, bina_set); //返回给定命题变项(值取0或1，可含括号)组合的运算结果
		*(p + i) = result;//存放命题公式的各行的运算结果的值
		cout << result << endl;
	}
	int m = 0, M = 0;//记录范式中极小项极大项的个数
	cout << "该命题公式的主析取范式：" << endl;
	for (int i = 0; i < power(proposition_set.size()); i++) {
		if (*(p + i) == 1) {
			if (m == 0)
				cout << "m<" << i << ">";//特判第一个极小项，因为输出时前面不用有\/符号
			else
				cout << " \\/ m<" << i << "> ";//非第一个
			m++;//极小项个数加一
		}
	}
	if (m == 0)
		cout << "0";//没有极小项
	cout << endl;
	cout << "该命题公式的主合取范式：" << endl;
	for (int i = 0; i < power(proposition_set.size()); i++) {
		if (*(p + i) == 0) {//当对应的运算结果为0时
			if (M == 0) //特判第一个极大项，因为输出时前面不用有/\符号
				cout << "M<" << i << ">";
			else
				cout << " /\\ M<" << i << "> ";//非第一个
			M++;//极大项个数加一
		}
	}
	if (M == 0)
		cout << "0";//没有极大项
	cout << endl;
	free(p);//释放内存
	return 0;
}

