
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
	printf("         1. 상행 (신창->학교)\n\n\n");
	printf("         2. 하행 (학교->신창)\n\n\n");
	printf("         3. 뒤로 가기 \n\n\n");
	printf("         4. 종료\n\n\n\n\n\n");
	printf("      원하는 서비스의 번호를 입력해 주세요\n\n");
	printf("                  -> ");
}
void print_commute() {
	printf("\n      =======================================\n");
	printf("                    통  학  버  스  ");
	printf("\n      =======================================\n\n\n\n\n");
	printf("         1. 등교\n\n\n");
	printf("         2. 하교\n\n\n");
	printf("         3. 뒤로 가기\n\n\n");
	printf("         4. 종료\n\n\n\n\n\n");
	printf("      원하는 서비스의 번호를 입력해 주세요\n\n");
	printf("                  -> ");
}
void print_commute_up() {
	printf("\n      =======================================\n");
	printf("                    통  학  버  스  ");
	printf("\n      =======================================\n\n\n\n\n");
	printf("         1. 안산\n\n\n");
	printf("         2. 인천\n\n\n");
	printf("         3. 송내\n\n\n");
	printf("         4. 교대\n\n\n\n\n\n");
	printf("      원하는 탑승 지역의 번호를 입력해 주세요\n\n");
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
				/*상행코드작성*/
			case 2:
				system("cls");
				/*하행코드작성*/
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
				void print_commute_up();



			case 2:
				system("cls");
				/*하교작성*/
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
		if (ser.bus_type == 3) {
				system("cls");
				exit(1);
				system("cls");
		}
	}
}