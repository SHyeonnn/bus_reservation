
#include<stdio.h>
#include<windows.h>
void print_firstp() {   //첫 화면 출력 함수
	printf("\n      =======================================\n");
	printf("         ┏━━━┓  ┏┓     ┏┓ ┏┓┏┓ ┏┓  ┏━━━┓\n");
	printf("        ┃  ━  ┃ ┃┃     ┃┃ ┃┗┛┃┏┛┃ ┏┛┏━┓┗┓ \n");
	printf("         ┗━━━┛  ┃┃     ┃┃ ┃┏┓┃┗┓┃ ┗━┛ ┗━┛\n");
	printf("        ┏━━━━┓  ┃ ━━━┓ ┃┃ ┃┗┛┃ ┃┃ ┏━━━━━┓\n");
	printf("        ┗┓┏┓┏┛  ┗━━━━┛ ┗┛ ┗━━┛ ┗┛ ┗━━━━━┛\n");
	printf("      =======================================\n");
	printf("     ♡순천향대 학생들을 위한 버스 서비스♡\n\n\n\n\n\n");
	printf("         1. 셔틀 버스\n\n\n");
	printf("         2. 통학 버스\n\n\n");
	printf("         3. 종료\n\n\n\n\n\n");
	printf("      원하는 서비스의 번호를 입력해 주세요\n\n");
	printf("                  -> ");
}
void print_shuttle() {
	printf("\n      =======================================\n");
	printf("                    셔  틀  버  스  ");
	printf("\n      =======================================\n\n\n\n\n");
	printf("         1. 버스 시간 확인\n\n\n");
	printf("         2. 버스 위치 확인\n\n\n");
	printf("         3. 뒤로 가기 \n\n\n");
	printf("         4. 종료\n\n\n\n\n\n");
	printf("      원하는 서비스의 번호를 입력해 주세요\n\n");
	printf("                  -> ");
}
void print_commute() {
	printf("\n      =======================================\n");
	printf("                    통  학  버  스  ");
	printf("\n      =======================================\n\n\n\n\n");
	printf("         1. 회원 정보 확인 및 충전\n\n\n");
	printf("         2. 배차 시간표 확인\n\n\n");
	printf("         3. 버스 예매\n\n\n");
	printf("         4. 통학버스 위치 확인\n\n\n");
	printf("         5. 뒤로 가기\n\n\n");
	printf("         6. 종료\n\n\n\n\n\n");
	printf("      원하는 서비스의 번호를 입력해 주세요\n\n");
	printf("                  -> ");
}

struct service {   //사용자의 메뉴얼 선택 변수들을 정의하기 위한 구조체
	int bus_type; //버스 종류 변수
	int shuttle;  //셔틀 버스 내용 세분화를 위한 변수
	int commute;  //통학 버스 내용 세분화를 위한 변수
};
int main(void) {
	system("mode con:cols=50 lines=40");   //콘솔창 크기 조절
	struct service ser;
	ser.bus_type = 0; ser.shuttle = 0; ser.commute = 0;
	print_firstp();
	scanf_s("%d", &ser.bus_type);
	while (1) {
		if (ser.bus_type == 1) {
			system("cls");
			print_shuttle();
			scanf_s("%d", &ser.shuttle);
			switch (ser.shuttle) {
			case 1:
				system("cls");
				/*버스시간확인코드작성*/
			case 2:
				system("cls");
				/*버스위치확인코드작성*/
			case 3:
				system("cls");
				ser.bus_type = 0;
				break;
			case 4:
				system("cls");
				exit(1);
				system("cls");
				break;
			}
			if (ser.bus_type == 0) {
				print_firstp();
				scanf_s("%d", &ser.bus_type);
			}
		}
		if (ser.bus_type == 2) {
			system("cls");
			print_commute();
			scanf_s("%d", &ser.commute);
			switch (ser.commute) {
			case 1:
				system("cls");
				/*회원정보확인코드작성*/
			case 2:
				system("cls");
				/*배차시간표확인코드작성*/
			case 3:
				system("cls");
				/*버스예매코드작성*/
			case 4:
				system("cls");
				/*통학버스위치확인코드작성*/
			case 5:
				system("cls");
				ser.bus_type = 0;
				break;
			case 6:
				system("cls");
				exit(1);
				system("cls");
				break;
			}
			if (ser.bus_type == 0) {
				print_firstp();
				scanf_s("%d", &ser.bus_type);
			}
		}
		if (ser.bus_type == 3) {
				system("cls");
				exit(1);
				system("cls");
		}
	}
}