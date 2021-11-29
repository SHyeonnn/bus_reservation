#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int menu() {   //셔틀(상행)버스 메뉴 선택 출력 함수
	printf("\n===================================================");
	printf("\n\n  1. 입력된 시간에서 가장 가까운 지하철 시간 보기\n\n");
	printf("  2. 종료 \n\n\n");
	printf("==================================================\n\n");
	printf("       원하는 서비스의 번호를 입력해 주세요\n\n ");
	printf("                  -> ");
	int choice;
	scanf("%d", &choice);
	return choice;
}
int get_trans_time(void) {    //시간과 분을 입력받고 시간에 *60을 하고 분을 더해 반환하는 함수
	printf("\n\n\n      시간을 입력하세요 (시 분) : ");
	int h, m, key;
	scanf("%d %d", &h, &m);  //시간과 분을 띄어쓰기로 구분
	return key = h * 60 + m;
}
void search_bus(int list[], int n, int key)  //가장 가까운 지하철시간이 몇 번째 배열인지 순차탐색하는 함수
{
	int i = 0;
	int o_key = key; // 원본 키를 o_key로 복사한다
	while (list[i] != key)
	{
		for (i = 0; i < n; i++) { //n(SIZE)까지 배열을 비교
			if (key == list[i]) { //키랑 list[i]가 같으면 출력 후 종료
				printf("\n\n        가장 가까운 지하철은 %d시 %d분입니다\n\n", list[i] / 60, list[i] % 60);
				printf("           대기 시간은 %d시간 %d분입니다\n\n\n\n", (key - o_key) / 60, (key - o_key) % 60);
				return 0;
			}
		}
		key = key + 1; //가장 가까운 list[i]를 못찾으면 key에 1을 합함
		if (key > 14400) { //키가 24*60을 넘어가면 시간 오류 출력 후 종료
			printf("시간 오류!");
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
		for (save_size = 0; !feof(fp); save_size++) // 파일이 끝날 때까지 list에 저장
		{
			fscanf(fp, "%d", &list[save_size]);
		}
		int SIZE = save_size - 1; //save_size는 0이 추가되기때문에 
		fclose(fp);               //실제 저장된 정수의 수는 save_size에서 1을 뺀 수

		switch (menu())
		{
		case 1:   //시간을 입력하고 가장 가까운 버스시간 찾기
			system("cls");
			printf("\n===============================================");
			printf("\n\n       가장 가까운 지하철의 시간을 출력합니다\n");
			int h, m, key;
			key = get_trans_time();  //시간과 분을 입력받고 시간에 *60을 하고 분을 더해 반환하는 함수
			search_bus(list, SIZE, key);  //가장 가까운 버스가 몇 번째 배열인지 순차탐색하는 함수
			break;
		case 2:
			exit(1);
			break;
		default:
			break;
		}
	}
}