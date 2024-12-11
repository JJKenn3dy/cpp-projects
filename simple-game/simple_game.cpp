#include <iostream>
#include <windows.h>
#include <ctime>

using namespace std;

const int MAX_HEALTH = 100;
const int MAX_ENERGY = 10;
const int HEAL_COST = 50;
const int ENERGY_COST = 50;
const int MIN_DAMAGE = 10;
const int MAX_DAMAGE = 30;
const int MIN_COIN_REWARD = 100;
const int MAX_COIN_REWARD = 300;
const int WIN_COIN = 1000;

void SetColor(int text, int bg) {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, (WORD)((bg << 4) | text));
}

void DisplayStats(int zdorov, int energ, int coin) {
    system("cls");
    cout << "Ваши характеристики:" << endl;
    cout << "_____________________" << endl;
    cout << "Здоровье: " << zdorov << endl;
    cout << "Энергия: " << energ << endl;
    cout << "Монеты: " << coin << endl;
    cout << "_____________________" << endl;
}

void DisplayMenu() {
    cout << "Меню:" << endl;
    cout << "1. В бой!" << endl;
    cout << "2. Купить лекарства." << endl;
    cout << "3. Купить энергетик." << endl;
    cout << "4. Выход" << endl;
    cout << "Выберите пункт: ";
}

void Fight(int& zdorov, int& coin, int& energ, int& totalwars, int boyev) {
    for (int i = 0; i < boyev; i++) {
        int damage = rand() % (MAX_DAMAGE - MIN_DAMAGE + 1) + MIN_DAMAGE;
        zdorov -= damage;

        int coin_rnd = rand() % (MAX_COIN_REWARD - MIN_COIN_REWARD + 1) + MIN_COIN_REWARD;
        coin += coin_rnd;
        totalwars++;
    }

    energ--;

    cout << "Бои завершены! Ваши новые характеристики:" << endl;
    cout << "Здоровье: " << zdorov << endl;
    cout << "Энергия: " << energ << endl;
    cout << "Монеты: " << coin << endl;

    if (coin >= WIN_COIN) {
        cout << "Поздравляем! Вы победили! У вас " << coin << " монет." << endl;
        cout << "Всего боёв: " << totalwars << endl;
        exit(0);
    }

    cin.get();
    cin.get();
}

void BuyMedicine(int& zdorov, int& coin) {
    if (coin < HEAL_COST) {
        cout << "Недостаточно монет!" << endl;
    }
    else {
        zdorov = min(zdorov + 20, MAX_HEALTH);
        coin -= HEAL_COST;
        cout << "Вы купили лекарства. Здоровье: " << zdorov << endl;
    }
    cin.get();
    cin.get();
}

void BuyEnergyDrink(int& energ, int& coin) {
    if (coin < ENERGY_COST) {
        cout << "Недостаточно монет!" << endl;
    }
    else {
        energ = min(energ + 1, MAX_ENERGY);
        coin -= ENERGY_COST;
        cout << "Вы купили энергетик. Энергия: " << energ << endl;
    }
    cin.get();
    cin.get();
}

int main() {
    srand(static_cast<unsigned int>(time(0)));
    setlocale(LC_ALL, "rus");

    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, FOREGROUND_RED);

    cout << "~ Я хз как назвать эту игру ~" << endl;
    Sleep(2000);

    int zdorov = MAX_HEALTH;
    int energ = 5;
    int coin = 0;
    int totalwars = 0;

    while (true) {
        if (zdorov <= 0 || energ <= 0) {
            cout << "\nВы проиграли! Нажмите Enter, чтобы выйти." << endl;
            cin.get();
            return 0;
        }

        DisplayStats(zdorov, energ, coin);
        DisplayMenu();

        int menu;
        cin >> menu;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Некорректный ввод! Попробуйте снова." << endl;
            Sleep(1000);
            continue;
        }

        switch (menu) {
        case 1: {
            cout << "Сколько вы хотите провести боёв? ";
            int boyev;
            cin >> boyev;

            if (cin.fail() || boyev <= 0) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Некорректное количество боёв! Минимум - 1." << endl;
                Sleep(1000);
                break;
            }

            Fight(zdorov, coin, energ, totalwars, boyev);
            break;
        }
        case 2:
            BuyMedicine(zdorov, coin);
            break;
        case 3:
            BuyEnergyDrink(energ, coin);
            break;
        case 4:
            cout << "Выход из игры. Спасибо за игру!" << endl;
            return 0;
        default:
            cout << "Некорректный выбор! Попробуйте снова." << endl;
            Sleep(1000);
            break;
        }
    }

    return 0;
}