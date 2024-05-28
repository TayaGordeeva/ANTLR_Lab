// Polinoms.cpp 

#include <iostream>
#include "polinom.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");

    /*Polynom p1("x^2+y^2");
	Polynom p2("x");
	Polynom p3 = p1 + p2;
	p3.Print();
    cout << endl;
    
    Polynom p4("yz");
    Polynom p5("x^5");
    Polynom p6 = p3 + p5 * p4;
    p6.Print();
    double a = p6.value_pol(1, 2, 2);*/

    Polynom p1("3x^2yz^2+10xy^2-7yz+x-12");
    Polynom p2("x+2");

    Polynom p3("-5xyz+7yz+18");
    Polynom p4("-x^4yz^3-8xy^2z+3z");

    Polynom p5 = p4 + p3 * (-4);
    Polynom p6 = p1 * p2 - p5;

    p6.Print();
    double a = p6.value_pol(1, 1, 1);

    cout << endl;
    cout << a;
    return 0;

	

}

