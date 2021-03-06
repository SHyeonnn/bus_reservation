#include<stdio.h>
#include<windows.h>
#include <direct.h>		//mkdir
#include <errno.h>		//errno
#include <time.h>
#include <string.h>
#include<stdlib.h>
#include <io.h>		//access
#define MAX 255
#pragma warning(disable : 4996)
struct user {
	char name[MAX];
	char directory[MAX];
	int id;
	int cash;
	int num_ticket;
};
struct service {   //사용자의 메뉴얼 선택 변수들을 정의하기 위한 구조체
	int bus_type; //버스 종류 변수
	int shuttle;  //셔틀 버스 내용 세분화를 위한 변수
	int commute;  //통학 버스 내용 세분화를 위한 변수
};
void RemoveScrollbar() //콘솔창의 스크롤바 삭제 함수
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(handle, &info);
	COORD new_size =
	{
	 info.srWindow.Right - info.srWindow.Left + 1,
	 info.srWindow.Bottom - info.srWindow.Top + 1
	};
	SetConsoleScreenBufferSize(handle, new_size);
}
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
	printf("                   -> ");
}
void print_shuttle() {   //셔틀버스 화면 출력 함수
	printf("\n      =======================================\n");
	printf("                    셔  틀  버  스  ");
	printf("\n      =======================================\n\n\n\n\n");
	printf("         1. 상행 (신창역->학교)\n\n\n");
	printf("         2. 하행 (학교->신창역)\n\n\n");
	printf("         3. 종료\n\n\n\n\n\n");
	printf("      원하는 서비스의 번호를 입력해 주세요\n\n");
	printf("                   -> ");
}
void print_commute() {   //통학버스 화면 출력 함수
	printf("\n      =======================================\n");
	printf("                   통  학  버  스  ");
	printf("\n      =======================================\n\n\n\n");
	printf("         1. 로그인 실행\n\n\n");
	printf("         2. 종료\n\n\n");
	printf("       원하는 서비스의 번호를 입력해 주세요\n\n ");
	printf("                   -> ");
}
int menu1() {   //셔틀(상행)버스 메뉴 선택 출력 함수
	printf("\n================ < 상 행 버 스 > =================");
	printf("\n\n                 (신창역 -> 학교)\n\n");
	printf("\n\n  1. 입력된 시간에서 가장 가까운 버스 시간 보기\n\n");
	printf("  2. 버스 전체 시간표 출력하기 \n\n");
	printf("  3. 버스 위치 검색하기\n\n");
	printf("  4. 종료 \n\n\n");
	printf("==================================================\n\n");
	printf("       원하는 서비스의 번호를 입력해 주세요\n\n ");
	printf("                   -> ");
	int choice;
	scanf("%d", &choice);
	return choice;
}
int menu2() {
	printf("\n================ < 하 행 버 스 > =================");
	printf("\n\n                 (학교 -> 신창역)\n\n");
	printf("\n\n  1. 입력된 시간에서 가장 가까운 버스 시간 보기\n\n");
	printf("  2. 버스 전체 시간표 출력하기 \n\n");
	printf("  3. 종료 \n\n\n");
	printf("==================================================\n\n");
	printf("       원하는 서비스의 번호를 입력해 주세요\n\n ");
	printf("                   -> ");
	int choice;
	scanf("%d", &choice);
	return choice;
}
int get_trans_time(void) {    //시간과 분을 입력받고 시간에 *60을 하고 분을 더해 반환하는 함수
	printf("\n\n\n      시간을 입력하세요 (시 분) : ");
	int h, m, key;
	scanf("%d %d", &h, &m);  //시간과 분을 띄어쓰기로 구분
	return key = h * 60 + m;
}
void search_bus(int list[], int n, int key)  //가장 가까운 버스가 몇 번째 배열인지 순차탐색하는 함수
{
	int i = 0;
	int o_key = key; // 원본 키를 o_key로 복사한다
	while (list[i] != key)
	{
		for (i = 0; i < n; i++) { //n(SIZE)까지 배열을 비교
			if (key == list[i]) { //키랑 list[i]가 같으면 출력 후 종료
				printf("\n\n        가장 가까운 버스는 %d시 %d분입니다\n\n", list[i] / 60, list[i] % 60);
				printf("           대기 시간은 %d시간 %d분입니다\n\n\n\n", (key - o_key) / 60, (key - o_key) % 60);
				return 0;
			}
		}
		key = key + 1; //가장 가까운 list[i]를 못찾으면 key에 1을 합함
		if (key > 14400) { //키가 24*60을 넘어가면 시간 오류 출력 후 종료
			printf("\n\n           잘못된 시간이 입력되었습니다\n\n");
			printf("              선택창을 재실행합니다\n\n");
			Sleep(1500);
			system("cls");
			return 0;
		}
	}
}
void count(int x, int y) //학내순환 버스 위치를 출력하는 함수
{
	if (x >= y && y <= x + 2)
		printf("\n\n     입력된 시간의 버스 위치는 신창역입니다\n");
	else if (x + 3 == y)
		printf("\n\n     입력된 시간의 버스 위치는 후문입니다\n");
	else if (x + 4 == y)
		printf("\n\n     입력된 시간의 버스 위치는 향설 3관입니다\n");
	else if (x + 5 == y)
		printf("\n\n     입력된 시간의 버스 위치는 향설 2관입니다\n");
	else if (x + 6 == y)
		printf("\n\n입력된 시간의 버스 위치는 향설기념중앙도서관입니다\n");
	else if (x + 7 == y)
		printf("\n\n     입력된 시간의 버스 위치는 정문입니다\n");
	else if (x + 8 >= y && y <= x + 12)
		printf("\n\n     입력된 시간의 버스 위치는 신창역입니다\n");
	else
		printf("\n\n        운행 중인 학내순환 버스가 없습니다\n\n");
}
void modify_profile(struct user* u) {
	FILE* fp;
	char filename[MAX] = "\0";
	char temp1[MAX] = "\0";
	char temp2[MAX] = "\0";
	itoa(u->cash, temp1, 10);
	itoa(u->num_ticket, temp2, 10);

	strcpy(filename, u->directory);
	strcat(filename, "/");
	strcat(filename, "data.csv");
	fp = fopen(filename, "w+");
	fprintf(fp, "cash,");
	fprintf(fp, temp1);
	fprintf(fp, "\n");

	fprintf(fp, "num_ticket,");
	fprintf(fp, temp2);
	fprintf(fp, "\n");
}
int make_new_profile(struct user* u) {
	FILE* fp;
	char filename[MAX] = "\0";
	strcpy(filename, u->directory);
	strcat(filename, "/");
	strcat(filename, "data.csv");
	fp = fopen(filename, "w");
	fprintf(fp, "cash,0\n");
	fprintf(fp, "num_ticket,0\n");

}
int load_profile(struct user* u) {
	FILE* fp;
	char* p;
	int count = 0;
	char str_tmp[MAX];
	char filename[MAX] = "\0";
	strcpy(filename, u->directory);
	strcat(filename, "/");
	strcat(filename, "data.csv");
	fp = fopen(filename, "r");
	if (fp != NULL)
	{
		while (!feof(fp)) {
			fgets(str_tmp, MAX, fp);
			p = strtok(str_tmp, ",");
			p = strtok(NULL, ",");
			if (count == 0) {
				u->cash = atoi(p);
			}
			else if (count == 1) {
				u->num_ticket = atoi(p);
			}
			count++;
		}
	}
}
int money_charger(struct user* u) {
	int input = 0;
	system("cls");

	while (1) {
		printf("\n=================================================\n");
		printf("\n      충전할 금액을 입력해 주세요 (<=10만원)");
		printf("\n\n                    -> ");
		scanf("%d", &input);
		if (input > 0 && input <= 100000) {
			u->cash += input;
			printf("\n\n              정상 처리되었습니다\n\n");
			printf("=================================================\n");

			printf("\n          충전 이후 잔액은 %d원입니다\n\n\n", u->cash);
			printf("              선택창을 재실행합니다\n\n");
			Sleep(2000);
			system("cls");
			modify_profile(u);
			return 1;
		}
		else {
			printf("\n\n           올바르지 않은 충전 값입니다\n");
			Sleep(1000);
			system("cls");
		}
	}
}
int GetDateTime(char* datetime)
{
	struct tm* t;
	time_t tnow;
	tnow = time(NULL);
	t = (struct tm*)localtime(&tnow);
	sprintf(datetime, "%04d%02d%02d", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday);
	return (int)tnow;
}
int user_search(struct user* u) {
	char user[] = { "./user" };
	char id[30] = { "./user/" };
	char temp[9] = { "\0" };
	int id_forder = 0;
	int user_forder = _mkdir(user);
	FILE* p_file = NULL;
	itoa(u->id, temp, 10);
	strcat(id, temp);
	strcat(id, u->name);
	int nResult = access(id, 0);
	strcpy(u->directory, id);
	if (nResult == 0)
	{
		printf("\n-------------------------------------------------\n");
		printf("         기존 로그인한 이력이 존재합니다.\n");
		printf("            사용자 정보를 불러옵니다.\n");
		printf("-------------------------------------------------\n\n");
		load_profile(u);
		printf("            충전된 금액 >> %d\n", u->cash);
		printf("            예매된 좌석 >> %d\n\n", u->num_ticket);

	}
	else if (nResult == -1)
	{
		printf("\n-------------------------------------------------\n");
		printf("      기존 로그인한 이력이 존재하지 않습니다.\n");
		printf("             신규 사용자를 생성합니다.\n");
		printf("-------------------------------------------------\n\n");

		id_forder = _mkdir(id);
		make_new_profile(u);
		u->cash = 0;
		u->num_ticket = 0;
		printf("            충전된 금액 >> %d\n", u->cash);
		printf("            예매된 좌석 >> %d\n\n", u->num_ticket);
	}
}
int reservation_bus(struct user* u) {
	FILE* fp = NULL;
	FILE* fp2 = NULL;
	char filename[MAX] = "\0";
	char filename2[MAX] = "\0";
	char temp[MAX] = "\0";
	char temp1[MAX] = "\0";
	char temp2[MAX] = "\0";
	int bus_seat[45] = { 0 };
	char bus_cate[MAX] = "\0";
	int seat = 0;
	char* p;
	int count = 1;
	char str_tmp[MAX];
	strcpy(filename, u->directory);
	strcat(filename, "/");
	strcat(filename, "bus.csv");

	strcpy(filename2, "./bus");
	_mkdir(filename2);
	int nResult = 0;
	char datetime[16];
	memset(datetime, 0X00, sizeof(datetime));

	fp = fopen(filename, "a");
	int reservation_day = 0;
	printf("\n-------------------------------------------------\n");
	if (u->cash >= 6000) {
		printf("\n      예매하려는 버스의 날짜를 입력해 주세요 \n");
		printf("                   (ex 20211126)\n\n                    -> ");
		scanf("%d", &reservation_day);
		fflush(stdin);
		printf("\n\n     버스 종류를 입력해 주세요 (등교 or 하교) \n\n                    -> ");
		scanf("%s", bus_cate);
		printf("\n-------------------------------------------------\n\n\n");
		strcat(filename2, "/");
		itoa(reservation_day, temp, 10);
		strcat(filename2, temp);
		strcat(filename2, bus_cate);
		strcat(filename2, ".csv");

		nResult = access(filename2, 0);
		if (nResult == -1) {
			fp2 = fopen(filename2, "w");

			for (int i = 1; i < 45; i++) {
				if (i % 4 == 0) {
					printf("[%2d]\n", i);
				}
				else if (i % 2 == 0) {
					printf("[%2d]\t", i);

				}
				else if (i % 2 != 0 || i % 4 != 0) {
					printf("[%2d]", i);

				}
			}

			printf("\n\n좌석을 선택해 주세요 -> ");
			scanf("%d", &seat);
			for (int i = 1; i < 45; i++) {
				if (i != seat) {
					fprintf(fp2, "%d,0\n", i);
				}
				else {
					fprintf(fp2, "%d,1\n", i);
				}
			}
		}
		else {
			fp2 = fopen(filename2, "a+");
			if (fp2 != NULL)
			{
				while (!feof(fp2) && count <= 44) {
					fgets(str_tmp, MAX, fp2);
					p = strtok(str_tmp, ",");
					p = strtok(NULL, ",");
					if (atoi(p) == 1) {
						bus_seat[count]++;
					}
					count++;
				}
			}
			for (int i = 1; i < 45; i++) {
				if (bus_seat[i] == 0) {
					if (i % 4 == 0) {
						printf("[%2d]\n", i);
					}
					else if (i % 2 == 0) {
						printf("[%2d]\t", i);

					}
					else if (i % 2 != 0 || i % 4 != 0) {
						printf("[%2d]", i);

					}
				}
				else {
					if (i % 4 == 0) {
						printf("[%2c]\n", 'x');
					}
					else if (i % 2 == 0) {
						printf("[%2c]\t", 'x');

					}
					else if (i % 2 != 0 || i % 4 != 0) {
						printf("[%2c]", 'x');

					}
				}
			}
			printf("\n\n좌석을 선택해 주세요 -> ");
			scanf("%d", &seat);
			if (bus_seat[seat] == 1) {
				printf("\n선택 불가한 자리입니다\n");
			}
			else {
				fclose(fp2);
				fp2 = fopen(filename2, "w+");
				for (int i = 1; i < 45; i++) {
					if (i != seat) {
						fprintf(fp2, "%d,%d\n", i, bus_seat[i]);
					}
					else {
						fprintf(fp2, "%d,1\n", i);
					}
				}
			}




		}
		printf("\n-------------------------------------------------\n");
		printf("              예매가 완료되었습니다\n");
		u->cash -= 6000;
		u->num_ticket++;


		modify_profile(u);
		GetDateTime(datetime);
		fprintf(fp, "%s,%d,%d,%s\n", datetime, reservation_day, seat, bus_cate);
		printf("                잔액은 %d원입니다\n", u->cash);
		printf("              선택창을 재실행합니다\n\n");
		printf("-------------------------------------------------\n");
		Sleep(2000);
		system("cls");
	}
	else {
		printf("\n                잔액이 부족합니다\n");
		printf("              선택창을 재실행합니다\n\n");
		printf("-------------------------------------------------\n");
		Sleep(2000);
		system("cls");
	}

}
int check_bus(struct user* u) {
	FILE* fp;
	char* p;
	int count = 0;
	int total = 0;
	char str_tmp[MAX];
	char filename[MAX] = "\0";
	strcpy(filename, u->directory);
	strcat(filename, "/");
	strcat(filename, "bus.csv");
	fp = fopen(filename, "r");
	printf("\n-------------------------------------------------\n");
	printf("\n         총 %d건의 예매 내역이 존재합니다\n", u->num_ticket);
	printf("\n-------------------------------------------------\n\n");

	if (fp != NULL)
	{
		while (total < u->num_ticket) {
			printf("< %d번 예약 >\n\n", total + 1);
			fgets(str_tmp, MAX, fp);
			p = strtok(str_tmp, ",");
			if (count == 0) {
				printf("   예매 일시 : %s\n", p);
				p = strtok(NULL, ",");

				count++;
			}
			if (count == 1) {
				printf("   탑승 일시 : %s\n", p);
				p = strtok(NULL, ",");

				count++;

			}
			if (count == 2) {
				printf("   좌석 번호 : %s\n", p);
				p = strtok(NULL, ",");

				count++;

			}
			if (count == 3) {
				printf("   구분 : %s\n", p);
				count = 0;
				printf("\n-------------------------------------------------\n\n");

			}
			total++;
		}
	}
}
int print_menu() {
	int input = 0;
	printf("=================================================\n\n");
	printf("  1. 금액 충전\n\n");
	printf("  2. 예매 내역 확인\n\n");
	printf("  3. 통학 버스 예매\n\n");
	printf("  4. 통학 버스 위치 확인\n\n");
	printf("  5. 종료\n\n");
	printf("=================================================\n\n");
	printf("        원하는 서비스의 번호를 입력해 주세요 \n\n ");
	printf("                   -> ");
	scanf("%d", &input);
	return input;
}
int login(struct user* u) {
	struct user* temp = u;
	char name[MAX];
	int id = 0;
	printf(" ================================================\n\n");
	printf("                     로 그 인                 \n\n");
	printf(" ================================================\n\n");
	printf("\n\n     이름을 입력하세요 : ");
	scanf("%s", &name);
	printf("\n\n     학번을 입력하세요 : ");
	scanf_s("%d", &id);

	if (name == "\0" || id == 0) {
		printf("\n\n\n        사용자 입력 정보가 잘못되었습니다\n\n\n");
		return 0;
	}
	else {
		printf("-------완료-------\n");
		system("cls");

		strcpy(temp->name, name);
		temp->id = id;
		user_search(temp);
		return 1;
	}
}

int main(void)   //메인함수 시작
{
	system("mode con:cols=50 lines=40");   //콘솔창 크기 조절
	struct user u;
	int menu_input = 0;
	struct service ser;
	ser.bus_type = 0; ser.shuttle = 0; ser.commute = 0;   //변수 선언 및 초기화
	while (1) {  //무한루프 실행 (메인 화면이 종료 번호 입력 외에는 종료되지 않도록 하기 위함)
		print_firstp();   //메인 화면 출력 함수
		scanf_s("%d", &ser.bus_type);

		if (ser.bus_type == 1)  //셔틀버스 번호 입력 시
		{
			while (1)   //무한루프 실행 (셔틀버스 화면이 종료 번호 입력 외에는 종료되지 않도록 하기 위함)
			{
				system("cls");
				print_shuttle();  //셔틀버스 화면 출력 함수
				scanf_s("%d", &ser.shuttle);    //셔틀 메뉴얼의 번호를 입력 받음

				switch (ser.shuttle)
				{
				case 1:   //상행 번호 입력 시
					system("cls");
					FILE* fp = NULL;
					int list[10000] = { 0 };
					int c;
					while (1)   //무한루프 실행 (상행 메뉴 화면이 종료 번호 입력 외에는 종료되지 않도록 하기 위함)
					{
						fp = fopen("bus.txt", "r");
						int save_size;
						for (save_size = 0; !feof(fp); save_size++) // 파일이 끝날 때까지 list에 저장
						{
							fscanf(fp, "%d", &list[save_size]);
						}
						int SIZE = save_size - 1; //save_size는 0이 추가되기 때문에 
						fclose(fp);               //실제 저장된 정수의 수는 save_size에서 1을 뺀 수

						switch (menu1())
						{
						case 1:   //가장 가까운 버스 시간 찾기 번호 입력 시
							RemoveScrollbar(); //콘솔창의 스크롤바 삭제 함수
							system("cls");
							printf("\n================ < 상 행 버 스 > =================");
							printf("\n\n       가장 가까운 버스의 시간을 출력합니다\n");
							int h, m, key;
							key = get_trans_time();  //시간과 분을 입력받고 시간에 *60을 하고 분을 더해 반환하는 함수
							search_bus(list, SIZE, key);  //가장 가까운 버스가 몇 번째 배열인지 순차 탐색하는 함수
							break;
						case 2:   //버스 전체 시간표 번호 입력 시
							RemoveScrollbar();
							printf("\n\n");
							fp = fopen("bustime.txt", "r");
							while ((c = fgetc(fp)) != EOF) //파일에서 문자를 읽어 c에 저장
								putchar(c);   //저장된 문자들을 출력
							fclose(fp);
							HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //콘솔창의 스크롤을 임시적으로 생성
							COORD bufferSize = { 50, 300 };
							SetConsoleScreenBufferSize(hConsole, bufferSize);
							printf("\n\n\n");
							break;
						case 3:   //버스 위치 번호 입력 시
							RemoveScrollbar();
							system("cls");
							printf("\n================ < 상 행 버 스 > =================");
							printf("\n\n       입력한 시간의 버스 위치를 출력합니다\n");
							printf("              ( 오전 8~11시 운행 )\n");
							int a, key2;
							key2 = get_trans_time();//시간과 분을 입력받고 시간에 *60을 하고 분을 더해 반환하는 함수
							if (key2 >= 479 && key2 <= 512) {
								a = 479;
								count(a, key2);   //학내순환 버스 위치 출력 함수
							}
							else if (key2 >= 513 && key2 <= 534) {
								a = 513;
								count(a, key2);
							}
							else if (key2 >= 535 && key2 <= 572) {
								a = 535;
								count(a, key2);
							}
							else if (key2 >= 573 && key2 <= 606) {
								a = 573;
								count(a, key2);
							}
							else if (key2 >= 607 && key2 <= 624) {
								a = 607;
								count(a, key2);
							}
							else if (key2 >= 625 && key2 <= 652) {
								a = 625;
								count(a, key2);
							}
							else if (key2 >= 653 && key2 <= 665) {
								a = 653;
								count(a, key2);
							}
							else
								printf("\n\n        운행 중인 학내순환 버스가 없습니다\n\n\n");
							Sleep(2000);   //2초 지연
							system("cls");   //화면 삭제
							break;
						case 4:  //종료 번호 입력 시
							RemoveScrollbar();
							system("cls");
							printf("\n\n\n\n              프로그램을 종료합니다\n\n\n");
							Sleep(1000);   //1초 지연
							exit(1);   //프로그램을 완전히 종료
						default:  //예외 숫자를 입력 받았을 시
							RemoveScrollbar();
							system("cls");
							printf("\n\n\n             잘못된 번호가 입력되었습니다\n\n\n");
							printf("              선택창을 재실행합니다\n\n");
							Sleep(1500);   //1.5초 지연
							system("cls");  //화면 삭제
							continue;  //메뉴 선택 화면으로 돌아가기 위함
						}
					}
				case 2:   //하행 번호 입력 시
					system("cls");
					FILE* fpd = NULL;
					int listd[10000] = { 0 };
					while (1)  //무한루프 실행 (하행 메뉴 화면이 종료 번호 입력 외에는 종료되지 않도록 하기 위함)
					{
						fpd = fopen("buss.txt", "r");
						int save_size;
						for (save_size = 0; !feof(fpd); save_size++) //파일이 끝날 때까지 list에 저장
						{
							fscanf(fpd, "%d", &listd[save_size]);
						}
						int SIZE = save_size - 1; //save_size는 0이 추가되기 때문에 
						fclose(fpd);              //실제 저장된 정수의 수는 save_size에서 1을 뺌

						switch (menu2())
						{
						case 1:   //가장 가까운 버스 시간 찾기 번호 입력 시
							RemoveScrollbar(); //콘솔창의 스크롤바 삭제
							system("cls");
							printf("\n================ < 하 행 버 스 > =================");
							printf("\n\n       가장 가까운 버스의 시간을 출력합니다\n");
							int h, m, key;
							key = get_trans_time();  //시간과 분을 입력받고 시간에 *60을 하고 분을 더해 반환하는 함수
							search_bus(listd, SIZE, key);  //가장 가까운 버스가 몇번째 배열인지 순차탐색하는 함수
							break;
						case 2:   //버스 전체 시간표 번호 입력 시
							RemoveScrollbar();
							printf("\n\n");
							fpd = fopen("bustime_down.txt", "r");
							while ((c = fgetc(fpd)) != EOF) //파일에서 문자를 읽어 c에 저장
								putchar(c);   //저장된 문자들을 출력
							fclose(fpd);
							HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //콘솔창의 스크롤을 임시적으로 생성
							COORD bufferSize = { 50, 300 };
							SetConsoleScreenBufferSize(hConsole, bufferSize);
							printf("\n\n\n");
							break;
						case 3:   //종료 번호 입력 시
							RemoveScrollbar(); // 콘솔창의 스크롤바 삭제
							system("cls");
							printf("\n\n\n\n              프로그램을 종료합니다\n\n\n");
							Sleep(1000);   //1초 지연
							exit(1);   //프로그램을 완전히 종료
							break;
						default:   //예외 숫자 입력 시
							RemoveScrollbar(); // 콘솔창의 스크롤바 삭제
							system("cls");
							printf("\n\n\n             잘못된 번호가 입력되었습니다\n\n\n");
							printf("              선택창을 재실행합니다\n\n");
							Sleep(1500);   //1.5초 지연
							system("cls");   //화면 삭제
							continue;   //메뉴 선택 창으로 돌아가기 위함
						}
					}
				case 3:   //종료 번호 입력 시
					system("cls");
					printf("\n\n\n\n              프로그램을 종료합니다\n\n\n");
					Sleep(1000);   //1초 지연
					exit(1);   //프로그램을 완전히 종료
					break;
				default:
					system("cls");
					printf("\n\n\n             잘못된 번호가 입력되었습니다\n\n\n");
					printf("              선택창을 재실행합니다\n\n");
					Sleep(1500);   //1.5초 지연
					system("cls");   //화면 삭제
					continue;   //메뉴 선택 창으로 돌가기 위함
				}
			}

		}
		else if (ser.bus_type == 2) //통학버스 번호 입력 시
		{
			system("cls");
			print_commute();  //통학버스 화면 출력 함수
			scanf_s("%d", &ser.commute);
			switch (ser.commute)
			{
			case 1:   //로그인 실행 번호 입력 시
				system("cls");
				if (login(&u) == 1) {
					while (1) //무한루프 실행
					{
						menu_input = print_menu();
						switch (menu_input)
						{
						case 1:
							money_charger(&u);

							break;
						case 2:
							system("cls");

							if (u.num_ticket == 0) {
								RemoveScrollbar();
								printf("\n-------------------------------------------------\n");
								printf("\n          조회 내역이 존재하지 않습니다\n");
								printf("              선택창을 재실행합니다\n\n");
								printf("\n-------------------------------------------------\n");
								Sleep(1500);
								system("cls");
							}
							else {
								check_bus(&u);
							}
							break;
						case 3:
							system("cls");
							reservation_bus(&u);
							break;
						case 4:
							system("cls");

							printf("\n-------------------------------------------------\n");
							printf("\n-------------------------------------------------\n");

							break;
						case 5:
							system("cls");
							printf("\n\n\n\n              프로그램을 종료합니다\n\n\n");
							Sleep(1000);
							exit(1);
							break;
						default:
							system("cls");
							printf("\n\n            잘못된 번호가 입력되었습니다\n\n");
							printf("              선택창을 재실행합니다\n\n");
							Sleep(1500);
							system("cls");
							continue;
						}
					}
				}
				else {
					printf("              메인화면을 재실행합니다\n\n");
					Sleep(1500);
					system("cls");
				}
				break;
			case 2:   //종료 번호 입력 시
				system("cls");
				printf("\n\n\n\n              프로그램을 종료합니다\n\n\n");
				Sleep(1000);
				exit(1);
				break;
			default:   //예외 번호 입력 시
				system("cls");
				printf("\n\n\n             잘못된 번호가 입력되었습니다\n\n\n");
				printf("              메인화면을 재실행합니다\n\n");
				Sleep(1500);   //1.5초 지연
				system("cls");   //화면 삭제
				continue;   //메뉴 선택 창으로 돌아가기 위함
			}
		}
		else if (ser.bus_type == 3)  //종료 번호 입력 시
		{
			system("cls");
			printf("\n\n\n\n              프로그램을 종료합니다\n\n\n");
			Sleep(1000);  //1초 지연
			exit(1);  //프로그램을 완전히 종료
			break;
		}
		else    //예외 번호 입력 시
		{
			system("cls");
			printf("\n\n            잘못된 번호가 입력되었습니다\n\n");
			printf("                  재실행합니다\n\n\n");
			Sleep(1500);  //1.5초 지연
			system("cls");  //화면 삭제
			continue;   //메뉴 화면으로 돌아가기 위함
		}
	}
}