#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<windows.h>

int main(void)
{
	system("mode con:cols=50 lines=40");
	FILE* fp1 = NULL;
	char* name[2] = { "����ö �ð�ǥ","���� �ð�" };
	int subway_h, subway_m;
	int bus_h = 0, bus_m = 0;
	if ((fp1 = fopen("bus.txt", "w")) == NULL)
	{
		printf("�߸��� �Է�1\n");
		exit(1);
	} 
	printf("����ö �ð� �Է� ��, ���� �ð��� 12�� ���� �Է��� �ּ���.\n");
	printf("����ö ���� �ð��� �Է����ּ��� (�� ��) -> ");
	scanf("%d %d", &subway_h, &subway_m);
	bus_h = subway_h;
	bus_m = subway_m + 10; //������
	// 50�� �̻��ϰ�� �ð� +1 �ؾ��ϴ°� �����ϱ�
	if (bus_m >= 60) {
		bus_h++;
		bus_m -= 60;
	}
	printf("Ż �� �ִ� ������ %d�� %d�п� ����ϴ� �����Դϴ�.\n", bus_h, bus_m);

	if (bus_h < 11) {
		printf("���� �����ϴ� ������ �г���ȯ �����Դϴ�.\n");
	}
	if (bus_h >= 11) {
		printf("���� �����ϴ� ������ ���� �����Դϴ�. \n");
	}

	fclose(fp1);

	if ((fp1 = fopen("bus.txt", "r")) == NULL)
	{
		printf("�߸��� �Է�1\n");
		exit(1);
	}
	
	fclose(fp1);

	return 0;
}