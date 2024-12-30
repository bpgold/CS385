#include <iostream>

using namespace std;

int mystery1(int a, int b) {
    int c = a - b,
        d = (c >> 7) & 1,
        mystery = a - c * d;
    return mystery;
}


int mystery2(int x) {
    return (x && !(x & (x - 1)));
    //cout<< x-1 <<endl
    //cout <<
}



int mystery3(int x, int y) {
    int s, c;
    s = x ^ y;
    c = x & y;
    while (c != 0) {
        c = c << 1;
        x = s;
        y = c;
        s = x ^ y;
        c = x & y;
    }
    return s;
}


int main(int argc, char *argv[]) {
    // mystery1() test
    cout << mystery1(3, 7) << endl;
    cout << mystery1(8, 7) << endl;

    //mystery2() test
    cout << "hi"; <<endl:
    cout << mystery2(1); << endl;
    cout << mystery2(2); << endl;
    cout << mystery2(3); << endl;
    cout << mystery2(4); << endl;
    cout << mystery2(5); << endl;
    cout << mystery2(6); << endl;
    cout << mystery2(7); << endl;
    cout << mystery2(8); << endl;

    // mystery3() test
    cout << mystery3(5, 7) << endl;
    cout << mystery3(2, 8) << endl;
    

}