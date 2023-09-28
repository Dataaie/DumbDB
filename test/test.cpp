#include "dumb.h"
#include <iostream>

int main() {
    DumbDB<std::string, std::string> db;
    db.Open("MyDatabase");

    db.Put("key1", "value1");
    db.Put("key2", "value2");
    db.Put("key3", "value3");

    std::cout << "Get key1: " << db.Get("key1") << "\n";
    std::cout << "Get key4: " << db.Get("key4") << "\n"; // Will print default-constructed string (empty string)

    auto results = db.Scan("key1", "key3");
    std::cout << "Scan results:\n";
    for (const auto& kv : results) {
        std::cout << kv.first << ": " << kv.second << "\n";
    }

    db.Close();
    return 0;
}
