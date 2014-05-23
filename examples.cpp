#include <string>
#include <iostream>
#include <vector>
#include <cmath>
#include <ctgmath>
#include <deque>
#include "compositional.hpp"

using std::cout;
using std::endl;
using std::vector;

using compositional::operator*;
using compositional::_L;

int add1(int x)  { return x+1; }
int sub1(int x)  { return x-1; }
auto incr = [](auto a) { return a+1; };
auto dbl = [](auto a) { return a*2; };
auto triple = [](auto a) { return a*3; };


int main()
{
    vector<int> data {1,2,3,4};
    auto double_and_incr = incr * dbl;
    auto double_incr_triple = triple * incr * dbl;

    vector<int> map_results = functional::map(double_and_incr,data);
    cout << map_results[0] << " " << map_results[3] << endl;
    cout << double_incr_triple(5) << endl;

    std::deque<int> deq {1,2,3,4};
    mutates::tmap(double_and_incr,deq);
    cout << deq[0] << " " << deq[3] << endl;
    cout << 3*5 << endl;   // make sure we haven't hidden plain old *

    auto ident = _L(add1) * _L(sub1);
    cout << ident(1) << endl;

    auto div = [](auto x) { return x/5.0; };
    auto find_angle = _L(cos) * div;
    cout << find_angle(1.5) << endl;
}
