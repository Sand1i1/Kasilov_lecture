#include <iostream>
#include <string>

template <class T>
struct BiList {
    T val;
    BiList<T>* next;
    BiList<T>* prev;

    
    BiList(const T& value) : val(value), next(nullptr), prev(nullptr) {}
};


template <class T>
class DoublyLinkedList {
private:
    BiList<T>* pseudoNode;

public:
    DoublyLinkedList() {
        pseudoNode = new BiList<T>(T());
        pseudoNode->next = pseudoNode;
        pseudoNode->prev = pseudoNode;
    }

    ~DoublyLinkedList() {
        clear();
        delete pseudoNode;
    }

    
    void pushBack(const T& value) {
        BiList<T>* newNode = new BiList<T>(value);

        newNode->prev = pseudoNode->prev;
        newNode->next = pseudoNode;

        pseudoNode->prev->next = newNode;
        pseudoNode->prev = newNode;
    }

    void clear() {
        BiList<T>* current = pseudoNode->next;
        while (current != pseudoNode) {
            BiList<T>* nextNode = current->next;
            delete current;
            current = nextNode;
        }

        pseudoNode->next = pseudoNode;
        pseudoNode->prev = pseudoNode;
    }

    void print() const {
        std::cout << "List: ";
        BiList<T>* current = pseudoNode->next;
        while (current != pseudoNode) {
            std::cout << current->val << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }
};

template <class T>
DoublyLinkedList<T> arrayToList(const T* array, size_t size) {
    DoublyLinkedList<T> list;
    for (size_t i = 0; i < size; i++) {
        list.pushBack(array[i]);
    }
    return list;
}

int main() {
    std::cout << "=== Task 4: Array to List Conversion ===\n\n";

    int arr[] = { 10, 20, 30, 40, 50 };
    size_t arrSize = sizeof(arr) / sizeof(arr[0]);

    std::cout << "Original array: ";
    for (size_t i = 0; i < arrSize; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    DoublyLinkedList<int> intList = arrayToList(arr, arrSize);
    std::cout << "Converted list: ";
    intList.print();

    std::cout << "\nString list example:\n";
    DoublyLinkedList<std::string> strList;
    strList.pushBack("Hello");
    strList.pushBack("World");
    strList.pushBack("C++");
    strList.print();

    std::cout << "\n=== Program completed. Memory freed. ===\n";

    return 0;
}