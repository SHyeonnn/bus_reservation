#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<windows.h>

int main(void)
{
	system("mode con:cols=50 lines=40");
	FILE* fp1 = NULL;
	char* name[2] = { "지하철 시간표","버스 시간" };
	int subway_h, subway_m;
	int bus_h = 0, bus_m = 0;
	if ((fp1 = fopen("bus.txt", "w")) == NULL)
	{
		printf("잘못된 입력1\n");
		exit(1);
	} 
	printf("지하철 시간 입력 시, 오후 시간은 12를 더해 입력해 주세요.\n");
	printf("지하철 하차 시간을 입력해주세요 (시 분) -> ");
	scanf("%d %d", &subway_h, &subway_m);
	bus_h = subway_h;
	bus_m = subway_m + 10; //분으로
	// 50분 이상일경우 시간 +1 해야하는거 생각하기
	if (bus_m >= 60) {
		bus_h++;
		bus_m -= 60;
	}
	printf("탈 수 있는 버스는 %d시 %d분에 출발하는 버스입니다.\n", bus_h, bus_m);

	if (bus_h < 11) {
		printf("지금 운행하는 버스는 학내순환 버스입니다.\n");
	}
	if (bus_h >= 11) {
		printf("지금 운행하는 버스는 직행 버스입니다. \n");
	}

	fclose(fp1);

	if ((fp1 = fopen("bus.txt", "r")) == NULL)
	{
		printf("잘못된 입력1\n");
		exit(1);
	}
	
	fclose(fp1);

	return 0;
}