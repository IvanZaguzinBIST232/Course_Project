#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#define MAX_SIZE 90

struct Web_services {
    char name[52];
    char version[40];
    char developer[50];
    char description[90];
    char platform[48];
    double perfomance;
};

typedef struct Web_services Web_services;

//возювращаем значение,пусть вернет int,что был renurn (Find_Name)
int Find_Name(Web_services* programs, int size, char* Find_of_Name);
int Find_Version(Web_services* service_s, int size, char* Find_of_Version);//функции должны возвращать значение
int Find_Developer(Web_services* service_s, int size, char* Find_of_Developer);
int Sort_Perfomance(Web_services* service_s, int size, double Sort_of_Perfomance);
int Write_to_File(Web_services* service_s, int size);

int print_menu() {
    printf("Меню:\n");
    printf("1) Добавить запись\n");
    printf("2) Поиск по названию\n");
    printf("3) Поиск по версии сервиса\n");
    printf("4) Поиск по разработчику\n");
    printf("5) Сортировка по производительности (сначала лучшие)\n");
    printf("6) Записать в файл\n");
    printf("7) Выход из программы\n");
    printf("Выберите пункт меню: ");
    return 0;
}

int main() {
    setlocale(LC_ALL, "RUS");
    system("chcp 1251");

    Web_services* service_s;
    service_s = (Web_services*)malloc(sizeof(Web_services) * MAX_SIZE); // динамическое выделение памяти для массива веб сервисов

    int size = 0;
    int choice = 0;

    do {
        print_menu();
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            if (size < MAX_SIZE) {
                printf("Введите данные для новой записи в программе:\n");
                printf("Название: ");
                scanf(" %[^\n]s", (service_s + size)->name);
                printf("Версия сервиса: ");
                scanf(" %[^\n]s", (service_s + size)->version);
                printf("Разработчик: ");
                scanf(" %[^\n]s", (service_s + size)->developer);
                printf("Описание: ");
                scanf(" %[^\n]s", (service_s + size)->description);
                printf("Платформа: ");
                scanf(" %[^\n]s", (service_s + size)->platform);
                printf("Производительность: ");
                scanf(" %lf", &((service_s + size)->perfomance));
                size++;
            }
            else {
                printf("База данных переполненна! Добавление запрещено! Ошибка!\n");
            }
            break;
        case 2:
            if (size > 0) {
                char Find_of_Name[40];
                printf("Введите наименование веб-сервиса для поиска: ");
                scanf(" %[^\n]s", Find_of_Name);
                Find_Name(service_s, size, Find_of_Name);
            }
            else {
                printf("База данных = пустое место!\n");
            }
            break;
        case 3:
            if (size > 0) {
                char Find_of_Version[40];
                printf("Введите обозначение версии веб-сервиса для поиска: ");
                scanf(" %[^\n]s", Find_of_Version);
                Find_Version(service_s, size, Find_of_Version);// здесьт вернуть значение find
            }
            else {
                printf("База данных = пустое место!\n");
            }
            break;
        case 4:
            if (size > 0) {
                char Find_of_Developer[48];
                printf("Введите имя разработчика для поиска: ");
                scanf(" %[^\n]s", Find_of_Developer);
                Find_Developer(service_s, size, Find_of_Developer);
            }
            else {
                printf("База данных = пустое место!\n");
            }
            break;
        case 5:
            if (size > 0) {
                double Sort_of_Perfomance;
                printf("Введите желаемый предел производительности (до): ");
                scanf("%lf", &Sort_of_Perfomance);
                Sort_Perfomance(service_s, size, Sort_of_Perfomance);
            }
            else {
                printf("База данных = пустое место!\n");
            }
            break;
        case 6:
            if (size > 0) {
                Write_to_File(service_s, size);
            }
            else {
                printf("База данных = пустое место!\n");
            }
            break;
        case 7:
            printf("Программа прекратила работу и была успешно завершена!\n");
            break;
        default:
            printf("Неправильный ввод. Пожалуйста, выберите существующий пункт меню.\n");
        }

    } while (choice != 7);

    free(service_s); // освобождение динамически выделенной памяти

    return 0;
}

int Find_Name(struct Web_services* service_s, int size, char* Find_of_Name) {
    // найти длину слова по которому ведём поиск
    int lenght_find_of_name = 0;
    while ((*(Find_of_Name + lenght_find_of_name)) != '\0') {
        lenght_find_of_name++;
    }

    int current_substring_length = 1;

    while (current_substring_length < lenght_find_of_name) {
        char substr_of_find[52];
        strncpy(substr_of_find, Find_of_Name, current_substring_length);
        (*(substr_of_find + lenght_find_of_name)) = '\0';

        int counter = 0;

        for (int i = 0; i < size; ++i) {
            if (strstr(service_s[i].name, substr_of_find) != NULL) {
                counter++;
            }
        }

        if (counter == 0) {
            if (current_substring_length == 1) {
                printf("Совпадений не найдено.\n");
                return -1;
            }

            current_substring_length--;
            break;
        }

        current_substring_length++;
    }// возращать значение должен поиск

    // create final substring of original Find_of_Name
    char substr_of_find[52];
    strncpy(substr_of_find, Find_of_Name, current_substring_length);
    (*(substr_of_find + lenght_find_of_name)) = '\0';

    printf("\nРезультаты поиска по названию веб-сервиса \"%s\":\n", substr_of_find);
    printf("------------------------------------------------\n");
    for (struct Web_services* element = service_s; element < service_s + size; ++element) {
        if (strstr(element->name, Find_of_Name) != NULL) {
            printf("Название: %s\n", element->name);
            printf("Версия серсвиса: %s\n", element->version);
            printf("Разработчик: %s\n", element->developer);
            printf("Описание: %s\n", element->description);
            printf("Платформа: %s\n", element->platform);
            printf("Производительность: %.2lf\n", element->perfomance);
            printf("------------------------------------------------\n");
        }
    }
    return 0;
}

int Find_Version(struct Web_services* service_s, int size, char* Find_of_Version) {
    printf("\nРезультаты поиска по версии сервиса \"%s\":\n", Find_of_Version);
    printf("------------------------------------------------\n");
    for (struct Web_services* element = service_s; element < service_s + size; ++element) {
        if (strstr(element->version, Find_of_Version) != NULL) {
            printf("Название: %s\n", element->name);
            printf("Версия серсвиса: %s\n", element->version);
            printf("Разработчик: %s\n", element->developer);
            printf("Описание: %s\n", element->description);
            printf("Платформа: %s\n", element->platform);
            printf("Производительность: %.2lf\n", element->perfomance);
            printf("------------------------------------------------\n");
        }
        
    }
    return 0;
}
int Find_Developer(struct Web_services* service_s, int size, char* Find_of_Developer) {
    printf("\nРезультаты поиска по Разработчику \"%s\":\n", Find_of_Developer);
    printf("------------------------------------------------\n");
    for (struct Web_services* element = service_s; element < service_s + size; ++element) {
        if (strstr(element->developer, Find_of_Developer) != NULL) {
            printf("Название: %s\n", element->name);
            printf("Версия серсвиса: %s\n", element->version);
            printf("Разработчик: %s\n", element->developer);
            printf("Описание: %s\n", element->description);
            printf("Платформа: %s\n", element->platform);
            printf("Производительность: %.2lf\n", element->perfomance);
            printf("------------------------------------------------\n");
        }
    }
    return 0;
}
//чтобы возвращало значение в отедльную функцию вывести

int Sort_Perfomance(struct Web_services* service_s, int size, double Sort_of_Perfomance) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (service_s[i].perfomance > service_s[j].perfomance) {
                struct Web_services temp;

                strcpy(temp.description, service_s[i].description);
                strcpy(temp.developer, service_s[i].developer);
                strcpy(temp.name, service_s[i].name);
                strcpy(temp.platform, service_s[i].platform);
                strcpy(temp.version, service_s[i].version);
                temp.perfomance = service_s[i].perfomance;

                strcpy(service_s[i].description, service_s[j].description);
                strcpy(service_s[i].developer, service_s[j].developer);
                strcpy(service_s[i].name, service_s[j].name);
                strcpy(service_s[i].platform, service_s[j].platform);
                strcpy(service_s[i].version, service_s[j].version);
                service_s[i].perfomance = service_s[j].perfomance;

                strcpy(service_s[j].description, temp.description);
                strcpy(service_s[j].developer, temp.developer);
                strcpy(service_s[j].name, temp.name);
                strcpy(service_s[j].platform, temp.platform);
                strcpy(service_s[j].version, temp.version);
                service_s[j].perfomance = temp.perfomance;
            }
        }

    }
    printf("\nРезультаты поиска по желаемому рейтингу до %.2lf:\n", Sort_of_Perfomance);
    printf("------------------------------------------------\n");
    for (int i = 0; i < size; ++i) {
        if (service_s[i].perfomance <= Sort_of_Perfomance) {
            printf("Название: %s\n", service_s[i].name);
            printf("Версия серсвиса: %s\n", service_s[i].version);
            printf("Разработчик: %s\n", service_s[i].developer);
            printf("Описание: %s\n", service_s[i].description);
            printf("Платформа: %s\n", service_s[i].platform);
            printf("Производительность: %.2lf\n", service_s[i].perfomance);
            printf("------------------------------------------------\n");
            
        }
    }
    return 0;
}

int Write_to_File(struct Web_services* service_s, int size) {
    FILE* file = fopen("service_s.txt", "w");
    if (file == NULL) {
        printf("Файл не найден.\n");
        return -1;
    }
    for (struct Web_services* element = service_s; element < service_s + size; ++element) {
        fprintf(file, "Название: %s\n", element->name);
        fprintf(file, "Версия сервиса: %s\n", element->version);
        fprintf(file, "Разработчик: %s\n", element->developer);
        fprintf(file, "Описание: %s\n", element->description);
        fprintf(file, "Платформа: %s\n", element->platform);
        fprintf(file, "Производительность: %.2lf\n", element->perfomance);
        fprintf(file, "------------------------------------------------\n");
    }

    fclose(file);
    printf("Данные были записаны в файл.\n");
    return 0;
}
//вернуть 0 если успешно,если не успиешно -1