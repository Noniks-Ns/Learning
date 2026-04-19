#include <iostream>
#include <memory>

// ---------------- UNIQUE_PTR ----------------
// Smart pointer with unique ownership.
// One owner. Cannot be copied, can only transfer ownership (move).
// Automatically frees memory when going out of scope.

void uniquePtrDemo() {
    std::cout << "n--- unique_ptr ---n";

    // Create a unique_ptr using make_unique
    auto p = std::make_unique<int>(10);
    std::cout << "unique_ptr value: " << *p << 'n';
    std::cout << "Address: " << p.get() << 'n';

    // Pass by reference (ownership is NOT transferred)
    auto printPtr = [](const std::unique_ptr<int>& ptr) {
        std::cout << "Value via const ref: " << *ptr << 'n';
    };
    printPtr(p); // p still owns the object

    // Transfer ownership (move) — p becomes empty
    auto p2 = std::move(p);
    if (p == nullptr) {
        std::cout << "p is now null after moven";
    }
    std::cout << "p2 value: " << *p2 << 'n';
}

// ---------------- SHARED_PTR ----------------
// Pointer with shared ownership.
// Reference count: the object is deleted when the count becomes 0.
// Used when multiple owners need to share a single object.

void sharedPtrDemo() {
    std::cout << "n--- shared_ptr ---n";

    // Create shared_ptr
    auto p1 = std::make_shared<int>(5);
    std::cout << "Use count: " << p1.use_count() << 'n'; // 1

    // Copy — ownership is shared
    auto p2 = p1;
    auto p3 = p1;
    std::cout << "Use count after 3 copies: " << p1.use_count() << 'n'; // 3

    // Delete one copy
    p3.reset();
    std::cout << "Use count after p3.reset(): " << p1.use_count() << 'n'; // 2

    // Delete another one
    p2.reset();
    std::cout << "Use count after p2.reset(): " << p1.use_count() << 'n'; // 1

    // p1 goes out of scope → object is deleted
}

// ---------------- WEAK_PTR ----------------
// Non-owning pointer, referring to a shared_ptr.
// Allows avoiding cyclic references.
// Needs to be "locked" via lock() to get a temporary shared_ptr.

class Node {
public:
    int data;
    std::shared_ptr<Node> next; // Owns the next node
    std::weak_ptr<Node> prev; // Does not own the previous one — avoids cycle

    Node(int v) : data(v) {
        std::cout << "Node created: " << data << 'n';
    }

    ~Node() {
        std::cout << "Node destroyed: " << data << 'n';
    }
};

void weakPtrDemo() {
    std::cout << "n--- weak_ptr ---n";

    auto n1 = std::make_shared<Node>(10);
    auto n2 = std::make_shared<Node>(20);

    n1->next = n2; // n1 owns n2 via next
    n2->prev = n1; // n2 refers to n1 via weak_ptr — no cycle

    std::weak_ptr<Node> w = n2->prev; // weak reference to n1

    // Check if the object is alive
    if (auto locked = w.lock()) {
        std::cout << "Weak ptr is valid. Data: " << locked->data << 'n';
    }
    else {
        std::cout << "Object expiredn";
    }

    n1.reset(); // deleting n1
    std::cout << "n1 destroyed. Checking weak_ptr...n";

    if (auto locked = w.lock()) {
        std::cout << "Still validn";
    }
    else {
        std::cout << "Expired weak_ptr — object is gonen";
    }
}

int main() {
    uniquePtrDemo();
    sharedPtrDemo();
    weakPtrDemo();

    return 0;
}
