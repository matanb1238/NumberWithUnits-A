#include "NumberWithUnits.hpp"
#include "doctest.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>
#include <stdexcept>
#include <vector>

using namespace ariel;
static vector<string> units = {"m"};
ifstream units_file{"units.txt"};

TEST_CASE("Multi operators"){
    NumberWithUnits::read_units(units_file);
    NumberWithUnits a{1, "m"};
    NumberWithUnits b{3, "m"};
    NumberWithUnits c{300, "cm"};
    double num = 3;
    CHECK(a*num==b);
    CHECK(a*num==c);
    CHECK(num*a==b);
    CHECK(num*a==c);
    double number = 2;
    CHECK_FALSE(a*number==b);
    CHECK_FALSE(a*number==c);
    CHECK(number*a!=b);
    CHECK(number*a!=c);
}

TEST_CASE("All bool operators"){
    NumberWithUnits a{110, "cm"};
    NumberWithUnits b{1, "m"};
    CHECK(a>b);
    CHECK(a>=b);
    CHECK(b<=a);
    CHECK(b<a);
    NumberWithUnits c{1, "hour"};
    NumberWithUnits d{3601, "sec"};
    NumberWithUnits e{60, "min"};
    CHECK(d>c);
    CHECK(d>=c);
    CHECK(c>=e);
    CHECK(e>=c);
    CHECK(c<d);
    NumberWithUnits f{1, "kg"};
    NumberWithUnits g{1000, "g"};
    CHECK_FALSE(f!=g);
    CHECK(g==f);
    CHECK(g<=f);
    NumberWithUnits h{0.001, "ton"};
    CHECK(f==h);
    CHECK(f==g);
    NumberWithUnits i{0.002, "ton"};
    CHECK(f!=i);
    g++;
    CHECK(f!=g);
}

TEST_CASE("+, -, +="){
    NumberWithUnits::read_units(units_file);
    NumberWithUnits a{2, "km"};
    NumberWithUnits b{1000, "m"};
    NumberWithUnits c{3000, "m"};
    CHECK((b+a)==c);
    NumberWithUnits d{5, "km"};
    CHECK((a+b)==c);
    CHECK((b+=a)==c);
    CHECK((a+=c)==d);
    CHECK_FALSE((b+=a)==d);
    NumberWithUnits e{1, "km"};
    NumberWithUnits a2{2, "km"};
    NumberWithUnits b2{1000, "m"};
    CHECK((a2-b2)==e);
    NumberWithUnits f{500, "m"};
    CHECK((b2-a2)==-e);
    CHECK((b2-a2)==-(f*2));
}

TEST_CASE("Postfix and Prefix operators (++/--)"){
    NumberWithUnits a{1, "hour"};
    NumberWithUnits b{2, "hour"};
    NumberWithUnits c{180, "min"};
    CHECK(++a==b);
    CHECK(++a==c);
    CHECK_FALSE(a++==a);
    NumberWithUnits d{4, "hour"};
    CHECK(a==d);
    CHECK(--a==++b); 
    CHECK(a--==b);
}