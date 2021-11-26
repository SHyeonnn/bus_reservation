#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int menu();
void search_bus(int list[], int n, int key);
int get_trans_time(void);
int main(void)
{
	FILE *fp = NULL;
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
		fclose(fp);               //���� ����� ������ ���� save_size���� 1�� ����

		switch (menu())
		{
		case 1:   //�ð��� �Է��ϰ� ���� ����� �����ð� ã��
			printf("���� �ð� ã��\n");
			int h, m, key;
			key = get_trans_time();  // �� �Լ��� �ð��� ���� �Է¹ް� �ð��� *60�� �ϰ� ���� ���� ��ȯ�ϴ� �Լ�
			search_bus(list, SIZE, key);  // �� �Լ��� ���� ����� ������ ���° �迭���� ����Ž���ϴ� �Լ�
			break;
		case 2:
			fp = fopen("bus.txt", "a+"); //���� ����
			for (int i = 0; i < SIZE; i++)
			{
				printf("%d�� %d ��\n", list[i] / 60, list[i] % 60); //����Ʈ�� �����ŭ ���
			}
			fclose(fp); //�����ݱ�
			break;
		case 3:
			exit(1);
			break;
		default:
			break;
		}
	}
}
int menu() {
	printf("===============================================\n\n");
	printf(" 1 �Էµ� �ð����� ���� ����� �����ð� ����\n");
	printf(" 2 ���� �ð�ǥ ����ϱ� \n");
	printf(" 3 ���� \n\n");
	printf("===============================================\n");
	printf("���� : ");
	int choice;
	scanf("%d", &choice);
	return choice;
}
int get_trans_time(void) {    //�ð��� ���� �Է¹ް� �ð��� *60�� �ϰ� ���� ���� ��ȯ�ϴ� �Լ�
	printf("�ð��� �Է��ϼ��� :  �� ��\b\b\b\b\b\b\b");
	int h, m, key;
	scanf("%d %d", &h, &m);  //�ð��� ���� ���� �ϳ��� ����
	return key = h * 60 + m;
}
void search_bus(int list[], int n, int key)  // ���� ����� ������ ���° �迭���� ����Ž���ϴ� �Լ�
{
	int i = 0;
	int o_key = key; // ���� Ű�� o_key�� �����Ѵ�
	while (list[i] != key)
	{
		for (i = 0; i < n; i++) { //n(SIZE) ���� �迭�� ���Ѵ�
			if (key == list[i]) { //Ű�� list[i]�� ������ ����ϰ� ����
				printf("���� ����� ������ %d�� %d���Դϴ�\n\n", list[i] / 60, list[i] % 60);
				printf("��� �ð��� %d�� %d ���Դϴ�\n", (key - o_key) / 60, (key - o_key) % 60);
				return 0;
			}
		}
		key = key + 1; //���� ����� list[i]�� ��ã���� key�� 1�� ���ϱ�
		if (key > 14400) { //Ű�� 24*60�� �Ѿ�� �ð� ���� ��� �� ����
			printf("�ð� ����!");
			return 0;
		}
	}
}