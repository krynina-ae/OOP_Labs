#include <iostream>
#include <string>
#include <stdexcept>
#include <windows.h>

using namespace std;

//Вариант 5
class ProgramError {
public:
    virtual void show() const = 0;
    virtual ~ProgramError() {}
};

class InvalidPointerError : public ProgramError {
public:
    void show() const override { cout << "  [Ошибка] Ошибочный указатель!" << endl; }
};

class ListOperationError : public ProgramError {
public:
    void show() const override { cout << "  [Ошибка] Ошибка работы со списком!" << endl; }
};

class InvalidIndexError : public ProgramError {
public:
    void show() const override { cout << "  [Ошибка] Недопустимый индекс!" << endl; }
};

class ListOverflowError : public ProgramError {
public:
    void show() const override { cout << "  [Ошибка] Список переполнен!" << endl; }
};

template <typename T>
class Storage {
private:
    T** data;
    int capacity;
    int count;

public:
    Storage(int cap) : capacity(cap), count(0) {
        data = new T * [capacity]; //память под массив указателей
    }

    ~Storage() {
        delete[] data; // освобождаем массив указателей
    }

    void add(T* obj) {
        if (count >= capacity) {
            // доп задание (вариант 3)
            throw overflow_error("Список переполнен! Превышена максимальная вместимость.");
        }
        data[count++] = obj;
    }

    T* operator[](int index) {
        if (index < 0 || index >= count) {
            throw InvalidIndexError();
        }
        return data[index];
    }

    int getCount() const { return count; }
};

int main() {
    SetConsoleOutputCP(1251);

    cout << "=== Демонстрация работы с иерархией ошибок ===" << endl;
    Storage<ProgramError> errStorage(2);

    try {
        errStorage.add(new InvalidPointerError());
        errStorage.add(new ListOperationError());
        cout << "Успешно добавлено 2 ошибки." << endl;

        cout << "Попытка добавить 3-й элемент..." << endl;
        errStorage.add(new ListOverflowError());
    }
    catch (const overflow_error& e) {
        cout << "\n[Перехвачено std::exception]: " << e.what() << endl;
    }

    cout << "\nВывод содержимого хранилища ошибок:" << endl;
    for (int i = 0; i < errStorage.getCount(); i++) {
        errStorage[i]->show();
    }

    cout << "\nПопытка обращения по индексу 5:" << endl;
    try {
        errStorage[5]->show();
    }
    catch (const InvalidIndexError& e) {
        e.show();
    }

    cout << "\n=== Демонстрация работы с другим типом (string) ===" << endl;
    Storage<string> strStorage(3);
    strStorage.add(new string("Первая строка"));
    strStorage.add(new string("Вторая строка"));

    for (int i = 0; i < strStorage.getCount(); i++) {
        cout << "  Элемент " << i << ": " << *strStorage[i] << endl;
    }

    cout << "\nОсвобождение памяти..." << endl;
    for (int i = 0; i < errStorage.getCount(); i++) {
        delete errStorage[i];
    }
    for (int i = 0; i < strStorage.getCount(); i++) {
        delete strStorage[i];
    }

    cout << "Программа завершена." << endl;
    return 0;
}