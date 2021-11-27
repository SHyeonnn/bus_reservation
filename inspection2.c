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
		printf("-------------------------------------------------\n");
		printf("������ �ݾ��� �Է��ϼ���. (<=10����) : ");
		scanf("%d", &input);
		if (input > 0 && input <= 100000) {
			u->cash += input;
			printf("\n���� ó���Ǿ����ϴ�.\n");
			printf("-------------------------------------------------\n\n");

			printf("     ���� ���� �ܾ��� %d���Դϴ�\n", u->cash);
			modify_profile(u);
			return 1;
		}
		else {
			printf("�ùٸ��� ���� ���� ���Դϴ�\n");
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
		printf("������ �ݾ� : %d\n", u->cash);
		printf("���ŵ� �¼� : %d\n", u->num_ticket);

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
		printf("������ �ݾ� : %d\n", u->cash);
		printf("���ŵ� �¼� : %d\n\n", u->num_ticket);
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
		printf("\n      �����Ϸ��� ������ ��¥�� �Է��� �ּ��� \n      (ex>20211126)\n         -> ");
		scanf("%d", &reservation_day);
		fflush(stdin);
		printf("      ���� ������ �Է��� �ּ��� (� or �ϱ�) \n             -> ");
		scanf("%s", bus_cate);
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

			printf("�¼��� ������ �ּ��� : ");
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
			printf("�¼��� ������ �ּ��� : ");
			scanf("%d", &seat);
			if (bus_seat[seat] == 1) {
				printf("���� �Ұ��� �ڸ��Դϴ�.\n");
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
		printf("-------------------------------------------------\n");
		printf("���Ű� �Ϸ�Ǿ����ϴ�.\n");
		u->cash -= 6000;
		u->num_ticket++;

		modify_profile(u);
		GetDateTime(datetime);
		fprintf(fp, "%s,%d,%d,%s\n", datetime, reservation_day, seat, bus_cate);
		printf("�ܾ��� %d���Դϴ�.\n", u->cash);
	}
	else {
		printf("�ܾ��� �����մϴ�.\n");
	}
	printf("-------------------------------------------------\n");
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
	printf("        �� %d���� ���� ������ �����մϴ�.\n", u->num_ticket);
	printf("-------------------------------------------------\n");
	if (fp != NULL)
	{
		while (total < u->num_ticket) {
			printf("%d�� ����\n", total + 1);
			fgets(str_tmp, MAX, fp);
			p = strtok(str_tmp, ",");
			if (count == 0) {
				printf("���� �Ͻ� : %s\n", p);
				p = strtok(NULL, ",");

				count++;
			}
			if (count == 1) {
				printf("ž�� �Ͻ� : %s\n", p);
				p = strtok(NULL, ",");

				count++;

			}
			if (count == 2) {
				printf("�¼� ��ȣ : %s\n", p);
				p = strtok(NULL, ",");

				count++;

			}
			if (count == 3) {
				printf("���� : %s\n", p);
				count = 0;
				printf("-------------------------------------------------\n");

			}
			total++;
		}
	}
}
int print_menu() {
	int input = 0;
	printf("\n-------------------------------------------------\n");
	printf(" 1. �ݾ� ����\n");
	printf(" 2. ���� ���� Ȯ��\n");
	printf(" 3. ���� ���� ����\n");
	printf(" 4. ���� ���� ��ġ Ȯ��\n");
	printf("-------------------------------------------------\n");
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
		printf("����� �Է� ������ �߸��Ǿ����ϴ�. ");
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
	printf("                  -> ");
}
void print_shuttle() {   //��Ʋ���� ȭ�� ��� �Լ�
	printf("\n      =======================================\n");
	printf("                    ��  Ʋ  ��  ��  ");
	printf("\n      =======================================\n\n\n\n\n");
	printf("         1. ���� (��â��->�б�)\n\n\n");
	printf("         2. ���� (�б�->��â��)\n\n\n");
	printf("         3. ����\n\n\n\n\n\n");
	printf("      ���ϴ� ������ ��ȣ�� �Է��� �ּ���\n\n");
	printf("                  -> ");
}
void print_commute() {   //���й��� ȭ�� ��� �Լ�
	printf("\n      =======================================\n");
	printf("                   ��  ��  ��  ��  ");
	printf("\n      =======================================\n\n\n\n\n");
	printf("         1. �\n\n\n");
	printf("         2. �ϱ�\n\n\n");
	printf("         3. ����\n\n\n\n\n\n");
	printf("      ���ϴ� ������ ��ȣ�� �Է��� �ּ���\n\n");
	printf("                  -> ");
}
void commute_updown() {   //���й��� � �� �ϱ� ���� ��� �Լ�
	printf("\n      =======================================\n");
	printf("                   ��  ��  ��  ��  ");
	printf("\n      =======================================\n\n\n\n\n");
	printf("         1. �Ȼ�\n\n\n");
	printf("         2. ��õ\n\n\n");
	printf("         3. �۳�\n\n\n");
	printf("         4. ����\n\n\n\n\n\n");
	printf("      ���ϴ� ž�� ������ ��ȣ�� �Է��� �ּ���\n\n");
	printf("                  -> ");
}
int menu1() {   //��Ʋ(����)���� �޴� ���� ��� �Լ�
	printf("\n================ < �� �� �� �� > =================");
	printf("\n\n                 (��â�� -> �б�)\n\n");
	printf("\n\n  1. �Էµ� �ð����� ���� ����� ���� �ð� ����\n\n");
	printf("  2. ���� ��ü �ð�ǥ ����ϱ� \n\n");
	printf("  3. ���� \n\n\n");
	printf("==================================================\n\n");
	printf("       ���ϴ� ������ ��ȣ�� �Է��� �ּ���\n\n ");
	printf("                  -> ");
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
	printf("                  -> ");
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

struct service {   //������� �޴��� ���� �������� �����ϱ� ���� ����ü
	int bus_type; //���� ���� ����
	int shuttle;  //��Ʋ ���� ���� ����ȭ�� ���� ����
	int commute;  //���� ���� ���� ����ȭ�� ���� ����
};
int main(void) {
	system("mode con:cols=50 lines=40");   //�ܼ�â ũ�� ����
	struct user u;
	int menu_input = 0;
	struct service ser;
	ser.bus_type = 0; ser.shuttle = 0; ser.commute = 0;
	while (1) {
		print_firstp();
		scanf_s("%d", &ser.bus_type);
		if (ser.bus_type == 1) {   //��Ʋ���� ��ȣ �Է� ��
			while (1) {
				system("cls");
				print_shuttle();
				scanf_s("%d", &ser.shuttle);
				switch (ser.shuttle) {
				case 1:   //���� ��ȣ �Է� ��
					system("cls");
					FILE* fp = NULL;
					int list[10000] = { 0 };
					while (1)
					{
						fp = fopen("bus.txt", "r");
						int save_size;
						for (save_size = 0; !feof(fp); save_size++) // ������ ���� ������ list�� ����
						{
							fscanf(fp, "%d", &list[save_size]);
						}
						int SIZE = save_size - 1; //save_size�� 0�� �߰��Ǳ⶧���� 
						fclose(fp);               //���� ����� ������ ���� save_size���� 1�� �� ��

						switch (menu1())
						{
						case 1:   //�ð��� �Է��ϰ� ���� ����� �����ð� ã��
							system("cls");
							printf("\n================ < �� �� �� �� > =================");
							printf("\n\n       ���� ����� ������ �ð��� ����մϴ�\n");
							int h, m, key;
							key = get_trans_time();  //�ð��� ���� �Է¹ް� �ð��� *60�� �ϰ� ���� ���� ��ȯ�ϴ� �Լ�
							search_bus(list, SIZE, key);  //���� ����� ������ �� ��° �迭���� ����Ž���ϴ� �Լ�
							break;
						case 2:
							fp = fopen("bus.txt", "a+"); //���� ����
							for (int i = 0; i < SIZE; i++)
							{
								printf("%d�� %d��\n", list[i] / 60, list[i] % 60); //����Ʈ�� �����ŭ ���
							}
							fclose(fp); //���� �ݱ�
							break;
						case 3:
							system("cls");
							printf("\n\n\n\n              ���α׷��� �����մϴ�\n\n\n");
							Sleep(1000);
							exit(1);
						default:
							system("cls");
							printf("\n\n\n             �߸��� ��ȣ�� �ԷµǾ����ϴ�\n\n\n");
							printf("              ����â�� ������մϴ�\n\n");
							Sleep(1500);
							system("cls");
							continue;
						}
					}
				case 2:   //���� ��ȣ �Է� ��
					system("cls");
					FILE* fpd = NULL;
					int listd[10000] = { 0 };
					while (1)
					{
						fpd = fopen("buss.txt", "r");
						int save_size;
						for (save_size = 0; !feof(fpd); save_size++) // ������ ���� ������ list�� ����
						{
							fscanf(fpd, "%d", &listd[save_size]);
						}
						int SIZE = save_size - 1; //save_size�� 0�� �߰��Ǳ� ������ 
						fclose(fpd);               //���� ����� ������ ���� save_size���� 1�� ��

						switch (menu2())
						{
						case 1:   //�ð��� �Է��ϰ� ���� ����� �����ð� ã��
							system("cls");
							printf("\n================ < �� �� �� �� > =================");
							printf("\n\n       ���� ����� ������ �ð��� ����մϴ�\n");
							int h, m, key;
							key = get_trans_time();  //�ð��� ���� �Է¹ް� �ð��� *60�� �ϰ� ���� ���� ��ȯ�ϴ� �Լ�
							search_bus(listd, SIZE, key);  //���� ����� ������ ���° �迭���� ����Ž���ϴ� �Լ�
							break;
						case 2:
							fpd = fopen("buss.txt", "a+"); //���� ����
							for (int i = 0; i < SIZE; i++)
							{
								printf("%d�� %d��\n", listd[i] / 60, listd[i] % 60); //����Ʈ�� �����ŭ ���
							}
							fclose(fpd); //���� �ݱ�
							break;
						case 3:
							system("cls");
							printf("\n\n\n\n              ���α׷��� �����մϴ�\n\n\n");
							Sleep(1000);
							exit(1);
							break;
						default:
							system("cls");
							printf("\n\n\n             �߸��� ��ȣ�� �ԷµǾ����ϴ�\n\n\n");
							printf("              ����â�� ������մϴ�\n\n");
							Sleep(1500);
							system("cls");
							continue;
						}
					}
				case 3:   //���� ��ȣ �Է� ��
					system("cls");
					printf("\n\n\n\n              ���α׷��� �����մϴ�\n\n\n");
					Sleep(1000);
					exit(1);
					break;
				default:
					system("cls");
					printf("\n\n\n             �߸��� ��ȣ�� �ԷµǾ����ϴ�\n\n\n");
					printf("              ����â�� ������մϴ�\n\n");
					Sleep(1500);
					system("cls");
					continue;
				}
			}

		}
		else if (ser.bus_type == 2) {   //���й��� ��ȣ �Է� ��
			while (1) {
				system("cls");
				print_commute();
				scanf_s("%d", &ser.commute);
				switch (ser.commute) {
				case 1:   //� ��ȣ �Է� ��
					system("cls");
					commute_updown();
					/*� �ڵ� �ۼ�*/
					break;
				case 2:   //�ϱ� ��ȣ �Է� ��
					system("cls");
					commute_updown();
					/*�ϱ� �ڵ� �ۼ�*/
					break;
				case 3:   //���� ��ȣ �Է� ��
					system("cls");
					printf("\n\n\n\n              ���α׷��� �����մϴ�\n\n\n");
					Sleep(1000);
					exit(1);
					break;
				default:
					system("cls");
					printf("\n\n\n             �߸��� ��ȣ�� �ԷµǾ����ϴ�\n\n\n");
					printf("              ����â�� ������մϴ�\n\n");
					Sleep(1500);
					system("cls");
					continue;
				}
			}
		}
		else if (ser.bus_type == 3) {   //���� ��ȣ �Է� ��
			system("cls");
			printf("\n\n\n\n              ���α׷��� �����մϴ�\n\n\n");
			Sleep(1000);
			exit(1);
			break;
		}
		else {
			system("cls");
			printf("\n\n            �߸��� ��ȣ�� �ԷµǾ����ϴ�\n\n");
			printf("                  ������մϴ�\n\n\n");
			Sleep(1500);
			system("cls");
			continue;
		}
	}
}