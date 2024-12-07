#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <algorithm>


// Класс, представляющий объект
class Object {
private:
    int id;
    std::string name;

public:
    // Конструктор
    Object(int id, const std::string& name) : id(id), name(name) {}

    // Методы доступа
    int getId() const { return id; }
    std::string getName() const { return name; }

    // Метод для обновления имени объекта
    void setName(const std::string& newName) { name = newName; }

    // Метод для отображения информации об объекте
    void display() const {
        std::cout << "ID: " << id << ", Name: " << name << std::endl;
    }
};

// Менеджер объектов
class ObjectManager {
private:
    std::vector<std::unique_ptr<Object>> objects;

public:
    // Метод для добавления нового объекта
    void addObject(int id, const std::string& name) {
        objects.push_back(std::make_unique<Object>(id, name));
    }

    // Метод для удаления объекта по ID
    void removeObject(int id) {
    auto it = std::remove_if(objects.begin(), objects.end(),
        [id](const std::unique_ptr<Object>& obj) {
            return obj->getId() == id;
        });

    if (it != objects.end()) {
        objects.erase(it, objects.end()); // Удаляем элементы, соответствующие условию
        std::cout << "Object with ID " << id << " has been removed.\n";
    } else {
        std::cout << "Object with ID " << id << " not found.\n";
    }
}

    // Метод для обновления имени объекта по ID
    void updateObject(int id, const std::string& newName) {
        for (const auto& obj : objects) {
            if (obj->getId() == id) {
                obj->setName(newName);
                std::cout << "Object with ID " << id << " has been updated.\n";
                return;
            }
        }
        std::cout << "Object with ID " << id << " not found.\n";
    }

    // Метод для отображения всех объектов
    void displayObjects() const {
        if (objects.empty()) {
            std::cout << "No objects to display.\n";
            return;
        }
        std::cout << "Current objects:\n";
        for (const auto& obj : objects) {
            obj->display();
        }
    }
};

int main() {
    ObjectManager manager;

    // Демонстрация добавления объектов
    manager.addObject(1, "First Object");
    manager.addObject(2, "Second Object");

    // Отображение текущих объектов
    manager.displayObjects();

    // Обновление объекта
    manager.updateObject(1, "Updated First Object");

    // Удаление объекта
    manager.removeObject(2);

    // Отображение объектов после обновления и удаления
    manager.displayObjects();

    return 0;
}
