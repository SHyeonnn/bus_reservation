#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#pragma warning(disable: 4996)
void go_school();
int main() {
    int total = 0;
    int now = 0;
    int now_case = 0;
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    total = tm.tm_hour * 60 + tm.tm_min;
    printf("현재시간: %d-%d-%d %d:%d:%d\n",
        tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
        tm.tm_hour, tm.tm_min, tm.tm_sec);

    if (total >= 390 && total <= 450) {
        printf("등교 통학 버스 운행 중입니다.\n");
        printf("----------------------------\n");
        now = total - 390;
        now_case = (int)now / 10;
        switch (now_case)
        {
        case 0:
            printf("주안역 1번 출구\n");
            break;
        case 1:
            printf("문학IC에서 '주안, 문학경기장' 방면으로 주행 중\n");

            break;
        case 2:
            printf("월곶분기점에서 '인천' 방면으로 왼쪽 도로 주행 중\n");

            break;
        case 3:
            printf("서평택분기점에서 '서울, 발안' 방면으로 오른쪽 방향\n");

            break;
        case 4:
            printf("청북IC에서 '청북IC' 방면으로 오른쪽 고속도로 진입 중\n");

            break;
        case 5:
            printf("읍내교차로에서 '아산, 아산방조제, 공주' 방면으로 오른쪽 방향\n");

            break;
        case 6:
            printf("순천향대학교 후문\n");

            break;
        default:
            break;
        }

    }
    else if (total <= 1170 && total >= 1110) {
        printf("하교 통학 버스 운행 중입니다.\n");
        printf("----------------------------\n");
        total = tm.tm_hour * 60 + tm.tm_min;
        now = total - 1110;
        now_case = (int)now / 10;
        switch (now_case)
        {
        case 0:
            printf("순천향대학교 후문\n");
            break;
        case 1:
            printf("읍내교차로에서 '아산, 아산방조제, 공주' 방면으로 오른쪽 방향\n");

            break;
        case 2:
            printf("청북IC에서 '청북IC' 방면으로 오른쪽 고속도로 진입 중\n");

            break;
        case 3:
            printf("서평택분기점에서 '서울, 발안' 방면으로 오른쪽 방향\n");

            break;
        case 4:
            printf("월곶분기점에서 '인천' 방면으로 왼쪽 도로 주행 중\n");

            break;
        case 5:
            printf("문학IC에서 '주안, 문학경기장' 방면으로 주행 중\n");

            break;
        case 6:
            printf("주안역 1번 출구\n");

            break;
        default:
            break;
        }
    }
    else {
        printf("운행시간이 아닙니다.\n");
    }
    return 0;
}