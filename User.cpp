#include <chrono>
#include <cstdio>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <regex>
#include <stack>
#include <string>
#include <vector>
#include "BloodSupply.h"
using namespace std;

class Donor : public BloodBank {
   private:
    User donor;  // donor information in struct User
    User recipient; //Use by the useBloodSupply

   public:
    // Donor constructor to initialize struct User donor to default value (0 or empty string)
    Donor() {
        donor.name = "";
        donor.ic = "";
        donor.contactNo = "";
        donor.bloodType = "";
        donor.gender = "";
        donor.age = 0;
        donor.weight = 0;
        donor.bloodAmount = 0;
        donor.dateAdded = "";
    }

    string getbloodType()
    {
        return donor.bloodType;
    }

    // functions to pass this donor , vector, queue, stack to recipient class to access
    const vector<User>& getDonorVector() const {
        return vecUser;
    }

    deque<string>& getBloodSupplyQueue() {
        return bloodSupply;
    }
    deque<string>& getTempQueue() {
        return tempQueue;
    }

    stack<string>& getBloodA() {
        return bloodA;
    }
    stack<string>& getBloodB() {
        return bloodB;
    }
    stack<string>& getBloodAB() {
        return bloodAB;
    }
    stack<string>& getBloodO() {
        return bloodO;
    }

    // current date
    string currentDate() {
        time_t rawtime;
        tm* timeinfo;
        char buffer[80];

        time(&rawtime);
        timeinfo = localtime(&rawtime);

        strftime(buffer, 80, "%Y-%m-%d", timeinfo);
        return buffer;
    }

    // calculate the age based on user given IC number then return the calculated age
    int calculateAge(tm birthdate) {
        time_t now = chrono::system_clock::to_time_t(chrono::system_clock::now());
        tm* now_tm = localtime(&now);
        int years = now_tm->tm_year - birthdate.tm_year;
        if (now_tm->tm_mon < birthdate.tm_mon || (now_tm->tm_mon == birthdate.tm_mon && now_tm->tm_mday < birthdate.tm_mday)) {
            years--;
        }
        return years;
    }


    // **function to add donor information
    void add() {
        bool eligible = true;  // assume donor is eligible to donate blood

        cout << "Donor Information: " << endl;

        // add name
        while (true) {
            cout << "Name: ";
            getline(cin, donor.name);
            if (regex_match(donor.name, checkABC)) {
                break;  // Exit the loop if the input is valid
            } else {
                cout << "Invalid name." << endl;
            }
        }

        // add ic number
        while (true) {
            cout << "IC: ";
            getline(cin, donor.ic);
            if (regex_match(donor.ic, checkIC)) {
                // auto get the age from IC number
                tm birthdate = {0};
                int year = stoi(donor.ic.substr(0, 2));
                if (year <= 24) { // Assuming the current year is 2024
                    year += 100; // For years 2000 and onwards
                }
                birthdate.tm_year = year;
                birthdate.tm_mon = stoi(donor.ic.substr(2, 2)) - 1;     // Months are 0-indexed
                birthdate.tm_mday = stoi(donor.ic.substr(4, 2));
                donor.age = calculateAge(birthdate);  // set the age of donor
                if (donor.age < 18 || donor.age > 65) {
                    eligible = false;
                }
                ///////////////////////////////////
                break;  // Exit the loop if the input is valid
            } else {
                cout << "Invalid IC." << endl;
            }
        }

        // add contact number
        while (true) {
            cout << "Contact Number: ";
            getline(cin, donor.contactNo);
            if (regex_match(donor.contactNo, checkContactNo)) {
                break;  // Exit the loop if the input is valid
            } else {
                cout << "Invalid contact number." << endl;
            }
        }

        // add blood type
        while (true) {
            cout << "Blood Type: ";
            getline(cin, donor.bloodType);
            if (donor.bloodType == "A" || donor.bloodType == "B" || donor.bloodType == "AB" || donor.bloodType == "O") {
                break;  // Exit the loop if the input is valid
            } else {
                cout << "Invalid blood type. Please enter 'A', 'B', 'AB', or 'O'." << endl;
            }
        }

        // add gender
        while (true) {
            cout << "Gender (M for male | F for female): ";
            getline(cin, donor.gender);
            if (donor.gender == "M" || donor.gender == "F") {
                break;  // Exit the loop if the input is valid
            } else {
                cout << "Invalid gender. Please enter M for male | F for female" << endl;
            }
        }

        // add weight
        while (true) {
            cout << "Weight (KG): ";
            cin >> donor.weight;
            if (cin.fail() || cin.peek() != '\n') {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid weight. " << endl;
                // cin fail, loop again
            } else {
                if (donor.weight < 45) {
                    eligible = false;
                }
                cin.ignore();  // clear the new line input
                break;         // Exit the loop if the input is valid
            }
        }

        // add blood amount
        while (true) {
            cout << "Blood amount to donate (ml): ";
            cin >> donor.bloodAmount;
            if (cin.fail() || cin.peek() != '\n') {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid blood amount. Please enter a number." << endl;
                // cin fail, loop again
            } else {
                if (donor.bloodAmount >= 350 && donor.bloodAmount <= 450) {
                    // Blood amount is within the valid range, do nothing
                } else {
                    cout << "Please enter a blood amount between 350 and 450 ml." << endl;
                    continue;  // Continue the loop to prompt the user again
                }
                cin.ignore();  // Clear the new line input
                break;         // Exit the loop if the input is valid
            }
        }

        // check if donor is eligible to donate blood
        if (eligible) {
            // update the blood supply and blood type if donor is eligible
            if (donor.bloodType == "A") {
                bloodSupply.push_back("A");
                bloodA.push("A");
            } else if (donor.bloodType == "B") {
                bloodSupply.push_back("B");
                bloodB.push("B");
            } else if (donor.bloodType == "AB") {
                bloodSupply.push_back("AB");
                bloodAB.push("AB");
            } else if (donor.bloodType == "O") {
                bloodSupply.push_back("O");
                bloodO.push("O");
            }

            donor.dateAdded = currentDate();  // set the date added
            vecUser.push_back(donor);
            cout << "Donor added successfully on " << donor.dateAdded << endl;
        } else {
            cout << "Unable to register donor because it is not eligible" << endl;
        }
    }

    // **function to delete donor information
    void del() {
        int index;

        if (vecUser.empty()) {
            cout << "No donors to delete" << endl;
        } else {
            display();  // show all donors
            cout << "Enter the index of donor you want to delete: ";
            cin >> index;

            if (index > 0 && index <= vecUser.size()) {
                // Remove blood type stack
                if (vecUser.at(index - 1).bloodType == "A" && !bloodA.empty()) {
                    bloodA.pop();
                } else if (vecUser.at(index - 1).bloodType == "B" && !bloodB.empty()) {
                    bloodB.pop();
                } else if (vecUser.at(index - 1).bloodType == "AB" && !bloodAB.empty()) {
                    bloodAB.pop();
                } else if (vecUser.at(index - 1).bloodType == "O" && !bloodO.empty()) {
                    bloodO.pop();
                }

                // Update bloodSupply queue
                // tempQueue = {};  // Clear tempQueue
                while (!bloodSupply.empty()) {
                    if (bloodSupply.front() != vecUser.at(index - 1).bloodType) {
                        tempQueue.push_back(bloodSupply.front());  // push all other blood type that we dont want to remove into tempQueue
                    }
                    bloodSupply.pop_front();  // remove the blood type that we want to remove
                }
                bloodSupply = tempQueue;  // copy tempQueue(updated version with the blood type removed) back to bloodSupply

                vecUser.erase(vecUser.begin() + index - 1);  // remove the donor, eg. begin is 0, we want to delete index 1, then we minus 1 to get the actual index of vector
                cout << "Donor deleted successfully" << endl;
            } else {
                cout << "Invalid index!" << endl;
            }
        }
    }

    // **function to display donor information
    void display() {
        if (vecUser.empty()) {
            cout << "No donors in the blood bank :(" << endl;
        } else {
            cout << "Donors in the Blood Bank:" << endl;
            cout << setw(5) << "Index" << setw(15) << "Name" << setw(15) << "IC" << setw(20) << "Contact Number" << setw(15) << "Blood Type" << setw(15) << "Gender" << setw(10) << "Age" << setw(10) << "Weight" << setw(15) << "Blood Amount" << setw(15) << "Date Added" << endl;

            for (int i = 0; i < vecUser.size(); i++) {
                cout << setw(5) << i + 1 << setw(15) << vecUser.at(i).name << setw(15) << vecUser.at(i).ic << setw(20) << vecUser.at(i).contactNo << setw(15) << vecUser.at(i).bloodType << setw(15) << vecUser.at(i).gender << setw(10) << vecUser.at(i).age << setw(10) << vecUser.at(i).weight << setw(15) << vecUser.at(i).bloodAmount << setw(15) << vecUser.at(i).dateAdded << endl;
            }
        }
    }

    // **function to edit donor information
    void edit() {
        int index;
        int choice;
        bool quitFlag;
        bool switchFlag;
        string quit;
        string continueEdit;

        if (vecUser.empty()) {
            cout << "No donors to edit" << endl;
        } else {
            do {
                quitFlag = true;

                display();  // show all the donors first

                while (true) {
                    cout << "Enter the index of donor you want to edit: ";
                    cin >> index;
                    if (cin.fail() || cin.peek() != '\n') {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid index. " << endl;
                        // cin fail, loop again
                    } else {
                        // if index is smaller than 1 or it is greater than vector size, it is invalid index
                        if (index < 1 || index > vecUser.size()) {
                            cout << "Invalid index." << endl;
                        } else {
                            break;  // exit loop, valid index
                        }
                    }
                }

                do {
                    switchFlag = true;

                    cout << "Which information you want to edit?" << endl;
                    cout << "1: Name" << endl;
                    cout << "2: IC" << endl;
                    cout << "3: Contact Number" << endl;
                    cout << "4: Blood Type" << endl;
                    cout << "5: Gender" << endl;
                    cout << "6: Weight" << endl;
                    cout << "7: Blood Amount" << endl;
                    cout << "8: Exit" << endl;
                    cin >> choice;
                    if (cin.fail() || cin.peek() != '\n') {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid input. " << endl;
                        // cin fail, loop again
                    } else {
                        cin.ignore();

                        switch (choice) {
                            case 1:
                                cout << "Current Name: " << vecUser.at(index - 1).name << endl;
                                while (true) {
                                    cout << "New Name: ";
                                    getline(cin, vecUser.at(index - 1).name);
                                    if (regex_match(vecUser.at(index - 1).name, checkABC)) {
                                        break;  // Exit the loop if the input is valid
                                    } else {
                                        cout << "Invalid name." << endl;
                                    }
                                }
                                break;
                            case 2:
                                cout << "Current IC: " << vecUser.at(index - 1).ic << endl;
                                while (true) {
                                    cout << "New IC: ";
                                    getline(cin, vecUser.at(index - 1).ic);
                                    if (regex_match(vecUser.at(index - 1).ic, checkIC)) {
                                        break;  // Exit the loop if the input is valid
                                    } else {
                                        cout << "Invalid IC." << endl;
                                    }
                                }
                                break;
                            case 3:
                                cout << "Current Contact Number: " << vecUser.at(index - 1).contactNo << endl;
                                while (true) {
                                    cout << "New Contact Number: ";
                                    getline(cin, vecUser.at(index - 1).contactNo);
                                    if (regex_match(vecUser.at(index - 1).contactNo, checkContactNo)) {
                                        break;  // Exit the loop if the input is valid
                                    } else {
                                        cout << "Invalid contact number." << endl;
                                    }
                                }
                                break;
                            case 4:
                                cout << "Current Blood Type: " << vecUser.at(index - 1).bloodType << endl;
                                while (true) {
                                    string oldBloodType = vecUser.at(index - 1).bloodType;
                                    string newBloodType;

                                    cout << "New Blood Type: ";
                                    getline(cin, newBloodType);
                                    if (newBloodType == "A" || newBloodType == "B" || newBloodType == "AB" || newBloodType == "O") {
                                        // if there is difference, update the old one with new one
                                        if (oldBloodType != newBloodType) {
                                            // update old blood type with new blood type
                                            vecUser.at(index - 1).bloodType = newBloodType;

                                            // Update blood type supply queue (using deque)
                                            bloodSupply.at(index - 1) = newBloodType;

                                            // Update blood supply counts (using stack)
                                            // Decrement the count for the old blood type (vecUser.at(index - 1).bloodType)
                                            if (oldBloodType == "A") {
                                                bloodA.pop();
                                            } else if (oldBloodType == "B") {
                                                bloodB.pop();
                                            } else if (oldBloodType == "AB") {
                                                bloodAB.pop();
                                            } else if (oldBloodType == "O") {
                                                bloodO.pop();
                                            }

                                            // Increment the count for the new blood type
                                            if (newBloodType == "A") {
                                                bloodA.push(newBloodType);
                                            } else if (newBloodType == "B") {
                                                bloodB.push(newBloodType);
                                            } else if (newBloodType == "AB") {
                                                bloodAB.push(newBloodType);
                                            } else if (newBloodType == "O") {
                                                bloodO.push(newBloodType);
                                            }
                                        }
                                        break;  // Exit the loop if the input is valid
                                    } else {
                                        cout << "Invalid blood type. Please enter 'A', 'B', 'AB', or 'O'." << endl;
                                    }
                                }
                                break;
                            case 5:
                                cout << "Current Gender: " << vecUser.at(index - 1).gender << endl;
                                while (true) {
                                    cout << "New Gender (M for male | F for female): ";
                                    getline(cin, vecUser.at(index - 1).gender);
                                    if (vecUser.at(index - 1).gender == "M" || vecUser.at(index - 1).gender == "F") {
                                        break;  // Exit the loop if the input is valid
                                    } else {
                                        cout << "Invalid gender. Please enter M for male | F for female" << endl;
                                    }
                                }
                                break;

                            case 6:
                                cout << "Current Weight (KG): " << vecUser.at(index - 1).weight << endl;
                                while (true) {
                                    double newWeight;

                                    cout << "New Weight: ";
                                    cin >> newWeight;
                                    if (cin.fail() || cin.peek() != '\n') {
                                        cin.clear();
                                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                        cout << "Invalid weight. " << endl;
                                        // cin fail, loop again
                                    } else {
                                        if (vecUser.at(index - 1).weight < 45) {
                                            cout << "You are not eligible" << endl;
                                        } else {
                                            // eligible, update with new weight
                                            vecUser.at(index - 1).weight = newWeight;
                                        }
                                        break;  // Exit the loop if the input is valid
                                    }
                                }
                                break;
                            case 7:
                                cout << "Current Blood Amount (ml): " << vecUser.at(index - 1).bloodAmount << endl;
                                while (true) {
                                    double newbloodAmount;

                                    cout << "New Blood Amount (ml): ";
                                    cin >> newbloodAmount;
                                    if (cin.fail() || cin.peek() != '\n') {
                                        cin.clear();
                                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                        cout << "Invalid blood amount. " << endl;
                                        // cin fail, loop again
                                    } else {
                                        if (vecUser.at(index - 1).bloodAmount >= 350 && vecUser.at(index - 1).bloodAmount <= 450) {
                                            // eligible, update with new weight
                                            vecUser.at(index - 1).bloodAmount = newbloodAmount;
                                        } else {
                                            cout << "Please enter a blood amount between 350 and 450 ml." << endl;
                                            continue;  // Continue the loop to prompt the user again
                                        }
                                        break;  // Exit the loop if the input is valid
                                    }
                                }
                                break;
                            case 8:
                                break;
                            default:
                                cout << "Invalid input!" << endl;
                                switchFlag = false;  // loop again
                                break;
                        }
                    }
                } while (!switchFlag);
                cout << "\nEdit successfully!" << endl;
                while (true) {
                    cout << "Do you want to edit again [y/n]: ";
                    getline(cin, continueEdit);
                    if (continueEdit == "n" || continueEdit == "N") {
                        quitFlag = false;  // quit do while loop
                        break;
                    } else if (continueEdit == "y" || continueEdit == "Y") {
                        // do nothing
                        break;
                    } else {
                        cout << "Invalid input!" << endl;
                    }
                }
            } while (quitFlag);
        }
    }

    // **function to reset donor information
    void reset() {
        string choice;
        while (true) {
            cout << "Are you sure you want to reset? [y/n]: ";
            getline(cin, choice);
            if (choice == "y" || choice == "Y") {
                vecUser.clear();      // clear vector of donor information
                bloodSupply.clear();  // clear blood supply queue
                // clear all the blood type count (stack)
                while (bloodA.size() != 0) {
                    bloodA.pop();
                }
                while (bloodB.size() != 0) {
                    bloodB.pop();
                }
                while (bloodAB.size() != 0) {
                    bloodAB.pop();
                }
                while (bloodO.size() != 0) {
                    bloodO.pop();
                }
                cout << "Reset successfully!" << endl;
                break;
            } else if (choice == "n" || choice == "N") {
                break;  // do nothing
            } else {
                cout << "Invalid input." << endl;
            }
        }
    }

    ////////// sort algorithm //////////

    // **function using bubble sort algorithm based on name
    void bubbleSort_bloodType() {
        int n = vecUser.size();
        for(int i = 0; i < n-1; i++) {
            for (int j = 0; j < n-i-1; j++) {
                if (vecUser[j].bloodType > vecUser[j+1].bloodType) {
                    swap(vecUser[j], vecUser[j+1]);
                }
            }
        }
    }


    // part of quick sort algorithm based on ic
    int partition(int low, int high) {
        string pivot = vecUser[high].ic;
        int i = (low - 1);

        for (int j = low; j <= high - 1; j++) {
            if (vecUser[j].ic <= pivot) {
                i++;
                swap(vecUser[i], vecUser[j]);
            }
        }
        swap(vecUser[i + 1], vecUser[high]);
        return (i + 1);
    }

    void quickSort(int low, int high) {
        if (low < high) {
            int pi = partition(low, high);
            quickSort(low, pi - 1);
            quickSort(pi + 1, high);
        }
    }

    // **function using quick sort algorithm based on ic
    void quickSort_ic() {
        if (vecUser.empty()) {
            cout << "There is no donor to sort" << endl;
        } else {
            quickSort(0, vecUser.size() - 1);
        }
    }

    ////////// search algorithm //////////

    // WARNING: vector must be sorted before using binary search!!!
    int binarySearch(const string& itemToSearch) {
        int left = 0;
        int right = vecUser.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;

            // check if it is at mid
            if (vecUser.at(mid).ic == itemToSearch)
                return mid;  // found it! return the index

            // it is not at left side, move our search area to right side by setting left(initial) to mid + 1
            if (vecUser.at(mid).ic < itemToSearch)
                left = mid + 1;

            // it is not at right side, move our search area to left side by setting right(end) to mid - 1
            else
                right = mid - 1;
        }
        return -1;  // Name not found
    }

    // **function using binary search algorithm based on ic
    void binarySearch_ic() {
        string searchItem;
        cout << "Enter donor ic to search: ";
        getline(cin, searchItem);
        int result = binarySearch(searchItem);  // get the result of binary search
        if (result != -1) {
            cout << "Donor ic found: "
                 << "[" << result + 1 << "] " << vecUser.at(result).ic << endl;
        } else {
            cout << "Donor not found." << endl;
        }
    }

    // linear search algorithm
    int linearSearch(const string& itemToSearch) {
        for (int i = 0; i < vecUser.size(); i++) {
            if (vecUser.at(i).name == itemToSearch) {
                return i;  // found it! return the index
            }
        }
        return -1;  // not found :(
    }

    // **function using linear search algorithm based on name
    void linearSearch_name() {
        string searchItem;
        cout << "Enter donor name to search: ";
        getline(cin, searchItem);
        int result = linearSearch(searchItem);  // get the result of binary search
        if (result != -1) {
            cout << "Donor name found: "
                 << "[" << result + 1 << "] " << vecUser.at(result).name << endl;
        } else {
            cout << "Donor not found." << endl;
        }
    }

    // **function to show what are available blood types
    void checkBloodSupply(const Donor& donor) {
        const vector<User>& vec = donor.getDonorVector();  // get the vector from donor and access it

        // check blood supply
        string selectedBloodType;
        bool bloodAvailable = false;
        cout << "Check blood type supply availability [A|B|AB|O]: ";
        getline(cin, selectedBloodType);
        if (bloodSupply.empty()) {
            cout << "Blood supply is empty!" << endl;
        } else {
            bool flag = true;
            for (int i = 0; i < vec.size(); i++) {
                if (vec.at(i).bloodType == selectedBloodType) {
                    bloodAvailable = true;
                    if (flag) {
                        cout << "Selected blood supply is available!" << endl;
                        cout << "Available blood type " << selectedBloodType <<endl;
                        flag = false;  // reset flag so above message only show once
                    }

                }
            }

            if (!bloodAvailable) {
                cout << "Your blood type supply is unavailable right now..." << endl;
            }
        }
    }
    ////////// file handling //////////

    // **function to save donor information to a new created file / overwrite it
    void saveFile() {
        string choice;

        while (true) {
            cout << "Do you want to save file?" << endl;
            cout << "This will overwrite or create a new file (\"donor.csv\") in your directory. Confirm? [y/n]" << endl;
            getline(cin, choice);
            if (choice == "n" || choice == "N") {
                break;  // exit loop, do nothing
            } else if (choice == "y" || choice == "Y") {
                fout.open("donor.csv", ios::trunc);  // truncate (Any contents that existed in the file before it is open are discarded.)
                if (fout.is_open()) {
                    fout << "Index,Name,IC,Contact No,Blood Type,Gender,Age,Weight,Blood Amount,Date Added" << endl;
                    for (int i = 0; i < vecUser.size(); i++) {
                        fout << i + 1 << "," << vecUser.at(i).name << "," << vecUser.at(i).ic << "," << vecUser.at(i).contactNo << "," << vecUser.at(i).bloodType << "," << vecUser.at(i).gender << "," << vecUser.at(i).age << "," << vecUser.at(i).weight << "," << vecUser.at(i).bloodAmount << "," << vecUser.at(i).dateAdded << endl;
                    }
                } else {
                    cout << "Error, file is not opened!" << endl;
                    break;  // exit loop
                }
                cout << "Saved file successfully!" << endl;
                break;  // exit loop after saving file
            } else {
                cout << "Invalid input." << endl;
            }
        }
        fout.close();
    }

    // **function to read donor information from the file
    void readFile() {
        string temp, line;

        fin.open("donor.csv");

        if (fin.is_open()) {
            vecUser.clear();      // clear vector of donor information

            // clear all the blood type count (stack)
            while (bloodA.size() != 0) {
                bloodA.pop();
            }
            while (bloodB.size() != 0) {
                bloodB.pop();
            }
            while (bloodAB.size() != 0) {
                bloodAB.pop();
            }
            while (bloodO.size() != 0) {
                bloodO.pop();
            } // reset all information before reading

            // Skipping the first line (title row)
            getline(fin, line);

            while (getline(fin, line)) {
                stringstream ss(line);  // used for breaking words

                // Read each field from the line
                getline(ss, temp, ',');  // Skipping index as it's not part of User data
                getline(ss, donor.name, ',');
                getline(ss, donor.ic, ',');
                getline(ss, donor.contactNo, ',');

                getline(ss, donor.bloodType, ',');
                if (donor.bloodType == "A") {
                    bloodSupply.push_back("A");
                    bloodA.push("A");
                } else if (donor.bloodType == "B") {
                    bloodSupply.push_back("B");
                    bloodB.push("B");
                } else if (donor.bloodType == "AB") {
                    bloodSupply.push_back("AB");
                    bloodAB.push("AB");
                } else if (donor.bloodType == "O") {
                    bloodSupply.push_back("O");
                    bloodO.push("O");
                }

                getline(ss, donor.gender, ',');

                // convert string to integer (age)
                getline(ss, temp, ',');
                donor.age = stoi(temp);

                // convert string to integer (weight)
                getline(ss, temp, ',');
                donor.weight = stoi(temp);

                // convert string to integer (bloodAmount)
                getline(ss, temp, ',');
                donor.bloodAmount = stoi(temp);

                getline(ss, donor.dateAdded);

                vecUser.push_back(donor);
            }
            cout << "Read file successfully!" << endl;
        } else {
            cout << "Error! You do not have \"donor.csv\" file in your directory :(" << endl;
        }
        fin.close();
    }
        //Use to read the blood count file
        void readBloodTypeCount() {
        // Open the file in read mode
        ifstream file("bloodcount.csv");

        // Check if the file is open
        if (!file.is_open()) {
            cerr << "Could not open the file '" << "bloodcount.csv" << "' for reading.\n";
            return;
        }

        string line;
        string bloodType;
        int count;

        // Skip the header line
        getline(file, line);

        // Read each line from the file
        while (getline(file, line)) {
            stringstream ss(line);

            // Parse the blood type and count from the line
            getline(ss, bloodType, ',');
            ss >> count;

            // Process the blood type and count (e.g., print them)
            cout << "Blood Type: " << bloodType << ", Count: " << count << endl;
        }

        // Close the file
        file.close();
    }

        //Use to save the blood count file
        void saveBloodTypeCount() {
        // Open the file in write mode
        ofstream file("bloodcount.csv");


        // Write the headers
        file << "Blood Type,Count\n";

        // Write the blood type counts
        file << "A," << bloodA.size() << "\n";
        file << "B," << bloodB.size() << "\n";
        file << "AB," << bloodAB.size() << "\n";
        file << "O," << bloodO.size() << "\n";

        // Close the file
        file.close();
    }

    // Function to decrease the blood supply when a new recipient is added
    bool useBloodSupply(string bloodType) {
        if (bloodType == "A" && !bloodA.empty()) {
            bloodA.pop();
        } else if (bloodType == "B" && !bloodB.empty()) {
            bloodB.pop();
        } else if (bloodType == "AB" && !bloodAB.empty()) {
            bloodAB.pop();
        } else if (bloodType == "O" && !bloodO.empty()) {
            bloodO.pop();
        } else {
            cout << "Insufficient blood supply of type " << bloodType << endl;
            return false; // Return false to indicate insufficient supply
        }
        return true; // Return true to indicate successful usage of supply
    }

    // Function to increase the blood supply when a recipient is deleted
    void replenishBloodSupply(string bloodType) {
        if (bloodType == "A") {
            bloodA.push("A");
        } else if (bloodType == "B") {
            bloodB.push("B");
        } else if (bloodType == "AB") {
            bloodAB.push("AB");
        } else if (bloodType == "O") {
            bloodO.push("O");
        } else {
            cout << "Invalid blood type " << bloodType << endl;
        }
    }

};

class Recipient : public BloodBank {
   private:
    User recipient;  // recipient information in struct User

   public:
    // Recipient constructor to initialize struct User recipient to default value (0 or empty string)
    Recipient() {
        recipient.name = "";
        recipient.ic = "";
        recipient.contactNo = "";
        recipient.bloodType = "";
        recipient.gender = "";
        recipient.age = 0;
        recipient.weight = 0;
        recipient.dateAdded = "";
    }

    string getbloodType()
    {
        return recipient.bloodType;
    }

    // current date
    string currentDate() {
        time_t rawtime;
        tm* timeinfo;
        char buffer[80];

        time(&rawtime);
        timeinfo = localtime(&rawtime);

        strftime(buffer, 80, "%Y-%m-%d", timeinfo);
        return buffer;
    }

    // calculate the age based on user given IC number then return the calculated age
    int calculateAge(tm birthdate) {
        time_t now = chrono::system_clock::to_time_t(chrono::system_clock::now());
        tm* now_tm = localtime(&now);
        int years = now_tm->tm_year - birthdate.tm_year;
        if (now_tm->tm_mon < birthdate.tm_mon || (now_tm->tm_mon == birthdate.tm_mon && now_tm->tm_mday < birthdate.tm_mday)) {
            years--;
        }
        return years;
    }

    // **function to add recipient information
    void add() {
        cout << "Recipient Information: " << endl;

        // add name
        while (true) {
            cout << "Name: ";
            getline(cin, recipient.name);
            if (regex_match(recipient.name, checkABC)) {
                break;  // Exit the loop if the input is valid
            } else {
                cout << "Invalid name." << endl;
            }
        }

        // add ic number
        while (true) {
            cout << "IC: ";
            getline(cin, recipient.ic);
            if (regex_match(recipient.ic, checkIC)) {
                // auto get the age from IC number
                tm birthdate = {0};
                int year = stoi(recipient.ic.substr(0, 2));
                if (year <= 24) { // Assuming the current year is 2024
                    year += 100; // For years 2000 and onwards
                }
                birthdate.tm_year = year;
                birthdate.tm_mon = stoi(recipient.ic.substr(2, 2)) - 1;     // Months are 0-indexed
                birthdate.tm_mday = stoi(recipient.ic.substr(4, 2));
                recipient.age = calculateAge(birthdate);  // set the age of recipient
                break;  // Exit the loop if the input is valid
            } else {
                cout << "Invalid IC." << endl;
            }
        }

        // add contact number
        while (true) {
            cout << "Contact Number: ";
            getline(cin, recipient.contactNo);
            if (regex_match(recipient.contactNo, checkContactNo)) {
                break;  // Exit the loop if the input is valid
            } else {
                cout << "Invalid contact number." << endl;
            }
        }

        // add blood type
        while (true) {
            cout << "Blood Type: ";
            getline(cin, recipient.bloodType);
            if (recipient.bloodType == "A" || recipient.bloodType == "B" || recipient.bloodType == "AB" || recipient.bloodType == "O") {
                break;  // Exit the loop if the input is valid
            } else {
                cout << "Invalid blood type. Please enter 'A', 'B', 'AB', or 'O'." << endl;
            }
        }

        // add gender
        while (true) {
            cout << "Gender (M for male | F for female): ";
            getline(cin, recipient.gender);
            if (recipient.gender == "M" || recipient.gender == "F") {
                break;  // Exit the loop if the input is valid
            } else {
                cout << "Invalid gender. Please enter M for male | F for female" << endl;
            }
        }

        // add weight
        while (true) {
            cout << "Weight (KG): ";
            cin >> recipient.weight;
            if (cin.fail() || cin.peek() != '\n' || recipient.weight < 0) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid weight. Please enter a non-negative number." << endl;
                // cin fail, loop again
            } else {
                cin.ignore();  // clear the new line input
                break;         // Exit the loop if the input is valid
            }
        }

        recipient.dateAdded = currentDate();  // set the date added
        vecUser.push_back(recipient);
        cout << "Recipient added successfully on " << recipient.dateAdded << endl;
    }

    // **function to delete recipient information
    void del() {
        int index;

        if (vecUser.empty()) {
            cout << "No recipients to delete" << endl;
        } else {
            display();  // show all recipients
            cout << "Enter the index of recipient you want to delete: ";
            cin >> index;

            if (index > 0 && index <= vecUser.size()) {
                // Remove blood type stack
                if (vecUser.at(index - 1).bloodType == "A" && !bloodA.empty()) {
                    bloodA.pop();
                } else if (vecUser.at(index - 1).bloodType == "B" && !bloodB.empty()) {
                    bloodB.pop();
                } else if (vecUser.at(index - 1).bloodType == "AB" && !bloodAB.empty()) {
                    bloodAB.pop();
                } else if (vecUser.at(index - 1).bloodType == "O" && !bloodO.empty()) {
                    bloodO.pop();
                }


                // Update bloodSupply queue
                // tempQueue = {};  // Clear tempQueue
                while (!bloodSupply.empty()) {
                    if (bloodSupply.front() != vecUser.at(index - 1).bloodType) {
                        tempQueue.push_back(bloodSupply.front());  // push all other blood type that we dont want to remove into tempQueue
                    }
                    bloodSupply.pop_front();  // remove the blood type that we want to remove
                }
                bloodSupply = tempQueue;  // copy tempQueue(updated version with the blood type removed) back to bloodSupply


                vecUser.erase(vecUser.begin() + index - 1);  // remove the recipient, eg. begin is 0, we want to delete index 1, then we minus 1 to get the actual index of vector
                cout << "Recipient deleted successfully" << endl;
            } else {
                cout << "Invalid index!" << endl;
            }
        }
    }

        void delblood() {
            if (!vecUser.empty()) {
                int index = vecUser.size(); // Get the index of the last element
                // Remove blood type stack
                if (vecUser.at(index - 1).bloodType == "A" && !bloodA.empty()) {
                    bloodA.pop();
                } else if (vecUser.at(index - 1).bloodType == "B" && !bloodB.empty()) {
                    bloodB.pop();
                } else if (vecUser.at(index - 1).bloodType == "AB" && !bloodAB.empty()) {
                    bloodAB.pop();
                } else if (vecUser.at(index - 1).bloodType == "O" && !bloodO.empty()) {
                    bloodO.pop();
                }

                vecUser.pop_back(); // Remove the last recipient
                cout << "Unable to add recipient due to lack of same blood type" << endl;
            } else {
                cout << "No recipients to delete" << endl;
            }
        }

    // **function to display recipient information
    void display() {
         if (vecUser.empty()) {
            cout << "No recipients in the blood bank :(" << endl;
        } else {
            cout << "Recipients in the Blood Bank:" << endl;
            cout << setw(5) << "Index" << setw(15) << "Name" << setw(15) << "IC" << setw(20) << "Contact Number" << setw(15) << "Blood Type" << setw(15) << "Gender" << setw(10) << "Age" << setw(10) << "Weight" << setw(15) << "Date Added" << endl;

            for (int i = 0; i < vecUser.size(); i++) {
                cout << setw(5) << i + 1 << setw(15) << vecUser.at(i).name << setw(15) << vecUser.at(i).ic << setw(20) << vecUser.at(i).contactNo << setw(15) << vecUser.at(i).bloodType << setw(15) << vecUser.at(i).gender << setw(10) << vecUser.at(i).age << setw(10) << vecUser.at(i).weight << setw(15) << vecUser.at(i).dateAdded << endl;
            }
        }

    }

    // **function to edit recipient information
    void edit() {
        int index;
        int choice;
        bool quitFlag;
        bool switchFlag;
        string quit;
        string continueEdit;

        if (vecUser.empty()) {
            cout << "No recipients to edit" << endl;
        } else {
            do {
                quitFlag = true;

                display();  // show all the recipients first

                while (true) {
                    cout << "Enter the index of recipient you want to edit: ";
                    cin >> index;
                    if (cin.fail() || cin.peek() != '\n') {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid index. " << endl;
                        // cin fail, loop again
                    } else {
                        // if index is smaller than 1 or it is greater than vector size, it is invalid index
                        if (index < 1 || index > vecUser.size()) {
                            cout << "Invalid index." << endl;
                        } else {
                            break;  // exit loop, valid index
                        }
                    }
                }

                do {
                    switchFlag = true;

                    cout << "Which information you want to edit?" << endl;
                    cout << "1: Name" << endl;
                    cout << "2: IC" << endl;
                    cout << "3: Contact Number" << endl;
                    cout << "4: Blood Type" << endl;
                    cout << "5: Gender" << endl;
                    cout << "6: Weight" << endl;
                    cout << "7: Exit" << endl;
                    cin >> choice;
                    if (cin.fail() || cin.peek() != '\n') {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid input. " << endl;
                        // cin fail, loop again
                    } else {
                        cin.ignore();

                        switch (choice) {
                            case 1:
                                cout << "Current Name: " << vecUser.at(index - 1).name << endl;
                                while (true) {
                                    cout << "New Name: ";
                                    getline(cin, vecUser.at(index - 1).name);
                                    if (regex_match(vecUser.at(index - 1).name, checkABC)) {
                                        break;  // Exit the loop if the input is valid
                                    } else {
                                        cout << "Invalid name." << endl;
                                    }
                                }
                                break;
                            case 2:
                                cout << "Current IC: " << vecUser.at(index - 1).ic << endl;
                                while (true) {
                                    cout << "New IC: ";
                                    getline(cin, vecUser.at(index - 1).ic);
                                    if (regex_match(vecUser.at(index - 1).ic, checkIC)) {
                                        break;  // Exit the loop if the input is valid
                                    } else {
                                        cout << "Invalid IC." << endl;
                                    }
                                }
                                break;
                            case 3:
                                cout << "Current Contact Number: " << vecUser.at(index - 1).contactNo << endl;
                                while (true) {
                                    cout << "New Contact Number: ";
                                    getline(cin, vecUser.at(index - 1).contactNo);
                                    if (regex_match(vecUser.at(index - 1).contactNo, checkContactNo)) {
                                        break;  // Exit the loop if the input is valid
                                    } else {
                                        cout << "Invalid contact number." << endl;
                                    }
                                }
                                break;
                            case 4:
                                cout << "Current Blood Type: " << vecUser.at(index - 1).bloodType << endl;
                                while (true) {
                                    string oldBloodType = vecUser.at(index - 1).bloodType;
                                    string newBloodType;

                                    cout << "New Blood Type: ";
                                    getline(cin, newBloodType);
                                    if (newBloodType == "A" || newBloodType == "B" || newBloodType == "AB" || newBloodType == "O") {
                                        // if there is difference, update the old one with new one
                                        if (oldBloodType != newBloodType) {
                                            // update old blood type with new blood type
                                            vecUser.at(index - 1).bloodType = newBloodType;

                                            // Update blood type supply queue (using deque)
                                            bloodSupply.at(index - 1) = newBloodType;

                                            // Update blood supply counts (using stack)
                                            // Decrement the count for the old blood type (vecUser.at(index - 1).bloodType)
                                            if (oldBloodType == "A") {
                                                bloodA.pop();
                                            } else if (oldBloodType == "B") {
                                                bloodB.pop();
                                            } else if (oldBloodType == "AB") {
                                                bloodAB.pop();
                                            } else if (oldBloodType == "O") {
                                                bloodO.pop();
                                            }

                                            // Increment the count for the new blood type
                                            if (newBloodType == "A") {
                                                bloodA.push(newBloodType);
                                            } else if (newBloodType == "B") {
                                                bloodB.push(newBloodType);
                                            } else if (newBloodType == "AB") {
                                                bloodAB.push(newBloodType);
                                            } else if (newBloodType == "O") {
                                                bloodO.push(newBloodType);
                                            }
                                        }
                                        break;  // Exit the loop if the input is valid
                                    } else {
                                        cout << "Invalid blood type. Please enter 'A', 'B', 'AB', or 'O'." << endl;
                                    }
                                }
                                break;
                            case 5:
                                cout << "Current Gender: " << vecUser.at(index - 1).gender << endl;
                                while (true) {
                                    cout << "New Gender (M for male | F for female): ";
                                    getline(cin, vecUser.at(index - 1).gender);
                                    if (vecUser.at(index - 1).gender == "M" || vecUser.at(index - 1).gender == "F") {
                                        break;  // Exit the loop if the input is valid
                                    } else {
                                        cout << "Invalid gender. Please enter M for male | F for female" << endl;
                                    }
                                }
                                break;

                            case 6:
                                cout << "Current Weight (KG): " << vecUser.at(index - 1).weight << endl;
                                while (true) {
                                    double newWeight;

                                    cout << "New Weight: ";
                                    cin >> newWeight;
                                    if (cin.fail() || cin.peek() != '\n') {
                                        cin.clear();
                                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                        cout << "Invalid weight. " << endl;
                                        // cin fail, loop again
                                    } else {
                                        if (vecUser.at(index - 1).weight < 45) {
                                            cout << "You are not eligible" << endl;
                                        } else {
                                            // eligible, update with new weight
                                            vecUser.at(index - 1).weight = newWeight;
                                        }
                                        break;  // Exit the loop if the input is valid
                                    }
                                }
                                break;

                            case 7:
                                break;
                        }
                    }
                } while (!switchFlag);
                cout << "\nEdit successfully!" << endl;
                while (true) {
                    cout << "Do you want to edit again [y/n]: ";
                    getline(cin, continueEdit);
                    if (continueEdit == "n" || continueEdit == "N") {
                        quitFlag = false;  // quit do while loop
                        break;
                    } else if (continueEdit == "y" || continueEdit == "Y") {
                        // do nothing
                        break;
                    } else {
                        cout << "Invalid input!" << endl;
                    }
                }
            } while (quitFlag);
        }
    }


    ////////// sort algorithm //////////

    // **function using bubble sort algorithm based on name
    void bubbleSort_bloodType() {
        int n = vecUser.size();
        for(int i = 0; i < n-1; i++) {
            for (int j = 0; j < n-i-1; j++) {
                if (vecUser[j].bloodType > vecUser[j+1].bloodType) {
                    swap(vecUser[j], vecUser[j+1]);
                }
            }
        }
    }

    // part of quick sort algorithm based on ic
    int partition(int low, int high) {
        string pivot = vecUser[high].ic;
        int i = (low - 1);

        for (int j = low; j <= high - 1; j++) {
            if (vecUser[j].ic <= pivot) {
                i++;
                swap(vecUser[i], vecUser[j]);
            }
        }
        swap(vecUser[i + 1], vecUser[high]);
        return (i + 1);
    }

    void quickSort(int low, int high) {
        if (low < high) {
            int pi = partition(low, high);
            quickSort(low, pi - 1);
            quickSort(pi + 1, high);
        }
    }


    // **function using quick sort algorithm based on ic
    void quickSort_ic() {
        if (vecUser.empty()) {
            cout << "There is no recipient to sort" << endl;
        } else {
            quickSort(0, vecUser.size() - 1);
        }
    }

    // **function to reset donor information
    void reset() {
        string choice;
        while (true) {
            cout << "Are you sure you want to reset? [y/n]: ";
            getline(cin, choice);
            if (choice == "y" || choice == "Y") {
                vecUser.clear();      // clear vector of donor information
                bloodSupply.clear();  // clear blood supply queue
                // clear all the blood type count (stack)
                while (bloodA.size() != 0) {
                    bloodA.pop();
                }
                while (bloodB.size() != 0) {
                    bloodB.pop();
                }
                while (bloodAB.size() != 0) {
                    bloodAB.pop();
                }
                while (bloodO.size() != 0) {
                    bloodO.pop();
                }
                cout << "Reset successfully!" << endl;
                break;
            } else if (choice == "n" || choice == "N") {
                break;  // do nothing
            } else {
                cout << "Invalid input." << endl;
            }
        }
    }
    ////////// search algorithm //////////

    // WARNING: vector must be sorted before using binary search!!!
    int binarySearch(const string& itemToSearch) {
        int left = 0;
        int right = vecUser.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;

            // check if it is at mid
            if (vecUser.at(mid).ic == itemToSearch)
                return mid;  // found it! return the index

            // it is not at left side, move our search area to right side by setting left(initial) to mid + 1
            if (vecUser.at(mid).ic < itemToSearch)
                left = mid + 1;

            // it is not at right side, move our search area to left side by setting right(end) to mid - 1
            else
                right = mid - 1;
        }
        return -1;  // Name not found
    }

    // **function using binary search algorithm based on ic
    void binarySearch_ic() {
        string searchItem;
        cout << "Enter recipient ic to search: ";
        getline(cin, searchItem);
        int result = binarySearch(searchItem);  // get the result of binary search
        if (result != -1) {
            cout << "Recipient ic found: "
                 << "[" << result + 1 << "] " << vecUser.at(result).ic << endl;
        } else {
            cout << "Recipient not found." << endl;
        }
    }

    // linear search algorithm
    int linearSearch(const string& itemToSearch) {
        for (int i = 0; i < vecUser.size(); i++) {
            if (vecUser.at(i).name == itemToSearch) {
                return i;  // found it! return the index
            }
        }
        return -1;  // not found :(
    }

    // **function using linear search algorithm based on name
    void linearSearch_name() {
        string searchItem;
        cout << "Enter recipient name to search: ";
        getline(cin, searchItem);
        int result = linearSearch(searchItem);  // get the result of binary search
        if (result != -1) {
            cout << "Recipient name found: "
                 << "[" << result + 1 << "] " << vecUser.at(result).name << endl;
        } else {
            cout << "Recipient not found." << endl;
        }
    }

    ////////// file handling //////////

    // **function to save recipient information to a new created file / overwrite it
    void saveFile() {
                fout.open("recipient.csv", ios::trunc);  // truncate (Any contents that existed in the file before it is open are discarded.)
                if (fout.is_open()) {
                    fout << "Index,Name,IC,Contact No,Blood Type,Gender,Age,Weight,Date Added" << endl;
                    for (int i = 0; i < vecUser.size(); i++) {
                        fout << i + 1 << "," << vecUser.at(i).name << "," << vecUser.at(i).ic << "," << vecUser.at(i).contactNo << "," << vecUser.at(i).bloodType << "," << vecUser.at(i).gender << "," << vecUser.at(i).age << "," << vecUser.at(i).weight << "," << vecUser.at(i).dateAdded << endl;
                    }
                } else {
                    cout << "Error, file is not opened!" << endl;

                }
                cout << "Saved file successfully!" << endl;
        fout.close();
    }

    // **function to read recipient information from the file
    void readFile() {
        string temp, line;

        fin.open("recipient.csv");

                if (fin.is_open()) {
                vecUser.clear();      // clear vector of donor information
                // clear all the blood type count (stack)
                while (bloodA.size() != 0) {
                    bloodA.pop();
                }
                while (bloodB.size() != 0) {
                    bloodB.pop();
                }
                while (bloodAB.size() != 0) {
                    bloodAB.pop();
                }
                while (bloodO.size() != 0) {
                    bloodO.pop();
                }  // reset all information before reading
                    // Skipping the first line (title row)
                    getline(fin, line);

                    while (getline(fin, line)) {
                        stringstream ss(line);  // used for breaking words

                        // Read each field from the line
                        getline(ss, temp, ',');  // Skipping index as it's not part of User data
                        getline(ss, recipient.name, ',');
                        getline(ss, recipient.ic, ',');
                        getline(ss, recipient.contactNo, ',');

                        getline(ss, recipient.bloodType, ',');
                        if (recipient.bloodType == "A") {
                            bloodSupply.push_back("A");
                            bloodA.push("A");
                        } else if (recipient.bloodType == "B") {
                            bloodSupply.push_back("B");
                            bloodB.push("B");
                        } else if (recipient.bloodType == "AB") {
                            bloodSupply.push_back("AB");
                            bloodAB.push("AB");
                        } else if (recipient.bloodType == "O") {
                            bloodSupply.push_back("O");
                            bloodO.push("O");
                        }

                        getline(ss, recipient.gender, ',');

                        // convert string to integer (age)
                        getline(ss, temp, ',');
                        recipient.age = stoi(temp);

                        // convert string to integer (weight)
                        getline(ss, temp, ',');
                        recipient.weight = stoi(temp);

                        getline(ss, recipient.dateAdded);

                        vecUser.push_back(recipient);
                    }
                    cout << "Read file successfully!" << endl;
                } else {
                    cout << "Error! You do not have \"recipient.csv\" file in your directory :(" << endl;
                }

        fin.close();
    }

};
