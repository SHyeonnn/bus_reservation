#include<stdio.h>
#include<windows.h>
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
	printf("         1. ���� (��â->�б�)\n\n\n");
	printf("         2. ���� (�б�->��â)\n\n\n");
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

struct service {   //������� �޴��� ���� �������� �����ϱ� ���� ����ü
	int bus_type; //���� ���� ����
	int shuttle;  //��Ʋ ���� ���� ����ȭ�� ���� ����
	int commute;  //���� ���� ���� ����ȭ�� ���� ����
};
int main(void) {
	system("mode con:cols=50 lines=40");   //�ܼ�â ũ�� ����
	struct service ser;
	ser.bus_type = 0; ser.shuttle = 0; ser.commute = 0;
	print_firstp();
	scanf_s("%d", &ser.bus_type);
	if (ser.bus_type == 1) {   //��Ʋ���� ��ȣ �Է� ��
		system("cls");
		print_shuttle();
		scanf_s("%d", &ser.shuttle);
		switch (ser.shuttle) {
		case 1:   //���� ��ȣ �Է� ��
			system("cls");
			/*���� �ڵ� �ۼ�*/
		case 2:   //���� ��ȣ �Է� ��
			system("cls");
			/*���� �ڵ� �ۼ�*/
		case 3:   //���� ��ȣ �Է� ��
			system("cls");
			exit(1);
			system("cls");
			break;
		}
	}
	else if (ser.bus_type == 2) {   //���й��� ��ȣ �Է� ��
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
			exit(1);
			system("cls");
			break;
		}
	}
	else if (ser.bus_type == 3) {   //���� ��ȣ �Է� ��
		system("cls");
		exit(1);
		system("cls");
	}
}