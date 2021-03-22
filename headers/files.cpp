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

        str.push_back(s);
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