#include "dumb.h"
#include <iostream>

int main() {
    IDumbDB<std::string, std::string>* db = CreateDumbDB<std::string, std::string>();
    db->Open("MyDatabase");

    db->Put("key1", "value1");
    db->Put("key2", "value2");
    db->Put("key3", "value3");

    auto result = db->Get("key1");
    if (result.has_value()) {
        std::cout << "Get key1: " << result.value() << "\n";
    } else {
        std::cout << "Get key1: not found\n";
    }
    result = db->Get("key4");
    if (result.has_value()) {
        std::cout << "Get key4: " << result.value() << "\n";
    } else {
        std::cout << "Get key4: not found\n";
    }

    auto results = db->Scan("key1", "key3");
    std::cout << "Scan results:\n";
    for (const auto& kv : results) {
        std::cout << kv.first << ": " << kv.second.value() << "\n";
    }

    db->Close();
    return 0;
}
