/*
* -------- Interval Arithmetic Project ---------
* A project to demonstrate how Object Orientated Programming paradigms, including practicies like friends
* and operator overloading, can be used to write scalable and efficient code
*
* Code is INCITS PL22.16 C++ compliant and is to be run under CodeBlocks / CLion | Meant for C++ 11
*
* Dependencies: iostream, interval.h - For logging/printing purposes using std::cout
*
* Copyright Daniel Marcovecchio
* @author https://github.com/BlackHat0001
*/

//---------- FILE main.cpp
// Contains the main body of the program and test data for testing the interval.h implementation
//
// Copyright Daniel Marcovecchio
//
// Dependencies: iostream - For logging/printing purposes using std::cout, interval.h for use of interval methods
//----------

#include <iostream>
#include "interval.h"

/*
 * PROGRAM INPUT & OUTPUT TEST DATA
 *

x: 3 3.1
y: 7 7

a=x+y result: 10 10.1

b=x-y result: -4 10.1

c=x*y result: 21 21.7

d=x/y result: 0.428571 0.442857

p(x) result: 3 3.1

13 13.2

p+=a result: 13 13.2

p-=a result: 2.9 23.2

p*=a result: 2.9 23.2

p/=a result: 2.9 23.2

COUT D:
0.428571 0.442857

CIN A:
USER INPUT -> 6
USER INPUT -> 2


g=a+f result: 11 7

h = f+a result:11 7

*/

using namespace std;

int main() {
    interval x(3.0,3.1); // Initialisation from complete data
    interval y(7); // Sensible (?) initialisation from a single float

    cout << "x: " << x << " y: " << y << "\n";

    interval a=x+y;
    cout << "a=x+y result: " << a << "\n";

    interval b=x-y;
    cout << "b=x-y result: " << b << "\n";

    interval c=x*y;
    cout << "c=x*y result: " << c << "\n";

    interval d=x/y;
    cout << "d=x/y result: " << d << "\n";

    interval p(x);
    cout << "p(x) result: " << p << "\n";

    p+=a; // and as a professional you realise that this suggests you should also add?
    cout << p << "\n";
    cout << "p+=a result: " << p << "\n";

    p-=a;
    cout << "p-=a result: " << p << "\n";

    p*=a;
    cout << "p*=a result: " << p << "\n";

    p/=a;
    cout << "p/=a result: " << p << "\n";

    cout<<d;
    cin>>a;
    float f(5.);
    interval g=a+f; // and as a professional you realise that this suggests you should also add?
    cout << "g=a+f result: " << g << "\n";
// A challenge for that final 1/50 mark – i.e. just to prove you can and beat the crowd
    interval h=f+a;
    cout << "h = f+a result:" << h << "\n";

    return 0;
}
