#include <iostream>
#include <Windows.h>
#include <conio.h>

using namespace std;

#define ESC 0x1b	//esc 아스키코드 키값

void mainbg();//메인 화면
void menubg();//메뉴 화면
void orderbg();//메뉴 확인
void showTable(int *t[]); //전체테이블 화면

void tablePrint(int n);	//현재 테이블 주문목록 출력
void tableOrder(int n, int menu, int num);	//현재 테이블 주문
int tableSum(int n);//테이블 합계금액

void setColor(int color, int bgcolor);

class SetTable {
	private :
		int menu1;	//라면
		int menu2;	//삼겹살
		int sum;	//합계금액

	public :
		SetTable();	//생성자
		void SetMenu(int menu, int num);	//메뉴수정
		void ShowReceipt(int n);	//영수증
		int returnSum();	//합계금액
};

SetTable t1, t2, t3;

int main() {
	int sales = 0;//매출
	int *tableNum[3] = { 0 };	//테이블
	int customCount = 1;	//고객 숫자
	char mainChoose;	//메인화면 선택
	int tableChoose;	//테이블 선택
	char c;	//화면 초기화할때 사용하는 변수

	while(true) {
		system("cls");	//화면 초기화

		mainbg();

		switch (mainChoose = getch()) {
		case '1': {
			showTable(tableNum);

			cout << "테이블을 선택하세요 : ";
			cin >> tableChoose;

			if (tableNum[tableChoose - 1] != 0) {
				tablePrint(tableChoose);
			}
			else {
				cout << "\n* " << tableChoose << "번 테이블이 선택됐습니다.\n" << endl;
				tableNum[tableChoose - 1]++;
			}

			orderbg();

			switch (mainChoose = getch()) {
			case '1': {
				int menu;
				int num;

				menubg();
				cout << "1.라면, 2.삼겹살, 3.둘다 : ";
				cin >> menu;

				if (menu == 1) {
					cout << "개수를 입력해주세요 : ";
					cin >> num;

					tableOrder(tableChoose, menu, num);
					cout << "주문이 완료되었습니다. 아무키나 입력하세요";
					c = getch();
				}
				else if (menu == 2) {
					cout << "개수를 입력해주세요 : ";
					cin >> num;

					tableOrder(tableChoose, menu, num);
					cout << "주문이 완료되었습니다. 아무키나 입력하세요";
					c = getch();
				}
				else if (menu == 3) {
					cout << "라면의 개수를 입력해주세요 : ";
					cin >> num;
					tableOrder(tableChoose, 1, num);

					cout << "삼겹살의 개수를 입력해주세요 : ";
					cin >> num;
					tableOrder(tableChoose, 2, num);
					cout << "주문이 완료되었습니다. 아무키나 입력하세요";
					c = getch();
				}
				break;
			}
			case '2': {
				for (int i = 1; i < 3; i++) {	//초기화
					tableOrder(tableChoose, i, 0);
				}
				tableNum[tableChoose-1] = 0;
				cout << "주문이 완료되었습니다. 아무키나 입력하세요";
				c = getch();
				break;
			}
			case '3': {
				sales += tableSum(tableChoose);

				for (int i = 1; i < 3; i++) {	//초기화
					tableOrder(tableChoose, i, 0);
				}
				tableNum[tableChoose - 1] = 0;

				cout << "계산이 완료되었습니다. 아무키나 입력하세요"<<endl;
				cout << "넘기 시려면 아무키나 입력하세요.";
				c = getch();
				break;
			}
			case '4': {
				if (tableNum[tableChoose - 1] == 0) {
					--tableNum[tableChoose - 1];
					c = getch();
				}
				else {
					cout << "* 주문을 완료하였습니다." << endl;
					cout << "넘기 시려면 아무키나 입력하세요.";
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
			cout << "* 현재 매출 : " << sales << "원" << endl;
			cout << "넘기 시려면 아무키나 입력하세요.";
			c = getch();
			continue;
		}
		case ESC: {
			cout << "* 오늘 매출 : " << sales << "원" << endl;
			return 0;
		}
		default: {
			continue;
		}
		}
	}

	return 0;
}

//화면 표시 함수
void mainbg() {
	cout << "======================================" << endl;
	cout << "                pos기기" << endl;
	cout << "1.테이블표시, 2.현재매출, ESC.영업종료" << endl;
	cout << "======================================" << endl;
}
void menubg() {
	cout << "------메뉴------" << endl;
	cout << "* 1.라면(5000원)" << endl;
	cout << "* 2.삼겹살1인분(12000원)" << endl;
	cout << "----------------\n" << endl;
}
void orderbg() {
	cout << "---선택하세요---" << endl;
	cout << "* 1. 주문 및 주문 변경" << endl;
	cout << "* 2. 주문 취소" << endl;
	cout << "* 3. 계산" << endl;
	cout << "* 4. 완료" << endl;
	cout << "----------------" << endl;
}
void showTable(int *t[]) {
	cout << "---현재 테이블 정보---" << endl;
	for (int i = 0; i < 3; i++) {
		if (t[i] == 0)
			cout << "* " << i + 1 << "번 테이블 비어있음" << endl;
		else {
			setColor(12, 0); //빨간색
			cout << "* " << i + 1 << "번 테이블 손님있음" << endl;
			setColor(7, 0);	//하얀색
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
SetTable::SetTable() {	//생성자
	menu1 = 0;
	menu2 = 0;
	sum = 0;
}
void SetTable::SetMenu(int menu, int num) { //메뉴 변경
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
void SetTable::ShowReceipt(int n) { //영수증
	sum = (menu1 * 5000) + (menu2 * 12000);
	cout << "\n* " << n+1 << "번 테이블";
	cout << "주문 메뉴 : 라면(" << menu1 << ")개, 삼겹살(" << menu2 << ")인분\t";
	cout << "총 금액 : " << sum << endl << endl;
}

int SetTable::returnSum() {//합계금액
	return sum;
}
	
void setColor(int color, int bgcolor) {
	color &= 0xf;
	bgcolor &= 0xf;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (bgcolor << 4) | color);
}