#include <iostream>
#include <exception>
#include <cmath>
using namespace std;


class div0 : public exception { // Custom exception: หารด้วย 0
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

            // ตรวจ cin.fail() ก่อน
            if (cin.fail()) throw fail();

            // ตรวจ range
            if (abs(x) > 10000 || abs(y) > 10000) throw OutOfRange_err();

            // ตรวจหารด้วย 0 ผ่าน function
            check0(y);

            // คำนวณปกติ
            d = (double)x / y;
            cout << "Result: " << d << endl;

            // ทดสอบ bad_alloc
            double* myarray;
            for (int i = 0; i < 100000; i++) {
                myarray = new double[50000000]; // จงใจให้ memory หมด
                cout << "Allocating array #" << i << endl;
            }

        } catch (fail& e) {
            cerr << e.what() << endl;
            cin.clear();
            cin.ignore(50, '\n');
            again = true;  // วนรับใหม่

        } catch (div0& e) {
            cerr << e.what() << endl;
            again = true;  // วนรับใหม่

        } catch (OutOfRange_err& e) {
            cerr << e.what() << endl;
            again = true;  // วนรับใหม่

        } catch (bad_alloc& e) {
            cerr << "Memory allocation failed: " << e.what() << endl;
            // ไม่วนรับใหม่ เพราะ calculation สำเร็จแล้ว

        } catch (exception& e) {
            cerr << "Unexpected error: " << e.what() << endl;
        }

    } while (again);

    return 0;
}

void check0(int y) {
    if (y == 0) throw div0();
}