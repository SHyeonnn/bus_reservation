#include <stdio.h>
#include <direct.h>		//mkdir
#include <errno.h>		//errno
#include <time.h>
#include <string.h>
#include<stdlib.h>
#include <io.h>		//access
#include <windows.h>

#define MAX 255
#pragma warning(disable : 4996)

struct user {
	char name[MAX];
	char directory[MAX];
	int id;
	int cash;
	int num_ticket;

};
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
		printf("\n                    -> ");
		scanf("%d", &input);
		if (input > 0 && input <= 100000) {
			u->cash += input;
			printf("\n\n              정상 처리되었습니다\n\n");
			printf("=================================================\n");

			printf("\n          충전 이후 잔액은 %d원입니다\n\n\n", u->cash);
			modify_profile(u);
			return 1;
		}
		else {
			printf("올바르지 않은 충전 값입니다.\n");
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
		printf("-------------------------------------------------\n");
		printf("         기존 로그인한 이력이 존재합니다.\n");
		printf("            사용자 정보를 불러옵니다.\n");
		printf("-------------------------------------------------\n\n");
		load_profile(u);
		printf("           충전된 금액 >> %d\n", u->cash);
		printf("           예매된 좌석 >> %d\n\n", u->num_ticket);

	}
	else if (nResult == -1)
	{
		printf("-------------------------------------------------\n");
		printf("      기존 로그인한 이력이 존재하지 않습니다.\n");
		printf("             신규 사용자를 생성합니다.\n");
		printf("-------------------------------------------------\n\n");

		id_forder = _mkdir(id);
		make_new_profile(u);
		u->cash = 0;
		u->num_ticket = 0;
		printf("           충전된 금액 >> %d\n", u->cash);
		printf("           예매된 좌석 >> %d\n\n", u->num_ticket);
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
	printf("-------------------------------------------------\n");
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
		printf("\n              예매가 완료되었습니다\n");
		u->cash -= 6000;
		u->num_ticket++;


		modify_profile(u);
		GetDateTime(datetime);
		fprintf(fp, "%s,%d,%d,%s\n", datetime, reservation_day, seat, bus_cate);
		printf("              잔액은 %d원입니다\n", u->cash);

	}
	else {
		printf("잔액이 부족합니다.\n");
	}
	printf("\n-------------------------------------------------\n");

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

	printf("-------------------------------------------------\n");
	printf("         총 %d건의 예매 내역이 존재합니다\n", u->num_ticket);
	printf("-------------------------------------------------\n\n");

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
	printf("-------------------------------------------------\n\n");
	printf(" 1. 금액 충전\n\n");
	printf(" 2. 예매 내역 확인\n\n");
	printf(" 3. 통학 버스 예매\n\n");
	printf(" 4. 통학 버스 위치 확인\n\n");
	printf("-------------------------------------------------\n\n");
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
	gets(name);
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

int main() {
	system("mode con:cols=50 lines=40");
	struct user u;
	int menu_input = 0;
	if (login(&u) == 1) {
		menu_input = print_menu();
		switch (menu_input)
		{
		case 1:
			money_charger(&u);

			break;
		case 2:
			system("cls");

			if (u.num_ticket == 0) {
				printf("-------------------------------\n");
				printf("조회 내역이 존재하지 않습니다.\n");
				printf("-------------------------------\n");
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

			printf("-------------------------------\n");
			printf("-------------------------------\n");

			break;
		default:
			system("cls");

			printf("-------------------------------\n");
			printf("적절하지 않은 입력 값입니다.\n");
			printf("프로그램을 종료합니다.\n");
			printf("-------------------------------\n");

			break;
		}
	}

	return 0;
}