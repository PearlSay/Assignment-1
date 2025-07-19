#include <iostream>
#include <stdexcept>
#include <vector>
#include <sstream>
#include <limits>

class Stack {
private:
    static const int MAX_SIZE = 100;
    int data[MAX_SIZE];
    int top;
    int currentSize;

public:
    Stack() : top(-1), currentSize(0) {}

    void push(int value) {
        if (isFull()) {
            throw std::overflow_error("Error: Stack is full (100 elements max)!");
        }
        data[++top] = value;
        currentSize++;
    }

    void pushMultiple(const std::vector<int>& values) {
        if (currentSize + values.size() > MAX_SIZE) {
            throw std::overflow_error("Error: Cannot add all elements - would exceed 100 element limit!");
        }
        
        for (int value : values) {
            push(value);
        }
    }

    int pop() {
        if (isEmpty()) {
            throw std::underflow_error("Error: Stack is empty - nothing to pop!");
        }
        currentSize--;
        return data[top--];
    }

    int peek() const {
        if (isEmpty()) {
            throw std::underflow_error("Error: Stack is empty - nothing to peek!");
        }
        return data[top];
    }

    bool isEmpty() const { return top == -1; }
    bool isFull() const { return currentSize >= MAX_SIZE; }
    int size() const { return currentSize; }

    void display() const {
        if (isEmpty()) {
            std::cout << "Current Stack: [Empty]" << std::endl;
            return;
        }
        std::cout << "Current Stack (" << currentSize << "/100 elements):\nTop -> ";
        for (int i = top; i >= 0; i--) {
            std::cout << data[i];
            if (i > 0) std::cout << ", ";
        }
        std::cout << " <- Bottom" << std::endl;
    }

    int search(int value) const {
        for (int i = top; i >= 0; i--) {
            if (data[i] == value) {
                return top - i + 1;
            }
        }
        return -1;
    }
};

std::vector<int> getInputNumbers() {
    std::string input;
    std::cout << "Enter numbers separated by spaces: ";
    std::getline(std::cin, input);

    std::vector<int> numbers;
    std::istringstream iss(input);
    int num;
    while (iss >> num) {
        numbers.push_back(num);
    }
    return numbers;
}

void handlePushMultiple(Stack& stack) {
    try {
        auto numbers = getInputNumbers();
        stack.pushMultiple(numbers);
        std::cout << "Successfully pushed " << numbers.size() << " elements." << std::endl;
        std::cout << "Stack now has " << stack.size() << "/100 elements." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        std::cerr << "Only pushed " << (100 - stack.size()) << " elements." << std::endl;
    }
}

void handleSearch(Stack& stack) {
    std::cout << "Enter value to search: ";
    int value;
    std::cin >> value;
    int pos = stack.search(value);
    if (pos != -1) {
        std::cout << "Value " << value << " found at position " << pos << " from top." << std::endl;
    } else {
        std::cout << "Value " << value << " not found in stack." << std::endl;
    }
}

void showMenu(const Stack& stack) {
    std::cout << "\n=== STACK CONTROL PANEL ===\n";
    std::cout << "1. Push multiple elements\n";
    std::cout << "2. Pop element\n";
    std::cout << "3. Peek top element\n";
    std::cout << "4. View stack contents\n";
    std::cout << "5. Search stack\n";
    std::cout << "6. Exit\n";
    std::cout << "Current stack size: " << stack.size() << "/100\n";
    std::cout << "Enter choice: ";
}

int main() {
    Stack stack;
    int choice;

    while (true) {
        showMenu(stack);
        std::cin >> choice;
        std::cin.ignore(); // Clear newline character
        
        try {
            switch (choice) {
                case 1:
                    handlePushMultiple(stack);
                    break;
                case 2:
                    std::cout << "Popped: " << stack.pop() << std::endl;
                    break;
                case 3:
                    std::cout << "Top element: " << stack.peek() << std::endl;
                    break;
                case 4:
                    stack.display();
                    break;
                case 5:
                    handleSearch(stack);
                    break;
                case 6:
                    std::cout << "Exiting program..." << std::endl;
                    return 0;
                default:
                    std::cout << "Invalid choice! Please try again." << std::endl;
            }
        } catch (const std::exception& e) {
            std::cerr << "Operation failed: " << e.what() << std::endl;
        }
    }
}
