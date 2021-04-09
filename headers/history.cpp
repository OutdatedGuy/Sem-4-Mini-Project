string appointmentHistory(ll pNum, bool cancel)
{
    vector<string> list;
Speciality:
    heading("Appointment History");
    string directoryPath = "Users/" + to_string(pNum);
    ll count = displayList(directoryPath, list);

    if (count == 1)
    {
        goBack("Appointment");
        return "";
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
            return "";
        if (isValidOption(option, count))
        {
            string doctorPath = (directoryPath + "/" + list[option - 1]);
        Doctor:
            heading("Appointment History");
            count = displayList(doctorPath, list);

            if (count == 1)
            {
                goBack("Appointment");
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
                    heading("Appointment History");
                    count = displayList(schedulePath, list);
                    if (count == 1)
                    {
                        goBack("Appointment");
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
                            if (!cancel)
                            {
                                heading("Appointment History");
                                displayFile(filePath, list);
                                getch();
                                cout << "\nPress Enter to Go Back...";
                                getch();
                                goto Schedule;
                            }
                            else if (!confirm())
                                goto Schedule;
                            else
                                return filePath;
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

    return "";
}
