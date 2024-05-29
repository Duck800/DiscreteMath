/*2151133 �ﺫ��*/
#include <iostream>
#include <string>
#include <map>//����map������ӳ�ķ��������ȼ���ӳ��
#include <stack>//ջ��ͷ�ļ�
using namespace std;

typedef map<char, int> M_ci;//Ϊmap<char, int>�����ΪMap_ci
typedef map<int, char> M_ic;//Ϊmap<int, char>�����ΪMap_ic
typedef map<int, int> M_ii;//Ϊmap<int, int>�����ΪMap_ii

M_ci priority;//���ȶ���һ����������ȼ�map,������map<char, int>

bool check_fomula (string a) {//������빫ʽ����ȷ��
	/*������������Ƿ�ɶԡ�������Ƿ�����*/
	int left = 0, right = 0;
	for (unsigned int i = 0; i < a.length(); i++) {//��ʽ�ӽ��б���
		if (left < right) //�����������ܶ�����������
			return false;
		if (a[i] == '(') {
			left++;
			if (a[i + 1] == '&' || a[i + 1] == '|' || a[i + 1] == '^') 
				//���ܴ��ڡ�(&����(|����(^�������
				return false;
		}
		else if (a[i] == ')') {
			right++;
			if (a[i - 1] == '&' || a[i - 1] == '|' || a[i - 1] == '^') 
				//���ܴ��ڡ�&)����|)����^)�������
				return false;
		}
	}
	if (left != right) //���������Ƿ�ɶ�
		return false;
	if (a[a.length() - 1] == '&' || a[a.length() - 1] == '|' || a[a.length() - 1] == '!' || a[a.length() - 1] == '~' || a[a.length() - 1] == '^')
		//�����ʽ�����һλ
		return false;
	return true;//��������û���⣬�򷵻���ֵ
}
int find_proposition(M_ic pSet, char p){//���㲻ͬ�������ĸ���
	M_ic::iterator it = pSet.begin();//map������itָ��map�Ŀ�ͷ
	while (it != pSet.end()) {
		if (it->second == p) //�ж�itָ���vaule�Ƿ�Ϊp
			return it->first;//��Ϊp���򷵻�ָ�����������±�
		it++;//������it����
	}
	return -1;//�����꣬û���ҵ����򷵻�-1
}
M_ic get_proposition(string formula) //�ú������������빫ʽ�е��������(�����������)
{
	M_ic proposition;
	int n_proposition = 0;//��¼��ͬ�������ĸ���
	for (unsigned int i = 0; i < formula.length(); i++){//����ַ�����ʽ��
		char c = formula[i];//�����������ַ������ַ��ͱ���c��
		if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {//�ж��Ƿ���Ӣ�Ĵ�Сд��ĸ
			if (find_proposition(proposition, c) == -1) //�����������δ��ʽ���г��ֹ�
				proposition[n_proposition++] = c;
		}
		else if (!priority.count(c)) { //c��priority�в����ڣ������������
			cout << c << " is undefined!" << endl;//���Ȳ�����ĸ���ֲ������������������ַ�δ�������ʾ
			exit(2);//�˳�����
		}
	}
	return proposition;
}
M_ii translate(int n_proposition, int value)  //�ú��������������Ķ�����ȡֵ
{
	M_ii result;
	for (int i = 0; i < n_proposition; i++) {
		result[n_proposition - 1 - i] = value % 2;
		value = value / 2;
	}
	return result;
}
int power(int n) {//����2^n��ֵ
	if (n == 0)
		return 1;
	else
		return 2 * power(n - 1);//�ݹ�n-1��
}
void stack_pop(int& p, int& q,stack<bool>value) {//Ϊ�˺�����������������ջ��������һ������
	p = value.top();//ȡ����ջջ��Ԫ��
	value.pop();//��ջ
	q = value.top();//ȡ����ջջ��Ԫ��
	value.pop();//��ջ
}
void check(stack<bool>& value, stack<char>& opter) {//���������������ֱ�ȡ0��1ʱ�ĸ������������
	int p, q, result;
	char opt = opter.top();//�ַ�ջ��ջ�������
	switch (opt) {
	case '&':
		stack_pop(p, q, value);
		result = p && q;//������
		value.push(result);//�������ջ
		opter.pop();//����ջջ��Ԫ�س�ջ
		break;
	case '|':
		stack_pop(p, q, value);
		result = p || q;//������
		value.push(result);//�������ջ
		opter.pop();//����ջջ��Ԫ�س�ջ
		break;
	case '!':
		p = value.top();//ȡ����ջջ��Ԫ��
		value.pop();//��ջ
		result = !p;//������
		value.push(result);//�������ջ
		opter.pop();//����ջջ��Ԫ�س�ջ
		break;
	case '^':
		stack_pop(p, q, value);
		result = !p || q;//�̺����㣬�ȼ�Ϊ~p��q
		value.push(result);//�������ջ
		opter.pop();//����ջջ��Ԫ�س�ջ
		break;
	case '~':
		stack_pop(p, q, value);
		result = (!p || q) && (p || !q);//��ֵ���㣬p�̺�q��q�̺�p��
		value.push(result);//�������ջ
		opter.pop();//����ջջ��Ԫ�س�ջ
		break;
	case ')':
		opter.pop();
		while (opter.top() != '(')
			check(value, opter);//�ݹ�
		if (opter.top() == '(')
			opter.pop();//��ջ
		break;
	default:
		break;
	}
}
int calculate(string formula, M_ic pSet, M_ii value) { //���ظ����������������ϵ�������
	stack<char> opter;//�ַ�ջ
	stack<bool> num;//����ջ
	opter.push('#');//ѹ��ջ��Ԫ�ر�ʶ
	formula = formula + "#";//��ʽ��β��ʶ��
	for (unsigned int i = 0; i < formula.length(); i++) {
		char c = formula[i];//�����������ַ�����c��
		if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) //����Ӣ�Ĵ�Сд��ĸ
			num.push(value[find_proposition(pSet, c)]);
		else {
			char tmp = opter.top();
			if (priority[tmp] > priority[c]) {//��ջ��Ԫ�����ȼ����ڱ������ķ��ŵ����ȼ�
				while (priority[tmp] > priority[c] && tmp != '(') {
					check(num, opter); //���������������(ȡֵ0��1)�ĸ���������
					tmp = opter.top();
					if (tmp == '#' && c == '#') //��Ϊ#����ջ�׻�ʽ�ӽ�β
						return num.top();//��������ջ��ջ��Ԫ��
				}
				opter.push(c);//������ջ
			}
			else
				opter.push(c);//������ջ
		}
	}
	return -1;
}

int main() {
	//����map<char, int> �����ͣ������ź����ȼ���Ӧ����
	priority['('] = 6;
	priority[')'] = 6;
	priority['!'] = 5;
	priority['&'] = 4;
	priority['|'] = 3;
	priority['^'] = 2;
	priority['~'] = 1;
	priority['#'] = 0;
	//�˵���ʾ
	cout << "***************************************\n";
	cout << "**                                   **\n";
	cout << "**         ��ӭ�����߼��������      **\n";
	cout << "**   (��������ֵ��,����ʽ,֧������)  **\n";
	cout << "**                                   **\n";
	cout << "**              ��!��ʾ��            **\n";
	cout << "**              ��&��ʾ��            **\n";
	cout << "**              ��|��ʾ��            **\n";
	cout << "**             ��^��ʾ�̺�           **\n";
	cout << "**             ��~��ʾ��ֵ           **\n";
	cout << "**                                   **\n";
	cout << "***************************************\n\n";
	cout << "Please enter a legitimate proposition formula: " << endl;

	string formula;//��ʽ����string�洢
	while (1) {
		cin >> formula;//���빫ʽ
		if (check_fomula(formula)) //���ʽ���Ƿ�Ϸ�
			break;//�Ϸ���������ѭ��
		else
			cout << "���ʽ�������������룡" << endl;
	}

	M_ic proposition_set = get_proposition(formula);//��ȡ���������빫ʽ�е���������map(�����������)
	//�����ʽ���еı�������
	cout << "��ʽ���еı�������Ϊ��" << proposition_set.size() << endl;
	cout << endl;//����
	cout << "�����ֵ�����£�" << endl;
	/*��ӡ��ͷ*/
	for (unsigned int i = 0; i < proposition_set.size(); i++)
		cout << proposition_set[i] << "       ";
	cout << formula << endl;//�����ʽ

	int* p=NULL;
	p = (int*)malloc(sizeof(int) * power(proposition_set.size()));   //���������δ�����⹫ʽ�ĸ���(0��1)����������ֵ
	for (int i = 0; i < power(proposition_set.size()); i++) {//ѭ��2����������Ĵη��Σ���Ϊ����ô���ֶ�������Ϸ�ʽ
		M_ii bina_set = translate(proposition_set.size(), i);//�����������Ķ�����ȡֵ
		for (unsigned int j = 0; j < bina_set.size(); j++)
			cout << bina_set[j] << endl;//���һ���������0��1�����
		int result = calculate(formula, proposition_set, bina_set); //���ظ����������(ֵȡ0��1���ɺ�����)��ϵ�������
		*(p + i) = result;//������⹫ʽ�ĸ��е���������ֵ
		cout << result << endl;
	}
	int m = 0, M = 0;//��¼��ʽ�м�С�����ĸ���
	cout << "�����⹫ʽ������ȡ��ʽ��" << endl;
	for (int i = 0; i < power(proposition_set.size()); i++) {
		if (*(p + i) == 1) {
			if (m == 0)
				cout << "m<" << i << ">";//���е�һ����С���Ϊ���ʱǰ�治����\/����
			else
				cout << " \\/ m<" << i << "> ";//�ǵ�һ��
			m++;//��С�������һ
		}
	}
	if (m == 0)
		cout << "0";//û�м�С��
	cout << endl;
	cout << "�����⹫ʽ������ȡ��ʽ��" << endl;
	for (int i = 0; i < power(proposition_set.size()); i++) {
		if (*(p + i) == 0) {//����Ӧ��������Ϊ0ʱ
			if (M == 0) //���е�һ���������Ϊ���ʱǰ�治����/\����
				cout << "M<" << i << ">";
			else
				cout << " /\\ M<" << i << "> ";//�ǵ�һ��
			M++;//�����������һ
		}
	}
	if (M == 0)
		cout << "0";//û�м�����
	cout << endl;
	free(p);//�ͷ��ڴ�
	return 0;
}

