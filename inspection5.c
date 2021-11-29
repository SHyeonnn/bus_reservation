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
struct service {   //������� �޴��� ���� �������� �����ϱ� ���� ����ü
	int bus_type; //���� ���� ����
	int shuttle;  //��Ʋ ���� ���� ����ȭ�� ���� ����
	int commute;  //���� ���� ���� ����ȭ�� ���� ����
};
void RemoveScrollbar() //�ܼ�â�� ��ũ�ѹ� ���� �Լ�
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
void print_firstp() {   //ù ȭ�� ��� �Լ�
	printf("\n      =======================================\n");
	printf("         ����������  ����     ���� �������� ����  ����������\n");
	printf("        ��  ��  �� ����     ���� �������������� �������������� \n");
	printf("         ����������  ����     ���� �������������� ������ ������\n");
	printf("        ������������  �� �������� ���� �������� ���� ��������������\n");
	printf("        ������������  ������������ ���� �������� ���� ��������������\n");
	printf("      =======================================\n");
	printf("     ����õ��� �л����� ���� ���� ���񽺢�\n\n\n\n\n\n");
	printf("         1. ��Ʋ ����\n\n\n");
	printf("         2. ���� ����\n\n\n");
	printf("         3. ����\n\n\n\n\n\n");
	printf("      ���ϴ� ������ ��ȣ�� �Է��� �ּ���\n\n");
	printf("                   -> ");
}
void print_shuttle() {   //��Ʋ���� ȭ�� ��� �Լ�
	printf("\n      =======================================\n");
	printf("                    ��  Ʋ  ��  ��  ");
	printf("\n      =======================================\n\n\n\n\n");
	printf("         1. ���� (��â��->�б�)\n\n\n");
	printf("         2. ���� (�б�->��â��)\n\n\n");
	printf("         3. ����\n\n\n\n\n\n");
	printf("      ���ϴ� ������ ��ȣ�� �Է��� �ּ���\n\n");
	printf("                   -> ");
}
void print_commute() {   //���й��� ȭ�� ��� �Լ�
	printf("\n      =======================================\n");
	printf("                   ��  ��  ��  ��  ");
	printf("\n      =======================================\n\n\n\n");
	printf("         1. �α��� ����\n\n\n");
	printf("         2. ����\n\n\n");
	printf("       ���ϴ� ������ ��ȣ�� �Է��� �ּ���\n\n ");
	printf("                   -> ");
}
int menu1() {   //��Ʋ(����)���� �޴� ���� ��� �Լ�
	printf("\n================ < �� �� �� �� > =================");
	printf("\n\n                 (��â�� -> �б�)\n\n");
	printf("\n\n  1. �Էµ� �ð����� ���� ����� ���� �ð� ����\n\n");
	printf("  2. ���� ��ü �ð�ǥ ����ϱ� \n\n");
	printf("  3. ���� ��ġ �˻��ϱ�\n\n");
	printf("  4. ���� \n\n\n");
	printf("==================================================\n\n");
	printf("       ���ϴ� ������ ��ȣ�� �Է��� �ּ���\n\n ");
	printf("                   -> ");
	int choice;
	scanf("%d", &choice);
	return choice;
}
int menu2() {
	printf("\n================ < �� �� �� �� > =================");
	printf("\n\n                 (�б� -> ��â��)\n\n");
	printf("\n\n  1. �Էµ� �ð����� ���� ����� ���� �ð� ����\n\n");
	printf("  2. ���� ��ü �ð�ǥ ����ϱ� \n\n");
	printf("  3. ���� \n\n\n");
	printf("==================================================\n\n");
	printf("       ���ϴ� ������ ��ȣ�� �Է��� �ּ���\n\n ");
	printf("                   -> ");
	int choice;
	scanf("%d", &choice);
	return choice;
}
int get_trans_time(void) {    //�ð��� ���� �Է¹ް� �ð��� *60�� �ϰ� ���� ���� ��ȯ�ϴ� �Լ�
	printf("\n\n\n      �ð��� �Է��ϼ��� (�� ��) : ");
	int h, m, key;
	scanf("%d %d", &h, &m);  //�ð��� ���� ����� ����
	return key = h * 60 + m;
}
void search_bus(int list[], int n, int key)  //���� ����� ������ �� ��° �迭���� ����Ž���ϴ� �Լ�
{
	int i = 0;
	int o_key = key; // ���� Ű�� o_key�� �����Ѵ�
	while (list[i] != key)
	{
		for (i = 0; i < n; i++) { //n(SIZE)���� �迭�� ��
			if (key == list[i]) { //Ű�� list[i]�� ������ ��� �� ����
				printf("\n\n        ���� ����� ������ %d�� %d���Դϴ�\n\n", list[i] / 60, list[i] % 60);
				printf("           ��� �ð��� %d�ð� %d���Դϴ�\n\n\n\n", (key - o_key) / 60, (key - o_key) % 60);
				return 0;
			}
		}
		key = key + 1; //���� ����� list[i]�� ��ã���� key�� 1�� ����
		if (key > 14400) { //Ű�� 24*60�� �Ѿ�� �ð� ���� ��� �� ����
			printf("\n\n           �߸��� �ð��� �ԷµǾ����ϴ�\n\n");
			printf("              ����â�� ������մϴ�\n\n");
			Sleep(1500);
			system("cls");
			return 0;
		}
	}
}
void count(int x, int y) //�г���ȯ ���� ��ġ�� ����ϴ� �Լ�
{
	if (x >= y && y <= x + 2)
		printf("\n\n     �Էµ� �ð��� ���� ��ġ�� ��â���Դϴ�\n");
	else if (x + 3 == y)
		printf("\n\n     �Էµ� �ð��� ���� ��ġ�� �Ĺ��Դϴ�\n");
	else if (x + 4 == y)
		printf("\n\n     �Էµ� �ð��� ���� ��ġ�� �⼳ 3���Դϴ�\n");
	else if (x + 5 == y)
		printf("\n\n     �Էµ� �ð��� ���� ��ġ�� �⼳ 2���Դϴ�\n");
	else if (x + 6 == y)
		printf("\n\n�Էµ� �ð��� ���� ��ġ�� �⼳����߾ӵ������Դϴ�\n");
	else if (x + 7 == y)
		printf("\n\n     �Էµ� �ð��� ���� ��ġ�� �����Դϴ�\n");
	else if (x + 8 >= y && y <= x + 12)
		printf("\n\n     �Էµ� �ð��� ���� ��ġ�� ��â���Դϴ�\n");
	else
		printf("\n\n        ���� ���� �г���ȯ ������ �����ϴ�\n\n");
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
		printf("\n      ������ �ݾ��� �Է��� �ּ��� (<=10����)");
		printf("\n\n                    -> ");
		scanf("%d", &input);
		if (input > 0 && input <= 100000) {
			u->cash += input;
			printf("\n\n              ���� ó���Ǿ����ϴ�\n\n");
			printf("=================================================\n");

			printf("\n          ���� ���� �ܾ��� %d���Դϴ�\n\n\n", u->cash);
			printf("              ����â�� ������մϴ�\n\n");
			Sleep(2000);
			system("cls");
			modify_profile(u);
			return 1;
		}
		else {
			printf("\n\n           �ùٸ��� ���� ���� ���Դϴ�\n");
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
		printf("         ���� �α����� �̷��� �����մϴ�.\n");
		printf("            ����� ������ �ҷ��ɴϴ�.\n");
		printf("-------------------------------------------------\n\n");
		load_profile(u);
		printf("            ������ �ݾ� >> %d\n", u->cash);
		printf("            ���ŵ� �¼� >> %d\n\n", u->num_ticket);

	}
	else if (nResult == -1)
	{
		printf("\n-------------------------------------------------\n");
		printf("      ���� �α����� �̷��� �������� �ʽ��ϴ�.\n");
		printf("             �ű� ����ڸ� �����մϴ�.\n");
		printf("-------------------------------------------------\n\n");

		id_forder = _mkdir(id);
		make_new_profile(u);
		u->cash = 0;
		u->num_ticket = 0;
		printf("            ������ �ݾ� >> %d\n", u->cash);
		printf("            ���ŵ� �¼� >> %d\n\n", u->num_ticket);
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
		printf("              ���Ű� �Ϸ�Ǿ����ϴ�\n");
		u->cash -= 6000;
		u->num_ticket++;


		modify_profile(u);
		GetDateTime(datetime);
		fprintf(fp, "%s,%d,%d,%s\n", datetime, reservation_day, seat, bus_cate);
		printf("                �ܾ��� %d���Դϴ�\n", u->cash);
		printf("              ����â�� ������մϴ�\n\n");
		printf("-------------------------------------------------\n");
		Sleep(2000);
		system("cls");
	}
	else {
		printf("\n                �ܾ��� �����մϴ�\n");
		printf("              ����â�� ������մϴ�\n\n");
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
	printf("\n         �� %d���� ���� ������ �����մϴ�\n", u->num_ticket);
	printf("\n-------------------------------------------------\n\n");

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
	printf("=================================================\n\n");
	printf("  1. �ݾ� ����\n\n");
	printf("  2. ���� ���� Ȯ��\n\n");
	printf("  3. ���� ���� ����\n\n");
	printf("  4. ���� ���� ��ġ Ȯ��\n\n");
	printf("  5. ����\n\n");
	printf("=================================================\n\n");
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
	scanf("%s", &name);
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

int main(void)   //�����Լ� ����
{
	system("mode con:cols=50 lines=40");   //�ܼ�â ũ�� ����
	struct user u;
	int menu_input = 0;
	struct service ser;
	ser.bus_type = 0; ser.shuttle = 0; ser.commute = 0;   //���� ���� �� �ʱ�ȭ
	while (1) {  //���ѷ��� ���� (���� ȭ���� ���� ��ȣ �Է� �ܿ��� ������� �ʵ��� �ϱ� ����)
		print_firstp();   //���� ȭ�� ��� �Լ�
		scanf_s("%d", &ser.bus_type);

		if (ser.bus_type == 1)  //��Ʋ���� ��ȣ �Է� ��
		{
			while (1)   //���ѷ��� ���� (��Ʋ���� ȭ���� ���� ��ȣ �Է� �ܿ��� ������� �ʵ��� �ϱ� ����)
			{
				system("cls");
				print_shuttle();  //��Ʋ���� ȭ�� ��� �Լ�
				scanf_s("%d", &ser.shuttle);    //��Ʋ �޴����� ��ȣ�� �Է� ����

				switch (ser.shuttle)
				{
				case 1:   //���� ��ȣ �Է� ��
					system("cls");
					FILE* fp = NULL;
					int list[10000] = { 0 };
					int c;
					while (1)   //���ѷ��� ���� (���� �޴� ȭ���� ���� ��ȣ �Է� �ܿ��� ������� �ʵ��� �ϱ� ����)
					{
						fp = fopen("bus.txt", "r");
						int save_size;
						for (save_size = 0; !feof(fp); save_size++) // ������ ���� ������ list�� ����
						{
							fscanf(fp, "%d", &list[save_size]);
						}
						int SIZE = save_size - 1; //save_size�� 0�� �߰��Ǳ� ������ 
						fclose(fp);               //���� ����� ������ ���� save_size���� 1�� �� ��

						switch (menu1())
						{
						case 1:   //���� ����� ���� �ð� ã�� ��ȣ �Է� ��
							RemoveScrollbar(); //�ܼ�â�� ��ũ�ѹ� ���� �Լ�
							system("cls");
							printf("\n================ < �� �� �� �� > =================");
							printf("\n\n       ���� ����� ������ �ð��� ����մϴ�\n");
							int h, m, key;
							key = get_trans_time();  //�ð��� ���� �Է¹ް� �ð��� *60�� �ϰ� ���� ���� ��ȯ�ϴ� �Լ�
							search_bus(list, SIZE, key);  //���� ����� ������ �� ��° �迭���� ���� Ž���ϴ� �Լ�
							break;
						case 2:   //���� ��ü �ð�ǥ ��ȣ �Է� ��
							RemoveScrollbar();
							printf("\n\n");
							fp = fopen("bustime.txt", "r");
							while ((c = fgetc(fp)) != EOF) //���Ͽ��� ���ڸ� �о� c�� ����
								putchar(c);   //����� ���ڵ��� ���
							fclose(fp);
							HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //�ܼ�â�� ��ũ���� �ӽ������� ����
							COORD bufferSize = { 50, 300 };
							SetConsoleScreenBufferSize(hConsole, bufferSize);
							printf("\n\n\n");
							break;
						case 3:   //���� ��ġ ��ȣ �Է� ��
							RemoveScrollbar();
							system("cls");
							printf("\n================ < �� �� �� �� > =================");
							printf("\n\n       �Է��� �ð��� ���� ��ġ�� ����մϴ�\n");
							printf("              ( ���� 8~11�� ���� )\n");
							int a, key2;
							key2 = get_trans_time();//�ð��� ���� �Է¹ް� �ð��� *60�� �ϰ� ���� ���� ��ȯ�ϴ� �Լ�
							if (key2 >= 479 && key2 <= 512) {
								a = 479;
								count(a, key2);   //�г���ȯ ���� ��ġ ��� �Լ�
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
								printf("\n\n        ���� ���� �г���ȯ ������ �����ϴ�\n\n\n");
							Sleep(2000);   //2�� ����
							system("cls");   //ȭ�� ����
							break;
						case 4:  //���� ��ȣ �Է� ��
							RemoveScrollbar();
							system("cls");
							printf("\n\n\n\n              ���α׷��� �����մϴ�\n\n\n");
							Sleep(1000);   //1�� ����
							exit(1);   //���α׷��� ������ ����
						default:  //���� ���ڸ� �Է� �޾��� ��
							RemoveScrollbar();
							system("cls");
							printf("\n\n\n             �߸��� ��ȣ�� �ԷµǾ����ϴ�\n\n\n");
							printf("              ����â�� ������մϴ�\n\n");
							Sleep(1500);   //1.5�� ����
							system("cls");  //ȭ�� ����
							continue;  //�޴� ���� ȭ������ ���ư��� ����
						}
					}
				case 2:   //���� ��ȣ �Է� ��
					system("cls");
					FILE* fpd = NULL;
					int listd[10000] = { 0 };
					while (1)  //���ѷ��� ���� (���� �޴� ȭ���� ���� ��ȣ �Է� �ܿ��� ������� �ʵ��� �ϱ� ����)
					{
						fpd = fopen("buss.txt", "r");
						int save_size;
						for (save_size = 0; !feof(fpd); save_size++) //������ ���� ������ list�� ����
						{
							fscanf(fpd, "%d", &listd[save_size]);
						}
						int SIZE = save_size - 1; //save_size�� 0�� �߰��Ǳ� ������ 
						fclose(fpd);              //���� ����� ������ ���� save_size���� 1�� ��

						switch (menu2())
						{
						case 1:   //���� ����� ���� �ð� ã�� ��ȣ �Է� ��
							RemoveScrollbar(); //�ܼ�â�� ��ũ�ѹ� ����
							system("cls");
							printf("\n================ < �� �� �� �� > =================");
							printf("\n\n       ���� ����� ������ �ð��� ����մϴ�\n");
							int h, m, key;
							key = get_trans_time();  //�ð��� ���� �Է¹ް� �ð��� *60�� �ϰ� ���� ���� ��ȯ�ϴ� �Լ�
							search_bus(listd, SIZE, key);  //���� ����� ������ ���° �迭���� ����Ž���ϴ� �Լ�
							break;
						case 2:   //���� ��ü �ð�ǥ ��ȣ �Է� ��
							RemoveScrollbar();
							printf("\n\n");
							fpd = fopen("bustime_down.txt", "r");
							while ((c = fgetc(fpd)) != EOF) //���Ͽ��� ���ڸ� �о� c�� ����
								putchar(c);   //����� ���ڵ��� ���
							fclose(fpd);
							HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //�ܼ�â�� ��ũ���� �ӽ������� ����
							COORD bufferSize = { 50, 300 };
							SetConsoleScreenBufferSize(hConsole, bufferSize);
							printf("\n\n\n");
							break;
						case 3:   //���� ��ȣ �Է� ��
							RemoveScrollbar(); // �ܼ�â�� ��ũ�ѹ� ����
							system("cls");
							printf("\n\n\n\n              ���α׷��� �����մϴ�\n\n\n");
							Sleep(1000);   //1�� ����
							exit(1);   //���α׷��� ������ ����
							break;
						default:   //���� ���� �Է� ��
							RemoveScrollbar(); // �ܼ�â�� ��ũ�ѹ� ����
							system("cls");
							printf("\n\n\n             �߸��� ��ȣ�� �ԷµǾ����ϴ�\n\n\n");
							printf("              ����â�� ������մϴ�\n\n");
							Sleep(1500);   //1.5�� ����
							system("cls");   //ȭ�� ����
							continue;   //�޴� ���� â���� ���ư��� ����
						}
					}
				case 3:   //���� ��ȣ �Է� ��
					system("cls");
					printf("\n\n\n\n              ���α׷��� �����մϴ�\n\n\n");
					Sleep(1000);   //1�� ����
					exit(1);   //���α׷��� ������ ����
					break;
				default:
					system("cls");
					printf("\n\n\n             �߸��� ��ȣ�� �ԷµǾ����ϴ�\n\n\n");
					printf("              ����â�� ������մϴ�\n\n");
					Sleep(1500);   //1.5�� ����
					system("cls");   //ȭ�� ����
					continue;   //�޴� ���� â���� ������ ����
				}
			}

		}
		else if (ser.bus_type == 2) //���й��� ��ȣ �Է� ��
		{
			system("cls");
			print_commute();  //���й��� ȭ�� ��� �Լ�
			scanf_s("%d", &ser.commute);
			switch (ser.commute)
			{
			case 1:   //�α��� ���� ��ȣ �Է� ��
				system("cls");
				if (login(&u) == 1) {
					while (1) //���ѷ��� ����
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
								printf("\n          ��ȸ ������ �������� �ʽ��ϴ�\n");
								printf("              ����â�� ������մϴ�\n\n");
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
							printf("\n\n\n\n              ���α׷��� �����մϴ�\n\n\n");
							Sleep(1000);
							exit(1);
							break;
						default:
							system("cls");
							printf("\n\n            �߸��� ��ȣ�� �ԷµǾ����ϴ�\n\n");
							printf("              ����â�� ������մϴ�\n\n");
							Sleep(1500);
							system("cls");
							continue;
						}
					}
				}
				else {
					printf("              ����ȭ���� ������մϴ�\n\n");
					Sleep(1500);
					system("cls");
				}
				break;
			case 2:   //���� ��ȣ �Է� ��
				system("cls");
				printf("\n\n\n\n              ���α׷��� �����մϴ�\n\n\n");
				Sleep(1000);
				exit(1);
				break;
			default:   //���� ��ȣ �Է� ��
				system("cls");
				printf("\n\n\n             �߸��� ��ȣ�� �ԷµǾ����ϴ�\n\n\n");
				printf("              ����ȭ���� ������մϴ�\n\n");
				Sleep(1500);   //1.5�� ����
				system("cls");   //ȭ�� ����
				continue;   //�޴� ���� â���� ���ư��� ����
			}
		}
		else if (ser.bus_type == 3)  //���� ��ȣ �Է� ��
		{
			system("cls");
			printf("\n\n\n\n              ���α׷��� �����մϴ�\n\n\n");
			Sleep(1000);  //1�� ����
			exit(1);  //���α׷��� ������ ����
			break;
		}
		else    //���� ��ȣ �Է� ��
		{
			system("cls");
			printf("\n\n            �߸��� ��ȣ�� �ԷµǾ����ϴ�\n\n");
			printf("                  ������մϴ�\n\n\n");
			Sleep(1500);  //1.5�� ����
			system("cls");  //ȭ�� ����
			continue;   //�޴� ȭ������ ���ư��� ����
		}
	}
}