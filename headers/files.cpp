void makePasswordFile()
{
    fstream file;
    file.open("files/Login/password.txt", ios::app);
    file.close();
}