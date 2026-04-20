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
        cin.clear();
        cin.ignore(50, '\n');
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
    int a = 1;

    do {
        try {
            cout << "Enter 2 numbers: ";
            cin >> x >> y;

            if (cin.fail()) throw fail();
            if (abs(x) > 1000 || abs(y) > 1000) throw "Value out of range";
            check0(y);

            a = 0;

            d = (double)x / y;
            cout << "The result is " << d << endl;

            int i;
            double* myarray;
            for (i = 0; i < 100000; i++) {
                cout << "Allocating memory .... " << i << endl;
                myarray = new double[50000000000];
            }

        } catch (exception& e) {
            cerr << e.what() << endl;
            if (dynamic_cast<bad_alloc*>(&e)) break;
        } catch (const char* e) {
            cerr << e << endl;
        }

    } while (a);

    return 0;
}

void check0(int y) {
    if (y == 0) throw div0();
}