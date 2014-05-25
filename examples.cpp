#include <string>
#include <iostream>
#include <vector>
#include <cmath>
#include <math.h>
#include <ctgmath>
#include <deque>
#include "compositional.hpp"

using std::cout;
using std::endl;
using std::vector;

using compositional::operator*;
using compositional::_L1;
using compositional::_L2;
using compositional::_L3;
using compositional::_L;

// some static fcns to test with
namespace tst {
    int add1(int x)  { return x+1; }
    int sub1(int x)  { return x-1; }
    double div(double x, double y) { return x/y; }
    double mult(double x, double y) { return x*y; }
};


int main()
{

    // some lambdas to test with
    auto incr = [](auto a) { return a+1; };
    auto dbl = [](auto a) { return a*2; };
    auto triple = [](auto a) { return a*3; };
    auto output_decorate = [] (auto a) { cout << a << " "; return a; };

    vector<int> data {1,2,3,4};

    //  basic composition
    auto double_incr_decor = output_decorate * incr * dbl;
    int x = double_incr_decor(5);
    double y = double_incr_decor(.5);
    cout << endl;
    vector<int> map_results = functional::map(double_incr_decor,data);
    
    // inline
    cout << endl << (triple * incr *dbl)(5) << endl;

    // try the destructive map
    std::deque<int> deq {1,2,3,4};
    mutates::tmap((triple*incr*dbl),deq);
    functional::map(output_decorate,deq);
    cout << endl;

    // make sure we haven't hidden plain old *
    cout << 3*5 << endl;   

    // try composing some user defined fcns
    auto ident = _L(tst::add1) * _L(tst::sub1);
    auto ident2 = incr * _L(tst::sub1);
    cout << ident(1) << "," << ident2(1) << endl;
    
    // composing with multiple args
    auto pow_plus_one = incr * _L(pow);
    cout << pow_plus_one(4,2) << endl;

    // composing with argument binding
    auto to_radians = _L1(tst::mult,M_PI/180.0);
    auto cos_in_degrees = _L(cos) * to_radians;
    cout << cos_in_degrees(45.0) << endl;

    // binding closure over more than one argument
    auto rad45 = _L2(tst::mult,M_PI/180.0,45.0);
    cout << rad45() << endl;

    // composing with a closure that takes no arguments
    cout << ( _L(tan) * rad45 ) () << endl;


}
