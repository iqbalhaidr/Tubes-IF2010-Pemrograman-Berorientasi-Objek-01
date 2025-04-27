#include <iostream>
#include <vector>

#include "../include/Randomizer.hpp"

using namespace std;

void switchTest(int i) {
    switch (i) {
        case 1:
            cout << "ini masuk 1" << endl;
            break;
        case 2:
            cout << "ini masuk 2" << endl;
            break;
        case 3:
            cout << "ini masuk 3" << endl;
            break;
        default:
            cout << "ini selain 1 2 3" << endl;
            break;
    }
}

int main() {
    // int i = 5;
    // for (; i < 10; i++) {
    //     cout << i << endl;
    // }
    for (int i = 0; i < 5; i++) {
        switchTest(Randomizer::random(1, 3));
        cout << "================\n";
    }
}