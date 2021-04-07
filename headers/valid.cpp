bool isValidNumber(ll num)
{
    for (int i = 0; i < 10; i++)
    {
        if (num == 0)
            return false;

        if ((num % 10) < 0 || (num % 10) > 9)
            return false;

        num /= 10;
    }

    if (num != 0)
        return false;

    return true;
}

bool isValidOption(int op, int n)
{
    if (op < 1 || op > n)
        return false;
    return true;
}

bool isValidPassword(string pass)
{
    int len = pass.length();

    if (len < 8 || len > 12)
        return false;

    for (int i = 0; i < len; i++)
    {
        if (pass[i] == ' ')
            return false;
    }

    return true;
}

bool confirm()
{
    cout << "\nEnter Y/y to confirm: ";
    string done;
    getline(cin, done);
    cin.clear();
    fflush(stdin);

    if (done == "Y" || done == "y" || done == "Yes" || done == "yes")
        return true;

    return false;
}