#include <iostream>
#include <string>
#include <windows.h>
using namespace std;

class Book {
public:
    string author;   
    string title;    
    int type;        
 
    Book(string author, string title, int type) {
        if (author.empty() || title.empty()) {
            cout << "Ошибка: книга не может быть без автора или названия!" << endl;
            this->author = "Неизвестный";
            this->title = "Без названия";
        }
        else {
            this->author = author;
            this->title = title;
        }
        this->type = type;
    }
};

void countBooksSwitch(Book* library, int size) {
    int fictionCount = 0;    
    int technicalCount = 0; 

    for (int i = 0; i < size; i++) {
        switch (library[i].type) {
        case 1:
            fictionCount++;
            break;
        case 2:
            technicalCount++;
            break;
        default:
            cout << "Неизвестный тип книги: " << library[i].title << endl;
            break;
        }
    }

    cout << "\n=== Подсчёт через switch ===" << endl;
    cout << "Художественных книг: " << fictionCount << endl;
    cout << "Технических книг: " << technicalCount << endl;
}

void countBooksNoSwitch(Book* library, int size) {
    int fictionCount = 0;
    int technicalCount = 0;

    for (int i = 0; i < size; i++) {
        if (library[i].type == 1) {
            fictionCount++;
        }
        else if (library[i].type == 2) {
            technicalCount++;
        }
    }

    cout << "\n=== Подсчёт через if ===" << endl;
    cout << "Художественных книг: " << fictionCount << endl;
    cout << "Технических книг: " << technicalCount << endl;
}

int main() {
    SetConsoleOutputCP(1251);

    const int librarySize = 5;
    Book* library = new Book[librarySize]{
        Book("Пушкин", "Евгений Онегин", 1),      
        Book("Толстой", "Война и мир", 1),        
        Book("Кнут", "Искусство программирования", 2), 
        Book("Страуструп", "C++ для чайников", 2),  
        Book("Достоевский", "Преступление и наказание", 1) 
    };

    cout << "=== Библиотека ===" << endl;
    for (int i = 0; i < librarySize; i++) {
        cout << i + 1 << ". " << library[i].author << " - \""
            << library[i].title << "\" (тип: "
            << (library[i].type == 1 ? "художественная" : "техническая")
            << ")" << endl;
    }

    countBooksSwitch(library, librarySize);
    countBooksNoSwitch(library, librarySize);

    delete[] library;
    library = nullptr;

    return 0;
}