bool bookAppointment(ll pNum)
{
    vector<string> list;
Speciality:
    system("cls");
    string pathName = "Speciality";
    ll count = displayList(pathName, list);

    if (count == 1)
    {
        goBack("Specialities");
        return false;
    }
    else
    {
        cout << count << ") Go Back\n\n:";
        ll option;
        cin >> option;
        if (option == count)
            return false;
        if (isValidOption(option, count))
        {
        Doctor:
            system("cls");
            pathName += ("/" + list[option - 1]);
            count = displayList(pathName, list);

            if (count == 1)
            {
                goBack("Doctors");
                goto Speciality;
            }
            else
            {
                cout << count << ") Go Back\n\n:";
                cin >> option;
                if (option == count)
                    goto Speciality;
                if (isValidOption(option, count))
                {
                Schedule:
                    system("cls");
                    pathName += ("/" + list[option - 1]);
                    count = displayList(pathName, list);
                    if (count == 1)
                    {
                        goBack("Schedule");
                        goto Doctor;
                    }
                    else
                    {
                        cout << count << ") Go Back\n\n:";
                        cin >> option;
                        if (option == count)
                            goto Doctor;
                        if (isValidOption(option, count))
                        {
                            pathName += ("/" + list[option - 1]);
                            // count = displayFile(pathName, list);
                        }
                        else
                        {
                            cout << "\nPlease Select a VALID Option!" << endl;
                            tryAgain();
                            goto Schedule;
                        }
                    }
                }
                else
                {
                    cout << "\nPlease Select a VALID Option!" << endl;
                    tryAgain();
                    goto Doctor;
                }
            }
        }
        else
        {
            cout << "\nPlease Select a VALID Option!" << endl;
            tryAgain();
            goto Speciality;
        }
    }
}
