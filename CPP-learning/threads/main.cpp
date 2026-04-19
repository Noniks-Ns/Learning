#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>

// Global variable
int n = 0;
std::atomic<int> atomic_n = 0; // Atomic variable — thread-safe
std::mutex mtx; // Mutex for access synchronization

// Function with race condition (unsafe)
void unsafeAdd() {
    for (int i = 0; i < 1000; ++i) {
        n++; // Non-atomic operation: ++ can be interrupted
    }
}

// with mutex
void safeAddWithMutex() {
    for (int i = 0; i < 1000; ++i) {
        std::lock_guard<std::mutex> lock(mtx); // Automatic locking
        n++;
    }
}

// Function with atomic variable (safe and fast)
void safeAddWithAtomic() {
    for (int i = 0; i < 1000; ++i) {
        atomic_n++; // Atomic operation — does not require a mutex
    }
}

int main() {
    std::cout << "=== Race Condition Example ===\n";
    n = 0;

    std::thread t1(unsafeAdd);
    std::thread t2(unsafeAdd);
    t1.join();
    t2.join();

    std::cout << "Unsafe result (n): " << n << " (probably not 2000)\n\n";
    
    // === With mutex ===
    std::cout << "=== Safe with Mutex ===\n";
    n = 0;

    std::thread t3(safeAddWithMutex);
    std::thread t4(safeAddWithMutex);
    t3.join();
    t4.join();

    std::cout << "Safe with mutex (n): " << n << " (should be 2000)\n\n";

    // === With atomic variable === 
    std::cout << "=== Safe with Atomic ===\n";
    atomic_n = 0;

    std::thread t5(safeAddWithAtomic);
    std::thread t6(safeAddWithAtomic);
    t5.join();
    t6.join();

    std::cout << "Safe with atomic (atomic_n): " << atomic_n << " (should be 2000)\n";
    return 0;
}
