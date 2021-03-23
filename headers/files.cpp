void makePasswordFile()
{
    fstream file;
    file.open("database/Login/password.txt", ios::app);
    file.close();
    file.open("database/Login/doctors.txt", ios::app);
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

    system(("cd database/Users/" + user + " && mkdir " + type + " && cd " + type + " && mkdir " + doctor).c_str());

    fstream file;
    file.open("database/Users/" + user + "/" + type + "/" + doctor + "/" + date, ios::out);
    file << "Appointment with " + type + " " + doctor + " on " + date + " at " + time << endl;
    file.close();
}