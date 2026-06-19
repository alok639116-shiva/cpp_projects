#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Book {
public:
    int id;
    string title;
    string author;

    void addBook() {
        cout << "\nEnter Book ID: ";
        cin >> id;
        cin.ignore(); 
        cout << "Enter Book Title: ";
        getline(cin, title);
        cout << "Enter Author Name: ";
        getline(cin, author);
    }

    void showBook() {
        cout << "\nID: " << id << "\tTitle: " << title << "\tAuthor: " << author;
    }
};

int main() {
    int choice;
    Book b;
    
    while (true) {
        cout << "\n\n=== LIBRARY MANAGEMENT SYSTEM ===";
        cout << "\n1. Add New Book";
        cout << "\n2. Display All Books";
        cout << "\n3. Search Book by ID";
        cout << "\n4. Delete Book by ID";
        cout << "\n5. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        if (choice == 1) {
            b.addBook();
            ofstream file("library.txt", ios::app);
            file << b.id << "|" << b.title << "|" << b.author << "\n";
            file.close();
            cout << "Book saved successfully!";
        } 
        else if (choice == 2) {
            cout << "\n--- Book List ---";
            ifstream file("library.txt");
            if (!file) {
                cout << "\nNo books found! Add some books first.";
                continue;
            }
            while (file >> b.id) {
                file.ignore(); 
                getline(file, b.title, '|');
                getline(file, b.author);
                b.showBook();
            }
            file.close();
        } 
        else if (choice == 3) {
            int searchId;
            bool found = false;
            cout << "\nEnter Book ID to Search: ";
            cin >> searchId;

            ifstream file("library.txt");
            while (file >> b.id) {
                file.ignore();
                getline(file, b.title, '|');
                getline(file, b.author);
                
                if (b.id == searchId) {
                    cout << "\n--- Book Found! ---";
                    b.showBook();
                    found = true;
                    break;
                }
            }
            file.close();
            if (!found) cout << "\nBook not found with ID " << searchId;
        }
        else if (choice == 4) {
            int deleteId;
            bool found = false;
            cout << "\nEnter Book ID to Delete: ";
            cin >> deleteId;

            ifstream file("library.txt");
            ofstream tempFile("temp.txt");

            while (file >> b.id) {
                file.ignore();
                getline(file, b.title, '|');
                getline(file, b.author);
                
                if (b.id != deleteId) {
                    tempFile << b.id << "|" << b.title << "|" << b.author << "\n";
                } else {
                    found = true;
                }
            }
            file.close();
            tempFile.close();

            remove("library.txt");        
            rename("temp.txt", "library.txt"); 

            if (found) cout << "\nBook Deleted Successfully!";
            else cout << "\nBook not found!";
        }
        else if (choice == 5) {
            cout << "\nThank you for using the Library System!\n";
            break;
        } 
        else {
            cout << "\nInvalid Choice! Try again.";
        }
    }
    return 0;
}