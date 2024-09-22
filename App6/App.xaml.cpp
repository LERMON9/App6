#include <iostream>  
#include <windows.h> 
#include <string>  
// aftours: LeRMoN, Kolia, XeSh, FlesH. school Shag, code: house worken. my tg:https://t.me/LERMONfupa <- click Ctrl+right mouse, im check sms.Надеюсь правильно написал.     \\ 
using namespace std;
// Кодом вдохновился из урочка 
enum KeyCodes { ENTER = 13, ESCAPE = 27, LEFT = 75, RIGHT = 77, UP = 72, DOWN = 80, SPACEBAR = 32 };// кнопочки= ентер, ескейп, стрелочки : левая правая верх низ. И пробел 
enum Colors { DARKGREEN = 2, RED = 12, YELLOW = 14, BLUE = 9 };// цвета= чорно зеленый, краснинький, жолтенький, сининький.
enum Objects { HALL, WALL, COIN, ENEMY }; // обьёкты= коридорчик, стеночка, монеточка, человек.

const int width = 50;
const int height = 15;

int main() {
    int coins = 0;
    system("title Бомбер!");
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;

    info.bVisible = false;
    info.dwSize = 100;
    SetConsoleCursorInfo(h, &info);

    int location[height][width] = {};
    const string hallSymbol = " "; // коридор  
    const string wallSymbol = "#"; // стенка 
    const string coinSymbol = "0"; // монеткыа
    const string enemySymbol = "+"; // человечек 

    srand(static_cast<unsigned int>(time(NULL)));

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            location[y][x] = rand() % 4;

            if (x == 0 || y == 0 || x == width - 1 || y == height - 1) {
                location[y][x] = WALL;
            }
            if ((x == 0 && y == 2) || (x == width - 1 && y == height - 3)) {
                location[y][x] = HALL;
            }
            if (location[y][x] == ENEMY) {
                int prob = rand() % 10;
                if (prob != 0) {
                    location[y][x] = HALL;
                }
            }
        }
    }

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            switch (location[y][x]) {
            case HALL:
                cout << hallSymbol;
                break;
            case WALL:
                SetConsoleTextAttribute(h, DARKGREEN);
                cout << wallSymbol;
                break;
            case COIN:
                SetConsoleTextAttribute(h, YELLOW);
                cout << coinSymbol;
                break;
            case ENEMY:
                SetConsoleTextAttribute(h, RED);
                cout << enemySymbol;
                break;
            }
        }
        cout << "\n";
    }

    COORD position;
    position.X = 1;
    position.Y = 2;
    SetConsoleCursorPosition(h, position);
    SetConsoleTextAttribute(h, BLUE);
    cout << enemySymbol;

    // Игровой цикл  
    while (true) {
        int code = _getch();
        if (code == 224) {
            code = _getch();
        }

        SetConsoleCursorPosition(h, position);
        cout << hallSymbol;

        switch (code) {
        case ENTER:
            break;
        case SPACEBAR:
            break;
        case ESCAPE:
            return 0;
        case RIGHT:
            if (location[position.Y][position.X + 1] != WALL) {
                position.X++;
            }
            break;
        case LEFT:
            if (position.X > 0 && location[position.Y][position.X - 1] != WALL) {
                position.X--;
            }
            break;
        case UP:
            if (position.Y > 0 && location[position.Y - 1][position.X] != WALL) {
                position.Y--;
            }
            break;
        case DOWN:
            if (position.Y < height - 1 && location[position.Y + 1][position.X] != WALL) {
                position.Y++;
            }
            break;
        default:
            cout << code << "\n";
            break;
        }

        SetConsoleCursorPosition(h, position);
        SetConsoleTextAttribute(h, BLUE);
        cout << enemySymbol;

        if (location[position.Y][position.X] == COIN) {
            coins++;
            cout << coins << " монета(ы) собраны\n";
            location[position.Y][position.X] = HALL;
        }
    }
}