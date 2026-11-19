#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

class Publication {
protected:
    string title = "";
    float price = 0.0f;

public:
    void getdata() {
        cout << "Введите название: ";
        getline(cin, title);
        cout << "Введите цену: ";
        while (!(cin >> price)) {
            cout << "  [Ошибка] Введите корректное число! Попробуйте снова: ";
            cin.clear();
            cin.ignore(256, '\n');
        }
        cin.ignore(256, '\n');
    }

    void putdata() {
        cout << "Название: " << title << endl;
        cout << "Цена: " << price << " руб." << endl;
    }
};

class Sales {
protected:
    float sales[3] = { 0.0f, 0.0f, 0.0f };

public:
    void getdata() {
        cout << "Введите продажи за последние 3 месяца:" << endl;
        for (int i = 0; i < 3; i++) {
            cout << "  Месяц " << i + 1 << ": ";
            while (!(cin >> sales[i])) {
                cout << "  [Ошибка] Введите число! Попробуйте снова для месяца " << i + 1 << ": ";
                cin.clear();
                cin.ignore(256, '\n');
            }
        }
        cin.ignore(256, '\n');
    }

    void putdata() {
        cout << "Продажи за 3 месяца:" << endl;
        float total = 0;
        for (int i = 0; i < 3; i++) {
            cout << "  Месяц " << i + 1 << ": " << sales[i] << " руб." << endl;
            total += sales[i];
        }
        cout << "  Итого: " << total << " руб." << endl;
    }
};

class Book : public Publication, public Sales {
private:
    int pages = 0;

public:
    void getdata() {
        cout << "\n=== Ввод данных о КНИГЕ ===" << endl;
        Publication::getdata();
        cout << "Введите количество страниц: ";
        while (!(cin >> pages)) {
            cout << "  [Ошибка] Введите целое число! Попробуйте снова: ";
            cin.clear();
            cin.ignore(256, '\n');
        }
        cin.ignore(256, '\n');
        Sales::getdata();
    }

    void putdata() {
        cout << "\n=== Информация о КНИГЕ ===" << endl;
        Publication::putdata();
        cout << "Количество страниц: " << pages << endl;
        Sales::putdata();
    }
};

class Tape : public Publication, public Sales {
private:
    float minutes = 0.0f;

public:
    void getdata() {
        cout << "\n=== Ввод данных об АУДИОЗАПИСИ ===" << endl;
        Publication::getdata();
        cout << "Время записи (в минутах): ";
        while (!(cin >> minutes)) {
            cout << "  [Ошибка] Введите число! Попробуйте снова: ";
            cin.clear();
            cin.ignore(256, '\n');
        }
        cin.ignore(256, '\n');
        Sales::getdata();
    }

    void putdata() {
        cout << "\n=== Информация об АУДИОЗАПИСИ ===" << endl;
        Publication::putdata();
        cout << "Время записи: " << minutes << " мин." << endl;
        Sales::putdata();
    }
};

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Book book;
    book.getdata();

    Tape tape;
    tape.getdata();

    cout << "\n\n";
    book.putdata();
    tape.putdata();

    return 0;
}