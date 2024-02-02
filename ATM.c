#include <stdio.h>
#include <ctype.h>

int balance = 1000;
//function for displaying ATM
int display_menu();
void add_balance(); 
void view_balance();
void withdraw();
void print_receipt();


int main (void){

    enum operation {view = 1, add, withdrawal, receipt, stop};

    int flag = 1;
    int choice;
    
    do {

        choice = display_menu();
       
    
        if(choice == view){
            view_balance();
        } else if (choice == add){
            add_balance();
        } else if (choice == withdrawal){
           withdraw();
        } else if (choice == receipt){
            print_receipt();
            flag = 0;
        } else if (choice == stop){
           flag = 0;
        }

    } while(flag);

    printf("\nHave a nice day..");

}

//Function that displays the menu

int display_menu(void){
    
    int choice;
    printf("ATM\n");
    printf("1. View balance\n");
    printf("2. Deposit\n");
    printf("3. Withdraw\n");
    printf("4. Receipt\n");
    printf("5. EXIT\n");

    scanf("%d", &choice);
    
    return choice;
    
}

//

void view_balance(){
     printf("\nAccount:");
     printf("\nAccount balance: %d €\n", balance);
}       

//Function checks accounts balance

void add_balance(){
    int amount = 0;
    printf("\nGive amount: ");
    scanf("%d", &amount);
    if(amount > 0 ){
        balance += amount;
    }
    printf("\n");
}

//Function for withdrawal

void withdraw(){
    int amount = 0;
    int choice = 1;
    
    while(choice){

        view_balance();
        printf("\nGive amount: ");
        scanf("%d", &amount);
        if((balance >= amount)){
            balance -= amount;
        } else if (amount > balance) {
            printf("\namount too large");
        } else if (balance = 0){
            printf("\nbalance is zero");
        }
    }
}

void print_receipt(){
    printf("\nReceipt\n");
    printf("Account balance: %d", balance);
    printf("\n");
}