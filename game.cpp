#include <stdio.h>
#include <string>
#include <string.h>
#include <locale.h>
#include <unistd.h>
#include <stdlib.h>
#include <cctype>


char allCity[1000][50];
int cityCount = -1;
char wordNow[50];
char answear[50];
void readAllCity(){
    FILE* data = fopen("db.txt", "r");
    do{
        cityCount++;
        fgets(allCity[cityCount], 255, data);
        
    }while (strlen(allCity[cityCount] ) > 0);
    
    fclose(data);
}

void readScore(){
    printf("\033c");
    char scoreRes[11];

    FILE* data = fopen("score.txt", "r");
    fgets(scoreRes, 10, data);
    if (strlen(scoreRes) > 0){
        printf("\n� ��� ���� ��� �����������\n");
    } else {
        printf("\n��� ��������� ��������� - %s\n", scoreRes);
    }
    
    fclose(data);
}

// ��������� ���������� �����
void getRandWord(){
    int number = rand()%100;
    strcpy(wordNow, allCity[number]);
    printf("���������: %s", wordNow);
}

// ����� ������� � ������
void helpOn(int help){
    if (help)
    printf("\n� ��� ������� ����� ��������� - ��� ����, ����� �������� ���������, �������� '������'\n");
    else 
    printf("\n� ��� ��������� ��������� - ���� �� ������!\n");
}

void compFirst(int help){
    helpOn(help);
    getRandWord();
    fscanf(stdin, "%[^\n]", answear);
    do {
        scanf("%s", answear);
    }while(strlen(answear) < 0 || strlen(answear) > 50);
    if (tolower(answear[0]) == tolower(wordNow[strlen(wordNow) - 2])){
        compFirst(help);
    } else{
        printf("\n� ����...\n");
    }
}

void youFirst(int help){
    helpOn(help);
    
    
}

void gameControl(){
     printf("\033c");
     printf("\n�� ������� ����!\n");
     sleep(1);
     int variant;
     int helpers = 0;
        printf("\n�������� �����?\n");
        do {
            printf("\n0 - ������ ��� ���\n1 - ������ ����� ���������\n2 - ��������� � ����\n");
            while (scanf("%d", &variant) != 1){
                while (getchar() != '\n');
                printf("\n������� ����� ����������:\n");
            }
        }while (variant < 0 || variant > 2);

    if (variant == 0 || variant == 1){
        do {
            printf("\n�������� ���������? (1 - ��, 0 - ���)\n");
            while (scanf("%d", &helpers) != 1){
                while (getchar() != '\n');
                printf("\n������� ����� ����������:\n");
            }
        }while (helpers < 0 || helpers > 1);
    }

    switch (variant)
    {
        case 0: {
            youFirst(helpers);
            break;
        }
        case 1: {
            compFirst(helpers);
            break;
        }
        case 2: {
            printf("\033c");
            return;
            break;
        }
    }
    gameControl();
}

void rights(){
            printf("\033c");
            sleep(1);
            printf("\n������� ���� ����� ������\n");
            sleep(2);
            printf("\n�� ������ �������� ����������� ������ - �������� '�������'\n");
            sleep(3);
            printf("\n����, ��� ������� ����� �������� - ����������� ������ ������ �������!\n");
            sleep(4);
            printf("\n����� ��������� �������� ���� �������, ������� ���������� � ��� �����, �� ������� ������������ ����� �����\n");
            sleep(2);
            printf("��������: '�������' - '������'\n");
            sleep(3);
            printf("\n������ �� ������ �������� �������, ������� ����� ��������� � ��� �����, � ������� ������������ ����� ����������\n");
             sleep(2);
            printf("��������: '�������' - '������' - '�����'\n");
            sleep(2);
            printf("\n� ��� �����\n");
            sleep(2);
            printf("\n��������� ���, ��� ������ ����� ���������\n");
            sleep(3);
            printf("\n�������, � ������� ��������.... ������� ����!\n");
}


void controls(){
    int variant;
    printf("\n��� ����� ������?\n");
    do {
        printf("\n0 - ������ ����\n1 - ������ �������\n2 - ���������� ���� ����������\n3 - �������� ����\n");
        while (scanf("%d", &variant) != 1){
            while (getchar() != '\n');
            printf("\n������� ����� ����������:\n");
        }
    }while (variant < 0 || variant > 3);

    switch (variant)
    {
        case 0: {
            gameControl();
            break;
        }
        case 1: {
            rights();
            break;
        }
        case 2: {
            readScore();
            break;
        }
        case 3: {
            printf("\033c");
            return;
            break;
        }
    }
    printf("\n");
    controls();
}


int main(){
    printf("\033c");
    system("chcp 1251");
	setlocale(LC_ALL, "Russian");

    readAllCity();
    printf("����� ���������� � ���� '������ ������'!\n");
    controls();

}