#ifndef INTERFACE_H
#define INTERFACE_H

#include <Windows.h>
#include <conio.h>
#include <iomanip>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <queue>
#include <regex>
#include <stack>
#include <string>
#include <vector>
#include <chrono>
#include <ctime>


using namespace std;

class Interface1 {
public:
    void blood_symbol(int middle);
    int screen_size();
    void position_str(int middle, string str1);
    void blink_word(int middle, string str2);
    void header(int middle);
    void main_menu(int middle);
    void menu_donor(int middle);
    void donor_show(int middle);
    void donor_sort(int middle);
    void donor_search(int middle);
    void menu_recipient(int middle);
    void recipient_show(int middle);
    void recipient_sort(int middle);
    void recipient_search(int middle);
    void quit(int middle);

    struct {
        int height, width, middle;
    } size1;
};

#endif // INTERFACE_H

