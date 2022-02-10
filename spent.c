#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 100

//TODO  
//Add feature for keeping track of monthly expenses

void spend();
void total();
void display();
int isnumber();
int string_to_int(const char* s);

int main(int argc, char** argv) {

    if (argc == 1) 
        printf("usage: spent amount spent_on\n");
    
    else if (strcmp(argv[1], "--help") == 0) 
        printf("usage: spent amount spent_on\n");

    else if (strcmp(argv[1], "--list") == 0) 
        display();

    else if (strcmp(argv[1], "--total") == 0) 
        total();

    else if (argc == 3 && isnumber(argv[1]) == 0 && isnumber(argv[2]) == -1) 
        spend(argv[1], argv[2]);
    
    else 
        printf("usage: spent amount spent_on\n");

    return 0;
}

void spend(const char* amount, const char* spent_on) {
    unsigned int spent;

    int c;
    int i = 0;


    printf("Amount: %s\n", amount);
    printf("Spent on: %s\n", spent_on);


    FILE *ex;
    if ((ex = fopen("/home/naachiket/.expenses/expenses.dat", "a")) == NULL) {
        printf("Error opening expenses file. Exiting.....");
        exit(0);
    }

    fprintf(ex, "%s\t\t", amount);
    fprintf(ex, "%s\n", spent_on);

    fclose(ex);
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

int isnumber(char s[]) {
    for (int i = 0; i < strlen(s); i++) {
        if (s[i] < '0' || s[i] > '9') 
            return -1;
    }
    return 0;
}
