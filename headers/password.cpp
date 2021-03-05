#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>

using namespace std;

#define lli long long int

string isExisting(lli num)
{
    lli user;
    string code;
    fstream file;
    file.open("files/Login/password.txt", ios::in);

    while (!file.eof())
    {
        file >> user >> code;
        cout << user << " " << code << endl;

        if (num == user)
        {
            file.close();
            return code;
        }
    }
    return "-1";
}

bool registerUser(lli num, string password)
{
    fstream pass;
    pass.open("../files/Login/password.txt", ios::out);

    pass << num << " " << password << endl;
    pass.close();

    string value = isExisting(num);
    if (value != "-1" && value == password)
        return true;

    return false;
}

void createPassword(lli num)
{
    bool registered = false;
notValidPassword:
    cout << "Instructions:" << endl;
    cout << "1. Password should be 8 to 12 characters long" << endl;
    cout << "2. Spaces are not allowed" << endl;
    cout << "\nPress Enter to continue...";
    getch();
    system("cls");

    string password;
    cout << "Enter New Password: ";
    getline(cin, password);
    cin.clear();
    fflush(stdin);

    if (isValidPassword(password))
    {
        string pass2;
        cout << "\nEnter Password Again: ";
        getline(cin, pass2);
        cin.clear();
        fflush(stdin);
        if (password == pass2)
            registered = registerUser(num, password);
        else
        {
            cout << "\nPassword doesn't Match!" << endl;
            cout << "\nPress Enter to try Again...";
            getch();
            system("cls");
            goto notValidPassword;
        }
    }
    else
    {
        cout << "\nPassword not VALID!" << endl;
        cout << "\nPress Enter to try Again...";
        getch();
        system("cls");
        goto notValidPassword;
    }

    system("cls");
    if (registered)
        cout << "Your number is registered successfully!" << endl;
    else
        cout << "Your number is not registered due to some error!" << endl;

    cout << "\nPress Enter to continue...";
    getch();
}