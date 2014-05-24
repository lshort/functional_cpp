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
using compositional::_LL;
using compositional::_L;

// some static fcns to test with
namespace tst {
    int add1(int x)  { return x+1; }
    int sub1(int x)  { return x-1; }
    double div(double x, double y) { return x/y; }
};


int main()
{

    // some lambdas to test with
    auto incr = [](auto a) { return a+1; };
    auto dbl = [](auto a) { return a*2; };
    auto triple = [](auto a) { return a*3; };
    auto output_decorate = [] (auto a) { cout << a << " "; return a; };

    vector<int> data {1,2,3,4};

    auto double_incr_decor = output_decorate * incr * dbl;
    vector<int> map_results = functional::map(double_incr_decor,data);

    auto double_incr_triple = triple * incr * dbl;
    cout << endl << double_incr_triple(5) << endl;

    std::deque<int> deq {1,2,3,4};
    mutates::tmap(double_incr_triple,deq);
    cout << deq[0] << " " << deq[3] << endl;
    cout << 3*5 << endl;   // make sure we haven't hidden plain old *

    auto ident = _LL(tst::add1) * _LL(tst::sub1);
    cout << ident(1) << endl;

    //    auto to_radians = [](auto x) { return x*M_PI/180.0; };
    auto foo = _L(div);
    auto cos_in_degrees = _L(cos) * _L(tst::div);
    cout << cos_in_degrees(45.0,180.0) << endl;
}
