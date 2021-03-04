#include <iostream>
#include <conio.h>

#include "headers/valid.cpp"
#include "headers/password.cpp"
#include "headers/booking.cpp"
#include "headers/history.cpp"

using namespace std;

#define lli long long int

void error()
{
    cout << "\nPress Enter to continue...";
    getch();
    system("cls");
}

int main()
{
    lli pNum;
    bool validUser = false;
notValidNumber:
    cout << "Enter Your Phone Number: ";
    cin >> pNum;
    cin.clear();
    fflush(stdin);

    if (isValidNumber(pNum))
    {
        string value = isExisting(pNum);
        if (value != "-1")
        {
            string password;
            cout << "Enter password: ";
            cin >> password;
            cin.clear();
            fflush(stdin);
            if (password == value)
                validUser = true;
            else
            {
                cout << "\nPassword does not Match!" << endl;
                error();
                goto notValidNumber;
            }
        }
        else
        {
            cout << "You are not an Existing User!" << endl;
            cout << "\nPress Enter to create a Password...";
            getch();
            system("cls");
            createPassword(pNum);
        }
    }
    else
    {
        cout << "\nGiven Phone Number is not VALID!" << endl;
        error();
        goto notValidNumber;
    }

    if (validUser)
    {
    notValidOption:
        system("cls");
        int op;
        cout << "1. Book Appointment" << endl;
        cout << "2. Search Appointment History" << endl;
        cout << "\n:";

        cin >> op;
        cin.clear();
        fflush(stdin);

        if (isValidOption(op, 2))
        {
            if (op == 1)
                bookAppointment(pNum);
            else
                appointmentHistory(pNum);
        }
        else
        {
            cout << "\nPlease Select a VALID Option!" << endl;
            error();
            goto notValidOption;
        }
    }

    return 0;
}