#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
	FILE* fp = NULL;
	int c;
	fp = fopen("bustime.txt", "r"); //bustime������ �б���� ����

	if (fp == NULL)
	{
		printf("���� ���� ����. \n");
	}
	else
	{
		printf("���� ���� ����. \n");
	}
	while ((c = fgetc(fp)) != EOF) //���� �����ִ� ���Ͽ��� �����ϳ��� �о� c�� ����
	{
		putchar(c); 
	}

	fclose(fp);
	return 0;
}