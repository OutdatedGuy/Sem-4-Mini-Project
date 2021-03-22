void waiting()
{
    cout << "\nPress Enter to continue...";
    getch();
    system("cls");
}

void tryAgain()
{
    cout << "\nPress Enter to Try Again...";
    getch();
    system("cls");
}

void goBack(string s)
{
    cout << "No " + s + " Available" << endl;
    cout << "\nPress Enter to go Back...";
    getch();
}
