#include "Interface.h"

using namespace std;

class Interface {
   public:
    void blood_symbol(int middle) { // show blood symbol
        int h = 1;
        int middle_1 = middle;
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        for (int i = 0; i < 5; i++) {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED);  // set the word to red colour
            cout << string(middle_1, ' ') << string(h, '|') << endl;
            middle_1 = middle_1 - 1;
            h = h + 2;
            usleep(100000);
        }
        for (int i = 0; i < 3; i++) {
            cout << string(middle_1, ' ') << string(h, '|') << endl;
            middle_1 = middle_1 + 1;
            h = h - 2;
            usleep(100000);
        }
        position_str(middle, "\\\\\|//");
        cout<<endl;

        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);  // reset to default
        position_str(middle, "Once a blood donor, always a lifesaver");
        for (int j = 0; j < 2; j++) {
            cout << endl;
        }
    }

    struct // declare these variable
    {
        int height, width, middle;
    } size1;

    int screen_size() {  // detect the size of the screen like width, height and the center
        CONSOLE_SCREEN_BUFFER_INFO csbi;  // to get the width and height of the screen display (calculate in character)
        if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
            // an error occourred
            cerr << "Cannot determine console size." << endl;  // cerr (character error -- use to display error message)
        } else {
            size1.width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
            size1.height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
            size1.middle = size1.width / 2;
        }
        return size1.width, size1.height, size1.middle;
    }

    void position_str(int middle, string str1) {   // align the string to center
        int middle_1 = middle;
        int str_length = str1.length();
        middle_1 = middle_1 - (str_length / 2);
        cout << string(middle_1, ' ') << str1 << endl
             << endl;
    }

    void blink_word(int middle, string str2)  // 	make the word blink
    {
        int middle_1 = middle;
        int str_length = str2.length();
        middle_1 = middle_1 - (str_length / 2);
        cout << string(middle_1, ' ') << "\033[5m" << str2 << "\033[0m" << endl;
    }

    void header(int middle) {  // cover page welcoming the user
        position_str(middle, "Welcome to Blood Donation System");
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        blink_word(middle, "Press y to continue......");
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }



    void main_menu(int middle) {
        blood_symbol(middle);
        position_str(middle, "[1] DONOR PAGE    ");
        position_str(middle, "[2] RECIPIENT PAGE");
        position_str(middle, "[3] EXIT          ");
    }

    void menu_donor(int middle) {
        system("cls");
        blood_symbol(middle);
        position_str(middle, "[1] ADD DONOR           ");
        position_str(middle, "[2] DELETE DONOR        ");
        position_str(middle, "[3] DISPLAY DONOR       ");
        position_str(middle, "[4] EDIT DONOR          ");
        position_str(middle, "[5] RESET DONOR         ");
        position_str(middle, "[6] SORT DONOR          ");
        position_str(middle, "[7] SEARCH DONOR        ");
        position_str(middle, "[8] RETURN              ");
        cout << "Please enter your option: ";
    }

    void donor_show(int middle){
        system("cls");
        blood_symbol(middle);
        position_str(middle,"[1] DISPLAY DONOR LIST    ");
        position_str(middle,"[2] DISPLAY BLOOD TYPE    ");
        position_str(middle,"[3] DISPLAY ALL           ");
        position_str(middle,"[4] RETURN                ");
        cout << "Please enter your option: ";
    }

    void donor_sort(int middle){
        system("cls");
        blood_symbol(middle);
        position_str(middle,"[1] SORT BY BLOOD TYPE    ");
        position_str(middle,"[2] SORT BY IC            ");
        position_str(middle,"[3] RETURN                ");
        cout << "Please enter your option: ";
    }

    void donor_search(int middle){
        system("cls");
        blood_symbol(middle);
        position_str(middle,"[1] SEARCH BY NAME        ");
        position_str(middle,"[2] SEARCH BY IC          ");
        position_str(middle,"[3] RETURN                ");
        cout << "Please enter your option: ";
    }

    void menu_recipient(int middle) {
        system("cls");
        blood_symbol(middle);
        position_str(middle, "[1] ADD RECIPIENT         ");
        position_str(middle, "[2] DELETE RECIPIENT      ");
        position_str(middle, "[3] DISPLAY RECIPIENT     ");
        position_str(middle, "[4] EDIT RECIPIENT        ");
        position_str(middle, "[5] SORT RECIPIENT        ");
        position_str(middle, "[6] SEARCH RECIPIENT      ");
        position_str(middle, "[7] CHECK BLOOD SUPPLY    ");
        position_str(middle, "[8] RETURN                ");
        cout << "Please enter your option: ";
    }

    void recipient_show(int middle){
        system("cls");
        blood_symbol(middle);
        position_str(middle,"[1] DISPLAY RECIPIENT LIST");
        position_str(middle,"[2] DISPLAY BLOOD TYPE    ");
        position_str(middle,"[3] DISPLAY ALL           ");
        position_str(middle,"[4] RETURN                ");
        cout << "Please enter your option: ";
    }

    void recipient_sort(int middle){
        system("cls");
        blood_symbol(middle);
        position_str(middle,"[1] SORT BY BLOOD TYPE    ");
        position_str(middle,"[2] SORT BY IC            ");
        position_str(middle,"[3] RETURN                ");
        cout << "Please enter your option: ";
    }

    void recipient_search(int middle){
        system("cls");
        blood_symbol(middle);
        position_str(middle,"[1] SEARCH BY NAME        ");
        position_str(middle,"[2] SEARCH BY IC          ");
        position_str(middle,"[3] RETURN                ");
        cout << "Please enter your option: ";
    }


    void quit(int middle) {
        system("cls");
        blood_symbol(middle);
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);  // set to yellow colour
        blink_word(middle, "Thanks for using this system!");
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        cout << endl;
        position_str(middle, "Press any key to exit.");

    }

};


