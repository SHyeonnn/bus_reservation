#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int menu() {   //��Ʋ(����)���� �޴� ���� ��� �Լ�
	printf("\n================ < �� �� �� �� > =================");
	printf("\n\n                 (��â�� -> �б�)\n\n");
	printf("\n\n  1. �Էµ� �ð����� ���� ����� ���� �ð� ����\n\n");
	printf("  2. ���� ��ü �ð�ǥ ����ϱ� \n\n");
	printf("  3. ���� ��ġ �˻��ϱ�\n\n");
	printf("  4. ���� \n\n\n");
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
			printf("�ð� ����!");
			return 0;
		}
	}
}
void count(a, key) //�г����� ���� ��ġ�� ����ϴ� �Լ�
{
	if (a >= key && key <= a + 2)
		printf("\n\n     �Էµ� �ð��� ���� ��ġ�� ��â���Դϴ�\n");
	else if (key == a + 3)
		printf("\n\n     �Էµ� �ð��� ���� ��ġ�� �Ĺ��Դϴ�\n");
	else if (key == a + 4)
		printf("\n\n     �Էµ� �ð��� ���� ��ġ�� �⼳ 3���Դϴ�\n");
	else if (key == a + 5 )
		printf("\n\n     �Էµ� �ð��� ���� ��ġ�� �⼳ 2���Դϴ�\n");
	else if (key == a + 6)
		printf("\n\n�Էµ� �ð��� ���� ��ġ�� �⼳����߾ӵ������Դϴ�\n");
	else if (key == a + 7 )
		printf("\n\n     �Էµ� �ð��� ���� ��ġ�� �����Դϴ�\n");
	else if (a + 8 >= key && key <= a + 12)
		printf("\n\n     �Էµ� �ð��� ���� ��ġ�� ��â���Դϴ�\n");
	else
		printf("\n\n      �������� �г����� ������ �����ϴ�\n");
}
int main(void)
{
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

		switch (menu())
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
			fclose(fp); //�����ݱ�
			break;
		case 3:
			system("cls");
			printf("\n================ < �� �� �� �� > =================");
			printf("\n\n �Է��� �ð��� ���� ��ġ�� ����մϴ�( ����8~11�� ���� )\n");
			int a;
			key = get_trans_time();//�ð��� ���� �Է¹ް� �ð��� *60�� �ϰ� ���� ���� ��ȯ�ϴ� �Լ�
			if (key <= 478 || key >= 466)
				printf("\n\n      �������� �г����� ������ �����ϴ�\n");
			else if (key >= 479 && key <= 512) {
				a = 479;
				count(a, key);
			}
			else if (key >= 513 && key <= 534) {
				a = 513;
				count(a, key);
			}
			else if (key >= 535 && key <= 572) {
				a = 535;
				count(a, key);
			}
			else if (key >= 573 && key <= 606) {
				a = 573;
				count(a, key);
			}
			else if (key >= 607 && key <= 624) {
				a = 607;
				count(a, key);
			}
			else if (key >= 625 && key <= 652) {
				a = 625;
				count(a, key);
			}
			else if (key >= 653 && key <= 665) {
				a = 653;
				count(a, key);
			}
			break;

		case 4:
			exit(1);
			break;
		default:
			break;
		}
	}
}