#include <iostream>
#include <string>

// Item 5 (Functii generate automat de C++)
class UserData {
public:
    std::string name;
    int id;
};

// Item 6 (Interzicere explicita a functiilor generate)
class DatabaseLock {
public:
    DatabaseLock() {
        std::cout << "[DatabaseLock] Resursa blocata.\n";
    }
    
    ~DatabaseLock() {
        std::cout << "[DatabaseLock] Resursa eliberata.\n";
    }

    // Interzicere copy constructor
    DatabaseLock(const DatabaseLock&) = delete;
    
    // Interzicere copy assignment operator
    DatabaseLock& operator=(const DatabaseLock&) = delete;
};

// Item 4 (Initializare inainte de utilizare)
class SystemManager {
private:
    std::string managerName;
    int accessLevel;
    DatabaseLock dbLock; 

public:
    // Lista de initializare membri
    SystemManager(const std::string& name, int level) 
        : managerName(name), accessLevel(level), dbLock() {
        std::cout << "[SystemManager] Initializat in lista de initializare.\n";
    }

    void showStatus() const {
        std::cout << "Manager: " << managerName << " | Nivel: " << accessLevel << "\n";
    }
};

int main() {
    std::cout << "--- Test Item 5 ---\n";
    UserData data1;
    data1.name = "Alex";
    data1.id = 10;
    
    // Apel copy constructor generat automat
    UserData data2 = data1; 
    std::cout << "Date copiate: " << data2.name << " - " << data2.id << "\n\n";


    std::cout << "--- Test Item 4 si 6 ---\n";
    SystemManager sys("Admin", 1);
    sys.showStatus();

    // Daca am decomenta linia de mai jos, compilatorul ar da eroare
    // SystemManager sys2 = sys;

    std::cout << "\n--- Finalizare program ---\n";
    return 0;
}