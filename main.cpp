//
// Created by Yusuf Pisan on 4/26/18.
// Created by Jonathan Young on 11/16/19
//

#include "skiplist.h"
#include <iostream>
#include <sstream>

using namespace std;

int TotalPassed = 0;
int TotalTests = 0;

template<typename T>
string isOK(const T &got, const T &expected) {
    ++TotalTests;
    if (got == expected) {
        ++TotalPassed;
        return "OK: ";
    } else {
        cout << "    Got   " << got << "\n expected " << expected << endl;
        return "ERR: ";
    }
}

void test02() {
    SkipList Skip(3);
    stringstream Ss;
    Ss << Skip;
    cout << isOK(Ss.str(), "Level: 2 -- -2147483648, 2147483647 \n"s +
                           "Level: 1 -- -2147483648, 2147483647 \n"s +
                           "Level: 0 -- -2147483648, 2147483647 \n"s)
         << "Empty SkipList of Depth=3" << endl;
    srand(100);
    Skip.add(10);
    Skip.add(30);
    Skip.add(5);
    Skip.add(25);
    Ss.str("");
    Ss << Skip;
    cout << isOK(Ss.str(),
                 "Level: 2 -- -2147483648, 5, 30, 2147483647 \n"s +
                 "Level: 1 -- -2147483648, 5, 25, 30, 2147483647 \n"s +
                 "Level: 0 -- -2147483648, 5, 10, 25, 30, 2147483647 \n"s)
         << "SkipList of Depth=3 with 10, 30, 5, 25" << endl;
    cout << isOK(Skip.contains(10), true) << "Contains 10" << endl;
    cout << isOK(Skip.contains(30), true) << "Contains 30" << endl;
    cout << isOK(Skip.contains(71), false) << "Does not contain 71" << endl;
}

void test01() {
    SkipList Skip(1);
    stringstream Ss;
    Ss << Skip;
    cout << isOK(Ss.str(), "Level: 0 -- -2147483648, 2147483647 \n"s)
         << "Empty SkipList" << endl;
    Skip.add(10);
    Skip.add(30);
    Skip.add(5);
    Skip.add(25);
    Ss.str("");
    Ss << Skip;
    cout << isOK(Ss.str(),
                 "Level: 0 -- -2147483648, 5, 10, 25, 30, 2147483647 \n"s)
         << "Added 10, 30, 5, 25," << endl;
    cout << isOK(Skip.contains(10), true) << "Contains 10" << endl;
    cout << isOK(Skip.contains(30), true) << "Contains 30" << endl;
    cout << isOK(Skip.contains(71), false) << "Does not contain 71" << endl;
}

void test03() {
    SkipList Skip(5);
    stringstream Ss;
    Ss << Skip;
    cout << isOK(Ss.str(), "Level: 4 -- -2147483648, 2147483647 \n"s +
                           "Level: 3 -- -2147483648, 2147483647 \n"s +
                           "Level: 2 -- -2147483648, 2147483647 \n"s +
                           "Level: 1 -- -2147483648, 2147483647 \n"s +
                           "Level: 0 -- -2147483648, 2147483647 \n"s)
         << "Empty SkipList" << endl;
    srand(100);
    Skip.add(5);
    Skip.add(22);
    Skip.add(1);
    Skip.add(55);
    Skip.add(17);
    Skip.add(7);
    Ss.str("");
    Ss << Skip;

    cout << isOK(Ss.str(),
                 "Level: 4 -- -2147483648, 17, 22, 2147483647 \n"s +
                 "Level: 3 -- -2147483648, 17, 22, 55, 2147483647 \n"s +
                 "Level: 2 -- -2147483648, 17, 22, 55, 2147483647 \n"s +
                 "Level: 1 -- -2147483648, 1, 17, 22, 55, 2147483647 \n"s +
                 "Level: 0 -- -2147483648, 1, 5, 7, 17, 22, 55, 2147483647 \n"s)
         << "SkipList of Depth=5 with 1, 5, 7, 17, 22, 55" << endl;
    cout << isOK(Skip.contains(10), false) << "Does not contain 10" << endl;
    cout << isOK(Skip.add(30), true) << "Added 30" << endl;
    cout << isOK(Skip.add(30), false) << "Cannot add 30 again" << endl;
    cout << isOK(Skip.remove(30), true) << "Removed 30" << endl;
    cout << isOK(Ss.str(),
                 "Level: 4 -- -2147483648, 17, 22, 2147483647 \n"s +
                 "Level: 3 -- -2147483648, 17, 22, 55, 2147483647 \n"s +
                 "Level: 2 -- -2147483648, 17, 22, 55, 2147483647 \n"s +
                 "Level: 1 -- -2147483648, 1, 17, 22, 55, 2147483647 \n"s +
                 "Level: 0 -- -2147483648, 1, 5, 7, 17, 22, 55, 2147483647 \n"s)
         << "SkipList of Depth=5 with 1, 5, 7, 17, 22, 55" << endl;
}

int main() {
    cout << "Because of the random nature of SkipList, "
         << "the skip list levels may not match" << endl;
    // Set the random seed for easy debugging
    // NOLINTNEXTLINE
    srand(424242);
    test01();
    test02();
    test03();
    cout << "Passed: " << TotalPassed << "/" << TotalTests << endl;
    return 0;
}