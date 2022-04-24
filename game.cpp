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

int gameStatus = 0; // ��� ���������� ����

int thisScore = 0; // ������� �����

void readAllCity(){
    cityCount = -1;
    FILE* data = fopen("db.txt", "r");
    do{
        cityCount++;
        fgets(allCity[cityCount], 255, data);
        
    }while (strlen(allCity[cityCount] ) > 0);
    cityCount++;

    fclose(data);
}

void readScore(){
    printf("\033c");
    char scoreRes[11];

    FILE* data = fopen("score.txt", "r");
    fgets(scoreRes, 10, data);
    if (atoi(scoreRes) > 0){
        printf("��� ������ ��������� - %s\n", scoreRes);
    } else {
        printf("� ��� ���� ��� �����������\n");
    }
    
    fclose(data);
    sleep(1);
}

// ���������� ���������
void setScore(){

    char scoreRes[11];

    FILE* data = fopen("score.txt", "r");
    fgets(scoreRes, 10, data);
     if (atoi(scoreRes) > 0){
        if (atoi(scoreRes) < thisScore){
            FILE* dataWrite = fopen("score.txt", "w");
            fprintf(dataWrite, "%d", thisScore);
            fclose(dataWrite);
        }
    } else {
        FILE* dataWrite = fopen("score.txt", "w");
        fprintf(dataWrite, "%d", thisScore);
        fclose(dataWrite);
    }
    thisScore = 0;
    fclose(data);
}


// ����� ����
void endGame(int variant){
    switch (variant)
    {
        case 1:{
            printf("\n�� ������� ���� �����������, �������� ����� �� ���������...\n");
            gameStatus = 1;
            break;
        }
        case 2:{
            printf("\n�� �������� ���! ������ ����� ������� �����!\n");
            gameStatus = 1;
            break;
        }
    }


    setScore();
    sleep(3);
}

// ������� ����� �� ����
void deliteWord(int index){
    int j = 0;
    for (int i =0; i<cityCount; i++){
        if (i != index){
            strcpy(allCity[j],allCity[i]);
            j++;
        }
    }
    cityCount--;
}


// ��������� ���������� �����
void getRandWord(){
    int number = rand()%cityCount;
    strcpy(wordNow, allCity[number]);
    deliteWord(number);
    printf("���������: %s", wordNow);
}

// ����� ������� � ������
void helpOn(int help){
    if (help)
    printf("\n� ��� ������� ����� ��������� - ��� ����, ����� �������� ���������, �������� '������'\n");
    else 
    printf("\n� ��� ��������� ��������� - ���� �� ������!\n");
}

// ��������� ����� �����������
void getCompWord(char sym){
    int flag = 1; // �������� ������� �� �����

    for (int i =0; i<cityCount; i++){
        if (allCity[i][0] == sym){
            strcpy(wordNow, allCity[i]);
            deliteWord(i);
            printf("���������: %s", wordNow);
            flag = 0;
            break;
        }
    }

    if (flag){
        endGame(1);
    }
}

// ������
void helpMeNow(char sym){
    int flag = 1; // �������� ������� �� �����

    for (int i =0; i<cityCount; i++){
        if (allCity[i][0] == sym){
            printf("�� ������ ������� ���� �����: %s", allCity[i]);
            flag = 0;
            break;
        }
    }

    if (flag){
        printf("��� ������ �� ��� ����� ����������� - ��������");
    }
}

int isRealCity(){
    int flag = 0;
    int searchFlag = 1;
    int index = 0;

    for (int i =0; i<cityCount; i++){
        searchFlag = 1;
        if ((strlen(allCity[i]) - 1) == strlen(answear)){
            for (int j =0; j< (strlen(allCity[i]) - 1); j++){
                if (answear[j] != allCity[i][j]){
                    searchFlag = 0;
                }
            }
        }else{
            searchFlag = 0;
        }
        if (searchFlag){
            flag = 1;
            index = i;
            break;
        }
    }
    if (flag){
        deliteWord(index);
        return 1;
    }else{
        if (strcmp(answear, "������") != 0 && strcmp(answear, "������") != 0){
            printf("������ ������ ���!\n");
        }
        return 0;
    }
}

void compFirst(int help){
    int flag = 0;
    int endWord = 2; // ����������� ����� - ��� ��� � ���� ������ ���� � �����
    printf ("\n���� �� ������ ������� - ������ �������� '������'\n");
    getRandWord();
    
    while (cityCount > 1){
        do{ 
            if (wordNow[strlen(wordNow) - 2] == '�' || wordNow[strlen(wordNow) - 2] == '�'){
                endWord = 3;
                printf("��� ����� ������������ �� ���� - ���� ����� �� ������������� ����� - %c\n", wordNow[strlen(wordNow) - endWord]);
                sleep(1);
            }else{
                endWord = 2;
            }
            do {
                printf("���� �����: ");
                scanf("%s", answear);
                if (strcmp(answear, "������") == 0){
                    endGame(2);
                    break;
                }
                if (strcmp(answear, "������") == 0 && help == 1){
                    helpMeNow(wordNow[strlen(wordNow) - endWord]);
                }
            }while(strlen(answear) < 0 || strlen(answear) > 50 || isRealCity() == 0 );

            if (gameStatus){
                gameStatus = 0;
                return;
            }

            if (tolower(answear[0]) == tolower(wordNow[strlen(wordNow) - endWord])){
                flag = 1;
                
            } else{
                printf("����� �� � ��� �����\n");
            }
        }while(flag == 0);
        flag = 0;
        thisScore++;
        getCompWord(answear[strlen(answear) - 1]);
    }
    
}

void youFirst(int help){
    int flag = 0;
    int endWord = 2; // ����������� ����� - ��� ��� � ���� ������ ���� � �����
    printf ("\n���� �� ������ ������� - ������ �������� '������'\n");
    do {
        printf("���� �����: ");
        scanf("%s", answear);
        if (strcmp(answear, "������") == 0){
            endGame(2);
            break;
        }
        if (strcmp(answear, "������") == 0 && help == 1){
            printf("����� � ������ ������\n");
        }
    }while(strlen(answear) < 0 || strlen(answear) > 50 || isRealCity() == 0 );
     if (gameStatus){
        gameStatus = 0;
        return;
    }
    getCompWord(answear[strlen(answear) - 1]);

    while (cityCount > 1){
        do{ 
            if (wordNow[strlen(wordNow) - 2] == '�' || wordNow[strlen(wordNow) - 2] == '�'){
                endWord = 3;
                printf("��� ����� ������������ �� ���� - ���� ����� �� ������������� ����� - %c\n", wordNow[strlen(wordNow) - endWord]);
                sleep(1);
            }else{
                endWord = 2;
            }
            do {
                printf("���� �����: ");
                scanf("%s", answear);
                if (strcmp(answear, "������") == 0){
                    endGame(2);
                    break;
                }
                if (strcmp(answear, "������") == 0 && help == 1){
                    helpMeNow(wordNow[strlen(wordNow) - endWord]);
                }
            }while(strlen(answear) < 0 || strlen(answear) > 50 || isRealCity() == 0 );

            if (gameStatus){
                gameStatus = 0;
                return;
            }

            if (tolower(answear[0]) == tolower(wordNow[strlen(wordNow) - endWord])){
                flag = 1;
                
            } else{
                printf("����� �� � ��� �����\n");
            }
        }while(flag == 0);
        flag = 0;
        thisScore++;
        getCompWord(answear[strlen(answear) - 1]);
    }
}

void gameControl(){
     readAllCity();
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

    helpOn(helpers);

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