#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 100

void printMenu();
void spend();
void total();
void display();
int string_to_int(const char* s);

int main(int argc, char** argv) {
    
    if (strcmp(argv[1], "--list") == 0) 
        display();

    else if (strcmp(argv[1], "--total") == 0) 
        total();

    else {
        spend(argv[1], argv[2]);
    }

    return 0;
}

void spend(const char* amount, const char* spent_on) {
    unsigned int spent;

    int c;
    int i = 0;

    //Inputting amount and spent_on

    printf("Amount: %s\n", amount);
    printf("Spent on: %s\n", spent_on);


    //Opening file for storing data
    FILE *ex;
    if ((ex = fopen("/home/naachiket/.expenses/expenses.dat", "a")) == NULL) {
        printf("Error opening expenses file. Exiting.....");
        exit(0);
    }

    fprintf(ex, "%s\t\t", amount);
    fprintf(ex, "%s\n", spent_on);

    fclose(ex);
}

void printMenu() {
    printf("1 --> Spend\n");
    printf("2 --> Total\n");
    printf("3 --> Display\n");
    printf("4 --> Exit\n");
}

void total() {
    FILE* ex;
    if ((ex = fopen("/home/naachiket/.expenses/expenses.dat", "r")) == NULL) {
        printf("Error opening expenses file. Exiting.....");
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

    fclose(ex);
    free(spent_money);
}

void display() {
    FILE* ex;
    if ((ex = fopen("/home/naachiket/.expenses/expenses.dat", "r")) == NULL) {
        printf("Error opening expenses file. Exiting.....");
        exit(0);
    }

    printf("List:\n");
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

























