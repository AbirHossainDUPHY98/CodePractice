// Write a hash table from scratch using chaining and a simple hash function.

#include <iostream>
#include <string>
using namespace std;

template<typename K, typename V>
struct Node {
    K key;
    V value;
    Node* next;

    Node(const K& k, const V& v) : key(k), value(v), next(nullptr) {}
};

template<typename K, typename V>
class HashTable {
private:
    Node<K,V>** table;     // array of bucket pointers
    int capacity;         // total buckets
    int size;             // total elements
    double maxLoadFactor; // threshold for rehash

    // -------- Polynomial Rolling Hash --------
    unsigned long hashFunction(const K& key) {
        const unsigned long p = 31;   // base
        unsigned long hash = 0;
        unsigned long power = 1;

        for (char c : key) {          // assumes K is string-like
            hash += (c * power);
            power *= p;
        }
        return hash % capacity;
    }

    // -------- Rehashing --------
    void rehash() {
        int oldCapacity = capacity;
        capacity *= 2;  // grow table
        Node<K,V>** newTable = new Node<K,V>*[capacity];

        for (int i = 0; i < capacity; i++)
            newTable[i] = nullptr;

        // move nodes
        for (int i = 0; i < oldCapacity; i++) {
            Node<K,V>* curr = table[i];
            while (curr) {
                Node<K,V>* nextNode = curr->next;

                unsigned long newIndex = hashFunction(curr->key);
                curr->next = newTable[newIndex];
                newTable[newIndex] = curr;

                curr = nextNode;
            }
        }

        delete[] table;
        table = newTable;
    }

    double loadFactor() {
        return (double)size / capacity;
    }

public:
    HashTable(int initialCap = 8, double lf = 0.75)
        : capacity(initialCap), size(0), maxLoadFactor(lf)
    {
        table = new Node<K,V>*[capacity];
        for (int i = 0; i < capacity; i++)
            table[i] = nullptr;
    }

    // -------- Insert --------
    void insert(const K& key, const V& value) {
        if (loadFactor() >= maxLoadFactor) {
            rehash();
        }

        unsigned long index = hashFunction(key);

        Node<K,V>* curr = table[index];
        while (curr) {
            if (curr->key == key) {
                curr->value = value;   // update
                return;
            }
            curr = curr->next;
        }

        Node<K,V>* newNode = new Node<K,V>(key, value);
        newNode->next = table[index];
        table[index] = newNode;
        size++;
    }

    // -------- Search --------
    bool search(const K& key, V& outValue) {
        unsigned long index = hashFunction(key);
        Node<K,V>* curr = table[index];

        while (curr) {
            if (curr->key == key) {
                outValue = curr->value;
                return true;
            }
            curr = curr->next;
        }
        return false;
    }

    // -------- Remove --------
    bool remove(const K& key) {
        unsigned long index = hashFunction(key);
        Node<K,V>* curr = table[index];
        Node<K,V>* prev = nullptr;

        while (curr) {
            if (curr->key == key) {
                if (prev)
                    prev->next = curr->next;
                else
                    table[index] = curr->next;

                delete curr;
                size--;
                return true;
            }
            prev = curr;
            curr = curr->next;
        }
        return false;
    }

    // -------- Display --------
    void display() {
        cout << "\nCapacity: " << capacity 
             << " | Size: " << size 
             << " | LoadFactor: " << loadFactor() << "\n";

        for (int i = 0; i < capacity; i++) {
            cout << i << ": ";
            Node<K,V>* curr = table[i];
            while (curr) {
                cout << "(" << curr->key << "," << curr->value << ") -> ";
                curr = curr->next;
            }
            cout << "NULL\n";
        }
    }

    // -------- Destructor --------
    ~HashTable() {
        for (int i = 0; i < capacity; i++) {
            Node<K,V>* curr = table[i];
            while (curr) {
                Node<K,V>* tmp = curr;
                curr = curr->next;
                delete tmp;
            }
        }
        delete[] table;
    }
};

int main() {
    HashTable<string, int> ht;

    ht.insert("apple", 10);
    ht.insert("banana", 20);
    ht.insert("orange", 30);
    ht.insert("grape", 40);
    ht.insert("melon", 50);
    ht.insert("kiwi", 60);
    ht.insert("mango", 70);
    ht.insert("pear", 80);

    ht.display();

    int val;
    if (ht.search("banana", val))
        cout << "\nbanana = " << val << endl;

    ht.remove("orange");
    cout << "\nAfter removing orange:\n";
    ht.display();

    return 0;
}

