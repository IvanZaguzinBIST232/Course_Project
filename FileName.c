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

//����������� ��������,����� ������ int,��� ��� renurn (Find_Name)
int Find_Name(Web_services* programs, int size, char* Find_of_Name);
int Find_Version(Web_services* service_s, int size, char* Find_of_Version);//������� ������ ���������� ��������
int Find_Developer(Web_services* service_s, int size, char* Find_of_Developer);
int Sort_Perfomance(Web_services* service_s, int size, double Sort_of_Perfomance);
int Write_to_File(Web_services* service_s, int size);

int print_menu() {
    printf("����:\n");
    printf("1) �������� ������\n");
    printf("2) ����� �� ��������\n");
    printf("3) ����� �� ������ �������\n");
    printf("4) ����� �� ������������\n");
    printf("5) ���������� �� ������������������ (������� ������)\n");
    printf("6) �������� � ����\n");
    printf("7) ����� �� ���������\n");
    printf("�������� ����� ����: ");
    return 0;
}

int main() {
    setlocale(LC_ALL, "RUS");
    system("chcp 1251");

    Web_services* service_s;
    service_s = (Web_services*)malloc(sizeof(Web_services) * MAX_SIZE); // ������������ ��������� ������ ��� ������� ��� ��������

    int size = 0;
    int choice = 0;

    do {
        print_menu();
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            if (size < MAX_SIZE) {
                printf("������� ������ ��� ����� ������ � ���������:\n");
                printf("��������: ");
                scanf(" %[^\n]s", (service_s + size)->name);
                printf("������ �������: ");
                scanf(" %[^\n]s", (service_s + size)->version);
                printf("�����������: ");
                scanf(" %[^\n]s", (service_s + size)->developer);
                printf("��������: ");
                scanf(" %[^\n]s", (service_s + size)->description);
                printf("���������: ");
                scanf(" %[^\n]s", (service_s + size)->platform);
                printf("������������������: ");
                scanf(" %lf", &((service_s + size)->perfomance));
                size++;
            }
            else {
                printf("���� ������ ������������! ���������� ���������! ������!\n");
            }
            break;
        case 2:
            if (size > 0) {
                char Find_of_Name[40];
                printf("������� ������������ ���-������� ��� ������: ");
                scanf(" %[^\n]s", Find_of_Name);
                Find_Name(service_s, size, Find_of_Name);
            }
            else {
                printf("���� ������ = ������ �����!\n");
            }
            break;
        case 3:
            if (size > 0) {
                char Find_of_Version[40];
                printf("������� ����������� ������ ���-������� ��� ������: ");
                scanf(" %[^\n]s", Find_of_Version);
                Find_Version(service_s, size, Find_of_Version);// ������ ������� �������� find
            }
            else {
                printf("���� ������ = ������ �����!\n");
            }
            break;
        case 4:
            if (size > 0) {
                char Find_of_Developer[48];
                printf("������� ��� ������������ ��� ������: ");
                scanf(" %[^\n]s", Find_of_Developer);
                Find_Developer(service_s, size, Find_of_Developer);
            }
            else {
                printf("���� ������ = ������ �����!\n");
            }
            break;
        case 5:
            if (size > 0) {
                double Sort_of_Perfomance;
                printf("������� �������� ������ ������������������ (��): ");
                scanf("%lf", &Sort_of_Perfomance);
                Sort_Perfomance(service_s, size, Sort_of_Perfomance);
            }
            else {
                printf("���� ������ = ������ �����!\n");
            }
            break;
        case 6:
            if (size > 0) {
                Write_to_File(service_s, size);
            }
            else {
                printf("���� ������ = ������ �����!\n");
            }
            break;
        case 7:
            printf("��������� ���������� ������ � ���� ������� ���������!\n");
            break;
        default:
            printf("������������ ����. ����������, �������� ������������ ����� ����.\n");
        }

    } while (choice != 7);

    free(service_s); // ������������ ����������� ���������� ������

    return 0;
}

int Find_Name(struct Web_services* service_s, int size, char* Find_of_Name) {
    // ����� ����� ����� �� �������� ���� �����
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
                printf("���������� �� �������.\n");
                return -1;
            }

            current_substring_length--;
            break;
        }

        current_substring_length++;
    }// ��������� �������� ������ �����

    // create final substring of original Find_of_Name
    char substr_of_find[52];
    strncpy(substr_of_find, Find_of_Name, current_substring_length);
    (*(substr_of_find + lenght_find_of_name)) = '\0';

    printf("\n���������� ������ �� �������� ���-������� \"%s\":\n", substr_of_find);
    printf("------------------------------------------------\n");
    for (struct Web_services* element = service_s; element < service_s + size; ++element) {
        if (strstr(element->name, Find_of_Name) != NULL) {
            printf("��������: %s\n", element->name);
            printf("������ ��������: %s\n", element->version);
            printf("�����������: %s\n", element->developer);
            printf("��������: %s\n", element->description);
            printf("���������: %s\n", element->platform);
            printf("������������������: %.2lf\n", element->perfomance);
            printf("------------------------------------------------\n");
        }
    }
    return 0;
}

int Find_Version(struct Web_services* service_s, int size, char* Find_of_Version) {
    printf("\n���������� ������ �� ������ ������� \"%s\":\n", Find_of_Version);
    printf("------------------------------------------------\n");
    for (struct Web_services* element = service_s; element < service_s + size; ++element) {
        if (strstr(element->version, Find_of_Version) != NULL) {
            printf("��������: %s\n", element->name);
            printf("������ ��������: %s\n", element->version);
            printf("�����������: %s\n", element->developer);
            printf("��������: %s\n", element->description);
            printf("���������: %s\n", element->platform);
            printf("������������������: %.2lf\n", element->perfomance);
            printf("------------------------------------------------\n");
        }
        
    }
    return 0;
}
int Find_Developer(struct Web_services* service_s, int size, char* Find_of_Developer) {
    printf("\n���������� ������ �� ������������ \"%s\":\n", Find_of_Developer);
    printf("------------------------------------------------\n");
    for (struct Web_services* element = service_s; element < service_s + size; ++element) {
        if (strstr(element->developer, Find_of_Developer) != NULL) {
            printf("��������: %s\n", element->name);
            printf("������ ��������: %s\n", element->version);
            printf("�����������: %s\n", element->developer);
            printf("��������: %s\n", element->description);
            printf("���������: %s\n", element->platform);
            printf("������������������: %.2lf\n", element->perfomance);
            printf("------------------------------------------------\n");
        }
    }
    return 0;
}
//����� ���������� �������� � ��������� ������� �������

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
    printf("\n���������� ������ �� ��������� �������� �� %.2lf:\n", Sort_of_Perfomance);
    printf("------------------------------------------------\n");
    for (int i = 0; i < size; ++i) {
        if (service_s[i].perfomance <= Sort_of_Perfomance) {
            printf("��������: %s\n", service_s[i].name);
            printf("������ ��������: %s\n", service_s[i].version);
            printf("�����������: %s\n", service_s[i].developer);
            printf("��������: %s\n", service_s[i].description);
            printf("���������: %s\n", service_s[i].platform);
            printf("������������������: %.2lf\n", service_s[i].perfomance);
            printf("------------------------------------------------\n");
            
        }
    }
    return 0;
}

int Write_to_File(struct Web_services* service_s, int size) {
    FILE* file = fopen("service_s.txt", "w");
    if (file == NULL) {
        printf("���� �� ������.\n");
        return -1;
    }
    for (struct Web_services* element = service_s; element < service_s + size; ++element) {
        fprintf(file, "��������: %s\n", element->name);
        fprintf(file, "������ �������: %s\n", element->version);
        fprintf(file, "�����������: %s\n", element->developer);
        fprintf(file, "��������: %s\n", element->description);
        fprintf(file, "���������: %s\n", element->platform);
        fprintf(file, "������������������: %.2lf\n", element->perfomance);
        fprintf(file, "------------------------------------------------\n");
    }

    fclose(file);
    printf("������ ���� �������� � ����.\n");
    return 0;
}
//������� 0 ���� �������,���� �� �������� -1