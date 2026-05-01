/*
 * Library Management System
 * Concepts: Abstraction, Encapsulation, Inheritance, Polymorphism
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// -------------------------------------------------------
// ABSTRACTION: Abstract base class (cannot be instantiated)
// Defines the "contract" that all library items must follow

class LibraryItem {
public:
    // Pure virtual functions make this class abstract
    virtual void displayInfo() const = 0;
    virtual string getTitle() const = 0;
    virtual int getID() const = 0;

    // Virtual destructor is important for proper cleanup in inheritance
    virtual ~LibraryItem() {
        // Base destructor (called automatically when derived object is destroyed)
    }
};


// -------------------------------------------------------
// INHERITANCE + ENCAPSULATION: Book derives from LibraryItem
// Private data members accessed only through public methods

class Book : public LibraryItem {
private:
    int bookID;
    string title;
    string author;
    bool isAvailable;  // true = in library, false = issued out

public:
    // Constructor — sets up the book when it's created
    Book(int id, string t, string a) {
        bookID = id;
        title = t;
        author = a;
        isAvailable = true;  // all books start as available
        cout << "[+] Book added: \"" << title << "\"" << endl;
    }

    // Destructor — called when a Book object is destroyed
    ~Book() {
        // nothing special to clean up here, but good to show it exists
    }

    // --- Getters (Encapsulation: controlled read access) ---
    int getID() const override {
        return bookID;
    }

    string getTitle() const override {
        return title;
    }

    string getAuthor() const {
        return author;
    }

    bool getAvailability() const {
        return isAvailable;
    }

    // --- Setters ---
    void setAvailability(bool status) {
        isAvailable = status;
    }

    // POLYMORPHISM: overrides the base class pure virtual function
    // Each type of LibraryItem can display info in its own way
    void displayInfo() const override {
        cout << "  ID     : " << bookID << endl;
        cout << "  Title  : " << title << endl;
        cout << "  Author : " << author << endl;
        cout << "  Status : " << (isAvailable ? "Available" : "Issued Out") << endl;
    }
};


// -------------------------------------------------------
// Library Manager: handles all operations on the collection
// -------------------------------------------------------
class Library {
private:
    vector<Book> books;  // stores all Book objects

    // Helper: find a book by ID, returns index or -1 if not found
    int findByID(int id) {
        for (int i = 0; i < (int)books.size(); i++) {
            if (books[i].getID() == id)
                return i;
        }
        return -1;
    }

public:
    Library() {
        cout << "\n  Library system initialized.\n";
    }

    ~Library() {
        cout << "\n  Library system shut down. Goodbye!\n";
    }

    // ADD a new book
    void addBook() {
        int id;
        string title, author;

        cout << "\n-- Add New Book --\n";
        cout << "Enter Book ID   : ";
        cin >> id;
        cin.ignore();  // clear newline left in buffer

        // Check for duplicate ID
        if (findByID(id) != -1) {
            cout << "[!] A book with ID " << id << " already exists.\n";
            return;
        }

        cout << "Enter Title     : ";
        getline(cin, title);

        cout << "Enter Author    : ";
        getline(cin, author);

        books.push_back(Book(id, title, author));
    }

    // DISPLAY all books
    void displayAllBooks() {
        cout << "\n-- All Books in Library --\n";

        if (books.empty()) {
            cout << "  No books found.\n";
            return;
        }

        for (int i = 0; i < (int)books.size(); i++) {
            cout << "\nBook " << (i + 1) << ":\n";

            // POLYMORPHISM in action: calling displayInfo() on a Book
            // through a pointer to LibraryItem (base class)
            LibraryItem* item = &books[i];
            item->displayInfo();
        }
    }

    // SEARCH by ID or title
    void searchBook() {
        cout << "\n-- Search Book --\n";
        cout << "Search by:\n";
        cout << "  1. Book ID\n";
        cout << "  2. Title\n";
        cout << "Choice: ";

        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            int id;
            cout << "Enter Book ID: ";
            cin >> id;

            int idx = findByID(id);
            if (idx == -1) {
                cout << "[!] No book found with ID " << id << ".\n";
            } else {
                cout << "\nBook found:\n";
                books[idx].displayInfo();
            }

        } else if (choice == 2) {
            string keyword;
            cout << "Enter title keyword: ";
            getline(cin, keyword);

            // Convert keyword to lowercase for case-insensitive search
            string lowerKey = keyword;
            transform(lowerKey.begin(), lowerKey.end(), lowerKey.begin(), ::tolower);

            bool found = false;
            for (auto& b : books) {
                string lowerTitle = b.getTitle();
                transform(lowerTitle.begin(), lowerTitle.end(), lowerTitle.begin(), ::tolower);

                if (lowerTitle.find(lowerKey) != string::npos) {
                    cout << "\nMatch found:\n";
                    b.displayInfo();
                    found = true;
                }
            }

            if (!found)
                cout << "[!] No books matched \"" << keyword << "\".\n";

        } else {
            cout << "[!] Invalid choice.\n";
        }
    }

    // ISSUE a book to someone
    void issueBook() {
        cout << "\n-- Issue Book --\n";
        cout << "Enter Book ID to issue: ";
        int id;
        cin >> id;

        int idx = findByID(id);
        if (idx == -1) {
            cout << "[!] Book not found.\n";
            return;
        }

        if (!books[idx].getAvailability()) {
            cout << "[!] \"" << books[idx].getTitle() << "\" is already issued out.\n";
            return;
        }

        books[idx].setAvailability(false);
        cout << "[✓] \"" << books[idx].getTitle() << "\" has been issued successfully.\n";
    }

    // RETURN a book
    void returnBook() {
        cout << "\n-- Return Book --\n";
        cout << "Enter Book ID to return: ";
        int id;
        cin >> id;

        int idx = findByID(id);
        if (idx == -1) {
            cout << "[!] Book not found.\n";
            return;
        }

        if (books[idx].getAvailability()) {
            cout << "[!] \"" << books[idx].getTitle() << "\" was not issued. Nothing to return.\n";
            return;
        }

        books[idx].setAvailability(true);
        cout << "[✓] \"" << books[idx].getTitle() << "\" returned successfully. It is now available.\n";
    }
};


// -------------------------------------------------------
// Menu display 

void showMenu() {
    cout << "\n===========================================\n";
    cout << "     ASMITA YADAV ---> RA2511003050539 \n         LIBRARY MANAGEMENT SYSTEM \n            OODP MINI Project  \n";
    cout << "============================================\n";
    cout << "  1. Add Book\n";
    cout << "  2. Display All Books\n";
    cout << "  3. Search Book\n";
    cout << "  4. Issue Book\n";
    cout << "  5. Return Book\n";
    cout << "  6. Exit\n";
    cout << "-----------------------------\n";
    cout << "  Enter your choice: ";
}


// -------------------------------------------------------
// Main function
int main() {
    Library lib;  // Library object created, constructor called

    int choice;

    do {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                lib.addBook();
                break;
            case 2:
                lib.displayAllBooks();
                break;
            case 3:
                lib.searchBook();
                break;
            case 4:
                lib.issueBook();
                break;
            case 5:
                lib.returnBook();
                break;
            case 6:
                cout << "\n  Exiting...\n";
                break;
            default:
                cout << "\n[!] Invalid option. Please enter 1-6.\n";
        }

    } while (choice != 6);

    // lib destructor runs automatically here when it goes out of scope

    return 0;
}
