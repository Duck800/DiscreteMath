/*2151133 �ﺫ��*/
#include <stdio.h>
#include <iostream>
using namespace std;

int main() {
	bool p = false, q = false;
	char choice_continue;//���ڴ���Ƿ���������ѡ��
	cout << "***************************************" << endl;  
	cout << "**                                   **" << endl;
	cout << "**        ��ӭ�����߼��������       **" << endl;
	cout << "**                                   **" << endl;
	cout << "***************************************" << endl << endl;
PART1:
	cout << "������P��ֵ��0��1��:";
	cin >> p;  
	if (cin.fail()) {
		cout << "P��ֵ��������,����������!" << endl;
		cin.clear();
		cin.ignore(100, '\n');
		goto PART1;
	}
PART2:
	cout << "������Q��ֵ��0��1��:";
	cin >> q; 
	if (cin.fail()){
		cout << "Q��ֵ��������,����������!" << endl;
		cin.clear();
		cin.ignore(100, '\n');
		goto PART2;
	}

	cout << endl;
	cout << "��ȡ: P/\\Q =" << (p && q )<< endl; //�����ȡ���
	cout << "��ȡ: P\\/Q =" << (p || q )<< endl; //�����ȡ���
	cout << "����: P->Q =" <<((!p) || q) << endl; //����������
	cout << "˫����: P<->Q =" << (((!p) || q) && ((!q) || p))<< endl; //���˫�������

PART3:
	cout << endl << "�Ƿ��������?��y/n��";  //�Ƿ��������
	cin >> choice_continue;
	if (choice_continue == 'y' || choice_continue == 'n'|| choice_continue == 'Y'|| choice_continue == 'N'){
		if (choice_continue == 'y'|| choice_continue == 'Y')
			goto PART1;  //����Pֵ������
		else
			cout << "�������˳�!" << endl;  
	}
	else{
		cout << "�������,����������!" << endl; 
		cin.clear();
		cin.ignore(100, '\n');
		goto PART3; //�ص�ѯ���Ƿ��������
	}
	return 0;
}