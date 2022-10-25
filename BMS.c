#include <stdio.h>
#include <stdlib.h>

// Struct Declarations
// This is all information about a bank account
struct Account
{
    // Personal info
    char* username; // username
    char* password; // password
    int accountNum; // account number
    int dob; // date of birth
    int age; // age
    int phoneNum; // phone number
    int address; // address
    // Financial info
    char* accountType; // "checking" or "savings"
    double balance; // account balance
};

// Function Declarations
void printMainHeader();
int promptInputNum(char* options, int numOptions, char* header);

// Main function
int main (void)
{
    // Local Declarations
    int input;

    // Statements
    char* mainMenuOptions = {"1. Create New Account\n2. Sign-in\n3. Close Account\n4. View customer list\n5. Exit"};
    // Loop the main menu prompt
    do
    {
        input = promptInputNum(mainMenuOptions, 5, "--- Welcome to the Main Menu ---");
        printf("\nYou chose option %d!\n", input);
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