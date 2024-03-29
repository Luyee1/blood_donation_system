#include "Admin.h"
#include <iostream>
#include <string>
using namespace std;

// Initialize static member variables
const string Admin::default_name = "admin";
const string Admin::default_pwd = "admin";

bool Admin::login(const string& username, const string& password) {
    return username == default_name && password == default_pwd;
}

bool Admin::displayLoginPrompt() {
    string admin_name, admin_pwd;

        cout << "Username: ";
        cin >> admin_name;
        cout << endl;
        cout << "Password: ";
        cin >> admin_pwd;

        if (login(admin_name, admin_pwd)) {
            cout << "Login success!" << endl;
            system("pause");
            system("cls");
            // Additional code to handle successful login
            return false;
        } else {
            cout << "Invalid name or password, please try again..." << endl;
            system("pause");
            system("cls");
            // Additional code to handle failed login

        }

}
