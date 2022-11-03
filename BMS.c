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
int correctAccountNum(char[21], char[7]);
int accountNumExists(char[7]);
int isDigitString(char*, int);
int indexOfAccount(char[21]);
struct Account getAccount(char[21]);

void createAccount();
void signIn();
void closeAccount();
void viewCustomerList();

void accountMenu(struct Account);
void printAccountInfo(struct Account);
struct Account changePassword(struct Account);
struct Account deposit(struct Account);
struct Account withdraw(struct Account);

void saveToFile();
void readFile();

// Main function
int main (void)
{
    // Local Declarations
    int input;

    // Statements
    numAccounts = 0;
    accounts = malloc(numAccounts * sizeof(struct Account));
    readFile();
    char* mainMenuOptions = "1. Create New Account\n2. Sign-in\n3. Close Account\n4. View customer list\n5. Exit";
    // Loop the main menu
    do
    {
        input = promptInputNum(mainMenuOptions, 5, "--- Welcome to the Main Menu ---");
        switch (input)
        {
            case 1: createAccount();
                    break;
            case 2: signIn();
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
    readFile();
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
    readFile();
    for (int i = 0; i < numAccounts; i++)
    {
        if (!strcmp(accounts[i].username, username) && !strcmp(accounts[i].password, password)) // 0 means they match for some reason
        {
            return 1;
        }
    }
    return 0;
}

// Return if the given account number is correct for the given username
int correctAccountNum(char username[21], char accountNum[7])
{
    // Statements
    readFile();
    for (int i = 0; i < numAccounts; i++)
    {
        if (!strcmp(accounts[i].username, username) && !strcmp(accounts[i].accountNum, accountNum)) // 0 means they match for some reason
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
    readFile();
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
    readFile();
    for (int i = 0; i < numAccounts; i++)
    {
        if (!strcmp(accounts[i].username, username)) // 0 means they match for some reason
        {
            return i;
        }
    }
    return -1; // Should never happen, since this function will only call when the account does exist
}

// Return the account with the given username
// Since this is only called when signing in, it is implied that the username does exist
// So it can't ever NOT return an account
struct Account getAccount(char username[21])
{
    // Statements
    readFile();
    for (int i = 0; i < numAccounts; i++)
    {
        if (!strcmp(accounts[i].username, username)) // 0 means they match for some reason
        {
            return accounts[i];
        }
    }
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

        if (strcmp(newAccount.accountType, "checking") && strcmp(newAccount.accountType, "savings")) // 0 means they match for some reason
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
    saveToFile();
}

// Handle the sign in menu
void signIn()
{
    // Local Declarations
    char username[21];
    char password[21];

    // Statements
    printMainHeader();
    printf("--- Sign-in ---\n");

    // Quick check for no existing account to even sign-in to
    if (numAccounts < 1)
    {
        printf("No accounts registered yet.\n");
        return;
    }

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

    // Now enter the account menu with the account we signed into
    accountMenu(getAccount(username));
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

    // Statements
    printMainHeader();
    printf("--- Close Account ---\n");

    // Quick check for no existing account to even close
    if (numAccounts < 1)
    {
        printf("No accounts registered yet.\n");
        return;
    }

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

    // Ask for account number
    do
    {
        printf("Enter account number -> ");
        scanf("%6s", accountNum);

        if (!correctAccountNum(username, accountNum))
        {
            printf("Invalid account number!\n");
        }
    } while (!correctAccountNum(username, accountNum));

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
        saveToFile();
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
    readFile();
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

// Handle the menu once you've signed in
void accountMenu(struct Account account)
{
    // Local Declarations
    int input;

    // Statements
    char* accountMenuOptions = "1. View Account Info\n2. Change Password\n3. Deposit\n4. Withdraw\n5. Sign-out";
    char header[39] = "--- Account: ";
    strcat(header, account.username);
    strcat(header, " ---");
    // Loop the account menu
    do
    {
        input = promptInputNum(accountMenuOptions, 5, header);
        switch (input)
        {
            case 1: printAccountInfo(account);
                    break;
            case 2: account = changePassword(account);
                    break;
            case 3: account = deposit(account);
                    break;
            case 4: account = withdraw(account);
                    break;
        }
    } while (input != 5); // Option 5 - Sign-out: exits this menu effectively signing out
}

// Print out all account information, including current balance
void printAccountInfo(struct Account account)
{
    // Statements
    printMainHeader();
    printf("ACCOUNT TYPE: %s\n", account.accountType);
    printf("BALANCE: %.2lf\n", account.balance);
    printf("\nUsername: %s\n", account.username);
    printf("Password: %s\n", account.password);
    printf("Account Number: %s\n", account.accountNum);
    printf("Date-of-Birth: ");
    for (int i = 0; i < strlen(account.dob); i++)
    {
        printf("%c", account.dob[i]);
        if (i == 1 || i == 3)
        {
            printf("/");
        }
    }
    printf("\nPhone Number: ");
    for (int i = 0; i < strlen(account.phoneNum); i++)
    {
        printf("%c", account.phoneNum[i]);
        if (i == 2 || i == 5)
        {
            printf("-");
        }
    }
    printf("\nAddress: %s\n", account.address);
}

// Change password menu, pretty standard for anything with accounts
struct Account changePassword(struct Account account)
{
    // Local Declarations
    char password[21];

    // Statements
    printMainHeader();
    printf("--- Change Password ---\n");
    // Enter current password
    do
    {
        printf("Enter current password -> ");
        scanf("%19s", password);

        if (strcmp(password, account.password)) // 0 means they match for some reason
        {
            printf("Incorrect password!\n"); 
        }
    } while (strcmp(password, account.password)); // 0 means they match for some reason

    // Enter new password
    do
    {
        printf("Enter new password -> ");
        scanf("%19s", password);

        if (!strcmp(password, account.password)) // 0 means they match for some reason
        {
            printf("Must be a different password!\n"); 
        }
    } while (!strcmp(password, account.password)); // 0 means they match for some reason

    // Return newly changed account to keep messing with in the account menu
    strcpy(account.password, password);
    accounts[indexOfAccount(account.username)] = account;
    saveToFile();
    return account;
}

// Deposit money into your account
struct Account deposit(struct Account account)
{
    // Local Declarations
    double amount;

    // Statements
    printMainHeader();
    printf("--- Deposit ---\n");
    // Ask for deposit amount
    do
    {
        printf("Current Balance: %.2lf\n", account.balance);
        printf("Enter deposit amount -> ");
        scanf("%lf", &amount);

        if (amount < 0.0)
        {
            printf("Must enter a positive value!\n");
        }
    } while (amount < 0.0);

    account.balance += amount;
    printf("New Balance: %.2lf\n", account.balance);

    // Return newly changed account to keep messing with in the account menu
    accounts[indexOfAccount(account.username)] = account;
    saveToFile();
    return account;
}

// Withdraw money from your account
struct Account withdraw(struct Account account)
{
    // Local Declarations
    double amount;

    // Statements
    printMainHeader();
    printf("--- Withdraw ---\n");
    // Ask for withdraw amount
    do
    {
        printf("Current Balance: %.2lf\n", account.balance);
        printf("Enter withdraw amount -> ");
        scanf("%lf", &amount);

        if (amount < 0.0)
        {
            printf("Must enter a positive value!\n");
        }
        if (amount > account.balance)
        {
            printf("Not enough funds for withdraw!\n");
        }
    } while (amount < 0.0 || amount > account.balance);

    account.balance -= amount;
    printf("New Balance: %.2lf\n", account.balance);

    // Return newly changed account to keep messing with in the account menu
    accounts[indexOfAccount(account.username)] = account;
    saveToFile();
    return account;
}

// Write accounts data to the data file
void saveToFile()
{
    // Opon the binary file for writing
    FILE* fptr;
    fptr = fopen("accounts.bin","wb");

    // Write data to the file
    fwrite(&numAccounts, sizeof(numAccounts), 1, fptr);
    for (int i = 0; i < numAccounts; i++)
    {
        fwrite(&accounts[i], sizeof(struct Account), 1, fptr);
    }

    // Lastly close the file
    fclose(fptr);
}

// Read accounts data from the data file
void readFile()
{
    // Opon the binary file for reading
    FILE* fptr;
    fptr = fopen("accounts.bin","rb");

    // Read data from the file
    fread(&numAccounts, sizeof(numAccounts), 1, fptr);
    accounts = realloc(accounts, numAccounts * sizeof(struct Account));
    for (int i = 0; i < numAccounts; i++)
    {
        fread(&accounts[i], sizeof(struct Account), 1, fptr);
    }

    // Lastly close the file
    fclose(fptr);
}