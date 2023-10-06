#include "dumb.hpp"
#include "utils.hpp"
#include "balanced_tree_factory.hpp"
#include <iostream>
#include <sstream>
#include <vector>
#include <stdexcept>
#include <cstdio>
#include <fstream>

typedef void (*TestFunc)();

using namespace std;

void project_can_be_built_test() {
    IDumbDB<string, string>* db = CreateDumbDB<string, string>();
    db->Open("MyDatabase");

    db->Put("key1", "value1");
    db->Put("key2", "value2");
    db->Put("key3", "value3");

    auto result = db->Get("key1");
    if (result.has_value()) {
        cout << "Get key1: " << result.value() << "\n";
    } else {
        throw runtime_error("Get key1: not found");
    }
    result = db->Get("key4");
    if (result.has_value()) {
        throw runtime_error("Get key4: " + result.value());
    } else {
        cout << "Get key4: not found\n";
    }
    auto results = db->Scan("key1", "key3");
    if (results.size() != 3) {
        throw runtime_error("Scan results size: " + to_string(results.size()));
    }
    if (results.size() != 3) {
        throw runtime_error("Scan results size: " + to_string(results.size()));
    }
    vector<pair<string, optional<string>>> supposed_results = {
        {"key1", "value1"},
        {"key2", "value2"},
        {"key3", "value3"}
    };
    // for (size_t i = 0; i < results.size(); ++i) {
    //     if (results[i].first != supposed_results[i].first) {
    //         throw runtime_error("Scan result key: " + results[i].first + " != " + supposed_results[i].first);
    //     }
    //     if (results[i].second.value() != supposed_results[i].second.value()) {
    //         throw runtime_error("Scan result value: " + results[i].second.value() + " != " + supposed_results[i].second.value());
    //     }
    // }
    db->Close();
}

void red_black_tree_simple_test() {
    auto tree = create_balanced_tree<string, string>(TreeType::RedBlackTree);
    tree->insert("key1", "value1");
    tree->insert("key2", "value2");
    tree->insert("key3", "value3");

    auto result = tree->search("key1");
    if (result.has_value()) {
        cout << "Get key1: " << result.value() << "\n";
    } else {
        throw runtime_error("Get key1: not found");
    }
    result = tree->search("key4");
    if (result.has_value()) {
        throw runtime_error("Get key4: " + result.value());
    } else {
        cout << "Get key4: not found\n";
    }
    auto results = tree->scan("key1", "key3");
    if (results.size() != 3) {
        throw runtime_error("Scan results size: " + to_string(results.size()));
    }
    vector<pair<string, optional<string>>> supposed_results = {
        {"key1", "value1"},
        {"key2", "value2"},
        {"key3", "value3"}
    };
    for (size_t i = 0; i < results.size(); ++i) {
        if (results[i].first != supposed_results[i].first) {
            throw runtime_error("Scan result key: " + results[i].first + " != " + supposed_results[i].first);
        }
        if (results[i].second.value() != supposed_results[i].second.value()) {
            throw runtime_error("Scan result value: " + results[i].second.value() + " != " + supposed_results[i].second.value());
        }
    }
}

void test_insert(BalancedTree<string, string>* tree, const string& key, const string& value) {
    tree->insert(key, value);
    if (!tree->is_valid()) {
        tree->print_tree();
        throw runtime_error("Tree is not valid after insert");
    } else {
        cout << key << " inserted\n";
    }
}

void red_black_tree_insert_robust_test() {
    auto tree = create_balanced_tree<string, string>(TreeType::RedBlackTree);
    auto numbers = TestUtils::suffled_numbers(1000);
    for (auto& number : numbers) {
        test_insert(tree.get(), number, number);
    }
}

void simple_open_close_test() {
    IDumbDB<string, string>* db = CreateDumbDB<string, string>();
    db->Open("MyDatabase");
    db->Put("key1", "value1");
    db->Put("key4", "value4");
    db->Put("key5", "value5");
    db->Put("key2", "value2");
    db->Put("key3", "value3");
    db->Close();

    db->Open("MyDatabase");
    db->Put("key6", "value6");
    db->Put("key7", "value7");
    db->Put("key9", "value9");
    db->Put("key8", "value8");
    db->Close();
}

void executeTests(const vector<pair<TestFunc, string>>& tests) {
    for (auto& [test, test_name] : tests) {
        stringstream buffer;
        auto oldCoutBuf = cout.rdbuf(buffer.rdbuf());
        bool success = false;
        try {
            test();
            cout.rdbuf(oldCoutBuf);
            TestUtils::printTestSuccess(test_name);
            success = true;
        } catch (const exception& e) {
            cout.rdbuf(oldCoutBuf);
            cout << "Error: \n" << e.what() << endl;
            cout << "Buffered output: \n" << buffer.str() << endl;
            TestUtils::printTestFailure(test_name);
        }
        if (!success) {
            return;
        }
    }
}

int main() {
    vector<pair<TestFunc, string>> tests = {
        {project_can_be_built_test, "project can be built test"}, 
        {red_black_tree_simple_test, "red black tree simple test"},
        {red_black_tree_insert_robust_test, "red black tree insert robust test"}
    };
    executeTests(tests);
    TestUtils::printAllTestsSuccess();
    // simple_write_file_test();
    // simple_read_file_test();
    // simple_file_test();
    simple_open_close_test();
    return 0;
}

