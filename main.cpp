///EVENT MANAGEMENT SYSTEM///

/***CONCEPTS COVERED

1.Class and(friend function)
2.Object
3.Constructor (default+parameterized+copy) & Destructors
4.Abstraction
5.Inheritence
6.Polymorphisim
7.Encapsulation
8.Operator Overloading
9.STL container(vector+map)

***/

#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Event
{
public:
    virtual ~Event() {}
    virtual void displayDetails() const = 0;
    virtual void deleteEvent() = 0;
    virtual double calculateCost() const = 0;
};

class EventType
{
public:
    virtual ~EventType() {}
    virtual void displayEventTypes() const = 0;
};

class Conference : public EventType
{
public:
    void displayEventTypes() const override //polymorphism override function
    {
        cout << "1. Conferences" << endl;
    }
};

class TradeShow : public EventType
{
public:
    void displayEventTypes() const override
    {
        cout << "2. Trade shows" << endl;
    }
};

class Exhibition : public EventType
{
public:
    void displayEventTypes() const override
    {
        cout << "3. Exhibition" << endl;
    }
};

class Concert : public EventType
{
public:
    void displayEventTypes() const override
    {
        cout << "4. Concert" << endl;
    }
};

class ComedyShow : public EventType
{
public:
    void displayEventTypes() const override
    {
        cout << "5. ComedyShow" << endl;
    }
};

class TheatrePlays : public EventType
{
public:
    void displayEventTypes() const override
    {
        cout << "6. TheatrePlays" << endl;
    }
};

class FilmScreenings : public EventType
{
public:
    void displayEventTypes() const override
    {
        cout << "7. FilmScreenings" << endl;
    }
};

class Others : public EventType
{
public:
    void displayEventTypes() const override
    {
        cout << "8. Others" << endl;
    }
};

class EventDetails : public Event
{
private:
    string name;
    string date;
    string time;
    string location;
    int no_of_participants;

public:
    EventDetails() {}  //default constructor called
    EventDetails(string n, string d, string t, string l, int participants) //parameterized constructor
        : name(n), date(d), time(t), location(l), no_of_participants(participants){}

    void displayDetails() const override
    {
        cout << "Event Details:" << endl;
        cout << "Name: " << name << endl;
        cout << "Date: " << date << endl;
        cout << "Time: " << time << endl;
        cout << "Location: " << location << endl;
        cout << "No. of Participants: " << no_of_participants << endl;
    }
    friend istream& operator>>(istream& input, EventDetails& event);
    friend ostream& operator<<(ostream& output, EventDetails& event);

    void deleteEvent() override
    {
    }

    double calculateCost() const override
    {
        double tablesCostPerUnit = 12;
        double chairsCostPerUnit = 10;
        double powerCableCost = 1000;
        double lightingCost = 1500;
        double stageCost = 2000;
        double soundCost = 5000;
        double storageCost = 1000;

        double totalCost = tablesCostPerUnit + chairsCostPerUnit + powerCableCost + lightingCost + stageCost + soundCost + storageCost;

        return totalCost * no_of_participants;
    }


};

class Equipment
{
public:
    virtual ~Equipment() {}
    virtual double getCost() const = 0;
};

// Derived classes for different equipment items
class Tables : public Equipment
{
public:
    double getCost() const override
    {
        return 12.0;
    }
};

class Chairs : public Equipment
{
public:
    double getCost() const override
    {
        return 10.0;
    }
};

class PowerCable : public Equipment
{
public:
    double getCost() const override
    {
        return 1000.0;
    }
};

class Lighting : public Equipment
{
public:
    double getCost() const override
    {
        return 1500.0;
    }
};

class Stage : public Equipment
{
public:
    double getCost() const override
    {
        return 2000.0;
    }
};

class Sound : public Equipment
{
public:
    double getCost() const override
    {
        return 5000.0;
    }
};

class Storage : public Equipment
{
public:
    double getCost() const override
    {
        return 1000.0;
    }
};

class EquipmentManager
{
private:
    map<string, int> selectedEquipment; // Equipment name to quantity

public:
    // Function to select equipment
    void selectEquipment(const string &equipmentName, int quantity)
    {
        selectedEquipment[equipmentName] = quantity;
    }


    void displaySelectedEquipment() const
    {
        double totalCost = 0.0;

        cout << "Selected Equipment:" << endl;
        for (const auto &pair : selectedEquipment)
        {
            const string &equipmentName = pair.first;
            int quantity = pair.second;

            double costPerUnit = 0.0;

            if (equipmentName == "Tables")
                costPerUnit = 12.0;
            else if (equipmentName == "Chairs")
                costPerUnit = 10.0;
            else if (equipmentName == "Power Cable")
                costPerUnit = 1000.0;
            else if (equipmentName == "Lighting")
                costPerUnit = 1500.0;
            else if (equipmentName == "Stage")
                costPerUnit = 2000.0;
            else if (equipmentName == "Sound")
                costPerUnit = 5000.0;
            else if (equipmentName == "Storage")
                costPerUnit = 1000.0;

            double equipmentCost = costPerUnit * quantity;
            totalCost += equipmentCost;

            cout << equipmentName << ": " << quantity << " x $" << costPerUnit << " = $" << equipmentCost << endl;
        }

        cout << "Total Equipment Cost: $" << totalCost << endl;
    }
};

class EventManager
{
private:
    vector<Event *> events;

public:
    ~EventManager()
    {
        for (Event *event : events)
        {
            delete event;
        }
    }

    //Function to Add event

    void addEvent(Event *event)
    {
        events.push_back(event);
        cout << "Event Added Successfully!" << endl;
    }

    //Function to Delete Event
    void deleteEvent(int index)
    {
        if (index >= 0 && index < events.size())
        {
            delete events[index];
            events.erase(events.begin() + index);
            cout << "Event deleted successfully." << endl;
        }
        else
        {
            cout << "Invalid event index." << endl;
        }
    }

    void displayEvents() const
    {
        cout << "List of Events:" << endl;
        for (size_t i = 0; i < events.size(); ++i)
        {
            cout << "Event " << i + 1 << ":" << endl;
            events[i]->displayDetails();
            cout << "Cost: $" << events[i]->calculateCost() << endl;
            cout << "-----------------------" << endl;
        }
    }
};
istream& operator>>(istream& input, EventDetails& event)
{
    cout << "Enter event name: ";
    input.ignore();
    getline(input, event.name);
    cout << "Enter date (DD/MM/YYYY): ";
    input >> event.date;
    cout << "Enter time: ";
    input >> event.time;
    cout << "Enter location: ";
    input.ignore();
    getline(input, event.location);
    cout << "Enter No. of Participants: ";
    input >> event.no_of_participants;

    return input;
}
int main()
{
    EventManager manager;
    Conference conference;
    TradeShow tradeshow;
    Exhibition exhibition;
    Concert concert;
    ComedyShow comedyshow;
    TheatrePlays theatreplays;
    FilmScreenings filmscreenings;
    Others others;
    EquipmentManager equipmentManager;

    int choice,choicce;
    char exit;
    do
    {
        cout << "\nEvent Management System" << endl;
        cout << "1. Add Event" << endl;
        cout << "2. Delete Event" << endl;
        cout << "3. Display Events" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter Your Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            cout << "List of event types:" << endl;
            conference.displayEventTypes();
            tradeshow.displayEventTypes();
            exhibition.displayEventTypes();
            concert.displayEventTypes();
            comedyshow.displayEventTypes();
            theatreplays.displayEventTypes();
            filmscreenings.displayEventTypes();
            others.displayEventTypes();

            cout << "Enter your choice: ";
            int evchoice;
            cin >> evchoice;

            Event *newEvent = nullptr;

            if (evchoice == 1 || evchoice == 2 || evchoice == 3 || evchoice == 4 || evchoice == 5 || evchoice == 6 || evchoice == 7 || evchoice == 8)
            {
                EventDetails new_event;
                cin>>new_event;
                Event* newEventPtr = new EventDetails(new_event); /*copy constructor for the EventDetails class is implicitly used in this part of the code.*/
                                                                //The copy constructor is invoked here to perform the copying operation from
                                                                //new_event to newEventPtr. The line Event* newEventPtr = new EventDetails(new_event);
                                                                //involves copying the data members of new_event to newEventPtr*/
                manager.addEvent(newEventPtr);


            }

            do
            {
                cout << "\nEquipment Management System" << endl;
                cout << "1. Select Equipment" << endl;

                cout << "2. Exit" << endl;
                cout << "Enter Your Choice: ";
                cin >> choicce;

                switch (choicce)
                {
                case 1:
                {
                    cout << "List of equipment items:" << endl;
                    cout << "1. Tables" << endl;
                    cout << "2. Chairs" << endl;
                    cout << "3. Power Cable" << endl;
                    cout << "4. Lighting" << endl;
                    cout << "5. Stage" << endl;
                    cout << "6. Sound" << endl;
                    cout << "7. Storage" << endl;

                    cout << "Enter the equipment number (1-7): ";
                    int equipmentChoice;
                    cin >> equipmentChoice;

                    if (equipmentChoice >= 1 && equipmentChoice <= 7)
                    {
                        string equipmentName;
                        int quantity;

                        switch (equipmentChoice)
                        {
                        case 1:
                            equipmentName = "Tables";
                            break;
                        case 2:
                            equipmentName = "Chairs";
                            break;
                        case 3:
                            equipmentName = "Power Cable";
                            break;
                        case 4:
                            equipmentName = "Lighting";
                            break;
                        case 5:
                            equipmentName = "Stage";
                            break;
                        case 6:
                            equipmentName = "Sound";
                            break;
                        case 7:
                            equipmentName = "Storage";
                            break;
                        default:
                            cout<<"nothing here"<<endl;
                        }

                        cout << "Enter the quantity: ";
                        cin >> quantity;

                        equipmentManager.selectEquipment(equipmentName, quantity);
                        cout << "Equipment " << equipmentName << " (Quantity: " << quantity << ") selected successfully." << endl;
                    }
                    else
                    {
                        cout << "Invalid equipment choice. Please try again." << endl;
                    }
                    break;
                }

                case 2:
                {
                    cout << "Exiting equipment management." << endl;
                    break;
                }
                default:
                    cout << "Invalid choice. Please try again." << endl;
                }
            }
            while(choicce!=2);
            break;
        }

        case 2:
        {
            cout << "Enter the index of the event you want to delete: ";
            int index;
            cin >> index;
            manager.deleteEvent(index - 1);
            break;
        }

        case 3:
        {
            manager.displayEvents();
            break;
        }

        case 4:
        {
            cout << "Exiting program." << endl;
        }

        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }

    }
    while(choice!=4);
    return 0;
}
