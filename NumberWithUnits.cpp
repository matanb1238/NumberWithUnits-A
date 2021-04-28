#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <map>
#include <string.h>
#include "graph.cpp"
#include "NumberWithUnits.hpp"

using namespace std;

namespace ariel
{
    static graph g;

    double NumberWithUnits::convert(const string &from, const string &to, double fromVal){
        if(from == to){
            return fromVal;
        }
        double retVal = g.getConv(from, to);
        if(retVal > -1){
            return fromVal*retVal;
        }
         __throw_invalid_argument("Not valid convertion");
    }

    void NumberWithUnits::read_units(ifstream &f)
    {    
        string num1;
        string num2;
        string n;
        string l;
        double value1 = 0;
        double value2 = 0;
        while (getline(f, l))
        {
            istringstream Sstream(l);
            if (!(Sstream >> value1 >> num1 >> n >> value2 >> num2))
            {
                break;
            }
            g.addEdge(num1 ,num2, (value2/value1)); 
        }
    }
    NumberWithUnits::NumberWithUnits(const double& value, const string &unit){ 
        if (!g.checkExist(unit))
        {
           __throw_invalid_argument("Invalid unit");
        }
        num=value;
        the_unit=unit;
    }

    int comparison(const NumberWithUnits& num1, const NumberWithUnits& num2)
    {
        double x = num1.num - NumberWithUnits::convert(num2.the_unit, num1.the_unit, num2.num);
        double y = NumberWithUnits::convert(num2.the_unit, num1.the_unit, num2.num) - num1.num;
        const double epsilon = 0.00001;
        if (x > epsilon)
        {
            return 1;
        }
        if (y > epsilon)
        {
            return -1;
        }
        return 0;
    }

    // in/out

    ostream &operator<<(ostream &os, const NumberWithUnits &number) {
        return (os <<  number.num << '[' << number.the_unit << ']'); 
    }
    istream &operator>>(std::istream &is, NumberWithUnits &unit)
    {
        string s;
        double number = 0;
        char c = ']';
        is >> number >> c;
        while(c != ']'){
            if(c != '['){
                s.insert(s.end(), c);
            }
            is >> c;
        }
        unit.num = number;
        unit.the_unit = s;
        if(!g.checkExist(unit.the_unit)){
            __throw_invalid_argument("Unit is not exist");
        }
        return is;
    }

    
    NumberWithUnits operator+(const NumberWithUnits &num1, const NumberWithUnits &num2)
    {
        double converted = NumberWithUnits::convert(num2.the_unit, num1.the_unit, num2.num);
        return NumberWithUnits(num1.num + converted, num1.the_unit);
    }
    NumberWithUnits operator+(const NumberWithUnits& num1, double num) {
        return NumberWithUnits(num1.num + num, num1.the_unit);
    }
    NumberWithUnits& NumberWithUnits::operator+=(const NumberWithUnits &num2)
    {
        double con = convert(num2.the_unit, this->the_unit, num2.num);
        this->num += con; 
        return *this;
    }
    NumberWithUnits operator-(const NumberWithUnits &num1, const NumberWithUnits &num2)
    {
        double converted = NumberWithUnits::convert(num2.the_unit, num1.the_unit, num2.num);
        return NumberWithUnits(num1.num - converted, num1.the_unit);
    }
    NumberWithUnits operator-(const NumberWithUnits& num1, double num){
        return NumberWithUnits(num1.num - num, num1.the_unit);
    }   
    NumberWithUnits& NumberWithUnits::operator-=(const NumberWithUnits &num2)
    {
        double con = convert(num2.the_unit, this->the_unit, num2.num);
        this->num -= con; 
        return *this;
    }
    


    // bool operators
    bool operator>(const NumberWithUnits &num1, const NumberWithUnits &num2) { return comparison(num1, num2) > 0; }
    bool operator>=(const NumberWithUnits &num1, const NumberWithUnits &num2) { return comparison(num1, num2) >= 0; }
    bool operator<(const NumberWithUnits &num1, const NumberWithUnits &num2) { return comparison(num1, num2) < 0; }
    bool operator<=(const NumberWithUnits &num1, const NumberWithUnits &num2) { return comparison(num1, num2) <= 0; }
    bool operator==(const NumberWithUnits &num1, const NumberWithUnits &num2) { return comparison(num1, num2) == 0; }
    bool operator!=(const NumberWithUnits &num1, const NumberWithUnits &num2) { return comparison(num1, num2) != 0; }
    
    
    // increment/decrement
    NumberWithUnits& operator++(NumberWithUnits &number) { 
        ++number.num;
        return number; 
    }    
    NumberWithUnits operator++(NumberWithUnits &number, int) { 
        NumberWithUnits temp = number; 
        number.num++;
        return temp; 
    }
    NumberWithUnits& operator--(NumberWithUnits &number) {
        --number.num;
        return number;
    }    
    NumberWithUnits operator--(NumberWithUnits &number, int) {
        NumberWithUnits temp = number; 
        number.num--;
        return temp; 
    } 
    NumberWithUnits operator*(const NumberWithUnits &unit, double n) {
        return NumberWithUnits{unit.num*n, unit.the_unit};
    }
    NumberWithUnits operator*(double n, const NumberWithUnits &unit) {
        return NumberWithUnits{unit.num*n, unit.the_unit};
    }
    
}
