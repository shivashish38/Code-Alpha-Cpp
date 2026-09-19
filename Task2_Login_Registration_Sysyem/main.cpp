#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <limits>
using namespace std;

const string USER_FILE = "users.txt";

bool isValidUsername(const string& username) {
    if (username.length() < 3 || username.length() > 20)
        return false;

    for (char ch : username) {
        if (!isalnum(static_cast<unsigned char>(ch)) && ch != '_')
            return false;
    }
    return true;
}

bool isValidPassword(const string& password) {
    if (password.length() < 6)
        return false;

    bool hasLetter = false;
    bool hasDigit = false;

    for (char ch : password) {
        if (isalpha(static_cast<unsigned char>(ch)))
            hasLetter = true;
        if (isdigit(static_cast<unsigned char>(ch)))
            hasDigit = true;
    }

    return hasLetter && hasDigit;
}

bool usernameExists(const string& username) {
    ifstream file(USER_FILE);
    string storedUsername, storedPassword;

    while (file >> storedUsername >> storedPassword) {
        if (storedUsername == username)
            return true;
    }
    return false;
}

void registerUser() {
    string username, password, confirmPassword;

    cout << "\n========== REGISTRATION ==========\n";
    cout << "Username: ";
    cin >> username;

    if (!isValidUsername(username)) {
        cout << "Error: Username must be 3-20 characters and contain only "
                "letters, numbers, or underscore.\n";
        return;
    }

    if (usernameExists(username)) {
        cout << "Error: Username already exists.\n";
        return;
    }

    cout << "Password: ";
    cin >> password;

    if (!isValidPassword(password)) {
        cout << "Error: Password must be at least 6 characters and contain "
                "both letters and numbers.\n";
        return;
    }

    cout << "Confirm password: ";
    cin >> confirmPassword;

    if (password != confirmPassword) {
        cout << "Error: Passwords do not match.\n";
        return;
    }

    ofstream file(USER_FILE, ios::app);
    if (!file) {
        cout << "Error: Could not open user database.\n";
        return;
    }

    // For an educational console project, credentials are stored locally.
    // A production system should use salted password hashing.
    file << username << ' ' << password << '\n';

    cout << "Registration successful! You can now log in.\n";
}

void loginUser() {
    string username, password;
    string storedUsername, storedPassword;

    cout << "\n============== LOGIN ==============\n";
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    ifstream file(USER_FILE);
    if (!file) {
        cout << "No user database found. Please register first.\n";
        return;
    }

    while (file >> storedUsername >> storedPassword) {
        if (storedUsername == username && storedPassword == password) {
            cout << "Login successful. Welcome, " << username << "!\n";
            return;
        }
    }

    cout << "Login failed: Invalid username or password.\n";
}

int main() {
    int choice;

    do {
        cout << "\n====================================\n";
        cout << "     LOGIN & REGISTRATION SYSTEM\n";
        cout << "====================================\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter 1, 2, or 3.\n";
            continue;
        }

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                loginUser();
                break;
            case 3:
                cout << "Exiting program. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 3);

    return 0;
}
