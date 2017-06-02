#include <iostream>
#include <Windows.h>
#include <conio.h>

using namespace std;

#define ESC 0x1b	//esc �ƽ�Ű�ڵ� Ű��

void mainbg();//���� ȭ��
void menubg();//�޴� ȭ��
void orderbg();//�޴� Ȯ��
void showTable(int *t[]); //��ü���̺� ȭ��

void tablePrint(int n);	//���� ���̺� �ֹ���� ���
void tableOrder(int n, int menu, int num);	//���� ���̺� �ֹ�
int tableSum(int n);//���̺� �հ�ݾ�

void setColor(int color, int bgcolor);

class SetTable {
	private :
		int menu1;	//���
		int menu2;	//����
		int sum;	//�հ�ݾ�

	public :
		SetTable();	//������
		void SetMenu(int menu, int num);	//�޴�����
		void ShowReceipt(int n);	//������
		int returnSum();	//�հ�ݾ�
};

SetTable t1, t2, t3;

int main() {
	int sales = 0;//����
	int *tableNum[3] = { 0 };	//���̺�
	int customCount = 1;	//�� ����
	char mainChoose;	//����ȭ�� ����
	int tableChoose;	//���̺� ����
	char c;	//ȭ�� �ʱ�ȭ�Ҷ� ����ϴ� ����

	while(true) {
		system("cls");	//ȭ�� �ʱ�ȭ

		mainbg();

		switch (mainChoose = getch()) {
		case '1': {
			showTable(tableNum);

			cout << "���̺��� �����ϼ��� : ";
			cin >> tableChoose;

			if (tableNum[tableChoose - 1] != 0) {
				tablePrint(tableChoose);
			}
			else {
				cout << "\n* " << tableChoose << "�� ���̺��� ���õƽ��ϴ�.\n" << endl;
				tableNum[tableChoose - 1]++;
			}

			orderbg();

			switch (mainChoose = getch()) {
			case '1': {
				int menu;
				int num;

				menubg();
				cout << "1.���, 2.����, 3.�Ѵ� : ";
				cin >> menu;

				if (menu == 1) {
					cout << "������ �Է����ּ��� : ";
					cin >> num;

					tableOrder(tableChoose, menu, num);
					cout << "�ֹ��� �Ϸ�Ǿ����ϴ�. �ƹ�Ű�� �Է��ϼ���";
					c = getch();
				}
				else if (menu == 2) {
					cout << "������ �Է����ּ��� : ";
					cin >> num;

					tableOrder(tableChoose, menu, num);
					cout << "�ֹ��� �Ϸ�Ǿ����ϴ�. �ƹ�Ű�� �Է��ϼ���";
					c = getch();
				}
				else if (menu == 3) {
					cout << "����� ������ �Է����ּ��� : ";
					cin >> num;
					tableOrder(tableChoose, 1, num);

					cout << "������ ������ �Է����ּ��� : ";
					cin >> num;
					tableOrder(tableChoose, 2, num);
					cout << "�ֹ��� �Ϸ�Ǿ����ϴ�. �ƹ�Ű�� �Է��ϼ���";
					c = getch();
				}
				break;
			}
			case '2': {
				for (int i = 1; i < 3; i++) {	//�ʱ�ȭ
					tableOrder(tableChoose, i, 0);
				}
				tableNum[tableChoose-1] = 0;
				cout << "�ֹ��� �Ϸ�Ǿ����ϴ�. �ƹ�Ű�� �Է��ϼ���";
				c = getch();
				break;
			}
			case '3': {
				sales += tableSum(tableChoose);

				for (int i = 1; i < 3; i++) {	//�ʱ�ȭ
					tableOrder(tableChoose, i, 0);
				}
				tableNum[tableChoose - 1] = 0;

				cout << "����� �Ϸ�Ǿ����ϴ�. �ƹ�Ű�� �Է��ϼ���"<<endl;
				cout << "�ѱ� �÷��� �ƹ�Ű�� �Է��ϼ���.";
				c = getch();
				break;
			}
			case '4': {
				if (tableNum[tableChoose - 1] == 0) {
					--tableNum[tableChoose - 1];
					c = getch();
				}
				else {
					cout << "* �ֹ��� �Ϸ��Ͽ����ϴ�." << endl;
					cout << "�ѱ� �÷��� �ƹ�Ű�� �Է��ϼ���.";
				}
				break;
			}
			default: {
				break;
			}
			}
			break;
		}
		case '2': {
			cout << "* ���� ���� : " << sales << "��" << endl;
			cout << "�ѱ� �÷��� �ƹ�Ű�� �Է��ϼ���.";
			c = getch();
			continue;
		}
		case ESC: {
			cout << "* ���� ���� : " << sales << "��" << endl;
			return 0;
		}
		default: {
			continue;
		}
		}
	}

	return 0;
}

//ȭ�� ǥ�� �Լ�
void mainbg() {
	cout << "======================================" << endl;
	cout << "                pos���" << endl;
	cout << "1.���̺�ǥ��, 2.�������, ESC.��������" << endl;
	cout << "======================================" << endl;
}
void menubg() {
	cout << "------�޴�------" << endl;
	cout << "* 1.���(5000��)" << endl;
	cout << "* 2.����1�κ�(12000��)" << endl;
	cout << "----------------\n" << endl;
}
void orderbg() {
	cout << "---�����ϼ���---" << endl;
	cout << "* 1. �ֹ� �� �ֹ� ����" << endl;
	cout << "* 2. �ֹ� ���" << endl;
	cout << "* 3. ���" << endl;
	cout << "* 4. �Ϸ�" << endl;
	cout << "----------------" << endl;
}
void showTable(int *t[]) {
	cout << "---���� ���̺� ����---" << endl;
	for (int i = 0; i < 3; i++) {
		if (t[i] == 0)
			cout << "* " << i + 1 << "�� ���̺� �������" << endl;
		else {
			setColor(12, 0); //������
			cout << "* " << i + 1 << "�� ���̺� �մ�����" << endl;
			setColor(7, 0);	//�Ͼ��
		}
	}
	cout << endl;
}

void tablePrint(int n) {
	switch (n) {
	case 1: {
		t1.ShowReceipt(n - 1);
		break;
	}
	case 2: {
		t2.ShowReceipt(n - 1);
		break;
	}
	case 3: {
		t3.ShowReceipt(n - 1);
		break;
	}
	}
}

void tableOrder(int n, int menu, int num) {
	switch (n) {
	case 1: {
		t1.SetMenu(menu, num);
		break;
	}
	case 2: {
		t2.SetMenu(menu, num);
		break;
	}
	case 3: {
		t3.SetMenu(menu, num);
		break;
	}
	}
}

int tableSum(int n) {
	switch (n) {
	case 1: {
		return t1.returnSum();
	}
	case 2: {
		return t2.returnSum();
	}
	case 3: {
		return t3.returnSum();
	}
	}
}

//SetTable.class
SetTable::SetTable() {	//������
	menu1 = 0;
	menu2 = 0;
	sum = 0;
}
void SetTable::SetMenu(int menu, int num) { //�޴� ����
	switch(menu) {
	case 1: {
		menu1 = num;
		break;
	}
	case 2:{
		menu2 = num;
	}
	}
}
void SetTable::ShowReceipt(int n) { //������
	sum = (menu1 * 5000) + (menu2 * 12000);
	cout << "\n* " << n+1 << "�� ���̺�";
	cout << "�ֹ� �޴� : ���(" << menu1 << ")��, ����(" << menu2 << ")�κ�\t";
	cout << "�� �ݾ� : " << sum << endl << endl;
}

int SetTable::returnSum() {//�հ�ݾ�
	return sum;
}
	
void setColor(int color, int bgcolor) {
	color &= 0xf;
	bgcolor &= 0xf;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (bgcolor << 4) | color);
}