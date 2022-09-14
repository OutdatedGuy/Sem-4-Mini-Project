string isExisting(ll num)
{
    ll user;
    string code;
    fstream file;
    file.open("database/Login/password.txt", ios::in);

    while (!file.eof())
    {
        file >> user >> code;

        if (num == user)
        {
            file.close();
            return code;
        }
    }
    file.close();
    return "-1";
}

bool registerUser(ll num, string password)
{
    fstream pass;
    pass.open("database/Login/password.txt", ios::app);

    pass << num << " " << password << endl;
    pass.close();

    string value = isExisting(num);
    if (value != "-1" && value == password)
        return true;

    return false;
}

void createPassword(ll num)
{
    bool registered = false;
notValidPassword:
    heading("Registration Instructions");
    cout << "Instructions:" << endl;
    cout << "1. Password should be 8 to 12 characters long" << endl;
    cout << "2. Spaces are not allowed" << endl;
    waiting();

    heading("Create Password");

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
            tryAgain();
            goto notValidPassword;
        }
    }
    else
    {
        cout << "\nPassword not VALID!" << endl;
        tryAgain();
        goto notValidPassword;
    }

    heading("Registration");
    if (registered)
    {
        makeUserDirectory(to_string(num));
        cout << "Your number is registered successfully!" << endl;
    }
    else
        cout << "Your number is not registered due to some error!" << endl;

    waiting();
}