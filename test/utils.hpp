#include <iostream>
using namespace std;

namespace TestUtils {
    void printGreenCheck() {
        cout << "\033[32m✔\033[0m";
    }

    void printRedCross() {
        cout << "\033[31m✗\033[0m";
    }

    void printRedText(const string& text) {
        cout << "\033[31m" << text << "\033[0m";
    }

    void printGreenText(const string& text) {
        cout << "\033[32m" << text << "\033[0m";
    }

    void printTestSuccess(const string& testName) {
        printGreenText("Test " + testName + " success ");
        printGreenCheck();
        cout << endl;
    }

    void printTestFailure(const string& testName) {
        printRedText("Test " + testName + " failed ");
        printRedCross();
        cout << endl;
    }

    void printAllTestsSuccess() {
        printGreenText("All tests passed. Hooray! 🎉");
        cout << endl;
    }
    
    string randomString(size_t length) {
        string result;
        result.reserve(length);
        for (size_t i = 0; i < length; ++i) {
            result += 'a' + rand() % 26;
        }
        return result;
    }

    vector<string> randomStrings(size_t count, size_t length) {
        vector<string> result;
        result.reserve(count);
        for (size_t i = 0; i < count; ++i) {
            result.push_back(randomString(length));
        }
        return result;
    }

    void suffle(vector<string>& v) {
        for (size_t i = 0; i < v.size(); ++i) {
            swap(v[i], v[rand() % v.size()]);
        }
    }

    vector<string> suffled_numbers(size_t count) {
        vector<string> result;
        result.reserve(count);
        for (size_t i = 0; i < count; ++i) {
            result.push_back(to_string(i));
        }
        suffle(result);
        suffle(result);
        suffle(result);
        suffle(result);
        return result;
    }
}