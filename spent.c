#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAXSIZE 100

void spend();
void total(char* month);
void display(char* month);
void print_usage();
int isnumber();
int string_to_int(const char* s);
char* int_to_string();

int main(int argc, char** argv) {

    if (argc == 1) {
        print_usage();
    }
        
    else if (strcmp(argv[1], "--help") == 0)  {
        print_usage();
    }

    else if (argc == 3 && strcmp(argv[1], "--list") == 0) 
        display(argv[2]);

    else if (argc == 3 && strcmp(argv[1], "--total") == 0)  
        total(argv[2]);

    else if (argc == 3 && isnumber(argv[1]) == 0 && isnumber(argv[2]) == -1) 
        spend(argv[1], argv[2]);
    
    else {
        print_usage();
    }

    return 0;
}

void spend(const char* amount, const char* spent_on) {
    
    time_t t = time(NULL);
    struct tm time = *localtime(&t);

    char *month = malloc(sizeof(char) * 2);
    month = int_to_string(time.tm_mon + 1);

    char *year = malloc(sizeof(char) * 4); 
    year = int_to_string(time.tm_year + 1900);

    int c;
    int i = 0;


    printf("Amount: %s\n", amount);
    printf("Spent on: %s\n", spent_on);

    //Get path of file for current month
    char temp[] = "/.expenses/";
    char* path = malloc(sizeof(char) * 256);
    char* home = getenv("HOME");
    strcpy(path, strcat(home, temp));
    strcat(path, strcat(month, ".dat"));

    free(month);
    free(year);
    month = NULL;
    year = NULL;

    FILE *ex;
    if ((ex = fopen(path, "a")) == NULL) {
        printf("Error opening data file. Exiting.....\n");
        exit(0);
    }

    fprintf(ex, "%s\t\t", amount);
    fprintf(ex, "%s\n", spent_on);

    free(path);
    path = NULL;

    fclose(ex);
}

void total(char* month) {

    //Get path of file for specified month
    char temp[] = "/.expenses/";
    char *path = malloc(sizeof(char) * 256);
    char* home = getenv("HOME");
    strcpy(path, strcat(home, temp));
    strcat(path, strcat(month, ".dat"));

    FILE* ex;
    if ((ex = fopen(path, "r")) == NULL) {
        printf("Error opening data file. Exiting.....\n");
        exit(0);
    }

    char* spent_money = malloc(sizeof(char) * MAXSIZE);

    int sum = 0;
    int c;

    while ((c = getc(ex)) != EOF) {
        int i = 0;
        if (c  != '\t') {
            while (c  != '\t') {
                spent_money[i] = c;
                i++;
                c = getc(ex);
            }
            spent_money[i] = '\0';
            sum = sum + string_to_int(spent_money);
        }
        if (c == '\t') {
            while ((c = getc(ex) != '\n')); 
        }
        memset(spent_money, 0, sizeof spent_money);
    }
    printf("Total Spent: %d\n", sum);

    free(spent_money);
    free(path);
    path = NULL;
    home = NULL;
    fclose(ex);
}

void display(char* month) {

    //Get path of file for specified month
    char temp[] = "/.expenses/";
    char *path = malloc(sizeof(char) * 256);
    char* home = getenv("HOME");
    strcpy(path, strcat(home, temp));
    strcat(path, strcat(month, ".dat"));

    FILE* ex;
    if ((ex = fopen(path, "r")) == NULL) {
        printf("Error opening data file. Exiting.....\n");
        exit(0);
    }

    int c;
    while((c = getc(ex)) != EOF) 
        printf("%c", c);

    fclose(ex);
}

int string_to_int(const char* s) {
    int result = 0;
    int i = strlen(s) - 1;
    int m = 1;
    while (i >= 0) {
        int c = s[i] - '0';
        result = result + (m * c);
        m = m * 10;
        i--;
    }
    return result;
}

char* int_to_string(int n) {
    int length = snprintf(NULL, 0, "%d", n);
    char* str = malloc(length + 1);
    snprintf(str, length + 1, "%d", n);
    return str;
}

int isnumber(char s[]) {
    for (int i = 0; i < strlen(s); i++) {
        if (s[i] < '0' || s[i] > '9') 
            return -1;
    }
    return 0;
}

void print_usage() {
        printf("usage:\nspent amount spent_on\n");
        printf("\tThis will store the amount with the thing you spent it on\n");
        printf("spent --total month_number(1-12)\n");
        printf("\tThis will give you the total amount you have spent in the specified month\n");
        printf("spent --list month_number(1-12)\n");
        printf("\tThis will give you the amount and the list of items for the specified month\n");
}
