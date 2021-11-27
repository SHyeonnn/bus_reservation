#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int menu() {   //셔틀(상행)버스 메뉴 선택 출력 함수
	printf("\n================ < 상 행 버 스 > =================");
	printf("\n\n                 (신창역 -> 학교)\n\n");
	printf("\n\n  1. 입력된 시간에서 가장 가까운 버스 시간 보기\n\n");
	printf("  2. 버스 전체 시간표 출력하기 \n\n");
	printf("  3. 버스 위치 검색하기\n\n");
	printf("  4. 종료 \n\n\n");
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
void search_bus(int list[], int n, int key)  //가장 가까운 버스가 몇 번째 배열인지 순차탐색하는 함수
{
	int i = 0;
	int o_key = key; // 원본 키를 o_key로 복사한다
	while (list[i] != key)
	{
		for (i = 0; i < n; i++) { //n(SIZE)까지 배열을 비교
			if (key == list[i]) { //키랑 list[i]가 같으면 출력 후 종료
				printf("\n\n        가장 가까운 버스는 %d시 %d분입니다\n\n", list[i] / 60, list[i] % 60);
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
void count(a, key) //학내순한 버스 위치를 출력하는 함수
{
	if (a >= key && key <= a + 2)
		printf("\n\n     입력된 시간의 버스 위치는 신창역입니다\n");
	else if (key == a + 3)
		printf("\n\n     입력된 시간의 버스 위치는 후문입니다\n");
	else if (key == a + 4)
		printf("\n\n     입력된 시간의 버스 위치는 향설 3관입니다\n");
	else if (key == a + 5 )
		printf("\n\n     입력된 시간의 버스 위치는 향설 2관입니다\n");
	else if (key == a + 6)
		printf("\n\n입력된 시간의 버스 위치는 향설기념중앙도서관입니다\n");
	else if (key == a + 7 )
		printf("\n\n     입력된 시간의 버스 위치는 정문입니다\n");
	else if (a + 8 >= key && key <= a + 12)
		printf("\n\n     입력된 시간의 버스 위치는 신창역입니다\n");
	else
		printf("\n\n      운행중인 학내순한 버스가 없습니다\n");
}
int main(void)
{
	FILE* fp = NULL;
	int list[10000] = { 0 };
	while (1)
	{
		fp = fopen("bus.txt", "r");
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
			printf("\n================ < 상 행 버 스 > =================");
			printf("\n\n       가장 가까운 버스의 시간을 출력합니다\n");
			int h, m, key;
			key = get_trans_time();  //시간과 분을 입력받고 시간에 *60을 하고 분을 더해 반환하는 함수
			search_bus(list, SIZE, key);  //가장 가까운 버스가 몇 번째 배열인지 순차탐색하는 함수
			break;
		case 2:
			fp = fopen("bus.txt", "a+"); //폴더 오픈
			for (int i = 0; i < SIZE; i++)
			{
				printf("%d시 %d분\n", list[i] / 60, list[i] % 60); //리스트를 사이즈만큼 출력
			}
			fclose(fp); //폴더닫기
			break;
		case 3:
			system("cls");
			printf("\n================ < 상 행 버 스 > =================");
			printf("\n\n 입력한 시간의 버스 위치를 출력합니다( 오전8~11시 운행 )\n");
			int a;
			key = get_trans_time();//시간과 분을 입력받고 시간에 *60을 하고 분을 더해 반환하는 함수
			if (key <= 478 || key >= 466)
				printf("\n\n      운행중인 학내순한 버스가 없습니다\n");
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