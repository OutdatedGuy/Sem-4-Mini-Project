#include <iostream>
#include <string>
#include <fstream>
#include <conio.h>

using namespace std;

#define lli long long int

//programmer defined headers
#include "headers/files.cpp"
#include "headers/waiting.cpp"
#include "headers/valid.cpp"
#include "headers/password.cpp"
#include "headers/booking.cpp"
#include "headers/history.cpp"

int main()
{
    makePasswordFile();
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
            getline(cin, password);
            cin.clear();
            fflush(stdin);
            if (password == value)
                validUser = true;
            else
            {
                cout << "\nPassword does not Match!" << endl;
                waiting();
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
            goto notValidNumber;
        }
    }
    else
    {
        cout << "\nGiven Phone Number is not VALID!" << endl;
        waiting();
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
            waiting();
            goto notValidOption;
        }
    }

    return 0;
}