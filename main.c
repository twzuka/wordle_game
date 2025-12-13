#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_WORDS 100

int loadwords(char **library, char *filename, buffer) {
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

void inputword() {

}

int main() {
    char **library = malloc(MAX_WORDS * sizeof(char*));
    char buffer[100];

    int count = 0;
    count = loadwords(library, "words.txt", buffer);
    
    srand(time(NULL));
    int randomindex = rand() % count;
    char* secretword = library[randomindex];

    int win = 0;
    for (int i = 0; i < 6; i++){
        printf("Введите слово (попытка %d): ", i + 1);
        scanf("%s", buffer);
        if(strlen(buffer) != 5) {
            printf("Слишком короткое слово!\n");
            break;
        }

        for(int j = 0; j < 5; j++){
            if (buffer[j] == secretword[j]){
                printf("\033[32m%c\033[0m", buffer[j]);
            } 
            else {
                if (strchr(secretword, buffer[j]) != NULL) {
                    printf("\033[33m%c\033[0m", buffer[j]);
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
        printf("Ты проиграл! Правильно слово: %s\n", secretword);
    }

    return 0;
}