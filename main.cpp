#include <iostream>
#include <string>
#include <fstream>
#include <conio.h>
#include <vector>
using namespace std;

#define ll long long

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
    ll pNum;
    bool validUser = false;
notValidNumber:
    cout << "Enter Your Phone Number: ";
    // cin >> pNum;
    pNum = 9665143134; // for development ease
    cin.clear();
    fflush(stdin);

    if (isValidNumber(pNum))
    {
        string value = isExisting(pNum);
        if (value != "-1")
        {
            string password;
            cout << "Enter password: ";
            // getline(cin, password);
            cin.clear();
            fflush(stdin);
            password = value; // for development ease
            if (password == value)
                validUser = true;
            else
            {
                cout << "\nPassword does not Match!" << endl;
                tryAgain();
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
        tryAgain();
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
                searchDoctor(pNum);
            else
                appointmentHistory(pNum);

            goto notValidOption;
        }
        else
        {
            cout << "\nPlease Select a VALID Option!" << endl;
            tryAgain();
            goto notValidOption;
        }
    }

    return 0;
}
