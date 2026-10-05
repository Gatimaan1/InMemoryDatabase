#include <stdio.h>
#include <string.h>
struct Entry {
    char key[50];
    char value[100];
};
void SetEntry(struct Entry *entry, char key[], char value[]) {
    strcpy(entry->key, key);
    strcpy(entry->value, value);
}
void GetEntry(struct Entry database[], int a, char key[]) {
    for (int i=0; i<a; i++) {
    if (strcmp(database[i].key, key) == 0) {
        printf("%s\n", database[i].value);
        return;
        }
    }
    printf("ERROR: Key not found\n");
}
void DeleteEntry(struct Entry database[], int *a, char key[]) {
    for (int i=0; i<*a; i++) {
        if (strcmp(database[i].key, key) == 0) {
            for (int j=i; j<*a-1; j++) {
                database[j] = database[j + 1];
            }
            (*a)--;
            printf("OK\n");
            return;
        }
    }
    printf("ERROR: Key not found\n");
}
int EntryExists(struct Entry database[], int a, char key[]) 
{
    for (int i=0; i<a; i++) {
        if (strcmp(database[i].key, key) == 0) {
            return 1;
        }
    }
    return 0;
}
int FindEntry(struct Entry database[], int a, char key[]) {
    for (int i=0; i<a; i++) {
        if (strcmp(database[i].key, key) == 0) {
            return i;
        }
    }
    return -1;
}
void SaveDatabase(struct Entry database[], int a, char filename[]) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) 
    {
        printf("ERROR: Could not open file\n");
        return;
    }
    fprintf(file, "{\n");
    for (int i=0; i<a; i++) 
    {
        fprintf(file, "%s %s\n", database[i].key,database[i].value);
        if(i<a-1){
            fprintf(file, ",");
        }
        fprintf(file, "\n");
    }
    fprintf(file, "\n}");
    fclose(file);
    printf("OK\n");
}
void LoadDatabase(struct Entry database[], int *a, char filename[]) 
{
    FILE *file = fopen(filename, "r");
    if (file == NULL) 
        {
        printf("ERROR: Could not open file\n");
        return;
        }
    *a = 0;
    char c;
    fscanf(file, " %c", &c);
    while (*a < 100 &&  fscanf(file,"\"%49[^\"]\":\"%99[^\"]\"",database[*a].key,database[*a].value) == 2) 
    {   
        fscanf(file, " %c", &c);
        if (c == '}')
        {
            break;
        }
        (*a)++;
    }
    fclose(file);
    printf("OK\n");
}
int main() {
    struct Entry Database[100];
    int a=0;
    char command[20];
    char key[50];
    char value[100];
    while (1) {
        printf(">>>");
        scanf("%19s", command);
        if (strcmp(command, "SET") == 0) {
            scanf("%49s %99[^\n]", key, value);
            int index = FindEntry(Database, a, key);
            if (index != -1) {
                strcpy(Database[index].value, value);
                printf("OK\n");
            }
            else if (a >= 100) {
                printf("ERROR: Database full\n");
            }
            else {
                SetEntry(&Database[a], key, value);
                a++;
                printf("OK\n");
                }
        }
        else if (strcmp(command, "GET") == 0) {
            scanf("%49s", key);
            GetEntry(Database, a, key);
        }
        else if (strcmp(command, "DEL") == 0) {
        scanf("%49s", key);
        DeleteEntry(Database, &a, key);
        }
        else if (strcmp(command, "EXISTS") == 0) 
        {
            scanf("%49s", key);
            if (EntryExists(Database, a, key)) {
                printf("1\n");
                }
            else {
            printf("0\n");
                }
        }
        else if (strcmp(command, "SAVE") == 0) 
        {
            char filename[100];
            scanf("%99s", filename);
            SaveDatabase(Database, a, filename);
            printf("OK\n");
        }
        else if (strcmp(command, "LOAD") == 0) 
        {
        char filename[100];
        scanf("%99s", filename);
        LoadDatabase(Database, &a, filename);
        }
        else if (strcmp(command, "EXIT") == 0) 
        {
            break;
        }
        else {
            printf("Unknown command\n");
        }
    }
    return 0;
}