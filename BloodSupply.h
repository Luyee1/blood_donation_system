#include <chrono>
#include <cstdio>
#include <ctime>
#include <deque>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <queue>
#include <regex>
#include <stack>
#include <string>
#include <vector>
using namespace std;


struct User {
    string name;
    string ic;
    string contactNo;
    string bloodType;
    string gender;
    int age;
    double weight;
    double bloodAmount;

    string dateAdded;  // date added
};

class BloodBank {
   protected:
    vector<User> vecUser;  // create a vector based on struct User
    //deque inherits the properties of both queue and stack
    deque<string> bloodSupply;  // all of the blood type in queue
    deque<string> tempQueue;    // copy of bloodSupply queue

    // stack for tracking each blood type count
    stack<string> bloodA;
    stack<string> bloodB;
    stack<string> bloodAB;
    stack<string> bloodO;

    // regex for error checking
    static regex checkABC;
    static regex checkIC;
    static regex checkContactNo;

    ofstream fout;  // write file
    ifstream fin;   // read file

   public:
    // pure virtual functions
    virtual void add() = 0;
    virtual void del() = 0;
    virtual void display() = 0;
    virtual void edit() = 0;
    virtual void reset() = 0;
    virtual void bubbleSort_bloodType() = 0;
    virtual void quickSort_ic() = 0;
    virtual void binarySearch_ic() = 0;
    virtual void linearSearch_name() = 0;
    virtual void saveFile() = 0;
    virtual void readFile() = 0;

};

// regex for error checking
//match any uppercase or lowercase letter
regex BloodBank::checkABC("^[A-Za-z ]+$");


   //- first 2 digits is [0-9]
   //- thrid digit is [0-1]
   //-fourth digit is  [0-9]
   //-fifith digit is [0-3]
   //- sixth digit [0-9]
   //- 7th digit [0-5]
   //- 8th digit [0-9]
   //- 9th to 12th digit [0-9
regex BloodBank::checkIC("^[0-9][0-9][0-1][0-9][0-3][0-9][0-5][0-9][0-9]{4}$");


//(\\+?6?01):Matches the Malaysian country code (+60 or 60) followed by the mobile prefix "01".
//[02-46-9]:Matches any digit except 1 and 3, effectively covering 0, 2, 4, 5, 6, 7, 8, 9.
//-?: Matches an optional hyphen.
regex BloodBank::checkContactNo("^(\\+?6?01)[02-46-9]-*[0-9]{7}$|^(\\+?6?01)[1]-*[0-9]{8}$");

