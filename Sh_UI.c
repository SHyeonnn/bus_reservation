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
		printf("\n      ������ �ݾ��� �Է��� �ּ��� (<=10����)");
		printf("\n                    -> ");
		scanf("%d", &input);
		if (input > 0 && input <= 100000) {
			u->cash += input;
			printf("\n\n              ���� ó���Ǿ����ϴ�\n\n");
			printf("=================================================\n");

			printf("\n          ���� ���� �ܾ��� %d���Դϴ�\n\n\n", u->cash);
			modify_profile(u);
			return 1;
		}
		else {
			printf("�ùٸ��� ���� ���� ���Դϴ�.\n");
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
		printf("         ���� �α����� �̷��� �����մϴ�.\n");
		printf("            ����� ������ �ҷ��ɴϴ�.\n");
		printf("-------------------------------------------------\n\n");
		load_profile(u);
		printf("           ������ �ݾ� >> %d\n", u->cash);
		printf("           ���ŵ� �¼� >> %d\n\n", u->num_ticket);

	}
	else if (nResult == -1)
	{
		printf("-------------------------------------------------\n");
		printf("      ���� �α����� �̷��� �������� �ʽ��ϴ�.\n");
		printf("             �ű� ����ڸ� �����մϴ�.\n");
		printf("-------------------------------------------------\n\n");

		id_forder = _mkdir(id);
		make_new_profile(u);
		u->cash = 0;
		u->num_ticket = 0;
		printf("           ������ �ݾ� >> %d\n", u->cash);
		printf("           ���ŵ� �¼� >> %d\n\n", u->num_ticket);
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
		printf("\n      �����Ϸ��� ������ ��¥�� �Է��� �ּ��� \n");
		printf("                   (ex 20211126)\n\n                    -> ");
		scanf("%d", &reservation_day);
		fflush(stdin);
		printf("\n\n     ���� ������ �Է��� �ּ��� (� or �ϱ�) \n\n                    -> ");
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

			printf("\n\n�¼��� ������ �ּ��� -> ");
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
			printf("\n\n�¼��� ������ �ּ��� -> ");
			scanf("%d", &seat);
			if (bus_seat[seat] == 1) {
				printf("\n���� �Ұ��� �ڸ��Դϴ�\n");
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
		printf("\n              ���Ű� �Ϸ�Ǿ����ϴ�\n");
		u->cash -= 6000;
		u->num_ticket++;


		modify_profile(u);
		GetDateTime(datetime);
		fprintf(fp, "%s,%d,%d,%s\n", datetime, reservation_day, seat, bus_cate);
		printf("              �ܾ��� %d���Դϴ�\n", u->cash);

	}
	else {
		printf("�ܾ��� �����մϴ�.\n");
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
	printf("         �� %d���� ���� ������ �����մϴ�\n", u->num_ticket);
	printf("-------------------------------------------------\n\n");

	if (fp != NULL)
	{
		while (total < u->num_ticket) {
			printf("< %d�� ���� >\n\n", total + 1);
			fgets(str_tmp, MAX, fp);
			p = strtok(str_tmp, ",");
			if (count == 0) {
				printf("   ���� �Ͻ� : %s\n", p);
				p = strtok(NULL, ",");

				count++;
			}
			if (count == 1) {
				printf("   ž�� �Ͻ� : %s\n", p);
				p = strtok(NULL, ",");

				count++;

			}
			if (count == 2) {
				printf("   �¼� ��ȣ : %s\n", p);
				p = strtok(NULL, ",");

				count++;

			}
			if (count == 3) {
				printf("   ���� : %s\n", p);
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
	printf(" 1. �ݾ� ����\n\n");
	printf(" 2. ���� ���� Ȯ��\n\n");
	printf(" 3. ���� ���� ����\n\n");
	printf(" 4. ���� ���� ��ġ Ȯ��\n\n");
	printf("-------------------------------------------------\n\n");
	printf("        ���ϴ� ������ ��ȣ�� �Է��� �ּ��� \n\n ");
	printf("                   -> ");
	scanf("%d", &input);
	return input;
}
int login(struct user* u) {
	struct user* temp = u;


	char name[MAX];
	int id = 0;
	printf(" ================================================\n\n");
	printf("                     �� �� ��                 \n\n");
	printf(" ================================================\n\n");
	printf("\n\n     �̸��� �Է��ϼ��� : ");
	gets(name);
	printf("\n\n     �й��� �Է��ϼ��� : ");
	scanf_s("%d", &id);

	if (name == "\0" || id == 0) {
		printf("\n\n\n        ����� �Է� ������ �߸��Ǿ����ϴ�\n\n\n");
		return 0;
	}
	else {
		printf("-------�Ϸ�-------\n");
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
				printf("��ȸ ������ �������� �ʽ��ϴ�.\n");
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
			printf("�������� ���� �Է� ���Դϴ�.\n");
			printf("���α׷��� �����մϴ�.\n");
			printf("-------------------------------\n");

			break;
		}
	}

	return 0;
}