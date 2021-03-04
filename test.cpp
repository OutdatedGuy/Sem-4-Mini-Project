#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#define lli long long int

int main()
{
    string bat;
    lli num;
    fstream file;
    file.open("files/Login/password.txt", ios::in);
    while (!file.eof())
        file >> num >> bat;
    file.close();

    cout << num << bat;
}
