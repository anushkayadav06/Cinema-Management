#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Item
{
    string name;
    double price;

public:
    Item(string name, double price) : name(name), price(price) {}

    virtual void display() const { cout << name << " - Rs" << price << endl; }

    const string &getName() const { return name; }
    double getPrice() const { return price; }
};

class Beverage : public Item
{
public:
    Beverage(string name, double price) : Item(name, price) {}
};

class Snack : public Item
{
public:
    Snack(string name, double price) : Item(name, price) {}
};

class Movie
{
public:
    string title;
    int duration;
    string showtime;
    int totalSeats;
    int occupiedSeats;
    string language;
    bool isPremium;
    string genre;

    Movie(string title, string genre, int duration, string showtime,
          int totalSeats, string language, bool isPremium)
        : title(title), duration(duration), showtime(showtime),
          totalSeats(totalSeats), occupiedSeats(0), language(language),
          isPremium(isPremium) {}

    void displayInfo() const
    {
        cout << "Movie: " << title << " (" << language << ")" << endl;
        cout << "Genre: " << genre << endl;
        cout << "Duration: " << duration << " minutes" << endl;
        cout << "Showtime: " << showtime << endl;
        cout << "Ticket Price: Rs" << (isPremium ? 300.0 : 200.0) << endl;
        cout << "Vacant Seats: " << (totalSeats - occupiedSeats) << endl;
    }

    bool bookSeat(vector<Item *> &menu, double &totalCost)
    {
        if (occupiedSeats < totalSeats)
        {
            occupiedSeats++;
            cout << "Do you want to purchase snacks or beverages? (yes/no): ";
            string confirmation;
            cin >> confirmation;
            if (confirmation == "yes")
            {
                cout << "Menu at " << title << " (" << showtime << "):" << endl;
                while (true)
                {
                    for (int i = 0; i < menu.size(); i++)
                    {
                        cout << i + 1 << ". ";
                        menu[i]->display();
                    }
                    cout << "Enter the item number you want to purchase (0 to skip or -1 "
                            "to finish): ";
                    int itemChoice;
                    cin >> itemChoice;
                    if (itemChoice == -1)
                    {
                        break;
                    }
                    else if (itemChoice > 0 && itemChoice <= menu.size())
                    {
                        totalCost += menu[itemChoice - 1]->getPrice();
                        cout << "Item added to the order." << endl;
                    }
                }
            }
            return true;
        }
        else
        {
            return false;
        }
    }
};

class Cinema
{
public:
    string name;
    string location;
    vector<Movie *> movies;
    vector<Item *> menu;

    Cinema(string name, string location, vector<Movie *> &movies,
           vector<Item *> &menu)
        : name(name), location(location), movies(movies), menu(menu) {}

    void displayInfo() const
    {
        cout << "Cinema: " << name << " (" << location << ")" << endl;
        cout << "No of screens available: 4" << endl;
    }

    void displayMovieInfo() const
    {
        cout << "Movies currently showing at " << name << ":" << endl;

        int movieIndex = 1;
        for (const Movie *movie : movies)
        {
            cout << "Movie " << movieIndex << ":" << endl;
            movie->displayInfo();
            cout << endl;
            movieIndex++;
        }
    }

    void displayMenu() const
    {
        cout << "Menu at " << name << ":" << endl;

        for (const Item *item : menu)
        {
            item->display();
        }
    }

    void bookSeat(int movieNumber)
    {
        if (movieNumber >= 1 && movieNumber <= movies.size())
        {
            Movie *selectedMovie = movies[movieNumber - 1];
            double totalCost = (selectedMovie->isPremium ? 300.0 : 200.0);

            if (selectedMovie->bookSeat(menu, totalCost))
            {
                cout << "Do you want to confirm the booking? (yes/no): ";
                string confirmation;
                cin >> confirmation;
                if (confirmation == "yes")
                {
                    cout << "Booking confirmed. Here's your ticket:" << endl;
                    cout << "========================================" << endl;
                    cout << "Movie: " << selectedMovie->title << " ("
                         << selectedMovie->language << ")" << endl;
                    cout << "Showtime: " << selectedMovie->showtime << endl;
                    cout << "Total Cost: Rs" << totalCost << endl;
                    cout << "Enjoy the movie!" << endl;
                }
                else
                {
                    cout << "Booking canceled." << endl;
                }
            }
            else
            {
                cout << "No vacant seats available for " << selectedMovie->title
                     << " at " << selectedMovie->showtime
                     << " (Language: " << selectedMovie->language << ")" << endl;
            }
        }
        else
        {
            cout << "Invalid movie number. Please try again." << endl;
        }
    }
};

int main()
{
    vector<Movie *> movies;
    movies.push_back(new Movie("Interstellar", "Sci-Fi Adventure", 120, "13:00",
                               50, "English", false));
    movies.push_back(new Movie("Interstellar", "Sci-Fi Adventure", 120, "15:00",
                               50, "English", false));
    movies.push_back(
        new Movie("Conjuring", "Horror", 120, "12:30", 50, "English", true));
    movies.push_back(
        new Movie("Conjuring", "Horror", 120, "15:30", 50, "English", true));
    movies.push_back(new Movie("Zindagi Na Milegi Dobara", "Romance", 150,
                               "14:00", 30, "Hindi", true));
    movies.push_back(new Movie("Zindagi Na Milegi Dobara", "Romance", 150,
                               "18:00", 30, "Hindi", true));
    movies.push_back(
        new Movie("Duniyadari", "Drama", 150, "17:00", 30, "Marathi", false));
    movies.push_back(
        new Movie("Duniyadari", "Drama", 150, "11:00", 30, "Marathi", false));

    vector<Item *> menu;
    menu.push_back(new Beverage("Pepsi", 250));
    menu.push_back(new Snack("Salted Popcorn", 300));
    menu.push_back(new Snack("Caramel Popcorn", 350));
    menu.push_back(new Snack("Samosa", 100));

    Cinema cinema("PVR ICON", "Pavilion Mall, Pune", movies, menu);

    int choice;
    while (true)
    {
        cout << "----------------------------------------------" << endl;
        cout << "\nCinema Management Menu:" << endl;
        cout << "1. Display Cinema Information" << endl;
        cout << "2. Display Movie Information" << endl;
        cout << "3. Display Menu" << endl;
        cout << "4. Book a Seat" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        try
        {
            switch (choice)
            {
            case 1:
                cout << "----------------------------------------------" << endl;
                cout << "Welcome!!" << endl;
                cinema.displayInfo();
                break;
            case 2:
                cout << "----------------------------------------------" << endl;
                cinema.displayMovieInfo();
                break;
            case 3:
                cout << "----------------------------------------------" << endl;
                cinema.displayMenu();
                break;
            case 4:
                cout << "----------------------------------------------" << endl;
                cinema.displayMovieInfo();
                int movieChoice;
                cout << "Enter the movie number you want to book: ";
                cin >> movieChoice;

                if (movieChoice < 1 || movieChoice > cinema.movies.size())
                {
                    throw 1;
                }

                cinema.bookSeat(movieChoice);
                break;
            case 5:
                cout << "----------------------------------------------" << endl;
                cout << "Goodbye!" << endl;
                return 0;
            default:
                cout << "----------------------------------------------" << endl;
                cout << "Invalid choice. Please try again." << endl;
                break;
            }
        }
        catch (int)
        {
            cout << "Exception Caught: Invalid movie number" << endl;
        }
    }

    return 0;
}