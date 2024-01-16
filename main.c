#include <stdio.h>
#include<string.h>
#include "validation.h"


#define acc_max 10
#define acc_holder_max 50
#define gender_max 10
#define address_max 50
#define aadhar_max 20
#define pan_card_max 20

struct bank_account{
    char acc_no[20];
    char acc_holder_name[acc_holder_max];
    int age;
    char gender[gender_max];
    char dob[address_max];
    char address[address_max];
    char city[acc_max];
    char acc_type[acc_max];
    int balance;
    char pan_card[pan_card_max];
    char  aadhar_number[aadhar_max];
}ba[50];
static int i=0;
void accept(int cus){

    for(int j=0;j<cus;j++){
            int validAadhar = 0;
            int validPan = 0;
        printf("\n***************Customer details *****************\n");
        while (1) {
            printf("Enter Account Holder name=");
            fgets(ba[i].acc_holder_name, acc_holder_max, stdin);
            ba[i].acc_holder_name[strlen(ba[i].acc_holder_name) - 1] = '\0';

            if (isValidNameFormat(ba[i].acc_holder_name)) {
                break;  // Break the loop if the name is in the correct format
            } else {
                printf("Invalid name format. Enter full name in firstname, middlename, and lastname format.\n");
            }
        }

        generateAccNo(ba[i].acc_holder_name, ba[i].acc_no);

         while (1) {
            printf("Enter age=");
            scanf("%d", &ba[i].age);
            getchar();

            if (isValidAge(ba[i].age)) {
                break;  // Break the loop if the age is valid
            } else {
                printf("Invalid age. Age should be between 18 and 99.\n");
            }
        }


        while (1) {
            printf("Enter dob=");
            fgets(ba[i].dob, 20, stdin);
            ba[i].dob[strlen(ba[i].dob) - 1] = '\0';

            if (isValidDOB(ba[i].dob)) {
                break;  // Break the loop if the dob is in the correct format
            } else {
                printf("Invalid dob format. Enter dob in the format dd/mm/yyyy, with valid day, month, and year.\n");
            }
        }

        while (1) {
            printf("Enter gender=");
            fgets(ba[i].gender, 20, stdin);
            ba[i].gender[strlen(ba[i].gender) - 1] = '\0';

            if (isValidGender(ba[i].gender)) {
                break;  // Break the loop if the gender is valid
            } else {
                printf("Invalid gender. Expected values are 'male', 'female', or 'other'.\n");
            }
        }

       do {
            printf("Enter Address=");
            fgets(ba[i].address, address_max, stdin);
            ba[i].address[strlen(ba[i].address) - 1] = '\0';

            if (!isValidAddress(ba[i].address)) {
                printf("Invalid address. Please enter a valid one.\n");
            }
        } while (!isValidAddress(ba[i].address));

        // Accept and validate city
        do {
            printf("Enter city=");
            fgets(ba[i].city, acc_max, stdin);
            ba[i].city[strlen(ba[i].city) - 1] = '\0';

            if (!isValidCity(ba[i].city)) {
                printf("Invalid city. Please enter a valid one.\n");
            }
        } while (!isValidCity(ba[i].city));

        // Accept and validate account type
        do {
            printf("Enter Account type (saving/current)=");
            fgets(ba[i].acc_type, acc_max, stdin);
            ba[i].acc_type[strlen(ba[i].acc_type) - 1] = '\0';

            if (!isValidAccountType(ba[i].acc_type)) {
                printf("Invalid account type. Please enter either 'saving' or 'current'.\n");
            }
        } while (!isValidAccountType(ba[i].acc_type));

        ba[i].balance=0;

        while (!validPan) {
            printf("Enter Pan Card number=");
            fgets(ba[i].pan_card, pan_card_max, stdin);
            ba[i].pan_card[strlen(ba[i].pan_card) - 1] = '\0';
            validPan = checkPanCard(ba[i].pan_card);

            if (!validPan) {
                printf("Invalid Pan Card number. Please enter a valid one.\n");
            }
        }

       while (!validAadhar) {
            printf("Enter Aadhar number=");
            fgets(ba[i].aadhar_number, aadhar_max, stdin);
            ba[i].aadhar_number[strlen(ba[i].aadhar_number) - 1] = '\0';
            validAadhar = checkAadhar(ba[i].aadhar_number);

            if (!validAadhar) {
                printf("Invalid Aadhar number. Please enter a valid one.\n");
            }
        }
        i++;
    }
}
    void display(int cus){
        for(int j=0;j<i;j++){
            printf("\n******************* Customer Details ************************\n");
            printf("account number=%s\n",ba[j].acc_no);
            printf("account holder name=%s\n",ba[j].acc_holder_name);
            printf("age=%d\n",ba[j].age);
            printf("gender=%s\n",ba[j].gender);
            printf("dob=%s\n",ba[j].dob);
            printf("address=%s\n",ba[j].address);
            printf("city=%s\n",ba[j].city);
            printf("account type=%s\n",ba[j].acc_type);
            printf("balance=%d\n",ba[j].balance);
            printf("pan card number=%s\n",ba[j].pan_card);
            printf("aadhar number=%s\n",ba[j].aadhar_number);
        }

}

void deposit(struct bank_account *accounts, int cus, const char acc_no[], int amount) {
    for (int i = 0; i < strlen(accounts); i++) {
        if (strcmp(accounts[i].acc_no, acc_no) == 0) {
            accounts[i].balance += amount;
            printf("Deposit successful. Updated balance for account %s: %d\n", acc_no, accounts[i].balance);
            return;
        }
    }

    printf("Account not found with the given account number.\n");
}

void withdraw(struct bank_account *accounts, int cus, const char acc_no[], int amount) {
    for (int i = 0; i < strlen(accounts); i++) {
        if (strcmp(accounts[i].acc_no, acc_no) == 0) {
            if (amount > 0 && amount <= accounts[i].balance) {
                accounts[i].balance -= amount;
                printf("Withdrawal successful. Updated balance for account %s: %d\n", acc_no, accounts[i].balance);
            } else {
                printf("Invalid withdrawal amount or insufficient balance for account %s.\n", acc_no);
            }
            return;
        }
    }

    printf("Account not found with the given account number.\n");
}

void balanceEnquiry(const struct bank_account *accounts, int cus, const char acc_no[]) {
    int found = 0;
    for (int i = 0; i < strlen(accounts); i++) {
        if (strcmp(accounts[i].acc_no, acc_no) == 0) {
            found = 1;
            printf("Balance for account %s: %d\n", acc_no, accounts[i].balance);
            break;
        }
    }

    if (!found) {
        printf("Account not found with the given account number.\n");
    }
}

void fundTransfer(struct bank_account *accounts, int cus, const char from_acc_no[], const char to_acc_no[], int amount) {
    int from_index = -1;
    int to_index = -1;

    // Find the indices of the source and destination accounts
    for (int i = 0; i < strlen(accounts); i++) {
        if (strcmp(accounts[i].acc_no, from_acc_no) == 0) {
            from_index = i;
        }
        if (strcmp(accounts[i].acc_no, to_acc_no) == 0) {
            to_index = i;
        }

        // If both source and destination accounts are found, break from the loop
        if (from_index != -1 && to_index != -1) {
            break;
        }
    }

    // Check if both accounts are found
    if (from_index != -1 && to_index != -1) {
        // Check if the source account has sufficient balance
        if (amount > 0 && amount <= accounts[from_index].balance) {
            // Perform funds transfer
            accounts[from_index].balance -= amount;
            accounts[to_index].balance += amount;

            printf("Funds transfer successful. Updated balance for account %s: %d\n", from_acc_no, accounts[from_index].balance);
            printf("Updated balance for account %s: %d\n", to_acc_no, accounts[to_index].balance);
        } else {
            printf("Invalid transfer amount or insufficient balance in account %s.\n", from_acc_no);
        }
    } else {
        printf("One or both of the accounts not found.\n");
    }
}


void searchAccountHolder(struct bank_account *accounts, int cus) {
    printf("Select the option to search:\n");
    printf("a. Search by account number\n");
    printf("b. Search by name\n");
    printf("c. Search by Type of Account\n");

    char option;
    getchar(); // Consume the newline character left by previous input
    scanf("%c", &option);

    switch (option) {
        case 'a': {
            char searchAccNo[20];
            printf("Enter account number to search: ");
            scanf("%s", searchAccNo);

            int found = 0;
            for (int i = 0; i < strlen(accounts); i++) {
                if (strcmp(accounts[i].acc_no, searchAccNo) == 0) {
                    printf("\n******************* Customer Details ************************\n");
                    printf("account number=%s\n", accounts[i].acc_no);
                    printf("account holder name=%s\n", accounts[i].acc_holder_name);
                    printf("age=%d\n",accounts[i].age);
                    printf("gender=%s\n",accounts[i].gender);
                    printf("dob=%s\n",accounts[i].dob);
                    printf("address=%s\n",accounts[i].address);
                    printf("city=%s\n",accounts[i].city);
                    printf("account type=%s\n",accounts[i].acc_type);
                    printf("balance=%d\n",accounts[i].balance);
                    printf("pan card number=%s\n",accounts[i].pan_card);
                    printf("aadhar number=%s\n",accounts[i].aadhar_number);
                    found = 1;
                    break;
                }
            }

            if (!found) {
                printf("Account not found with the given account number.\n");
            }
            break;
        }
        case 'b': {
            char searchName[50];
            printf("Enter name to search: ");
            getchar(); // Consume the newline character left by previous input
            fgets(searchName, sizeof(searchName), stdin);
            searchName[strlen(searchName) - 1] = '\0';

            int found = 0;
            for (int i = 0; i < strlen(accounts); i++) {
                if (strcmp(accounts[i].acc_holder_name, searchName) == 0) {
                    printf("\n******************* Customer Details ************************\n");
                    printf("account number=%s\n", accounts[i].acc_no);
                    printf("account holder name=%s\n", accounts[i].acc_holder_name);
                    printf("age=%d\n",accounts[i].age);
                    printf("gender=%s\n",accounts[i].gender);
                    printf("dob=%s\n",accounts[i].dob);
                    printf("address=%s\n",accounts[i].address);
                    printf("city=%s\n",accounts[i].city);
                    printf("account type=%s\n",accounts[i].acc_type);
                    printf("balance=%d\n",accounts[i].balance);
                    printf("pan card number=%s\n",accounts[i].pan_card);
                    printf("aadhar number=%s\n",accounts[i].aadhar_number);
                    found = 1;
                    break;
                }
            }

            if (!found) {
                printf("Account not found with the given name.\n");
            }
            break;
        }
        case 'c': {
            char searchType[10];
            printf("Enter Type of Account to search: ");
            scanf("%s", searchType);

            int found = 0;
            for (int i = 0; i < strlen(accounts); i++) {
                if (strcmp(accounts[i].acc_type, searchType) == 0) {
                    if (!found) {
                        printf("\n******************* Customer Details ************************\n");
                        found = 1;
                    }

                    printf("account number=%s\n", accounts[i].acc_no);
                    printf("account holder name=%s\n", accounts[i].acc_holder_name);
                    printf("age=%d\n",accounts[i].age);
                    printf("gender=%s\n",accounts[i].gender);
                    printf("dob=%s\n",accounts[i].dob);
                    printf("address=%s\n",accounts[i].address);
                    printf("city=%s\n",accounts[i].city);
                    printf("account type=%s\n",accounts[i].acc_type);
                    printf("balance=%d\n",accounts[i].balance);
                    printf("pan card number=%s\n",accounts[i].pan_card);
                    printf("aadhar number=%s\n",accounts[i].aadhar_number);
                }
            }

            if (!found) {
                printf("No accounts found with the given Type of Account.\n");
            }
            break;
}
        default:
            printf("Invalid option!\n");
    }
}



void updateAccountDetails(struct bank_account *accounts, int cus) {
    char searchAccNo[20];
    printf("Enter account number to search: ");
    scanf("%s", searchAccNo);

    int found = 0;
    for (int i = 0; i < strlen(accounts); i++) {
        if (strcmp(accounts[i].acc_no, searchAccNo) == 0) {
            found = 1;

            printf("Select the option to update:\n");
            printf("a. Update name of account holder\n");
            printf("b. Update address of account holder\n");
            printf("c. Update DOB of account holder\n");

            char option;
            getchar(); // Consume the newline character left by previous input
            scanf("%c", &option);

            switch (option) {
                case 'a':
                    printf("Enter new name: ");
                    getchar();
                    fgets(accounts[i].acc_holder_name, acc_holder_max, stdin);
                    accounts[i].acc_holder_name[strlen(accounts[i].acc_holder_name) - 1] = '\0';
                    break;
                case 'b':
                    printf("Enter new address: ");
                    getchar();
                    fgets(accounts[i].address, address_max, stdin);
                    accounts[i].address[strlen(accounts[i].address) - 1] = '\0';
                    break;
                case 'c':
                    printf("Enter new DOB (dd/mm/yyyy): ");
                    getchar();
                    fgets(accounts[i].dob, 20, stdin);
                    accounts[i].dob[strlen(accounts[i].dob) - 1] = '\0';
                    break;
                default:
                    printf("Invalid option!\n");
            }
            break;
        }
    }

    if (!found) {
        printf("Account not found with the given account number.\n");
    }
}

int main()
{
    int cus,choice;
    char ch;

    do
    {

        printf("\n*************** Welcome To HDFC Bank *****************\n");
        printf("1. Create Account\n");
        printf("2. Update Account Details\n");
        printf("3. Deposit\n");
        printf("4. Withdraw\n");
        printf("5. Funds Transfer\n");
        printf("6. Search details of account holder\n");
        printf("7. Balance Enquiry\n");
        printf("8. Display All Customers\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d",&choice);
        switch (choice) {
            case 1:
                printf("Enter the number of customers you want to insert=");
                scanf("%d",&cus);
                getchar();
                accept(cus);
                break;
            case 2:
                updateAccountDetails(ba, cus);
                break;
            case 3:
                printf("Enter account number to deposit into: ");
                char depositAccNo[20];
                scanf("%s", depositAccNo);

                int depositAmount;
                printf("Enter the amount to deposit: ");
                scanf("%d", &depositAmount);

                deposit(ba, cus, depositAccNo, depositAmount);
                break;
            case 4:
                printf("Enter account number to withdraw from: ");
                char withdrawAccNo[20];
                scanf("%s", withdrawAccNo);

                int withdrawAmount;
                printf("Enter the amount to withdraw: ");
                scanf("%d", &withdrawAmount);

                withdraw(ba, cus, withdrawAccNo, withdrawAmount);
                break;
            case 5:
                 printf("Enter source account number for funds transfer: ");
                char fromAccNo[20];
                scanf("%s", fromAccNo);

                printf("Enter destination account number for funds transfer: ");
                char toAccNo[20];
                scanf("%s", toAccNo);

                int transferAmount;
                printf("Enter the amount to transfer: ");
                scanf("%d", &transferAmount);

                fundTransfer(ba, cus, fromAccNo, toAccNo, transferAmount);
                break;
            case 6:
                searchAccountHolder(ba, cus);
                break;
            case 7:
                    printf("Enter account number for balance enquiry: ");
                    char enquiryAccNo[20];
                    scanf("%s", enquiryAccNo);

                    balanceEnquiry(ba, cus, enquiryAccNo);
                break;
            case 8:
                if(cus==0)printf("No records found");
                else
                display(cus);
                break;
            case 9:
                printf("Exiting the HDFC Bank application. Goodbye!\n");
                break;
            default:
                printf("Invalid choice! Please enter a valid option.\n");
                getchar();
                break;
        }
    }while(choice!=9);

    return 0;
}
