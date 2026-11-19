#include <iostream>
#include <vector>
#include <string>
#include <windows.h>

using namespace std;

// Деталь
class Detail {
protected:
    string name;    
    double weight;

    Detail(string name, double weight) : name(name), weight(weight) {}

public:
    virtual ~Detail() {}

    virtual void show() const {
        cout << "  Деталь: " << name << ", вес: " << weight << " г" << endl;
    }

    template <typename T>
    friend void createAndAdd(vector<Detail*>& storage, string name, double weight);

    double getWeight() const { return weight; }
};

// Сборка
class Assembly : public Detail {
private:
    int partCount;

    Assembly(string name, double weight, int partCount)
        : Detail(name, weight), partCount(partCount) {
    }

public:
    void show() const override {
        cout << "  Сборка: " << name << ", вес: " << weight
            << " г, деталей: " << partCount << endl;
    }

    template <typename T>
    friend void createAndAdd(vector<Detail*>& storage, string name, double weight);

    template <typename T>
    friend void createAndAdd(vector<Detail*>& storage, string name, double weight, int parts);
};

template <typename T>
void createAndAdd(vector<Detail*>& storage, string name, double weight) {
    T* obj = new T(name, weight);
    storage.push_back(obj);
}

template <typename T>
void createAndAdd(vector<Detail*>& storage, string name, double weight, int parts) {
    T* obj = new T(name, weight, parts);
    storage.push_back(obj);
}

void showAll(const vector<Detail*>& storage) {
    cout << "\n=== Содержимое хранилища ===" << endl;
    for (size_t i = 0; i < storage.size(); i++) {
        cout << i + 1 << ":";
        storage[i]->show();  // Полиморфный вызов!
    }
}

int main() {
    SetConsoleOutputCP(1251);

    vector<Detail*> storage;

    createAndAdd<Detail>(storage, "Болт М6", 5.2);
    createAndAdd<Detail>(storage, "Гайка М6", 3.1);
    createAndAdd<Detail>(storage, "Шайба", 1.5);
    createAndAdd<Assembly>(storage, "Крепёжный узел", 25.0, 10);
    createAndAdd<Assembly>(storage, "Мотор в сборе", 1500.0, 45);

    showAll(storage);

    for (Detail* ptr : storage) {
        delete ptr;
    }
    storage.clear();

    cout << "\nПамять освобождена." << endl;
    return 0;
}