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

int gameStatus = 0; // для завершение игры

int thisScore = 0; // подсчёт очков

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
        printf("Ваш лучший результат - %s\n", scoreRes);
    } else {
        printf("У вас пока нет результатов\n");
    }
    
    fclose(data);
    sleep(1);
}

// установить результат
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


// Конец игры
void endGame(int variant){
    switch (variant)
    {
        case 1:{
            printf("\nТы обыграл меня человечешка, востание машин не случилось...\n");
            gameStatus = 1;
            break;
        }
        case 2:{
            printf("\nТы проиграл мне! Машины будут править миром!\n");
            gameStatus = 1;
            break;
        }
    }


    setScore();
    sleep(3);
}

// удаляем слово из базы
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


// Получение рамдомного слова
void getRandWord(){
    int number = rand()%cityCount;
    strcpy(wordNow, allCity[number]);
    deliteWord(number);
    printf("Компьютер: %s", wordNow);
}

// Вывод надписи о помощи
void helpOn(int help){
    if (help)
    printf("\nУ вас включен режим подсказок - для того, чтобы получить подсказку, напишите 'Помощь'\n");
    else 
    printf("\nУ вас отключены подсказки - игра на равных!\n");
}

// получение слова компьютером
void getCompWord(char sym){
    int flag = 1; // проверка найдено ли слово

    for (int i =0; i<cityCount; i++){
        if (allCity[i][0] == sym){
            strcpy(wordNow, allCity[i]);
            deliteWord(i);
            printf("Компьютер: %s", wordNow);
            flag = 0;
            break;
        }
    }

    if (flag){
        endGame(1);
    }
}

// Помощь
void helpMeNow(char sym){
    int flag = 1; // проверка найдено ли слово

    for (int i =0; i<cityCount; i++){
        if (allCity[i][0] == sym){
            printf("Ты можешь назвать этот город: %s", allCity[i]);
            flag = 0;
            break;
        }
    }

    if (flag){
        printf("Все города на эту букву закончились - сдавайся");
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
        if (strcmp(answear, "Сдаюсь") != 0 && strcmp(answear, "Помощь") != 0){
            printf("Такого города нет!\n");
        }
        return 0;
    }
}

void compFirst(int help){
    int flag = 0;
    int endWord = 2; // укарачиваем слово - для тех у кого мягкий знак в конце
    printf ("\nЕсли вы хотите сдаться - просто напишите 'Сдаюсь'\n");
    getRandWord();
    
    while (cityCount > 1){
        do{ 
            if (wordNow[strlen(wordNow) - 2] == 'ъ' || wordNow[strlen(wordNow) - 2] == 'ь'){
                endWord = 3;
                printf("Это слово оканчивается на знак - пиши город на предпоследнюю букву - %c\n", wordNow[strlen(wordNow) - endWord]);
                sleep(1);
            }else{
                endWord = 2;
            }
            do {
                printf("Ваше слово: ");
                scanf("%s", answear);
                if (strcmp(answear, "Сдаюсь") == 0){
                    endGame(2);
                    break;
                }
                if (strcmp(answear, "Помощь") == 0 && help == 1){
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
                printf("Слово не с той буквы\n");
            }
        }while(flag == 0);
        flag = 0;
        thisScore++;
        getCompWord(answear[strlen(answear) - 1]);
    }
    
}

void youFirst(int help){
    int flag = 0;
    int endWord = 2; // укарачиваем слово - для тех у кого мягкий знак в конце
    printf ("\nЕсли вы хотите сдаться - просто напишите 'Сдаюсь'\n");
    do {
        printf("Ваше слово: ");
        scanf("%s", answear);
        if (strcmp(answear, "Сдаюсь") == 0){
            endGame(2);
            break;
        }
        if (strcmp(answear, "Помощь") == 0 && help == 1){
            printf("Начни с города Москва\n");
        }
    }while(strlen(answear) < 0 || strlen(answear) > 50 || isRealCity() == 0 );
     if (gameStatus){
        gameStatus = 0;
        return;
    }
    getCompWord(answear[strlen(answear) - 1]);

    while (cityCount > 1){
        do{ 
            if (wordNow[strlen(wordNow) - 2] == 'ъ' || wordNow[strlen(wordNow) - 2] == 'ь'){
                endWord = 3;
                printf("Это слово оканчивается на знак - пиши город на предпоследнюю букву - %c\n", wordNow[strlen(wordNow) - endWord]);
                sleep(1);
            }else{
                endWord = 2;
            }
            do {
                printf("Ваше слово: ");
                scanf("%s", answear);
                if (strcmp(answear, "Сдаюсь") == 0){
                    endGame(2);
                    break;
                }
                if (strcmp(answear, "Помощь") == 0 && help == 1){
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
                printf("Слово не с той буквы\n");
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
            printf("\nПравила игры очень просты\n");
            sleep(2);
            printf("\nТы пишешь название российского города - например 'Барнаул'\n");
            sleep(3);
            printf("\nУчти, что регистр имеет значение - используйте только нижний регистр!\n");
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
    system("chcp 1251");
	setlocale(LC_ALL, "Russian");

    readAllCity();
    printf("Добро пожаловать в игру 'Города России'!\n");
    controls();

}