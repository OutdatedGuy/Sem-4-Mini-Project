#include <iostream>
#include <string>
#include <fstream>
#include <conio.h>
#include <vector>
#include <ctime>
#include <windows.h>
using namespace std;

#define ll long long

//programmer defined headers
#include "headers/style.cpp"
#include "headers/files.cpp"
#include "headers/waiting.cpp"
#include "headers/valid.cpp"
#include "headers/password.cpp"
#include "headers/history.cpp"
#include "headers/booking.cpp"

int main()
{
    makePasswordFile();
    for (int i = 0; i < 3; i++)
        fillDoctorSchedule(2 - i);
    fillDoctorSchedule(2);

    ll pNum;
notValidNumber:
    heading("Login/SignUp");
    bool validUser = false;
    cout << "Enter Your Phone Number: ";
    cin >> pNum;
    // pNum = 9665143134; // for development ease
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
            // password = value; // for development ease
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
        heading("Main Menu");
        int op;
        cout << "1. Book Appointment" << endl;
        cout << "2. Search Appointment History" << endl;
        cout << "3. Re-Schedule Appointment" << endl;
        cout << "4. Cancel Appointment" << endl;
        cout << "5. Logout" << endl;
        cout << "\nEnter Your Choice: ";

        cin >> op;
        cin.clear();
        fflush(stdin);

        if (isValidOption(op, 5))
        {
            switch (op)
            {
            case 1:
                searchDoctor(pNum);
                break;

            case 2:
                appointmentHistory(pNum, false);
                break;

            case 3:
                cancelAppointment(pNum, true);
                break;

            case 4:
                cancelAppointment(pNum, false);
                break;

            default:
                goto notValidNumber;
            }

            goto notValidOption;
        }
        else
        {
            cout << "\nPlease Select a VALID Option! (from 1 to 5)" << endl;
            tryAgain();
            goto notValidOption;
        }
    }

    return 0;
}
