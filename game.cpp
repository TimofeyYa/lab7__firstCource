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
        printf("\nУ вас пока нет результатов\n");
    } else {
        printf("\nВаш последний результат - %s\n", scoreRes);
    }
    
    fclose(data);
}

// Получение рамдомного слова
void getRandWord(){
    int number = rand()%100;
    strcpy(wordNow, allCity[number]);
    printf("Компьютер: %s", wordNow);
}

// Вывод надписи о помощи
void helpOn(int help){
    if (help)
    printf("\nУ вас включен режим подсказок - для того, чтобы получить подсказку, напишите 'Помощь'\n");
    else 
    printf("\nУ вас отключены подсказки - игра на равных!\n");
}

void compFirst(int help){
    helpOn(help);
    getRandWord();
    fscanf(stdin, "%[^\n]", answear);
    do {
        scanf("%s", answear);
    }while(strlen(answear) < 0 || strlen(answear) > 50);
    putchar(tolower(answear[0]));
    if (tolower(answear[0]) == tolower(wordNow[strlen(wordNow) - 1])){
        printf("\nАХУЕТЬ\n");
    } else{
        printf("\nЯ ебал...\n");
    }
    sleep(3);
}

void youFirst(int help){
    helpOn(help);
    
    
}

void gameControl(){
     printf("\033c");
     printf("\nДа начнётся игра!\n");
     sleep(1);
     int variant;
     int helpers = 0;
        printf("\nВыберете режим?\n");
        do {
            printf("\n0 - Первый ход ваш\n1 - Первым ходит компьютер\n2 - Вернуться в меню\n");
            while (scanf("%d", &variant) != 1){
                while (getchar() != '\n');
                printf("\nВведите число пожалуйста:\n");
            }
        }while (variant < 0 || variant > 2);

    if (variant == 0 || variant == 1){
        do {
            printf("\nВключить подсказки? (1 - да, 0 - нет)\n");
            while (scanf("%d", &helpers) != 1){
                while (getchar() != '\n');
                printf("\nВведите число пожалуйста:\n");
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
            printf("\nПравила игры очень просты\n");
            sleep(2);
            printf("\nТы пишешь название российского города - например 'Барнаул'\n");
            sleep(3);
            printf("\nУчти, что регистр не имеет значения, тоесть 'Барнаул' = 'барнаул' = 'БаРнАуЛ и тд'\n");
            sleep(4);
            printf("\nДалее компьютер отвечает тебе городом, который начинается с той буквы, на которую оканчивается товой город\n");
            sleep(2);
            printf("Например: 'Барнаул' - 'Липецк'\n");
            sleep(3);
            printf("\nТеперь ты должен ответить городом, который будет начинатся с той буквы, с которой оканчивается город противника\n");
             sleep(2);
            printf("Например: 'Барнаул' - 'Липецк' - 'Курск'\n");
            sleep(2);
            printf("\nИ так далее\n");
            sleep(2);
            printf("\nПобеждает тот, кто назовёт город последним\n");
            sleep(3);
            printf("\nНадеюсь, я понятно объяснил.... Удачной игры!\n");
}


void controls(){
    int variant;
    printf("\nЧто будем делать?\n");
    do {
        printf("\n0 - Начать игру\n1 - Узнать правила\n2 - Посмотреть свои результаты\n3 - Покинуть игру\n");
        while (scanf("%d", &variant) != 1){
            while (getchar() != '\n');
            printf("\nВведите число пожалуйста:\n");
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
    setlocale(LC_ALL, "");
    readAllCity();
    printf("Добро пожаловать в игру 'Города России'!\n");

    char a[]= "аб";
    printf("%i", a[0] + a[1]);
    printf("%i", a[2] + a[3]);
    controls();

}