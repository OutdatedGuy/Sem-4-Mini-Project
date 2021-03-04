#include <iostream>
#include <conio.h>

#include "headers/valid.cpp"

using namespace std;

#define lli long long int

int main()
{
    lli pNum;
notValidNum:
    cout << "Enter Your Phone Number: ";
    cin >> pNum;
    cin.clear();
    fflush(stdin);

    if (isValidNum(pNum))
    {
    notValidOp:
        system("cls");
        int op;
        cout << "1. Book Appointment" << endl;
        cout << "2. Search Appointment History" << endl;

        cin >> op;
        cin.clear();
        fflush(stdin);

        if (isValidOp(op, 2))
        {
        }
        else
        {
            cout << "\nPlease Select a VALID Option!\n"
                 << endl;
            cout << "Press Enter to continue...";
            getch();
            system("cls");
            goto notValidOp;
        }
    }
    else
    {
        cout << "\nGiven Phone Number is not VALID!\n"
             << endl;
        cout << "Press Enter to continue...";
        getch();
        system("cls");
        goto notValidNum;
    }

    return 0;
}
