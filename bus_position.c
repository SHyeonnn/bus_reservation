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
    printf("����ð�: %d-%d-%d %d:%d:%d\n",
        tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
        tm.tm_hour, tm.tm_min, tm.tm_sec);

    if (total >= 390 && total <= 450) {
        printf("� ���� ���� ���� ���Դϴ�.\n");
        printf("----------------------------\n");
        now = total - 390;
        now_case = (int)now / 10;
        switch (now_case)
        {
        case 0:
            printf("�־ȿ� 1�� �ⱸ\n");
            break;
        case 1:
            printf("����IC���� '�־�, ���а����' ������� ���� ��\n");

            break;
        case 2:
            printf("�����б������� '��õ' ������� ���� ���� ���� ��\n");

            break;
        case 3:
            printf("�����úб������� '����, �߾�' ������� ������ ����\n");

            break;
        case 4:
            printf("û��IC���� 'û��IC' ������� ������ ��ӵ��� ���� ��\n");

            break;
        case 5:
            printf("���������ο��� '�ƻ�, �ƻ������, ����' ������� ������ ����\n");

            break;
        case 6:
            printf("��õ����б� �Ĺ�\n");

            break;
        default:
            break;
        }

    }
    else if (total <= 1170 && total >= 1110) {
        printf("�ϱ� ���� ���� ���� ���Դϴ�.\n");
        printf("----------------------------\n");
        total = tm.tm_hour * 60 + tm.tm_min;
        now = total - 1110;
        now_case = (int)now / 10;
        switch (now_case)
        {
        case 0:
            printf("��õ����б� �Ĺ�\n");
            break;
        case 1:
            printf("���������ο��� '�ƻ�, �ƻ������, ����' ������� ������ ����\n");

            break;
        case 2:
            printf("û��IC���� 'û��IC' ������� ������ ��ӵ��� ���� ��\n");

            break;
        case 3:
            printf("�����úб������� '����, �߾�' ������� ������ ����\n");

            break;
        case 4:
            printf("�����б������� '��õ' ������� ���� ���� ���� ��\n");

            break;
        case 5:
            printf("����IC���� '�־�, ���а����' ������� ���� ��\n");

            break;
        case 6:
            printf("�־ȿ� 1�� �ⱸ\n");

            break;
        default:
            break;
        }
    }
    else {
        printf("����ð��� �ƴմϴ�.\n");
    }
    return 0;
}