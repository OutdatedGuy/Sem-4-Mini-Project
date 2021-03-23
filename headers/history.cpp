void appointmentHistory(ll pNum)
{
    vector<string> list;
Speciality:
    system("cls");
    string directoryPath = "Users/" + to_string(pNum);
    ll count = displayList(directoryPath, list);

    if (count == 1)
    {
        goBack("Appointment");
        return;
    }
    else
    {
        cout << count << ") Go Back\n\n:";
        ll option;
        cin >> option;
        cin.clear();
        fflush(stdin);
        if (option == count)
            return;
        if (isValidOption(option, count))
        {
            string doctorPath = (directoryPath + "/" + list[option - 1]);
        Doctor:
            system("cls");
            count = displayList(doctorPath, list);

            if (count == 1)
            {
                goBack("Appointment");
                goto Speciality;
            }
            else
            {
                cout << count << ") Go Back\n\n:";
                cin >> option;
                cin.clear();
                fflush(stdin);
                if (option == count)
                    goto Speciality;
                if (isValidOption(option, count))
                {
                    string schedulePath = (doctorPath + "/" + list[option - 1]);
                Schedule:
                    system("cls");
                    count = displayList(schedulePath, list);
                    if (count == 1)
                    {
                        goBack("Appointment");
                        goto Doctor;
                    }
                    else
                    {
                        cout << count << ") Go Back\n\n:";
                        cin >> option;
                        cin.clear();
                        fflush(stdin);
                        if (option == count)
                            goto Doctor;
                        if (isValidOption(option, count))
                        {
                            system("cls");
                            string filePath = (schedulePath + "/" + list[option - 1]);
                            displayFile(filePath, list);
                            getch();
                            cout << "\nPress Enter to Go Back...";
                            getch();
                            goto Schedule;
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

    return;
}