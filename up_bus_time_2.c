#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
	FILE* fp = NULL;
	int c;
	fp = fopen("bustime.txt", "r"); //bustime파일을 읽기모드로 열기

	if (fp == NULL)
	{
		printf("파일 열기 실패. \n");
	}
	else
	{
		printf("파일 열기 성공. \n");
	}
	while ((c = fgetc(fp)) != EOF) //지금 열려있는 파일에서 문자하나를 읽어 c에 저장
	{
		putchar(c); 
	}

	fclose(fp);
	return 0;
}