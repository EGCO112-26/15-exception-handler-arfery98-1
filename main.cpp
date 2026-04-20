#include <iostream>
#include <exception>
#include <cmath>
using namespace std;

class div0 : public exception {
public:
    virtual const char* what() const throw() {
        return "Error: Divided by zero";
    }
};

class fail : public exception {
public:
    virtual const char* what() const throw() {
        return "Error: Stupid!!";
    }
};

class OutOfRange_err : public exception {
public:
    virtual const char* what() const throw() {
        return "Error: Value out of range (-10000 to 1000)";
    }
};

void check0(int y);

int main() {
    int x, y;
    double d;
    bool again = true;

    do {
        again = false; // สมมติว่า success จนกว่าจะ throw

        try {
            cout << "Enter 2 integers: ";
            cin >> x >> y;

            if (cin.fail()) throw fail();  // ตรวจ cin.fail()
            if (abs(x) > 10000 || abs(y) > 10000) throw OutOfRange_err(); //ตรวจ Range
            check0(y);    // ตรวจหารด้วย 0 ผ่าน function

            d = (double)x / y;
            cout << "Result: " << d << endl;

            double* myarray;   // ทดสอบ bad_alloc
            for (int i = 0; i < 100000; i++) {
                myarray = new double[50000000];
                cout << "Allocating array #" << i << endl;
            }

        } catch (exception& e) {
            cerr << e.what() << endl;

            if (dynamic_cast<fail*>(&e)) {
                cin.clear();
                cin.ignore(50, '\n');
            }

            // bad_alloc = calc สำเร็จแล้ว ไม่ต้องวนใหม่
            again = dynamic_cast<bad_alloc*>(&e) ? false : true;
        }

    } while (again);

    return 0;
}

void check0(int y) {
    if (y == 0) throw div0();
}