#include <iostream>
#include <cassert>
#include <initializer_list>

template <typename T, int size>
class Array {
private:
    T a[size];

public:
    // Конструктор по умолчанию
    Array() {
        for (int i = 0; i < size; ++i) {
            a[i] = T(); // Инициализация значениями по умолчанию
        }
    }

    // Конструктор с initializer_list
    Array(std::initializer_list<T> list) {
        assert(list.size() <= size && "Initializer list exceeds array size");
        int i = 0;
        for (const T& element : list) {
            a[i++] = element;
        }
    }

    // Оператор доступа к элементу []
    T& operator[](int index) {
        assert(index >= 0 && index < size && "Index out of bounds");
        return a[index];
    }

    // Получить размер массива
    int getSize() const {
        return size;
    }

    // Метод для обмена содержимого двух массивов
    void swap(Array& other) {
        for (int i = 0; i < size; ++i) {
            std::swap(a[i], other.a[i]);
        }
    }

    // Вывод содержимого массива
    void print() const {
        for (int i = 0; i < size; ++i) {
            std::cout << a[i] << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    Array<int, 5> arr1 = {1, 2, 3, 4, 5};
    Array<int, 5> arr2;

    std::cout << "Массив 1: ";
    arr1.print();

    std::cout << "Массив 2 до обмена: ";
    arr2.print();

    arr1.swap(arr2);

    std::cout << "Массив 2 после обмена: ";
    arr2.print();

    return 0;
}
