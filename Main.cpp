#include "Interface.cpp"
#include "Admin.cpp"
#include "User.cpp"

using namespace std;





int main() {
    Donor donor;
    Recipient recipient;
    Interface itf;
    Admin admin;


    itf.screen_size();
    itf.blood_symbol(itf.size1.middle);

    ofstream out;
    string temp;
    char input, input_menu, input_main_menu, input_donor, input_recipient,display_op, sort_op, search_op, display_ri, sort_ri, search_ri;
    bool check, continueLoop;

    // header
    while (true) {
        itf.header(itf.size1.middle);
        cin >> input;
        if (input == 'y' || input == 'Y') {
            system("cls");
            // goto first menu
            break;
        } else {
            system("cls");
            itf.blood_symbol(itf.size1.middle);
        }
    }



    // admin page
    bool lg = true;
    while(lg){
        system("cls");
        itf.blood_symbol(itf.size1.middle);
        itf.position_str(itf.size1.middle, "Admin Login Page");
        cout<<endl<<endl<<endl;
        lg = admin.displayLoginPrompt();
      }

    // main menu
    while (true) {
        system("cls");
        itf.main_menu(itf.size1.middle);
        cin >> input_main_menu;
        //donor page
        if (input_main_menu == '1') {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            donor.readFile();

            while (true) {
                system("cls");
                itf.menu_donor(itf.size1.middle);
                cin >> input_donor;
               // cin_check();
                if (input_donor == '1') {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    donor.add();
                    donor.saveBloodTypeCount();
                } else if (input_donor == '2') {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    donor.del();
                    donor.saveBloodTypeCount();
                } else if (input_donor == '3') {
                   continueLoop = true;
                   while(continueLoop){
                        itf.donor_show(itf.size1.middle);
                        cin>> display_op;
                    switch(display_op){

                        case '1':
                            donor.display();
                            break;
                        case '2':
                            donor.readBloodTypeCount();
                            break;
                        case '3':
                                donor.display();
                                cout<<endl;
                                cout<<endl;
                                donor.readBloodTypeCount();
                            break;
                        case '4':
                            continueLoop = false;
                            break;
                        default:
                            cout << "Invalid input. Please try again" << endl;
                    }
                    system("pause");
                   }

                } else if (input_donor == '4') {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    donor.edit();
                } else if (input_donor == '5') {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    donor.reset();
                } else if (input_donor == '6') {
                    continueLoop = true;
                    while(continueLoop){
                        itf.donor_sort(itf.size1.middle);
                        cin>> sort_op;
                        switch(sort_op){
                            case '1':
                                donor.bubbleSort_bloodType();
                                donor.display();
                                break;
                            case '2':
                                donor.quickSort_ic();
                                donor.display();
                                break;
                            case '3':
                                continueLoop = false;
                                break;
                            default:
                                cout << "Invalid input. Please try again" << endl;
                        }
                        system("pause");
                    }
                } else if (input_donor == '7') {
                    continueLoop = true;
                    while (continueLoop) {
                        itf.donor_search(itf.size1.middle);
                        cin >> search_op;
                    switch (search_op) {
                    case '1':
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        donor.linearSearch_name();
                        break;
                    case '2':
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        donor.quickSort_ic();
                        donor.binarySearch_ic();
                        break;
                    case '3':  // Assuming 3 is the option to terminate the loop
                        continueLoop = false;
                        break;
                    default:
                        cout << "Invalid input. Please try again" << endl;
                    }
                    system("pause");
                    }

                }else if (input_donor == '8') {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    donor.saveFile();
                    donor.saveBloodTypeCount();
                    system("cls");
                    break;
                } else {
                    system("cls");
                    cout << "Invalid input. Please try again" << endl;
                }
                system("pause");
            }



        //recipient page
        } else if (input_main_menu == '2') {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                donor.readFile();
                recipient.readFile();
                donor.readBloodTypeCount();

             while (true) {
                system("cls");
                itf.menu_recipient(itf.size1.middle);
                cin >> input_recipient;
               // cin_check();
                if (input_recipient == '1') {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    recipient.add();
                    string bloodType = recipient.getbloodType();
                    bool success = donor.useBloodSupply(bloodType);
                    if (!success) {
                        recipient.delblood();
                    }

                    donor.saveBloodTypeCount();
                }
                else if (input_recipient == '2') {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    recipient.del();
                    string bloodType = recipient.getbloodType();
                    donor.replenishBloodSupply(bloodType);       //replenish blood
                    donor.saveBloodTypeCount();

                } else if (input_recipient == '3') {
                   continueLoop = true;
                   while(continueLoop){
                        itf.recipient_show(itf.size1.middle);
                        cin>> display_ri;
                    switch(display_ri){

                        case '1':
                            recipient.display();
                            break;
                        case '2':
                            donor.readBloodTypeCount();
                            break;
                        case '3':
                                recipient.display();
                                cout<<endl;
                                cout<<endl;
                                donor.readBloodTypeCount();
                            break;
                        case '4':
                            continueLoop = false;
                            break;
                        default:
                            cout << "Invalid input. Please try again" << endl;
                    }
                    system("pause");
                   }

                } else if (input_recipient == '4') {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    recipient.edit();
                } else if (input_recipient == '5') {
                    continueLoop = true;
                    while(continueLoop){
                        itf.recipient_sort(itf.size1.middle);
                        cin>> sort_ri;
                        switch(sort_ri){
                            case '1':
                                recipient.bubbleSort_bloodType();
                                recipient.display();
                                break;
                            case '2':
                                recipient.quickSort_ic();
                                recipient.display();
                                break;
                            case '3':
                                continueLoop = false;
                                break;
                            default:
                                cout << "Invalid input. Please try again" << endl;
                        }
                        system("pause");
                    }
                } else if (input_recipient == '6') {
                    continueLoop = true;
                    while (continueLoop) {
                        itf.recipient_search(itf.size1.middle);
                        cin >> search_ri;
                    switch (search_ri) {
                    case '1':
                        cin.clear();
                        cin.ignore();
                        recipient.linearSearch_name();
                        break;
                    case '2':
                        cin.clear();
                        cin.ignore();
                        recipient.quickSort_ic();
                        recipient.binarySearch_ic();
                        break;
                    case '3':  // Assuming 3 is the option to terminate the loop
                        continueLoop = false;
                        break;
                    default:
                        cout << "Invalid input. Please try again" << endl;
                    }
                    system("pause");
                    }

                }else if (input_recipient == '7') {
                    cin.clear();
                    cin.ignore();
                    donor.checkBloodSupply(donor);

                }else if (input_recipient == '8') {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    recipient.saveFile();
                    donor.saveBloodTypeCount();
                    system("cls");
                    break;
                } else {
                    cout << "Invalid input. Please try again" << endl;
                }
                system("pause");
            }

        } else if (input_main_menu == '3') {
            system("cls");
            itf.quit(itf.size1.middle);
            break;
        } else {
            cout << "Invalid input. Please try again" << endl;
            system("pause");
        }
    }

    return 0;
}

