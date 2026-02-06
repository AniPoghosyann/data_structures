#include <iostream>
using namespace std;

/*
 * Forward declarations for custom exception classes
 */
template <class T>
class EmptyStack;

template <class T>
class OutOfBounds;

/*
 * =========================
 * Node class (doubly linked)
 * =========================
 */
template <class T>
class Node {
public:
    T value;                 // Stored value
    Node<T>* prev = nullptr; // Previous node
    Node<T>* next = nullptr; // Next node

    Node(T value) {
        this->value = value;
    }
};

/*
 * =========================
 * Stack class (templated)
 * Implemented using doubly linked list
 * =========================
 */
template <class T>
class Stack {
private:
    Node<T>* head = nullptr; // Bottom of stack
    Node<T>* tail = nullptr; // Top of stack
    int count = 0;           // Number of elements

public:
    /*
     * Push element onto stack
     */
    void push(T value) {
        Node<T>* temp = new Node<T>(value);

        if (head == nullptr) {
            head = temp;
            tail = temp;
        } else {
            temp->prev = tail;
            tail->next = temp;
            tail = temp;
        }
        count++;
    }

    /*
     * Pop element from stack
     * Throws EmptyStack exception if stack is empty
     */
    T pop() {
        if (tail == nullptr) {
            EmptyStack<T> error(
                "Attempted to pop from empty stack",
                "Stop pop operation or push elements before popping"
            );
            throw error;
        } 
        else if (tail == head) {
            T value = tail->value;
            delete tail;
            tail = nullptr;
            head = nullptr;
            return value;
        } 
        else {
            T value = tail->value;
            tail = tail->prev;
            delete tail->next;
            tail->next = nullptr;
            return value;
        }
        count--;
    }

    /*
     * Print stack contents
     */
    void print() {
        for (Node<T>* current = head; current != nullptr; current = current->next) {
            cout << "value: " << current->value << endl;
        }
    }

    /*
     * Destructor
     */
    ~Stack() {
        while (head != nullptr) {
            Node<T>* nextNode = head->next;
            delete head;
            head = nextNode;
        }
    }

    Stack() {}

    /*
     * Copy constructor
     */
    Stack(Stack& other) {
        for (Node<T>* current = other.head; current != nullptr; current = current->next) {
            push(current->value);
        }
    }

    /*
     * Assignment operator
     */
    Stack& operator=(const Stack& other) {
        if (head == nullptr) {
            for (Node<T>* current = other.head; current != nullptr; current = current->next) {
                push(current->value);
            }
        } else {
            for (Node<T>* current = head; current != nullptr; current = current->next) {
                delete current;
            }
            for (Node<T>* current = other.head; current != nullptr; current = current->next) {
                push(current->value);
            }
        }
        return *this;
    }

    /*
     * Output stream operator
     */
    friend ostream& operator<<(ostream& out, Stack& stack) {
        out << "----- Stack contents -----" << endl;
        for (Node<T>* current = stack.head; current != nullptr; current = current->next) {
            out << "Value: " << current->value << endl;
        }
        return out;
    }

    /*
     * Input stream operator
     */
    friend istream& operator>>(istream& in, Stack& stack) {
        bool running = true;
        T value;

        while (running) {
            cout << "value:" << endl;
            in >> value;
            stack.push(value);

            bool ask = true;
            while (ask) {
                cout << "do you want to continue? 1. yes 0. no" << endl;
                int choice;
                in >> choice;

                if (choice == 1) {
                    ask = false;
                } else if (choice == 0) {
                    running = false;
                    ask = false;
                } else {
                    cout << "wrong number, try again" << endl;
                }
            }
        }
        return in;
    }

    /*
     * Prefix increment
     */
    Stack<T>& operator++() {
        for (Node<T>* current = head; current != nullptr; current = current->next) {
            current->value += 1;
        }
        return *this;
    }

    /*
     * Postfix increment
     */
    Stack<T> operator++(int) {
        Stack<T> temp = *this;
        for (Node<T>* current = head; current != nullptr; current = current->next) {
            current->value += 1;
        }
        return temp;
    }

    /*
     * Prefix decrement
     */
    Stack<T>& operator--() {
        for (Node<T>* current = head; current != nullptr; current = current->next) {
            current->value -= 1;
        }
        return *this;
    }

    /*
     * Postfix decrement
     */
    Stack<T> operator--(int) {
        Stack<T> temp = *this;
        for (Node<T>* current = head; current != nullptr; current = current->next) {
            current->value -= 1;
        }
        return temp;
    }

    /*
     * Index operator
     * Throws OutOfBounds exception
     */
    T operator[](int index) {
        if (index < 0 || index >= count) {
            OutOfBounds<T> error(index, count - 1, 0);
            throw error;
        }

        Node<T>* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->value;
    }

    int getCount() {
        return count;
    }
};

/*
 * =========================
 * EmptyStack Exception
 * =========================
 */
template <class T>
class EmptyStack {
public:
    string reason;
    string solution;

    EmptyStack(string reason, string solution) {
        this->reason = reason;
        this->solution = solution;
    }

    void print() {
        cout << "reason: " << reason << endl;
        cout << "solution: " << solution << endl;
    }
};

/*
 * =========================
 * OutOfBounds Exception
 * =========================
 */
template <class T>
class OutOfBounds {
public:
    int index;
    int start;
    int end;

    OutOfBounds(int index, int end, int start) {
        this->index = index;
        this->start = start;
        this->end = end;
    }

    void print() {
        cout << "your index: " << index << endl;
        cout << "start: " << start << "  end: " << end << endl;
    }
};

/*
 * =========================
 * Main function
 * =========================
 */
int main() {
    try {
        Stack<int> stack;
        stack.push(12);
        stack.push(34);
        stack.push(5);
        stack.push(45);
        stack.push(78);
        stack.pop();

        stack.print();

        cout << "stack[-1]: " << stack[-1] << endl;

        int value = stack[2];
        cout << "stack[2] = " << value << endl;

        int out = stack[7];
        cout << "stack[7] = " << out << endl;
    }
    catch (EmptyStack<int>& e) {
        e.print();
    }
    catch (OutOfBounds<int>& e) {
        e.print();
    }
    return 0;
}

