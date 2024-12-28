#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

using namespace std;

struct Booking
{
    string customerName, rideName, bookingId;
    int quantity;
    double cost;
    Booking *next;
};

struct Ride
{
    string name, id, status, capacity, duration, price;
    Ride *next;
};

Booking *bookingFront = NULL;
Booking *bookingRear = NULL;

Ride *rideHead = NULL;
int rideCount = 0;

class Customer
{

    void LoadRidesFromFile() // Load data from rides.txt
    {
        ifstream file("rides.txt");
        if (file.is_open())
        {
            string name, id, status, capacity, duration, price;

            while (file >> name >> id >> status >> capacity >> duration >> price)
            {
                Ride *newRide = new Ride;

                newRide->name = name;
                newRide->id = id;
                newRide->status = status;
                newRide->capacity = capacity;
                newRide->duration = duration;
                newRide->price = price;

                newRide->next = NULL;

                if (rideHead == NULL)
                {
                    rideHead = newRide;
                }
                else
                {

                    Ride *current = rideHead;

                    while (current->next != NULL)
                    {
                        current = current->next;
                    }
                    current->next = newRide;
                }
                rideCount++;
            }
            file.close();
            cout << "Rides loaded successfully!" << endl;
            ;
        }
        else
        {
            cout << "No ride file found." << endl;
            ;
        }
    }

    void ViewRides() // Display Rides
    {
        if (rideHead == NULL)
        {
            cout << "No rides available." << endl;
            ;
            return;
        }

        cout << "Available Rides:" << endl
             << endl;
        Ride *current = rideHead;

        while (current != NULL)
        {
            if (current->status == "working" || current->status == "Working")
            {
                cout << "Name: " << current->name << "  ";
                cout << "Duration: " << current->duration << "  ";
                cout << "Price: " << current->price << " " << endl
                     << endl;
            }
            current = current->next;
        }
    }

    void BookRide() // Booing Function
    {
        string customerName, rideName, bookingId;
        int quantity;

        cout << "Enter your name: ";
        cin.ignore();
        getline(cin, customerName);

        cout<<endl;
        ViewRides();

        cout << "Enter Ride Name: ";
        getline(cin, rideName);

        bool found = false;

        Ride *current = rideHead;

        while (current != NULL)
        {
            if (current->name == rideName)
            {
                found = true;
                break;
            }
            current = current->next;
        }

        if (!found)
        {
            cout << "Ride not found! Please choose a valid ride." << endl;
            ;
            return;
        }

        cout << "Enter Quantity: ";
        cin >> quantity;

        cout << "Enter Booking ID: ";
        cin.ignore();
        getline(cin, bookingId);

        double cost = quantity * stod(current->price);

        Booking *temp = bookingFront;
        while (temp != NULL)
        {
            if (temp->bookingId == bookingId)
            {
                cout << "Booking ID already exists. Please enter a unique ID." << endl;
                
                return;
            }
            temp = temp->next;
        }

        Booking *newBooking = new Booking;
        newBooking->customerName = customerName;
        newBooking->rideName = rideName;
        newBooking->bookingId = bookingId;
        newBooking->quantity = quantity;
        newBooking->cost = cost;
        newBooking->next = NULL;

        if (bookingRear == NULL)
        {
            bookingFront = bookingRear = newBooking;
        }
        else
        {
            bookingRear->next = newBooking;
            bookingRear = newBooking;
        }

        cout << "Ride booked successfully! Booking ID: " << newBooking->bookingId << "" << endl;
        ;
    }

    void CancelBooking() // Cancel Booking and update File
    {
        string bookingId;

        if (bookingFront == NULL)
        {
            cout << "No bookings to cancel." << endl;
            ;
            return;
        }

        cout << "Enter Booking ID to cancel: ";
        cin.ignore();
        getline(cin, bookingId);

        Booking *current = bookingFront;
        Booking *previous = NULL;

        while (current != NULL)
        {
            if (current->bookingId == bookingId)
            {

                if (previous == NULL)
                {

                    bookingFront = current->next;
                }
                else
                {
                    previous->next = current->next;
                }

                if (current == bookingRear)
                {
                    bookingRear = previous;
                }

                delete current;

                cout << "Booking with ID " << bookingId << " has been canceled." << endl;
                ;

                SaveBookingsToFile();

                return;
            }
            previous = current;
            current = current->next;
        }

        cout << "Booking ID not found." << endl;
        
    }

    void SubmitComplaint()  // Submint Complaints
    {
        string complaint, name;
        

        cout << "Enter your name: ";
        cin >> name;

        cout << "Enter your complaint: ";
        cin.ignore();
        getline(cin, complaint);

        ofstream file("complaints.txt", ios::app);
        if (file.is_open())
        {
            file << name << " " << complaint << endl;
            file.close();
            cout << "Complaint submitted successfully!" << endl;
            ;
        }
        else
        {
            cout << "Error saving complaint." << endl;
            ;
        }
    }

    void SaveAndExit() // Save bookings and empty ride and booking node
    {

        SaveBookingsToFile();

        Ride *currentRide = rideHead;

        while (currentRide != NULL)
        {
            Ride *nextRide = currentRide->next;
            delete currentRide;
            currentRide = nextRide;
        }

        Booking *currentBooking = bookingFront;
        while (currentBooking != NULL)
        {
            Booking *nextBooking = currentBooking->next;
            delete currentBooking;
            currentBooking = nextBooking;
        }

        cout << "Exiting..." << endl;
        
    }

    void SaveBookingsToFile() // Save booking data to bookings.txt
    {
        ofstream file("bookings.txt");
        if (file.is_open())
        {
            Booking *current = bookingFront;
            while (current != NULL)
            {
                file << current->customerName << " "
                     << current->rideName << " "
                     << current->quantity << " "
                     << current->cost << " "
                     << current->bookingId << endl;
                current = current->next;
            }
            file.close();
            cout << "Bookings updated successfully!" << endl;
            ;
        }
        else
        {
            cout << "Error saving bookings." << endl;
            ;
        }
    }

    void LoadBookingsFromFile()
    {
        ifstream file("bookings.txt");
        if (file.is_open())
        {
            string customerName, rideName, bookingId;
            int quantity;
            double cost;

            while (file >> customerName >> rideName >> quantity >> cost >> bookingId)
            {
                Booking *newBooking = new Booking;
                newBooking->customerName = customerName;
                newBooking->rideName = rideName;
                newBooking->quantity = quantity;
                newBooking->cost = cost;
                newBooking->bookingId = bookingId;
                newBooking->next = NULL;

                if (bookingRear == NULL)
                {
                    bookingFront = bookingRear = newBooking;
                }
                else
                {
                    bookingRear->next = newBooking;
                    bookingRear = newBooking;
                }
            }
            file.close();
            cout << "Bookings loaded successfully!" << endl;
            
        }
        else
        {
            cout << "No booking file found." << endl;
            
        }
    }

public:
    void menu() // Main Menu
    {

        LoadRidesFromFile();
        LoadBookingsFromFile();

        int choice;
        do
        {
            xAgain:
            
            cout << "\nCustomer Panel:" << endl;
            cout << "1. View Rides" << endl;
            cout << "2. Book Ride" << endl;
            cout << "3. Cancel Booking" << endl;
            cout << "4. Submit Complaint" << endl;
            cout << "5. Exit" << endl
                 << endl;
            cout << "Enter your choice: ";
            cin >> choice;
             if (cin.fail())
            {
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                cout << "Invalid input. Please enter a number.\n";
                goto xAgain;
            }

            switch (choice)
            {
            case 1:
                ViewRides();
                break;
            case 2:
                BookRide();
                break;
            case 3:
                CancelBooking();
                break;
            case 4:
                SubmitComplaint();
                break;
            case 5:
                SaveAndExit();
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
                ;
            }
        } while (choice != 5);
    }
};
int main()
{
    Customer obj;
    obj.menu();
}
