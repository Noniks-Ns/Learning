#include <iostream> 
#include <memory>

// ---------------- UNIQUE_PTR ---------------- 
// // Single owner. Cannot be copied.

void uniquePtrDemo() { 
    auto p = std::make_unique<int>(10); 
    std::cout << "unique_ptr address: " << p.get() << '\n';

    // Pass pointer (ownership is NOT transferred here)
    auto printPtr = [](const std::unique_ptr<int>& ptr) {
        std::cout << "unique_ptr address: " << ptr.get() << '\n';
    };

    printPtr(p);
}

// ---------------- SHARED_PTR ---------------- // 
// Shared ownership. Object is deleted when count = 0. 

void sharedPtrDemo() { 
    std::cout << "\n--- shared_ptr ---\n";

    auto p1 = std::make_shared<int>(5);
    std::cout << "count: " << p1.use_count() << '\n';

    auto p2 = p1;
    auto p3 = p1;
    std::cout << "count: " << p1.use_count() << '\n';

    p3.reset();
    std::cout << "count: " << p1.use_count() << '\n';

    p2.reset();
    std::cout << "count: " << p1.use_count() << '\n';

    p1.reset();
    std::cout << "p1 is empty\n";
}

// ---------------- WEAK_PTR ---------------- // 
// Non-owning reference to shared_ptr object 

class Node { 
public: 
    int data; 
    std::shared_ptr<Node> next; 
    std::weak_ptr<Node> prev;

    Node(int v) : data(v) {
        std::cout << "Node created: " << data << '\n';
    }

    ~Node() {
        std::cout << "Node destroyed: " << data << '\n';
    }
};

void weakPtrDemo() {
    std::cout << "\n--- weak_ptr ---\n";

    auto n1 = std::make_shared<Node>(10);
    auto n2 = std::make_shared<Node>(20);

    n1->next = n2;      // n1 owns n2
    n2->prev = n1;      // weak reference (no cycle)

    std::weak_ptr<Node> w = n2->prev;

    if (auto locked = w.lock()) {
        std::cout << "Valid: " << locked->data << '\n';
    }

    n1.reset(); // destroy node1

    if (w.lock()) {
        std::cout << "Still valid\n";
    }
    else {
        std::cout << "Expired weak_ptr\n";
    }
}

int main() { 
    uniquePtrDemo(); 
    sharedPtrDemo(); 
    weakPtrDemo(); 
    
    return 0; 
}
