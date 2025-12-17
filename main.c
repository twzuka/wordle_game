#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_WORDS 100
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define RESET "\033[0m"

int loadwords(char **library, char *filename) {
    char buffer[100];
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Ошибка! Файл пуст.\n");
        return 0;
    }

    int count = 0;
    
    while (fscanf(file, "%s", buffer) == 1 && count < MAX_WORDS)  {
        if (strlen(buffer) == 5) {
            library[count] = malloc(strlen(buffer) + 1);
            strcpy(library[count], buffer);
            count++;
        }
    }
    fclose(file);
    return count;
}

void inputword(int i, char* buffer) {
    printf("Введите слово (попытка %d): ", i + 1);
    scanf("%99s", buffer);
}

void greetings() {
    printf("\n========= Игра Wordle ===========\n");
    printf("Тема: \n");
    printf("Слово состоит из 5 англиских букв\n");
    printf("Всего количество попыток: 6\n");
    printf("==================================\n");
    printf("\n");
}

int main() {
    char **library = malloc(MAX_WORDS * sizeof(char*));
    char buffer[100];

    int count = 0;
    count = loadwords(library, "words.txt");
    
    srand(time(NULL));
    int randomindex = rand() % count;
    char* secretword = library[randomindex];

    greetings();
    

    int win = 0;
    for (int i = 0; i < 6; i++){
        inputword(i, buffer);

        if(strlen(buffer) != 5) {
            printf("Не удовлетворяет условие!\n");
            continue;
        }

        for(int j = 0; j < 5; j++){
            if (buffer[j] == secretword[j]){
                printf(GREEN "%c" RESET, buffer[j]);
            } 
            else {
                if (strchr(secretword, buffer[j]) != NULL) {
                    printf(YELLOW "%c" RESET, buffer[j]);
                } 
                else {
                    printf("%c", buffer[j]);
                }
            }
        }
        printf("\n");

        if (strcmp(buffer, secretword) == 0) {
            win++;
            printf("Ты победил!\n");
            break;
        }
    }

    if (win == 0) {
        printf("Ты проиграл! Правильное слово: %s\n", secretword);
    }

    return 0;
}