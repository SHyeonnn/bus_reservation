#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int menu() {   //��Ʋ(����)���� �޴� ���� ��� �Լ�
	printf("\n===================================================");
	printf("\n\n  1. �Էµ� �ð����� ���� ����� ����ö �ð� ����\n\n");
	printf("  2. ���� \n\n\n");
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
void search_bus(int list[], int n, int key)  //���� ����� ����ö�ð��� �� ��° �迭���� ����Ž���ϴ� �Լ�
{
	int i = 0;
	int o_key = key; // ���� Ű�� o_key�� �����Ѵ�
	while (list[i] != key)
	{
		for (i = 0; i < n; i++) { //n(SIZE)���� �迭�� ��
			if (key == list[i]) { //Ű�� list[i]�� ������ ��� �� ����
				printf("\n\n        ���� ����� ����ö�� %d�� %d���Դϴ�\n\n", list[i] / 60, list[i] % 60);
				printf("           ��� �ð��� %d�ð� %d���Դϴ�\n\n\n\n", (key - o_key) / 60, (key - o_key) % 60);
				return 0;
			}
		}
		key = key + 1; //���� ����� list[i]�� ��ã���� key�� 1�� ����
		if (key > 14400) { //Ű�� 24*60�� �Ѿ�� �ð� ���� ��� �� ����
			printf("�ð� ����!");
			return 0;
		}
	}
}
int main(void)
{
	FILE* fp = NULL;
	int list[10000] = { 0 };
	while (1)
	{
		fp = fopen("subway.txt", "r");
		int save_size;
		for (save_size = 0; !feof(fp); save_size++) // ������ ���� ������ list�� ����
		{
			fscanf(fp, "%d", &list[save_size]);
		}
		int SIZE = save_size - 1; //save_size�� 0�� �߰��Ǳ⶧���� 
		fclose(fp);               //���� ����� ������ ���� save_size���� 1�� �� ��

		switch (menu())
		{
		case 1:   //�ð��� �Է��ϰ� ���� ����� �����ð� ã��
			system("cls");
			printf("\n===============================================");
			printf("\n\n       ���� ����� ����ö�� �ð��� ����մϴ�\n");
			int h, m, key;
			key = get_trans_time();  //�ð��� ���� �Է¹ް� �ð��� *60�� �ϰ� ���� ���� ��ȯ�ϴ� �Լ�
			search_bus(list, SIZE, key);  //���� ����� ������ �� ��° �迭���� ����Ž���ϴ� �Լ�
			break;
		case 2:
			exit(1);
			break;
		default:
			break;
		}
	}
}