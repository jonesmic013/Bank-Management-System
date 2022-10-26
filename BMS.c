#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struct Declarations
// This is all information about a bank account
struct Account
{
    // Personal info
    char username[21]; // username
    char password[21]; // password
    char accountNum[7]; // account number
    char dob[9]; // date of birth
    char phoneNum[11]; // phone number
    char address[64]; // address
    // Financial info
    char accountType[9]; // "checking" or "savings"
    double balance; // account balance
};

// Function Declarations
void printMainHeader();
int promptInputNum(char* options, int numOptions, char* header);

void createAccount();
void signIn();
void closeAccount();
void viewCustomerList();

// Main function
int main (void)
{
    // Local Declarations
    int input;
    struct Account* accounts;

    // Statements
    char* mainMenuOptions = {"1. Create New Account\n2. Sign-in\n3. Close Account\n4. View customer list\n5. Exit"};
    // Loop the main menu prompt
    do
    {
        input = promptInputNum(mainMenuOptions, 5, "--- Welcome to the Main Menu ---");
        switch (input)
        {
            case 1: createAccount();
                    break;
            case 2: //signIn();
                    break;
            case 3: //closeAccount();
                    break;
            case 4: //viewCustomerList();
                    break;
        }
    } while (input != 5); // Option 5 - Exit: Exits the program

    return 0;
    // main
}

// Print the header for the program
void printMainHeader()
{
    // This will likely be used every time a new input menu is displayed
    printf("===========================================\n");
    printf("= CUSTOMER BANK ACCOUNT MANAGEMENT SYSTEM =\n");
    printf("===========================================\n");
}

// Prompt the user to enter a number until they enter a valid option
int promptInputNum(char* options, int numOptions, char* header)
{
    // Local Declarations
    int input;

    // Statements
    // Keep asking the user for input so long as they give an invalid choice
    do
    {
        input = 0;
        printMainHeader();
        printf("%s\n", header);
        printf("%s\n", options);

        scanf("%d", &input);
        if (input < 1 || input > numOptions)
        {
            printf("Invalid option! Please enter one of the listed choices.\n");
        }
    } while (input < 1 || input > numOptions);

    return input;
}

// Loop the create account menu
void createAccount()
{
    // Local Declarations
    struct Account newAccount;
    // the user will be asked for username/pw/dob/phone/address

    // Statements
    // Initialize each member of the newAccount struct
    printMainHeader();
    printf("--- Create Account ---");

    // Choose for username
    // TODO: check for duplicate usernames on account creation
    printf("\nEnter a username (20 characters max) -> ");
    scanf("%19s", newAccount.username);

    // Choose for password
    printf("Enter a password (20 characters max) -> ");
    scanf("%19s", newAccount.password);

    // Randomly generated account number
    // Logic: The first character from the username followed by a random 5 digit number
    // TODO: check for duplicate account numbers on account creation
    char number[7] = "";
    char randomNum[6];
    sprintf(randomNum, "%d", rand() % 99999 + 10000);
    strcat(number, (char[2]) {newAccount.username[0], '\0'});
    strcat(number, randomNum);
    strcpy(newAccount.accountNum, number);

    // Enter Date-of-Birth
    // TODO: loop until an 8 digit number string is entered
    printf("Enter Date-of-Birth (MMDDYYYY) -> ");
    scanf("%8s", newAccount.dob);

    // Enter phone number
    // TODO: loop until a 10 digit number string is entered
    printf("Enter 10-digit Phone Number -> ");
    scanf("%10s", newAccount.phoneNum);

    // Enter address
    printf("Enter address -> ");
    scanf("\n%[^\n]", newAccount.address);

    // Enter account type
    // TODO: loop until "checking" or "savings" is entered
    printf("Enter account type (\"checking\" or \"savings\") -> ");
    scanf("%8s", newAccount.accountType);

    // Initialize balance
    newAccount.balance = 0.0;
}