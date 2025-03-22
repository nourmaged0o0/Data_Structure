#include <iostream>
#include <cstring>

using namespace std;

class Guest
{
    string name;
    string contact;
    string iftar_date;

public:
    Guest() {}
    Guest(string Guest_name, string Guest_contact, string Guest_date)
        : name(Guest_name), contact(Guest_contact), iftar_date(Guest_date) {}

    void display_guest() const
    {   cout<<endl;
        cout << "Guest: " << name<<", ";
        cout << "Contact: " << contact<<", ";
        cout << "Iftar Date: " << iftar_date<<endl;
    }

    void update_invitation(string new_date)
    {
        iftar_date = new_date;
    }

    string get_name() const
    {
        return name;
    }

    string get_iftar_date() const
    {
        return iftar_date;
    }
};

class IftarManager
{
    static const int MAX_GUESTS = 100;
    Guest guests_list[MAX_GUESTS];
    int guest_count = 0;

public:
    void add_guest(Guest guest)
    {
        if (guest_count < MAX_GUESTS)
        {
            guests_list[guest_count] = guest;
            guest_count++;
        }
        else
        {
            cout << "Guest list is full!" << endl;
        }
    }

    void display_all_guests() const
    {
        if (guest_count == 0)
        {
            cout << "No guests." << endl;
        }
        else
        {
            for (int i = 0; i < guest_count; i++)
            {
                guests_list[i].display_guest();
            }
        }
    }

    void update_guest_invitation(const string &guest_name, const string &new_date)
    {
        bool found = false;
        for (int i = 0; i < guest_count; i++)
        {
            if (guests_list[i].get_name() == guest_name)
            {
                guests_list[i].update_invitation(new_date);
                found = true;
                cout << "Invitation updated for " << guest_name << " to " << new_date << endl;
                break;
            }
        }
        if (!found)
        {
            cout << "Guest " << guest_name << " not found!" << endl;
        }
    }

    void send_reminder(const string &date) const
    {
        cout << "Sending Reminder to iftar on " << date << "..." << endl;
        for (int i = 0; i < guest_count; i++)
        {
            if (guests_list[i].get_iftar_date() == date)
            {
                cout << "Reminder sent to " << guests_list[i].get_name() << endl;
            }
        }
    }

    void sort_guest_list()
    {
        for (int i = 0; i < guest_count - 1; i++)
        {
            for (int j = 0; j < guest_count - i - 1; j++)
            {
                if (guests_list[j].get_name() > guests_list[j + 1].get_name())
                {
                    Guest temp = guests_list[j];
                    guests_list[j] = guests_list[j + 1];
                    guests_list[j + 1] = temp;
                }
            }
        }
        cout << "Guests have been sorted by name." << endl;
    }

    void remove_guest(const string &guest_name) {
        bool found = false;
        for (int i = 0; i < guest_count; i++) {
            if (guests_list[i].get_name() == guest_name) {
                for (int j = i; j < guest_count - 1; j++) {
                    guests_list[j] = guests_list[j + 1];
                }
                guest_count--;
                found = true;
                cout << "Guest " << guest_name << " removed successfully." << endl;
                break;
            }
        }
        if (!found) {
            cout << "Guest " << guest_name << " not found!" << endl;
        }
    }
};

int main()
{
    IftarManager manager;
    int choice;
    string name, contact, date;

    do
    {
        cout << "\n1. Add Guest\n2. Update Guest Invitation\n3. Display All Guests\n4. Send Reminder\n5. Sort Guests\n6. Delete Guest\n7. Exit\nEnter your choice : ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter Guest Name : ";
            cin >> name;
            cout << "Enter Contact : ";
            cin >> contact;
            cout << "Enter Iftar Date : ";
            cin >> date;
            manager.add_guest(Guest(name, contact, date));
            break;

        case 2:
            cout << "Enter guest Name : ";
            cin >> name;
            cout << "Enter new Iftar date : ";
            cin >> date;
            manager.update_guest_invitation(name, date);
            break;

        case 3:
            manager.display_all_guests();
            break;

        case 4:
            cout << "Enter Iftar Date : ";
            cin >> date;
            manager.send_reminder(date);
            break;

        case 5:
            manager.sort_guest_list();
            break;
        case 6:
            cout << "Enter guest name to remove: ";
            cin >> name;
            manager.remove_guest(name);
            break;

        case 7:
            cout << "Exiting the program..." << endl;
            break;

        default:
            cout << "Invalid choice! Please try again." << endl;
            break;
        }
    } while (choice != 7);

    return 0;
}
