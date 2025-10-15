// 
// Linked Stack implementation for the 2025-10-17 homework
// C++17 compatible 
//
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <memory>

template<typename T>
struct Node {
    T value;
    std::unique_ptr<Node<T>> bottom;

    Node(const T& val, std::unique_ptr<Node<T>> btm = nullptr)
        : value(val), bottom(std::move(btm)) {}
};

template<typename T>
class LinkedStack {
private:
    std::unique_ptr<Node<T>> head;
    size_t ssize;

public:
    LinkedStack() : head(nullptr), ssize(0) {}
    ~LinkedStack() {
        while (head) {
            head = std::move(head->bottom);
        }
    }

    LinkedStack(const LinkedStack&) = delete;
    LinkedStack& operator=(const LinkedStack&) = delete;

    LinkedStack(LinkedStack&& other) noexcept = default;
    LinkedStack& operator=(LinkedStack&& other) noexcept = default; 

    void push(const T& value) {
        this->head = std::make_unique<Node<T>>(value, std::move(this->head));
        ++this->ssize;
    }

    void push(T&& value) {
        this->head = std::make_unique<Node<T>>(std::move(value), std::move(this->head));
        ++this->ssize;
    }

    void pop() {
        if(!this->head) {
            throw std::runtime_error("Stack is empty");
        }
        this->head = std::move(head->bottom);
        --this->ssize;
    }

    T& top() {
        if(!this->head) {
            throw std::runtime_error("Stack is empty");
        }
        return head->value;
    }

    bool empty() { return this->ssize == 0; }
    size_t size() { return this->ssize; }

    // Homework solution starts here

    // 1.
    template<typename Predicate>
    LinkedStack<T> Where(Predicate pred) const {
        LinkedStack<T> st;
        Node<T>* cur = this->head.get();
        while(cur) {
            if(pred(cur->value)){
                st.push(cur->value);
            }
            cur = cur->bottom.get();
        }
        return st;
    }

    // 2.
    template<typename Selector>
    LinkedStack<T> Select(Selector select) const {
        LinkedStack<T> st;
        Node<T>* cur = this->head.get();
        while(cur) {
            st.push(select(cur->value));
            cur = cur->bottom.get();
        }
        return st;
    }

    // 3.
    LinkedStack<T> Reverse() const {
        LinkedStack<T> st;
        Node<T>* cur = this->head.get();
        while(cur) {
            st.push(cur->value);
            cur = cur->bottom.get();
        }
        return st;
    }

    // 4.
    template<typename Predicate>
    T First(Predicate pred) const {
        Node<T>* cur = this->head.get();
        while(cur) {
            if(pred(cur->value)){
                return cur->value;
            }
            cur = cur->bottom.get();
        }
        return T();
    }

    // 5.
    template<typename Predicate>
    bool Contains(Predicate pred) const {
        Node<T>* cur = this->head.get();
        while(cur) {
            if(pred(cur->value)) return true;
            cur = cur->bottom.get();
        }
        return false;
    }

    // 6.
    template<typename Predicate>
    size_t Count(Predicate pred) const {
        size_t count = 0;
        Node<T>* cur = this->head.get();
        while(cur) {
            if(pred(cur->value)) ++count;
            cur = cur->bottom.get();
        }
        return count;
    }

    // 7.
    template<typename Comparator>
    T Max(Comparator comp) const {
        if(!this->ssize) throw std::runtime_error("Stack is empty");
        Node<T>* cur = this->head.get();
        T max = cur->value;
        cur = cur->bottom.get();
        while(cur) {
            if(comp(max, cur->value) < 0) max = cur->value; 
            cur = cur->bottom.get();
        }
        return max;
    }
};


bool is_fermat_prime(int a) {
    if (a < 3) return false;
    if (a == 3) return true;

    auto is_power_of_two = [](unsigned long long x){
        return x && !(x & (x - 1));
    };

    auto mod_pow = [](unsigned long long base, unsigned long long exp, unsigned long long mod){
        if (mod <= 1) return 0ULL;
        unsigned long long result = 1;
        base %= mod;
        while (exp) {
            if (exp & 1) result = (result * base) % mod;
            base = (base * base) % mod;
            exp >>= 1;
        }
        return result;
    };

    unsigned long long m = static_cast<unsigned long long>(a) - 1ULL;
    if (!is_power_of_two(m)) return false;

    unsigned long long t = 0;
    while ((1ULL << t) < m) ++t;
    if (!is_power_of_two(t)) return false;

    auto res = mod_pow(3, m / 2, a);
    return res == static_cast<unsigned long long>(a - 1);
}


int main(void) {
    // 'LinkedStack::Where' test
    {
        LinkedStack<int> test;
        for(int i = 0; i < 31; ++i){
            test.push(i);
        }
        LinkedStack<int> result = test.Where([](int e){
            return e % 2;
        }); 
        std::cout << "Where[0;32], ? e % 2:\n\t";
        while(!result.empty()){
            std::cout << result.top() << "; ";
            result.pop();
        }
        std::cout << "\n-----------------------------------------------\n";
    }

    // 'LinkedStack::Selector' test
    {
        LinkedStack<int> test;
        for(int i = 0; i < 15; ++i){
            test.push(i);
        }
        LinkedStack<int> result = test.Select([](int e){
            return e << 2;
        }); 
        std::cout << "Select[0;15], e << 2:\n\t";
        while(!result.empty()){
            std::cout << result.top() << "; ";
            result.pop();
        }
        std::cout << "\n-----------------------------------------------\n";
    }

    // 'LinkedStack::Reverse' test
    {
        LinkedStack<int> test;
        for(int i = 0; i < 15; ++i){
            test.push(i);
        }
        LinkedStack<int> result = test.Reverse();
        std::cout << "Reverse[0;15]:\n\t";
        while(!result.empty()){
            std::cout << result.top() << "; ";
            result.pop();
        }
    std::cout << "\n-----------------------------------------------\n";
    }

    // 'LinkedStack::First' test
    {
        LinkedStack<int> test;
        for(int i = 18; i < 512; ++i){
            test.push(i);
        }
        int result = test.First(is_fermat_prime);
        std::cout << "First[18;512], ? e == fermat-prime:\n\t"
                  << result
                  << ";\n-----------------------------------------------\n";
    }

    // 'LinkedStack::Contains' test
    {
        LinkedStack<int> test;
        for(int i = 0; i < 63; ++i){
            test.push(i);
        }
        bool result = test.Contains([](int e){
            return e == 123;
        });
        std::cout << "Contains[0;63], ? e == 123:\n\t"
                  << std::boolalpha << result
                  << ";\n-----------------------------------------------\n";
    }

    // 'LinkedStack::Count' test
    {
        LinkedStack<int> test;
        for(int i = 0; i < 1'000'000; ++i){
            test.push(i);
        }
        size_t count = test.Count(is_fermat_prime);
        std::cout << "Count[0;1'000'000], ? e == fermat-prime:\n\t"
                  << count
                  << ";\n-----------------------------------------------\n";
    }

    // 'LinkedStack::Max' test
    {
        LinkedStack<std::string> test;
        test.push("Bubble Sort");
        test.push("Merge Sort");
        test.push("Radix Sort");
        test.push("Heap Sort");
        test.push("Quick Sort");
        test.push("Selection Sort");
        test.push("Counting Sort");
        test.push("Intro Sort");
        test.push("Insertion Sort");
        std::string result = test.Max([](std::string a, std::string b){
            if(a.size() > b.size()) return (int)1;
            if(b.size() > a.size()) return (int)-1;
            return 0;
        });
        std::cout << "Max[] strings, max of strings:\n\t"
                  << result
                  << ";\n-----------------------------------------------\n";
    }

    return 0;
}
