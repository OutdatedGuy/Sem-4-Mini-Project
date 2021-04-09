bool bookAppointment(string str, ll option, string filePath, ll pNum)
{
    ll i = 0;
    while (str[i] != '\t')
        i++;

    if (str.substr(i + 1) == "Taken")
        return false;

    updateFile(filePath, option);
    updateUserHistory(pNum, filePath, str.substr(0, i));

    heading("Appointment Booked");
    cout << "Appointment Sucessfully Made" << endl;
    cout << "\nGo to Appointment History to view details" << endl;
    waiting();

    return true;
}

void searchDoctor(ll pNum)
{
    vector<string> list;
Speciality:
    heading("Select Speciality");
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
            heading("Select Doctor");
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
                    heading("Select Schedule");
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
                            heading("Select Timing");
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

int reSchedule(ll pNum, string type, string doctor, string day)
{
    vector<string> list;
Schedule:
    heading("Select Schedule");
    string schedulePath = "Speciality/" + type + "/" + doctor;
    ll count = displayList(schedulePath, list);

    if (count == 1)
    {
        goBack("Schedule");
        return 0;
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
            return 0;
        if (isValidOption(option, count))
        {
            string filePath = (schedulePath + "/" + list[option - 1]);
        Week:
            heading("Select Re-Schedule Timing");
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
                        return (filePath.substr(11) == day.substr(17) ? 1 : 2);
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

void cancelAppointment(ll pNum, bool re_Schedule)
{
    string filePath = appointmentHistory(pNum, true);
    if (filePath == "")
        return;
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

    string time;
    file >> time;
    file.close();

    if (day2 < day1)
    {
        heading("Select Valid Appointment");
        cout << "Appointment already DUE!" << endl;
        cout << "\nPress Enter to go Back...";
        getch();
        return;
    }
    else if (day2 == day1)
    {
        string timeNow = __TIME__;
        if (stoi(time.substr(0, 2)) <= stoi(timeNow.substr(0, 2)))
        {
            heading("Select Valid Appointment");
            cout << "Appointment already DUE!" << endl;
            cout << "\nPress Enter to go Back...";
            getch();
            return;
        }
    }

    int done = 0;
    if (re_Schedule)
    {
        done = reSchedule(pNum, type, doctor, filePath);
        if (done == 0)
            return;
        else if (done == 1)
        {
            string schedulePath = "Speciality/" + type + "/" + doctor + "/" + date + ".txt";
            availSchedule(schedulePath, time);
            cout << "Appointment Re-Scheduled Successfully!!!" << endl;
            waiting();
            return;
        }
    }

    for (ll i = 0; i < filePath.length(); i++)
        if (filePath[i] == '/')
            filePath[i] = '\\';

    system(("cd . && del /f \"database\\" + filePath + "\"").c_str());
    file.open("database/" + filePath, ios::in);

    if (!file)
    {
        string schedulePath = "Speciality/" + type + "/" + doctor + "/" + date + ".txt";
        availSchedule(schedulePath, time);
        if (done == 2)
            cout << "Appointment Re-Scheduled Successfully!!!" << endl;
        else
            cout << "Appointment Cancelled Successfully!!!" << endl;
    }
    else
    {
        heading("Cancelling Appointment");
        if (done == 2)
            cout << "Appointment Re-Scheduling Failed!!!" << endl;
        else
            cout << "Appointment Cancelling Failed!!!" << endl;
    }
    waiting();
    file.close();
}
