Library Management System — C++ OOP Mini Project
A console-based Library Management System built to demonstrate all four core OOP concepts in C++.
Designed for 1st-year B.Tech students learning Object-Oriented Programming.

How to Compile & Run
g++ -o library_mgmt library_management.cpp -std=c++17
./library_mgmt        # Linux / macOS
library_mgmt.exe      # Windows
OOP Concepts Used — Where and How
1. Abstraction
Class: LibraryItem

LibraryItem is an abstract base class — it defines what a library item must be able to do (display info, return its ID and title), but leaves the how to the derived class. You can't create a LibraryItem object directly because it has pure virtual functions (= 0). This forces every item type (like Book) to provide its own implementation.

virtual void displayInfo() const = 0;   // pure virtual — must be overridden
virtual string getTitle() const = 0;
2. Encapsulation
Class: Book

All data members (bookID, title, author, isAvailable) are private. Outside code cannot touch them directly. Instead, controlled access is provided through public getters and setters. This protects the internal state of the object.

private:
    int bookID;
    string title;
    bool isAvailable;

public:
    int getID() const { return bookID; }
    void setAvailability(bool status) { isAvailable = status; }
3. Inheritance
Classes: Book inherits from LibraryItem

Book extends LibraryItem using : public LibraryItem. This means Book automatically gets the interface defined in LibraryItem and must implement all pure virtual functions. Inheritance models the "is-a" relationship — a Book is a LibraryItem.

class Book : public LibraryItem {
    // Book must implement displayInfo(), getTitle(), getID()
};
4. Polymorphism
Where: Inside Library::displayAllBooks()

A LibraryItem* pointer is used to call displayInfo() on a Book object. Even though the pointer is of the base class type, it calls the correct overridden version in Book at runtime. This is runtime polymorphism through virtual functions.

LibraryItem* item = &books[i];
item->displayInfo();   // calls Book's version, not the base class
5. Constructors & Destructors
Class	Constructor	Destructor
Book	Sets all fields, prints confirmation message	Defined (no special cleanup here)
Library	Prints "system initialized"	Prints "system shut down"
The destructor of Library runs automatically when lib goes out of scope at the end of main().

Class Structure
LibraryItem  (abstract base class)
    └── Book  (concrete derived class)

Library      (manager class — contains a vector<Book>)
Features
Option	Feature	Description
1	Add Book	Enter ID, title, author — adds to list
2	Display All Books	Shows all books with their status
3	Search Book	Search by ID or partial title (case-insensitive)
4	Issue Book	Marks a book as "Issued Out"
5	Return Book	Marks a book as "Available" again
6	Exit	Exits the program cleanly
Sample Run
  Library system initialized.

=============================
     LIBRARY MANAGEMENT
=============================
  1. Add Book
  2. Display All Books
  3. Search Book
  4. Issue Book
  5. Return Book
  6. Exit
-----------------------------
  Enter your choice: 1

-- Add New Book --
Enter Book ID   : 101
Enter Title     : The Great Gatsby
Enter Author    : F. Scott Fitzgerald
[+] Book added: "The Great Gatsby"

-----------------------------
  Enter your choice: 1

-- Add New Book --
Enter Book ID   : 102
Enter Title     : 1984
Enter Author    : George Orwell
[+] Book added: "1984"

-----------------------------
  Enter your choice: 2

-- All Books in Library --

Book 1:
  ID     : 101
  Title  : The Great Gatsby
  Author : F. Scott Fitzgerald
  Status : Available

Book 2:
  ID     : 102
  Title  : 1984
  Author : George Orwell
  Status : Available

-----------------------------
  Enter your choice: 4

-- Issue Book --
Enter Book ID to issue: 101
[✓] "The Great Gatsby" has been issued successfully.

-----------------------------
  Enter your choice: 2

-- All Books in Library --

Book 1:
  ID     : 101
  Title  : The Great Gatsby
  Author : F. Scott Fitzgerald
  Status : Issued Out

Book 2:
  ID     : 102
  Title  : 1984
  Author : George Orwell
  Status : Available

-----------------------------
  Enter your choice: 3

-- Search Book --
Search by:
  1. Book ID
  2. Title
Choice: 2
Enter title keyword: 1984

Match found:
  ID     : 102
  Title  : 1984
  Author : George Orwell
  Status : Available

-----------------------------
  Enter your choice: 5

-- Return Book --
Enter Book ID to return: 101
[✓] "The Great Gatsby" returned successfully. It is now available.

-----------------------------
  Enter your choice: 6

  Exiting...

  Library system shut down. Goodbye!
File Structure
library_management.cpp   ← all code in one file
README.md                ← this file
