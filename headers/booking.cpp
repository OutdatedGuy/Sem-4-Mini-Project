bool bookAppointment(string str, ll option, string filePath, ll pNum)
{
    ll i = 0;
    while (str[i] != '\t')
        i++;

    if (str.substr(i + 1) == "Taken")
        return false;

    updateFile(filePath, option);
    updateUserHistory(pNum, filePath, str.substr(0, i));

    system("cls");
    cout << "Appointment Sucessfully Made" << endl;
    cout << "\nGo to Appointment History to view details" << endl;
    waiting();

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
        cin.clear();
        fflush(stdin);
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
                        goBack("Schedule");
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
                            string filePath = (schedulePath + "/" + list[option - 1]);
                        Week:
                            system("cls");
                            count = displayFile(filePath, list);
                            if (count == 0)
                            {
                                goBack("Slots");
                                goto Schedule;
                            }
                            else
                            {
                                cout << count << ") Go Back\n\n:";
                                cin >> option;
                                cin.clear();
                                fflush(stdin);
                                if (option == count)
                                    goto Schedule;
                                if (isValidOption(option, count))
                                {
                                    if (!bookAppointment(list[option - 1], option, filePath, pNum))
                                    {
                                        cout << "\nSlot Already Taken!" << endl;
                                        tryAgain();
                                        goto Week;
                                    }
                                    else
                                        return;
                                }
                                else
                                {
                                    cout << "\nPlease Select a VALID Option!" << endl;
                                    tryAgain();
                                    goto Week;
                                }
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
