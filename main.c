
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
void print_shuttle() {
	printf("\n      =======================================\n");
	printf("                    ��  Ʋ  ��  ��  ");
	printf("\n      =======================================\n\n\n\n\n");
	printf("         1. ���� �ð� Ȯ��\n\n\n");
	printf("         2. ���� ��ġ Ȯ��\n\n\n");
	printf("         3. �ڷ� ���� \n\n\n");
	printf("         4. ����\n\n\n\n\n\n");
	printf("      ���ϴ� ������ ��ȣ�� �Է��� �ּ���\n\n");
	printf("                  -> ");
}
void print_commute() {
	printf("\n      =======================================\n");
	printf("                    ��  ��  ��  ��  ");
	printf("\n      =======================================\n\n\n\n\n");
	printf("         1. ȸ�� ���� Ȯ�� �� ����\n\n\n");
	printf("         2. ���� �ð�ǥ Ȯ��\n\n\n");
	printf("         3. ���� ����\n\n\n");
	printf("         4. ���й��� ��ġ Ȯ��\n\n\n");
	printf("         5. �ڷ� ����\n\n\n");
	printf("         6. ����\n\n\n\n\n\n");
	printf("      ���ϴ� ������ ��ȣ�� �Է��� �ּ���\n\n");
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
	while (1) {
		if (ser.bus_type == 1) {
			system("cls");
			print_shuttle();
			scanf_s("%d", &ser.shuttle);
			switch (ser.shuttle) {
			case 1:
				system("cls");
				/*�����ð�Ȯ���ڵ��ۼ�*/
			case 2:
				system("cls");
				/*������ġȮ���ڵ��ۼ�*/
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
				/*ȸ������Ȯ���ڵ��ۼ�*/
			case 2:
				system("cls");
				/*�����ð�ǥȮ���ڵ��ۼ�*/
			case 3:
				system("cls");
				/*���������ڵ��ۼ�*/
			case 4:
				system("cls");
				/*���й�����ġȮ���ڵ��ۼ�*/
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