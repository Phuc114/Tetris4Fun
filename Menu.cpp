#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

class Menu {
public:
    Menu(string items[], int numItems);
    void drawFrame(int x, int y, string menuItem);
    void gotoXY(int x, int y);
    void run();
    
    int getTemp() { return temp; }
        
private:
    string* menuItems;
    int numItems;
    
    int temp;
};

Menu::Menu(string items[], int numItems) {
    this->menuItems = items;
    this->numItems = numItems;
    this->temp = -1;
}

void Menu::gotoXY(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Menu::drawFrame(int x, int y, string menuItem) {
    gotoXY(x, y);
    cout << "+";
    for (int i = 0; i < menuItem.length() + 2; i++) {
        cout << "-";
    }
    cout << "+";

    gotoXY(x, y + 1);
    cout << "| " << menuItem << " |";

    gotoXY(x, y + 2);
    cout << "+";
    for (int i = 0; i < menuItem.length() + 2; i++) {
        cout << "-";
    }
    cout << "+";
}

void Menu::run() {
    int selectedItem = 0;
    bool isExit = false;

    while (!isExit) {
        system("cls");
        for (int i = 0; i < numItems; i++) {
            if (i == selectedItem) {
                drawFrame(0, i * 3, menuItems[i]);
            } else {
                gotoXY(2, i * 3 + 1);
                cout << menuItems[i];
            }
        }

        char key = _getch();
        if (key == 72) { // Up arrow key
            selectedItem--;
            if (selectedItem < 0) {
                selectedItem = numItems - 1;
            }
        } else if (key == 80) { // Down arrow key
            selectedItem++;
            if (selectedItem >= numItems) {
                selectedItem = 0;
            }
        } else if (key == '\r') { // Enter key
            temp = selectedItem;
            switch (temp) {
                case 0: // PLAY
                    // func to play
                    break;
                case 1: // HOW TO PLAY
                    do {
                        system("cls");
                        cout << "Nhan phim S de tha tetromino nhanh hon." << endl;
                        cout << "Nhan phim A de di chuyen sang trai." << endl;
                        cout << "Nhan phim D de di chuyen sang trai." << endl;
                        cout << "Nhan phim E de quay tetromino theo chieu kim dong ho." << endl;
                        cout << "Nhan phim R de quay tetromino theo chieu kim dong ho." << endl << endl; 
                    } while (!_kbhit());
                    break;
                case 2: // CREDITS
                    do {
                        system("cls");
                        cout << "1. Cao Pham Hoang Thai - 22127382" << endl;
                        cout << "2. Bui Le Khoi - 22127205" << endl;
                        cout << "3. Nguyen Gia Phuc - 22127331" << endl;
                        cout << "4. Bui Cong Mau - 22127260" << endl << endl;
                    } while (!_kbhit());
                    break;
                case 3: // EXIT
                    isExit = true;
                    break;
            }
        }
    }
}


int main() {
    string menuItems[] = {"PLAY", "HOW TO PLAY", "CREDITS", "EXIT"};
    int numItems = sizeof(menuItems) / sizeof(string);

    Menu menu(menuItems, numItems);
    menu.run();

    return 0;
}

