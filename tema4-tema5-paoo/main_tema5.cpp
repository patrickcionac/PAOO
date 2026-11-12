#include <iostream>
#include <string>

// Clasa de baza
class Document {
protected:
    std::string title;

public:
    Document(const std::string& t) : title(t) {}

    // Copy constructor 
    Document(const Document& rhs) : title(rhs.title) {
        std::cout << "[Document] Copy constructor apelat\n";
    }

    // Item 10: Return reference to *this
    // Item 11: Handle assignment to self
    Document& operator=(const Document& rhs) {
        std::cout << "[Document] Operator= apelat\n";
        
        // Item 11
        if (this == &rhs) {
            return *this;
        }

        title = rhs.title;
        
        // Item 10
        return *this;
    }
};

// Clasa derivata 
class ClassifiedDocument : public Document {
private:
    int* clearanceLevel;

public:
    ClassifiedDocument(const std::string& t, int level) 
        : Document(t), clearanceLevel(new int(level)) {}

    // Item 12: Copy all parts of an object
    ClassifiedDocument(const ClassifiedDocument& rhs) 
        : Document(rhs), // Copiere clasa de baza
          clearanceLevel(new int(*rhs.clearanceLevel)) // Copiere membri proprii
    {
        std::cout << "[ClassifiedDocument] Copy constructor apelat\n";
    }

    // Item 10, 11 si 12 combinate
    ClassifiedDocument& operator=(const ClassifiedDocument& rhs) {
        std::cout << "[ClassifiedDocument] Operator= apelat\n";
        
        // Item 11
        if (this == &rhs) {
            return *this;
        }

        // Item 12 (apel operator= clasa de baza)
        Document::operator=(rhs);

        // Item 12 (copiere deep membri proprii)
        int* newLevel = new int(*rhs.clearanceLevel);
        delete clearanceLevel;
        clearanceLevel = newLevel;

        // Item 10
        return *this;
    }

    ~ClassifiedDocument() {
        delete clearanceLevel;
    }

    void print() const {
        std::cout << "Document: " << title << " | Nivel securitate: " << *clearanceLevel << "\n";
    }
};

int main() {
    std::cout << "--- Initializare obiecte ---\n";
    ClassifiedDocument doc1("Proiect_Secret", 5);
    ClassifiedDocument doc2("Raport_Public", 1);
    ClassifiedDocument doc3("Schiță", 2);

    std::cout << "\n--- Test Item 10 (Chaining) ---\n";
    // doc3 = doc2 = doc1 functioneaza doarece operator= returneaza o referinta la *this
    doc3 = doc2 = doc1;
    doc3.print();

    std::cout << "\n--- Test Item 11 (Self-assignment) ---\n";
    // Verificarea if (this == &rhs) previne stergerea memoriei proprii
    doc1 = doc1;

    std::cout << "\n--- Test Item 12 (Copy all parts) ---\n";
    // Copiaza atat string-ul din baza cat si pointer-ul din derivata
    ClassifiedDocument doc4(doc1);
    doc4.print();

    std::cout << "\n--- Finalizare ---\n";
    return 0;
}