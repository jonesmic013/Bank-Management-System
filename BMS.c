#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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
struct Account* accounts;
int numAccounts;

// Function Declarations
void printMainHeader();
int promptInputNum(char*, int, char*);
int usernameExists(char[21]);
int correctPassword(char[21], char[21]);
int accountNumExists(char[7]);
int isDigitString(char*, int);
int indexOfAccount(char[21]);

void createAccount();
void signIn();
void closeAccount();
void viewCustomerList();

// Main function
int main (void)
{
    // Local Declarations
    int input;

    // Statements
    numAccounts = 0;
    accounts = malloc(numAccounts * sizeof(struct Account));
    char* mainMenuOptions = {"1. Create New Account\n2. Sign-in\n3. Close Account\n4. View customer list\n5. Exit"};
    // Loop the main menu
    do
    {
        input = promptInputNum(mainMenuOptions, 5, "--- Welcome to the Main Menu ---");
        switch (input)
        {
            case 1: createAccount();
                    break;
            case 2: //signIn();
                    break;
            case 3: closeAccount();
                    break;
            case 4: viewCustomerList();
                    break;
        }
    } while (input != 5); // Option 5 - Exit: Exits the program

    return 0;
    // main
}

// Print the header for the program
void printMainHeader()
{
    // Statements
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

// Return if the given username exists (is taken)
int usernameExists(char username[21])
{
    // Statements
    for (int i = 0; i < numAccounts; i++)
    {
        if (!strcmp(accounts[i].username, username)) // 0 means they match for some reason
        {
            return 1;
        }
    }
    return 0;
}

// Return if the given password is correct for the given username
int correctPassword(char username[21], char password[21])
{
    // Statements
    for (int i = 0; i < numAccounts; i++)
    {
        if (!strcmp(accounts[i].username, username) && !strcmp(accounts[i].password, password)) // 0 means they match for some reason
        {
            return 1;
        }
    }
    return 0;
}

// Return if the given account number exists (to prevent duplicates)
int accountNumExists(char number[7])
{
    // Statements
    for (int i = 0; i < numAccounts; i++)
    {
        if (!strcmp(accounts[i].accountNum, number)) // 0 means they match for some reason
        {
            return 1;
        }
    }
    return 0;
}

// Return if the given string is strictly digits with the given number of digits
int isDigitString(char* str, int digits)
{
    // Statements
    // If string entered was too short
    if (strlen(str) != digits)
    {
        return 0;
    }
    for (int i = 0; i < digits; i++)
    {
        // If any char in the string is NOT a number
        if (!isdigit((int) str[i]))
        {
            return 0;
        }
    }
    return 1;
}

// Return the array index of the given account (username)
int indexOfAccount(char username[21])
{
    // Statements
    for (int i = 0; i < numAccounts; i++)
    {
        if (!strcmp(accounts[i].username, username)) // 0 means they match for some reason
        {
            return i;
        }
    }
    return -1; // Should never happen, since this function will only call when the account does exist
}

// Handle the create account menu
void createAccount()
{
    // Local Declarations
    struct Account newAccount;

    // Statements
    // Initialize each member of the newAccount struct
    printMainHeader();
    printf("--- Create Account ---\n");

    // Choose for username
    do
    {
        printf("Enter a username (20 characters max) -> ");
        scanf("%19s", newAccount.username);

        if (usernameExists(newAccount.username))
        {
            printf("This username is taken!\n");
        }
    } while (usernameExists(newAccount.username));

    // Choose for password
    printf("Enter a password (20 characters max) -> ");
    scanf("%19s", newAccount.password);

    // Randomly generated account number
    // Logic: The first character from the username followed by a random 5 digit number
    do // This realistically should almost never happen, but just to be safe
    {
        char tempNum[7] = "";
        char randomNum[6];
        sprintf(randomNum, "%d", rand() % 99999 + 10000);
        strcat(tempNum, (char[2]) {newAccount.username[0], '\0'});
        strcat(tempNum, randomNum);
        strcpy(newAccount.accountNum, tempNum);
    } while (accountNumExists(newAccount.accountNum));

    // Enter Date-of-Birth
    do
    {
        printf("Enter Date-of-Birth (MMDDYYYY) -> ");
        scanf("%8s", newAccount.dob);

        if (!isDigitString(newAccount.dob, 8))
        {
            printf("Invalid DOB!\n");
        }
    } while (!isDigitString(newAccount.dob, 8));

    // Enter phone number
    do
    {
        printf("Enter 10-digit Phone Number -> ");
        scanf("%10s", newAccount.phoneNum);

        if (!isDigitString(newAccount.phoneNum, 10))
        {
            printf("Invalid Phone Number!\n");
        }
    } while (!isDigitString(newAccount.phoneNum, 10));

    // Enter address
    printf("Enter address -> ");
    scanf("\n%[^\n]", newAccount.address);

    // Enter account type
    do
    {
        printf("Enter account type (\"checking\" or \"savings\") -> ");
        scanf("%8s", newAccount.accountType);

        if (strcmp(newAccount.accountType, "checking") && strcmp(newAccount.accountType, "savings"))
        {
            printf("Invalid option!\n");
        }
    } while (strcmp(newAccount.accountType, "checking") && strcmp(newAccount.accountType, "savings")); // 0 means they match for some reason

    // Initialize balance as zero
    newAccount.balance = 0.0;

    // Add this new account the the array of accounts
    numAccounts++;
    accounts = realloc(accounts, numAccounts * sizeof(struct Account));
    accounts[numAccounts - 1] = newAccount;
}

// Handle the close account menu
void closeAccount()
{

    // Local Declarations
    char username[21];
    char password[21];
    char accountNum[7];
    int input;
    int index;
    struct Account temp;

    // Statements
    printMainHeader();
    printf("--- Close Account ---\n");

    // Quick check for no existing account to even close
    if (numAccounts < 1)
    {
        printf("No accounts registered yet.\n");
        return;
    }

    // TODO: Have user enter account number as well to confirm identity
    // ^ This is waiting on the View Account Info menu, so you can find your account number

    // Ask for username
    do
    {
        printf("Enter username -> ");
        scanf("%19s", username);

        if (!usernameExists(username))
        {
            printf("Username does not exist!\n");
        }
    } while (!usernameExists(username));

    // Ask for password
    do
    {
        printf("Enter password -> ");
        scanf("%19s", password);

        if (!correctPassword(username, password))
        {
            printf("Incorrect password!\n");
        }
    } while (!correctPassword(username, password));

    // Confirm that the user would like to close their account
    char* confirmCloseOptions = {"1. Yes\n2. No"};
    input = promptInputNum(confirmCloseOptions, 2, "--- Are you sure you wish to close your account? ---");
    if (input == 1)
    {
        // Remove account from array
        index = indexOfAccount(username);
        for (int i = index; i < numAccounts - 1; i++)
        {
            accounts[i] = accounts[i + 1];
        }
        numAccounts--;
        accounts = realloc(accounts, numAccounts * sizeof(struct Account));
        printf("Account successfully closed.\n");
    }
}

// Show a list of all customers
// This one seemed a bit odd to me, since my banking app(s)
// don't do this... so I will just have it print a list of
// registered users' usernames.
void viewCustomerList()
{
    // Statements
    printMainHeader();
    printf("--- Registered Users ---\n");
    // No accounts exist yet
    if (numAccounts < 1)
    {
        printf("No accounts registered yet.\n");
    }
    // Otherwise print out all usernames
    for (int i = 0; i < numAccounts; i++)
    {
        printf("%d. %s\n", i + 1, accounts[i].username);
    }
}