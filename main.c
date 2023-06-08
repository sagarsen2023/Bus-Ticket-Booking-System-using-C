#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STANDARD_SEATS 52
#define MAX_VOLVO_TYPE_SEATS 36
#define MAX_VOLVO_SEATS 28
#define MAX_VOLVO_SLEEPER_SEATS 20
#define MAX_NAME_LENGTH 100

typedef struct
{
    char username[100];
    char password[50];
} LoginDetails;

void user_login(int i);

void bus_selection();

void bus(char bus_number[16], int seats);

void reservation(int seat_total, char strings[][MAX_NAME_LENGTH], char bus_number[16]);

void main_menu();

void saveSeatInfo(char bus_number[16], char strings[][MAX_NAME_LENGTH], int seats);

void loadSeatInfo(char bus_number[16], char strings[][MAX_NAME_LENGTH], int seats);

void getloginDetails();

int main()
{
    system("cls");
    printf("Bus Ticket Booking System...\n\n");
    int i = 3;
    user_login(i);
    return 0;
}

void bus_selection()
{
    int bus_type, user;
    char bus_number[16];
    int valid_input = 0;

    printf("Enter the bus number: ");
    scanf("%15s", bus_number);
    printf("\nConsider the table below to select the type of the bus: ");
    printf("\nEnter 1 for Standard type (52 Seats).\nEnter 2 for Volvo type. (36 Seats)\n");
    printf("Enter 3 for Volvo. (28 seats)\nEnter 4 for Volvo sleeper. (20 Seats)\n");
    printf("Enter 5 for custom seat arrangement.\n");
    do
    {
        printf("Enter the bus type: ");
        if (scanf("%d", &bus_type) == 1)
        {
            if (bus_type >= 1 && bus_type <= 5)
            {
                valid_input = 1;
            }
            else
            {
                system("cls");
                printf("Invalid bus type. Please try again.\n");
                printf("The bus number is %s.\n", bus_number);
                printf("\nConsider the table below to select the type of the bus: ");
                printf("\nEnter 1 for Standard type (52 Seats).\nEnter 2 for Volvo type. (36 Seats)\n");
                printf("Enter 3 for Volvo. (28 seats)\nEnter 4 for Volvo sleeper. (20 Seats)\n");
                printf("Enter 5 for custom seat arrangement.\n");
            }
        }
        else
        {
            system("cls");
            printf("Invalid input. Please try again.\n");
            printf("The bus number is %s.\n", bus_number);
            printf("\nConsider the table below to select the type of the bus: ");
            printf("\nEnter 1 for Standard type (52 Seats).\nEnter 2 for Volvo type. (36 Seats)\n");
            printf("Enter 3 for Volvo. (28 seats)\nEnter 4 for Volvo sleeper. (20 Seats)\n");
            printf("Enter 5 for custom seat arrangement.\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF)
                ;
        }
    } while (!valid_input);

    switch (bus_type)
    {
    case 1:
        system("cls");
        bus(bus_number, MAX_STANDARD_SEATS);
        break;
    case 2:
        system("cls");
        bus(bus_number, MAX_VOLVO_TYPE_SEATS);
        break;
    case 3:
        system("cls");
        bus(bus_number, MAX_VOLVO_SEATS);
        break;
    case 4:
        system("cls");
        bus(bus_number, MAX_VOLVO_SLEEPER_SEATS);
        break;
    case 5:
        system("cls");
        printf("Enter how many seats are available in the bus: ");
        scanf("%d", &user);
        bus(bus_number, user);
        break;
    default:
        printf("Invalid bus type. Please try again.\n");
        break;
    }
}

void bus(char bus_number[16], int seats)
{
    char ch;
    printf("Showing details of Standard type bus with number: %s\n", bus_number);
    printf("Current seat arrangement:\n");

    char strings[seats][MAX_NAME_LENGTH];
    for (int i = 0; i < seats; i++)
    {
        strcpy(strings[i], "Empty");
    }
    loadSeatInfo(bus_number, strings, seats);

    for (int i = 1; i <= seats; i++)
    {
        printf("%d. %s\t", i, strings[i - 1]);
        if (i % 4 == 0)
            printf("\n");
    }

    printf("\n\nDo you want to add any passenger or cancel any booking? \nType y for yes and n for no: ");
    scanf(" %c", &ch);

    while (ch != 'n')
    {
        reservation(seats, strings, bus_number);
        printf("\nDo you want to add passenger or cancel bookings? (y/n): ");
        scanf(" %c", &ch);
    }
    system("cls");
    int valid_input = 0, selection;
    printf("Enter the bus type: ");
    do
    {
        if (scanf("%d", &selection) == 1)
        {
            if (selection >= 1 && selection <= 5)
            {
                valid_input = 1;
            }
            else
            {
                system("cls");
                printf("Invalid bus type. Please try again.\n");
                printf("The bus number is %d.\n", selection);
                printf("Do you want to get back to the main meny? Enter 1.\n");
                printf("Do you wamt to get back to the bus Selection menu? Enter 2.\n");
            }
        }
        else
        {
            system("cls");
            printf("Invalid bus type. Please try again.\n");
            printf("The bus number is %d.\n", selection);
            printf("Do you want to get back to the main meny? Enter 1.\n");
            printf("Do you wamt to get back to the bus Selection menu? Enter 2.\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF)
                ;
        }
    } while (!valid_input);

    switch (selection)
    {
    case 1:
        main_menu();
        break;
    case 2:
        bus_selection();
        break;
        default:
        printf("Wrong input");
        break;
    }
}

void reservation(int seat_total, char strings[][MAX_NAME_LENGTH], char bus_number[16])
{
    char name[MAX_NAME_LENGTH];
    int seat_number;
    int status = 0;
    printf("Enter 1 to book a seat.\nEnter 0 to cancel a booking.\n");
    printf("Enter your choice: ");
    scanf("%d", &status);
    if (status == 1)
    {
        printf("\nEnter the passenger's full name: ");
        getchar();
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = '\0';

        do
        {
            printf("Enter the seat he/she wants to book (1-%d): ", seat_total);
            scanf("%d", &seat_number);

            if (seat_number < 1 || seat_number > seat_total)
            {
                printf("Invalid seat number. Please try again.\n");
            }
            else if (strcmp(strings[seat_number - 1], "Empty") != 0)
            {
                printf("Seat already booked. Please choose a different seat.\n");
            }
            else
            {
                strcpy(strings[seat_number - 1], name);
                break;
            }
        } while (1);

        printf("Seat booking successful.\n\n");
        system("cls");
        printf("===================================\n\n");
        printf("Updated seat arrangement:\n");
        for (int i = 1; i <= seat_total; i++)
        {
            printf("%d. %s\t", i, strings[i - 1]);
            if (i % 4 == 0)
                printf("\n");
        }
        saveSeatInfo(bus_number, strings, seat_total);
    }
    else if (status == 0)
    {
        printf("\nEnter which seat to cancel: ");
        scanf("%d", &seat_number);
        if (seat_number < 1 || seat_number > seat_total)
        {
            printf("Invalid seat number. Please try again.\n");
        }
        else if (strcmp(strings[seat_number - 1], "Empty") != 0)
        {
            strcpy(strings[seat_number - 1], "Empty");
            printf("The seat number %d successfully canceled.\n", seat_number);
            system("cls");
        }
        else
        {
            system("cls");
            printf("The seat is already empty\n");
        }
        printf("===================================\n\n");
        printf("Updated seat arrangement:\n");
        for (int i = 1; i <= seat_total; i++)
        {
            printf("%d. %s\t", i, strings[i - 1]);
            if (i % 4 == 0)
                printf("\n");
        }
        saveSeatInfo(bus_number, strings, seat_total);
    }
    else
        printf("Enter valid input. Try again.\n");
}

void user_login(int i)
{
   getLoginDetails();
    FILE *file;
    LoginDetails details;
    file = fopen("login.dat", "rb");
    if (file == NULL)
    {
        printf("Login details file does not exist.\n");
        return;
    }
    fread(&details, sizeof(LoginDetails), 1, file);
    fclose(file);
    char u[100], p[50];
    printf("\nEnter the username: ");
    fgets(u, sizeof(u), stdin);
    u[strcspn(u, "\n")] = '\0';
    printf("Enter password: ");
    fgets(p, sizeof(p), stdin);
    p[strcspn(p, "\n")] = '\0';
    int error = 0;
    if (strcmp(u, details.username) == 0 && strcmp(p, details.password) == 0)
    {
        printf("You've successfully logged in.\n\n");
        system("cls");
        main_menu();
    }
    else
    {
        system("cls");
        printf("Please try again: You have %d attempts left", i);
        i--;
        if (i == -1)
        {
            printf("You have entered wrong password 3 times. Now your system is locked. \n");
            printf("Press any key to close the software.\n");
            getc;
        }
        else
        {
            user_login(i);
        }
    }
}

void main_menu()
{
    int valid_input = 0, input;
    printf("Invalid input. Please try again.\n");
    printf("Press 1 to enter the bus booking system.\n");
    printf("Press 2 to delete bus details.\n");
    printf("Press 3 to reset the whole system.\n");
    printf("Press 4 to logout and close the system.\n");
    do
    {
        printf("\nEnter your selection: ");
        if (scanf("%d", &input) == 1)
        {
            if (input >= 1 && input <= 4)
            {
                valid_input = 1;
            }
            else
            {
                system("cls");
                printf("Invalid input. Please try again.\n");
                printf("Press 1 to enter the bus booking system.\n");
                printf("Press 2 to delete bus details.\n");
                printf("Press 3 to reset the whole system.\n");
                printf("Press 4 to logout and close the system.\n");
            }
        }
        else
        {
            system("cls");
            printf("Invalid input. Please try again.\n");
            printf("Press 1 to enter the bus booking system.\n");
            printf("Press 2 to delete bus details.\n");
            printf("Press 3 to reset the whole system.\n");
            printf("Press 4 to logout and close the system.\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF)
                ;
        }
    } while (!valid_input);

    switch (input)
    {
    case 1:
        bus_selection();
        break;
    case 2:
        char busName[20];
        printf("Enter the bus number: ");
        scanf("%s", busName);
        if (remove(busName) == 0)
        {
            printf("Bus details named %s deleted successfully.", busName);
            printf("Enter any key to return to the main menu...");
            getc;
            main_menu();
        }
        else
        {
            printf("The file you want to delete either doesn't exist or unable to delete.\n");
            printf("Enter any key to return to the main menu...");
            getc;
            main_menu();
        }
        break;
    case 3:
        if (remove("login.dat") == 0)
        {
            printf("Login details reseted successfully.\n");
            printf("Press any key to exit this system.");
            getc;
            exit(1);
        }
        else
        {
            printf("Unable to reset login credentials.\n");
            printf("Enter any key to return to the main menu...");
            getc;
            main_menu();
        }
        break;
    case 4:
        exit(0);
        break;
    default:
        printf("Wrong input");
        break;
    }
}

void saveSeatInfo(char bus_number[16], char strings[][MAX_NAME_LENGTH], int seats)
{
    FILE *file = fopen(bus_number, "wb");
    if (file != NULL)
    {
        for (int i = 0; i < seats; i++)
        {
            fprintf(file, "%s\n", strings[i]);
        }
        fclose(file);
    }
    else
    {
        printf("Error saving seat information.\n");
    }
}

void loadSeatInfo(char bus_number[16], char strings[][MAX_NAME_LENGTH], int seats)
{
    FILE *file = fopen(bus_number, "r");
    if (file != NULL)
    {
        for (int i = 0; i < seats; i++)
        {
            if (fgets(strings[i], MAX_NAME_LENGTH, file) != NULL)
            {
                strings[i][strcspn(strings[i], "\n")] = '\0';
            }
        }
        fclose(file);
    }
    else
    {
        for (int i = 0; i < seats; i++)
        {
            if (strcmp(strings[i], "Empty") != 0)
            {
                strcpy(strings[i], "Empty");
            }
        }
    }
}

void getLoginDetails()
{
    FILE *file;
    LoginDetails details;

    file = fopen("login.dat", "rb");
    if (file != NULL)
    {
        fclose(file);
        return;
    }

    file = fopen("login.dat", "wb");
    if (file == NULL)
    {
        printf("Failed to create login details file.\n");
        return;
    }

    printf("Terms and Conditions:\n");
    printf("1. Only authorized users are allowed to access the system.\n");
    printf("2. Unauthorized access is prohibited.\n");
    printf("Developer: Sagar Sen.\n");
    printf("\nEnter the username: ");
    fgets(details.username, sizeof(details.username), stdin);
    details.username[strcspn(details.username, "\n")] = '\0';
    printf("Enter password: ");
    fgets(details.password, sizeof(details.password), stdin);
    details.password[strcspn(details.password, "\n")] = '\0';

    fwrite(&details, sizeof(LoginDetails), 1, file);
    fclose(file);

    printf("\nLogin details created successfully.\n");
    system("cls");
}
