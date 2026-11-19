#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <windows.h>

using namespace std;

class Base {
protected:
    int id;

public:
    Base(int id) : id(id) {}
    virtual ~Base() {}

    virtual void describe() const {
        cout << "  Объект Base #" << id << " — базовый тип" << endl;
    }

    virtual string getType() const {
        return "Base";
    }

    int getId() const {
        return id;
    }
};

class Derived : public Base {
public:
    Derived(int id) : Base(id) {}

    void describe() const override {
        cout << "  Объект Derived #" << id << " — производный тип (расширенный)" << endl;
    }

    string getType() const override {
        return "Derived";
    }
};

void add(const Base& obj, vector<Base*>& storage) {
    Base* copy = nullptr;
    if (obj.getType() == "Base") {
        copy = new Base(obj);
    }
    else {
        copy = new Derived(dynamic_cast<const Derived&>(obj));
    }
    storage.push_back(copy);
    cout << "  [add] Добавлен объект типа " << obj.getType()
        << " с id=" << obj.getId() << endl;
}

int main() {
    SetConsoleOutputCP(1251);
    srand(time(nullptr));

    vector<Base*> storage;
    const int count = 10;

    cout << "=== Этап 1: Случайное создание объектов ===" << endl;
    for (int i = 1; i <= count; i++) {
        int randomNum = rand();

        Base* obj = nullptr;
        if (randomNum % 2 == 0) {
            obj = new Base(i);
            cout << "Случайное число " << randomNum << " (чётное) -> Base #" << i << endl;
        }
        else {
            obj = new Derived(i);
            cout << "Случайное число " << randomNum << " (нечётное) -> Derived #" << i << endl;
        }

        add(*obj, storage);

        delete obj;
    }

    cout << "\n=== Этап 2: Поведение объектов из хранилища ===" << endl;
    for (size_t i = 0; i < storage.size(); i++) {
        cout << "Объект " << i + 1 << ":";
        storage[i]->describe();
    }

    cout << "\n=== Этап 3: Освобождение ресурсов ===" << endl;
    for (Base* ptr : storage) {
        delete ptr;
    }
    storage.clear();
    cout << "Все ресурсы освобождены." << endl;

    return 0;
}