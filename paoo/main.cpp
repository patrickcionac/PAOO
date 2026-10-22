#include <iostream>
#include <utility>

class DataBuffer {
private:
    // Incapsulare
    int* data;
    size_t size;

public:
    // Initializare membri in constructor
    DataBuffer(size_t s) : size(s), data(new int[s]) {
        for (size_t i = 0; i < size; ++i) {
            data[i] = 0; // Initializare 
        }
        std::cout << "[Constructor] Buffer alocat: dimensiune " << size << ".\n";
    }

    // Copy constructor (deep copy)
    DataBuffer(const DataBuffer& other) : size(other.size), data(new int[other.size]) {
        for (size_t i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
        std::cout << "[Copy Constructor] Copiere completata: dimensiune " << size << ".\n";
    }

    // Move constructor (transfer resurse)
    DataBuffer(DataBuffer&& other) noexcept : size(other.size), data(other.data) {
        // Resetare obiect sursa
        other.size = 0;
        other.data = nullptr;
        std::cout << "[Move Constructor] Mutare resurse: dimensiune " << size << ".\n";
    }

    // Destructor (eliberare heap)
    ~DataBuffer() {
        if (data != nullptr) {
            std::cout << "[Destructor] Memorie eliberata: dimensiune " << size << ".\n";
            delete[] data;
        } else {
            std::cout << "[Destructor] Buffer gol, nu se elibereaza nimic.\n";
        }
    }

    // Setter auxiliar
    void setValue(size_t index, int value) {
        if (index < size) data[index] = value;
    }
};

// Functie test transfer prin valoare
void functionThatCopies(DataBuffer buffer) {
    std::cout << " -> functionThatCopies rulata.\n";
}

// Functie test returnare obiect
DataBuffer functionThatMoves() {
    DataBuffer temp(3);
    return temp;
}

int main() {
    std::cout << "--- Creare obiect normal ---\n";
    DataBuffer buf1(5);
    buf1.setValue(0, 100);

    std::cout << "\n--- Apel copy constructor (parametru) ---\n";
    functionThatCopies(buf1);

    std::cout << "\n--- Apel copy constructor (explicit) ---\n";
    DataBuffer buf2 = buf1;

    std::cout << "\n--- Apel move constructor (std::move) ---\n";
    DataBuffer buf3 = std::move(buf2);

    std::cout << "\n--- Finalizare program ---\n";
    return 0;
}