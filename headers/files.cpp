void makePasswordFile()
{
    fstream file;
    file.open("database/Login/password.txt", ios::app);
    file.close();
    file.open("database/Login/admin.txt", ios::app);
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
