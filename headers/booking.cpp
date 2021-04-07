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
    string directoryPath = "Speciality";
    ll count = displayList(directoryPath, list);

    if (count == 1)
    {
        goBack("Specialities");
        return;
    }
    else
    {
        cout << count << ") Go Back\n\n";
        cout << "Enter Your Choice: ";
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
                goBack("Doctors");
                goto Speciality;
            }
            else
            {
                cout << count << ") Go Back\n\n";
                cout << "Enter Your Choice: ";
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
                        cout << count << ") Go Back\n\n";
                        cout << "Enter Your Choice: ";
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
                                cout << count << ") Go Back\n\n";
                                cout << "Enter Your Choice: ";
                                cin >> option;
                                cin.clear();
                                fflush(stdin);
                                if (option == count)
                                    goto Schedule;
                                if (isValidOption(option, count))
                                {
                                    if (!confirm())
                                        goto Week;

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
                                    cout << "\nPlease Select a VALID Option! (from 1 to " << count << ")" << endl;
                                    tryAgain();
                                    goto Week;
                                }
                            }
                        }
                        else
                        {
                            cout << "\nPlease Select a VALID Option! (from 1 to " << count << ")" << endl;
                            tryAgain();
                            goto Schedule;
                        }
                    }
                }
                else
                {
                    cout << "\nPlease Select a VALID Option! (from 1 to " << count << ")" << endl;
                    tryAgain();
                    goto Doctor;
                }
            }
        }
        else
        {
            cout << "\nPlease Select a VALID Option! (from 1 to " << count << ")" << endl;
            tryAgain();
            goto Speciality;
        }
    }

    return;
}

void reSchedule(ll pNum)
{
    system("cls");
    string filePath = appointmentHistory(pNum, true);
    system("cls");
}

void cancelAppointment(ll pNum)
{
    system("cls");
    string filePath = appointmentHistory(pNum, true);
    system("cls");

    fstream file;
    file.open("database/" + filePath, ios::in);

    string s;
    do
        file >> s;
    while (s != "with");

    string type;
    file >> type;

    string doctor = "";
    file >> s;
    while (s != "on")
    {
        doctor += (s + " ");
        file >> s;
    }
    doctor = doctor.substr(0, doctor.length() - 1);

    string date = "";
    file >> s;
    while (s != "at")
    {
        date += (s + " ");
        file >> s;
    }
    date = date.substr(0, date.length() - 1);
    if (date[4] != ' ' && date[5] == ' ')
        date = date.substr(0, 4) + " " + date.substr(4);

    string dateNow = __DATE__;
    ll day1 = stoi(dateNow.substr(4, 2));
    ll day2 = stoi(date.substr(4, 2));

    if (day2 < day1)
    {
        file.close();
        system("cls");
        cout << "Appointment already DUE!" << endl;
        cout << "\nPress Enter to go Back...";
        getch();
    }
    else
    {
        string time;
        file >> time;
        file.close();

        string timeNow = __TIME__;
        if (stoi(time.substr(0, 2)) <= stoi(timeNow.substr(0, 2)))
        {
            system("cls");
            cout << "Appointment already DUE!" << endl;
            cout << "\nPress Enter to go Back...";
            getch();
        }
        else
        {
            for (ll i = 0; i < filePath.length(); i++)
                if (filePath[i] == '/')
                    filePath[i] = '\\';

            system(("cd . && del /f \"database\\" + filePath + "\"").c_str());
            system("cls");
            file.open("database/" + filePath, ios::in);

            system("cls");
            if (!file)
            {
                string schedulePath = "Speciality/" + type + "/" + doctor + "/" + date + ".txt";
                availSchedule(schedulePath, time);
                cout << "Appointment Cancelled Successfully!!!" << endl;
            }
            else
                cout << "Appointment Cancelling Failed!!!" << endl;
            waiting();
            file.close();
        }
    }
}
