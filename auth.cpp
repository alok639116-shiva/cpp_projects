#include <iostream>
#include <fstream>
#include <string>
#include <conio.h> // Password masking (_getch) ke liye

using namespace std;

class UserAuthentication {
private:
    string username;
    string password;

    // Password ko mask (*) karne wala special function
    string getMaskedPassword() {
        string pass = "";
        char ch;
        while ((ch = _getch()) != '\r') { // '\r' matlab Enter key
            if (ch == '\b') { // '\b' matlab Backspace
                if (pass.length() > 0) {
                    pass.pop_back();
                    cout << "\b \b"; // Screen se ek '*' mitaane ke liye
                }
            } else {
                pass.push_back(ch);
                cout << '*'; // Character ki jagah '*' dikhayega
            }
        }
        cout << endl;
        return pass;
    }

public:
    // 1. Register Function
    void registerUser() {
        string regUser, regPass, u, p;
        bool exists = false;

        cout << "\n--- USER REGISTRATION ---" << endl;
        cout << "Enter New Username: ";
        cin >> regUser;

        // Check karna ki username pehle se toh nahi hai
        ifstream infile("users.txt");
        while (infile >> u >> p) {
            if (u == regUser) {
                exists = true;
                break;
            }
        }
        infile.close();

        if (exists) {
            cout << "\n❌ Error: Username already exists! Try another one." << endl;
            return;
        }

        cout << "Enter New Password: ";
        regPass = getMaskedPassword();

        // Data ko file mein save karna
        ofstream outfile("users.txt", ios::app);
        outfile << regUser << " " << regPass << "\n";
        outfile.close();

        cout << "\n✅ Registration Successful! You can now login." << endl;
    }

    // 2. Login Function
    void loginUser() {
        string loginUser, loginPass, u, p;
        bool success = false;

        cout << "\n--- USER LOGIN ---" << endl;
        cout << "Enter Username: ";
        cin >> loginUser;
        cout << "Enter Password: ";
        loginPass = getMaskedPassword();

        // File se match karna
        ifstream infile("users.txt");
        while (infile >> u >> p) {
            if (u == loginUser && p == loginPass) {
                success = true;
                break;
            }
        }
        infile.close();

        if (success) {
            cout << "\n🔓 LOGIN SUCCESSFUL! Welcome to the secure dashboard." << endl;
        } else {
            cout << "\n❌ Invalid Username or Password! Access Denied." << endl;
        }
    }
};

int main() {
    int choice;
    UserAuthentication auth;

    while (true) {
        cout << "\n====================================";
        cout << "\n   SECURE AUTHENTICATION SYSTEM";
        cout << "\n====================================";
        cout << "\n1. Register (Sign Up)";
        cout << "\n2. Login (Sign In)";
        cout << "\n3. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        if (choice == 1) {
            auth.registerUser();
        } 
        else if (choice == 2) {
            auth.loginUser();
        } 
        else if (choice == 3) {
            cout << "\nThank you for using the Secure Auth System!\n";
            break;
        } 
        else {
            cout << "\nInvalid Choice! Please try again.";
        }
    }
    return 0;
}