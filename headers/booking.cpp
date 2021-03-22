bool bookAppointment(string str, ll pNum)
{
    ll i = 0;
    while (str[i] != 0)
        i++;

    if (str.substr(i + 1) == "Taken")
        return false;

    return true;
}

void searchDoctor(ll pNum)
{
    vector<string> list;
Speciality:
    system("cls");
    string specialityPath = "Speciality";
    ll count = displayList(specialityPath, list);

    if (count == 1)
    {
        goBack("Specialities");
        return;
    }
    else
    {
        cout << count << ") Go Back\n\n:";
        ll option;
        cin >> option;
        if (option == count)
            return;
        if (isValidOption(option, count))
        {
            string doctorPath = (specialityPath + "/" + list[option - 1]);
        Doctor:
            system("cls");
            count = displayList(doctorPath, list);

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
                    string schedulePath = (doctorPath + "/" + list[option - 1]);
                Schedule:
                    system("cls");
                    count = displayList(schedulePath, list);
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
                            string filePath = (schedulePath + "/" + list[option - 1]);
                            system("cls");
                            count = displayFile(filePath, list);
                            if (count == 1)
                            {
                                goBack("Slots");
                                goto Schedule;
                            }
                            else
                            {
                                cout << count << ") Go Back\n\n:";
                                cin >> option;
                                if (option == count)
                                    goto Schedule;
                                else if (!bookAppointment(list[option - 1], pNum))
                                    goto Schedule;
                                else
                                    return;
                            }
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
