#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 100

void printMenu();
void spend();
void total();
void display();

int main(void) {

    while(1) {
        printMenu();
        int choice;
        choice = getchar();

        switch(choice) {
            case '1':
                spend();
                break;
            case '2':
                total();
                break;
            case 3:
                display();
                break;
            default:
                printf("Wrong entry please try again\n");
                break;
        }
    }

    return 0;
}

void spend() {
    unsigned int spent;
    char* spent_on = malloc(sizeof(char) * MAXSIZE);
    char* amount = malloc(sizeof(char) * MAXSIZE); 

    while (1) {
        int c;
        int i = 0;

        //Inputting amount and spent_on
        printf("Enter amount spent: \n");
        while((c = getchar()) != '\n' && c != EOF){
            amount[i++] = c;
        }
        if (strcmp(amount, "done") == 0) {
            printf("Bye!\n");
            break;
        }

        i = 0;
        printf("Enter thing you spent amount on: \n");
        while((c = getchar()) != '\n' && c != EOF) {
            spent_on[i++] = c;
        }
        if (strcmp(spent_on, "done") == 0){
            printf("Bye!\n");
            break;
        }

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
        
        //clearing the strings
        memset(spent_on, 0, sizeof spent_on);
        memset(amount, 0, sizeof amount);
    }
}

void printMenu() {
    printf("1 --> Spend\n");
    printf("2 --> Total\n");
    printf("3 --> Display\n");
}

void total() {

}

void display() {

}



























