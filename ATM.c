/*  ATM program
    
    Written by Juho Ryynänen

    With this small ATM program user can view account information, add money, withdraw money and print recipe

    Maybe to-do: 
    1. Update data to file when deposit and withdrawal are completed.
    2. File for logging transactions.
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <errno.h>


#define MAX_ACCOUNTS 100

typedef struct {
    int accountId;
    char creditCard[30];
    int pin;
    char name[30];
    double balance;
} Account;

Account Accounts[MAX_ACCOUNTS];

bool readAccounts();
void deposit(Account *customer); 
void viewBalance(Account customer);
void withdraw(Account *customer);
void printReceipt(Account customer);
void runATM();
void displayMenu();
bool userValid(char creaditCard[30], int pin);


Account userSelection(char creaditCard[30], int pin);


int main (void){

    readAccounts();
    runATM();
   
    return 0;

}


void runATM(){
     Account customer;

    //printf("%s %d", Accounts[0].creditCard,  Accounts[0].pin);
    enum operation {view = 1, add, withdrawal, receipt, stop};

    int flag = 0,  logged = 1,  tries = 3, choice, pin;
    char card[30];
  

    while(logged == 1){
        
        printf("-ATM-\n");
        printf("\nCARD:");
        scanf("%s", card);
        
        if(strcmp("exit", card) == 0){
            printf("Goodbye!..");
            exit(0);
        }

        printf("\nPIN: ");
        scanf("%d", &pin);
       
        if(userValid(card, pin)){
            
            customer = userSelection(card, pin);
            logged = 0;
            printf("Welcome! %s\n", customer.name);
    
        } else if (!userValid(card, pin)) {
            
            printf("\nDeclined, take card...\n");
            tries++;
        } 
    }

    do {
  
        displayMenu();
        printf("\n> ");
        scanf("%d", &choice);

        switch (choice)
        {
        case view:
           viewBalance(customer);
        break;

        case add:
            deposit(&customer);
        break;

        case withdrawal:
            withdraw(&customer);
        break;

        case receipt:
             printReceipt(customer);
        break;
        
        case stop:
            exit(0);
            break;
        }
   
    } while(true);

    printf("\nHave a nice day..");
}

//Function that displays the menu

void displayMenu(void){
    
    const char *menu[] = {
        "View balance",
        "Deposit",
        "Withdraw",
        "Receipt",
        "Exit"
    };

    printf("------ATM-------\n");

    for(int i = 0; i < sizeof(menu) / sizeof(menu[0]); i++){
        printf("%d. %s\n", i+1, menu[i]);
    }

}


void viewBalance(Account a){
     printf ("\nAccount information");
     printf("\n%s", a.creditCard);
     printf("\nAvailable Balance: %lf €\n", a.balance);
     printf("\nTransactions");
     printf("\n");
   
}       


void deposit(Account *a){
    
    int amount = 0;
   
    printf("\nSUM: ");
    scanf("%d", &amount);
   
    if(amount > 0 ){
        a->balance += amount;
    }
   
    printf("\n");
 
}


void withdraw(Account *user){
   
    int amount = 0;
    int choice = 1;
    
    while(choice){

        viewBalance(*user);
        printf("\nSUM: ");
        scanf("%d", &amount);
        
        if((user->balance >= amount)){
            user->balance -= amount;
            choice = 0;
        } 
        if (amount > user->balance) {
            printf("\nError in withdrawal");
        } 
        if (user->balance == 0){
            printf("\nError in withdrawal");
        }
    }

}

void printReceipt(Account a){
    
    // Time reading
    time_t now = time(&now);
    struct tm *ptm = gmtime(&now);
    
    printf("\nReceipt\n");
    printf("Time: %s", asctime(ptm));
    printf("Account balance: %d\n", a.balance);
    printf("Card holder: %s\n", a.name);

    printf("\n");
}


bool readAccounts(){

    FILE *file = fopen("accounts.txt", "r");

    int errnum;
    
    if (file == NULL)
    {
        fprintf(stderr, "\nOUT OF ORDER! %s\n", strerror( errnum ));
        return false;
    }
    
    int read = 0;
    int records = 0;

    do {
     
      read = fscanf(file, "%d,%29[^,],%d,%29[^,],%lf\n",
                      &Accounts[records].accountId,
                      Accounts[records].creditCard,
                      &Accounts[records].pin,
                      Accounts[records].name,
                      &Accounts[records].balance);

        if(read == 5) {
            records++; 
        } else if (read != 5 && !feof(file)){
            printf("Error in file format.");
            return 1;
        }

    } while (!feof(file));
   
     fclose(file);
    
}

bool userValid(char creditCard[30], int pin) {
    for (int i = 0; i < MAX_ACCOUNTS; i++) {
        int compare = strcmp(Accounts[i].creditCard, creditCard);
        if (compare == 0 && Accounts[i].pin == pin) {
            return true;
        }
    }
    return false;
}

Account userSelection(char card[30], int pin){

    for(int i = 0; i < MAX_ACCOUNTS; i++){
        int compare = strcmp(Accounts[i].creditCard, card);
        if (compare == 0 && Accounts[i].pin == pin) {
            return Accounts[i];
        } else {
            printf("\nError in user selection.");
        }
    }

}