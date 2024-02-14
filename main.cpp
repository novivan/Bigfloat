#include <iostream>

#include "BigFloat.h"

int main() {
    std::cout << "Hello, BigFloat!" << std::endl;

    BigFloat a, b;
    a.read();
    b.read();

    a.write();
    b.write();

    BigFloat c = BigFloat(0);
    BigFloat d = BigFloat(1);
    BigFloat e = BigFloat(6);
    BigFloat f = BigFloat(10);
    BigFloat g = BigFloat(20);

    BigFloat i = BigFloat(-1);
    BigFloat j = BigFloat(-6);
    BigFloat k = BigFloat(-10);
    BigFloat l = BigFloat(-20);

    c.write();
    d.write();
    e.write();
    f.write();
    g.write();

    i.write();
    j.write();
    k.write();
    l.write();




    return 0;
}
