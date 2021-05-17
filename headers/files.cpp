void makePasswordFile()
{
    fstream file;
    file.open("database/Login/password.txt", ios::app);
    file.close();
}

void makeUserDirectory(string num)
{
    system(("cd database/Users && mkdir " + num).c_str());
}

ll displayList(string directory, vector<string> &str)
{
    str.clear();
    system(("cd database/" + directory + " && dir /b > files.txt").c_str());
    fstream file;
    file.open("database/" + directory + "/files.txt", ios::in);

    ll count = 1;
    while (!file.eof())
    {
        string s;
        getline(file, s);
        cin.clear();
        fflush(stdin);

        if (s == "files.txt" || s[0] == '\0' || s == ".gitkeep")
            continue;

        str.push_back(s);
        cout << count << ") " + s << endl;
        count++;
    }
    file.close();
    return count;
}

ll displayFile(string filePath, vector<string> &str)
{
    str.clear();
    fstream file;
    file.open("database/" + filePath, ios::in);

    ll count = 0;
    while (!file.eof())
    {
        string s;
        getline(file, s);
        cin.clear();
        fflush(stdin);

        if (s[0] == '\0')
            continue;

        if (count)
        {
            cout << count << ") " + s << endl;
            str.push_back(s);
        }
        else
            cout << s << endl;
        count++;
    }

    file.close();
    return count;
}

void updateFile(string filePath, ll option)
{
    vector<string> str;

    fstream file;
    file.open("database/" + filePath, ios::in);

    ll count = 0;
    while (!file.eof())
    {
        string s;
        getline(file, s);
        cin.clear();
        fflush(stdin);

        if (s[0] == '\0')
            continue;

        if (count != option)
            str.push_back(s);
        else
        {
            s = s.substr(0, 5) + "\tTaken";
            str.push_back(s);
        }
        count++;
    }
    file.close();

    file.open("database/" + filePath, ios::out);
    for (ll i = 0; i < str.size(); i++)
    {
        file << str[i] << endl;
        if (i == 0)
            file << endl;
    }
    file.close();
}

void updateUserHistory(ll pNum, string filePath, string time)
{
    string user = to_string(pNum);
    ll start = 0, end = 0;

    while (filePath[end] != '/')
        end++;
    end++;
    start = end;

    while (filePath[end] != '/')
        end++;
    string type = filePath.substr(start, end - start);
    end++;
    start = end;

    while (filePath[end] != '/')
        end++;
    string doctor = filePath.substr(start, end - start);
    end++;
    start = end;

    while (filePath[end] != '/')
        end++;
    string date = filePath.substr(start, end - start);
    end++;
    start = end;

    system(("cd database/Users/" + user + " && mkdir \"" + type + "\"").c_str());
    system(("cd database/Users/" + user + "/" + type + " && mkdir \"" + doctor + "\"").c_str());

    fstream file;
    file.open("database/Users/" + user + "/" + type + "/" + doctor + "/" + date, ios::out);
    file << "Appointment with " + type + " " + doctor + " on " + date.substr(0, date.length() - 4) + " at " + time << endl;
    file.close();
}

void fillSchedule(string fName, string date, string time, string docPath, bool present)
{
    fstream schedule;
    if (!present)
    {
        schedule.open(docPath + "/" + date + ".txt", ios::out);
        schedule << "Time\t\tSlots\n\n";

        string slot = "10:00";
        int count = 1;
        while (slot != "19:00")
        {
            schedule << slot;
            schedule << "\tAvailable" << endl;

            slot = slot[0] + to_string(count) + slot.substr(2);
            count++;
        }
    }
    else
    {
        schedule.open(docPath + "/" + date + ".txt", ios::in);
        vector<string> s;
        ll len = 0;
        while (!schedule.eof())
        {
            string data;
            getline(schedule, data);
            s.push_back(data);
            len++;
        }
        schedule.close();

        schedule.open(docPath + "/" + date + ".txt", ios::out);
        schedule << "Time\t\tSlots\n\n";

        string slot = "10:00";
        int count = 0;
        while ((stoi(slot.substr(0, 2)) <= stoi(time.substr(0, 2))) && count < 9)
        {
            schedule << slot;
            schedule << "\tTaken" << endl;

            count++;
            slot = slot[0] + to_string(count) + slot.substr(2);
        }
        for (ll i = count + 2; i < len; i++)
        {
            if (s[i][0] == '\0' || s[i][0] == '\n')
                continue;
            schedule << s[i] << endl;
        }
    }

    schedule.close();
}

void fillDoctorSchedule(int inc)
{
    system("cd database/Speciality && dir /b > files.txt");
    fstream file;
    file.open("database/Speciality/files.txt", ios::in);

    string date = __DATE__;
    ll day = stoi(date.substr(4, 2));
    day += inc;
    string date2;
    if (day / 10 == 0)
        date2 = date.substr(0, 5) + to_string(day) + date.substr(6);
    else
        date2 = date.substr(0, 4) + to_string(day) + date.substr(6);
    string time = __TIME__;

    while (!file.eof())
    {
        system("cls");
        string s;
        file >> s;

        if (s == ".gitkeep" || s == "files.txt" || s[0] == '\0' || s[0] == '\n')
            continue;

        string path = "database/Speciality/" + s;
        system(("cd " + path + " && dir /b > files.txt").c_str());

        fstream doctor;
        doctor.open(path + "/files.txt", ios::in);
        while (!doctor.eof())
        {
            system("cls");
            string docName;
            getline(doctor, docName);

            if (docName == ".gitkeep" || docName == "files.txt" || docName[0] == '\0' || docName[0] == '\n')
                continue;

            string docPath = path + "/" + docName;
            system(("cd " + docPath + " && dir /b > files.txt").c_str());

            fstream record;
            record.open(docPath + "/files.txt", ios::in);

        getTop:
            string fName;
            getline(record, fName);

            if (fName == ".gitkeep" || fName == "files.txt" || fName[0] == '\0' || fName[0] == '\n')
                goto getTop;

            if (fName != (date + ".txt"))
                fillSchedule(fName, date2, time, docPath, false);
            else
                fillSchedule(fName, date, time, docPath, true);
            if (fName != "files.txt" && fName != (date + ".txt"))
                system(("cd " + docPath + " && del /f \"" + fName + "\"").c_str());
            record.close();
            system(("cd " + docPath + " && del /f files.txt").c_str());
        }
        doctor.close();
        system(("cd " + path + " && del /f files.txt").c_str());
    }

    file.close();
}

void availSchedule(string filePath, string time)
{
    heading("Cancelling Appointment");

    vector<string> list;

    fstream file;
    file.open("database/" + filePath, ios::in);

    while (!file.eof())
    {
        string s;
        getline(file, s);
        list.push_back(s);
    }
    file.close();

    for (ll i = 2; i < list.size() - 1; i++)
        if (list[i].substr(0, 2) == time.substr(0, 2))
            list[i] = time + "\tAvailable";

    file.open("database/" + filePath, ios::out);
    for (ll i = 0; i < list.size() - 1; i++)
        file << list[i] << endl;

    file.close();
}
