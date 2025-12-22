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
        printf("Ошибка! Файл не найден.\n");
        return 0;
    }

    int count = 0;
    
    while (fscanf(file, "%s", buffer) == 1 && count < MAX_WORDS) {
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

int test_word(char *buffer, char **library, int count) {
    for (int i = 0; i < count; i++) {
        if (strcmp(buffer, library[i]) == 0){
            return 1;
        }
    }
    return 0;
}

void welcome() {
    printf("\n========= Игра Wordle ===========\n");
    printf("Тема: \n");
    printf("Слово состоит из 5 английских букв\n");
    printf("Всего количество попыток: 6\n");
    printf("==================================\n");
    printf("\n");
}

void clear_trml() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int main() {
    char **library = malloc(MAX_WORDS * sizeof(char*));
    char buffer[100];

    int count = 0;
    count = loadwords(library, "words.txt");
    
    if (count == 0) {
        printf("Ошибка! Файл пуст!\n");
        return 0;
    }

    srand(time(NULL));

    char answer;

    do {
        int randomindex = rand() % count;
        char* secretword = library[randomindex];

        welcome();

        int win = 0;
        for (int i = 0; i < 6; i++) {
            int colors[5] = {0};
            char tempsecret[6];
            strcpy(tempsecret, secretword);

            inputword(i, buffer);
            if (test_word(buffer, library, count) == 0) {
                if (strlen(buffer) != 5) {
                printf("Не удовлетворяет условие!\n");
                i--;
                continue;
            }
                printf("Такого слова нет!\n");
                i--;
                continue;
            }

            for (int j = 0; j < 5; j++) {
                if (buffer[j] == secretword[j]) {
                    colors[j] = 2;
                    tempsecret[j] = '*';
                }
            }

            for (int j = 0; j < 5; j++) {
                if (colors[j] != 2) {
                    char *p = strchr(tempsecret, buffer[j]);
                    if (p != NULL) {
                        colors[j] = 1;
                        *p = '.';
                    }
                }
            }

            for (int j = 0; j < 5; j++) {
                if (colors[j] == 2) {
                    printf(GREEN "%c" RESET, buffer[j]);
                } else if (colors[j] == 1) {
                    printf(YELLOW "%c" RESET, buffer[j]);
                } else {
                    printf("%c", buffer[j]);
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
            printf("\n");
            printf("==================================\n");
            printf("Ты проиграл! Правильное было слово: %s\n", secretword);
        }

        printf("\n");
        printf("==================================\n");
        printf("Сыграть еще? (y/n): ");
        scanf(" %c", &answer);

        clear_trml();

    } while (answer == 'y');
    
    clear_trml();

    for (int i = 0; i < count; i++) {
        free(library[i]);
    }

    free(library);

    return 0;
}