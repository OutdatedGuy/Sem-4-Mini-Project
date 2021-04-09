void printMargin(int width, string symbol)
{
    for (int i = 0; i < width; i++)
        cout << symbol;
    cout << endl;
}

void printPadding(int width)
{
    for (int i = 0; i < width; i++)
    {
        if (i == 0 || i == width - 1)
            cout << "|";
        else
            cout << " ";
    }
    cout << endl;
}

void printTitle(int width, string title)
{
    for (int i = 0; i < width; i++)
    {
        if (i == 0 || i == width - 1)
            cout << "|";
        else if (i >= (width - title.length()) / 2 && i < (width + title.length()) / 2)
        {
            cout << title;
            i += (title.length() - 1);
        }
        else
            cout << " ";
    }
    cout << endl;
}

void heading(string title)
{
    system("cls");
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int width;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    width = csbi.srWindow.Right - csbi.srWindow.Left;

    printMargin(width, "*");
    printPadding(width);
    printTitle(width, "Doctors Appointment System");
    printPadding(width);
    printMargin(width, "*");
    cout << "\n";

    printMargin(width, "-");
    printPadding(width);
    printTitle(width, title);
    printPadding(width);
    printMargin(width, "-");
    cout << "\n\n";
}