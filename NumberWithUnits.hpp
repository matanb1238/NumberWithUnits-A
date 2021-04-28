#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

namespace ariel{
    class NumberWithUnits{
            private:
                double num;
                string the_unit;
            public:
                NumberWithUnits(const double& value, const string& unit);                 
                NumberWithUnits(){}
                ~NumberWithUnits(){}


                static double convert(const std::string &from, const std::string &to, double fromVal);
                static void read_units(ifstream& file);
                friend int comparison(const NumberWithUnits& n1, const NumberWithUnits& n2);

                // in/out
                friend ostream& operator<<(ostream& os, const NumberWithUnits& unit);
                friend istream& operator>>(istream& in, NumberWithUnits& unit);
                
                // plus/minus
                friend NumberWithUnits operator+(const NumberWithUnits& unit1, const NumberWithUnits& unit2);
                friend NumberWithUnits operator+(const NumberWithUnits& unit, double num);
                NumberWithUnits& operator+=(const NumberWithUnits& unit2);
                friend NumberWithUnits operator-(const NumberWithUnits& unit1, const NumberWithUnits& unit2);
                friend NumberWithUnits operator-(const NumberWithUnits& unit1, double num);
                NumberWithUnits& operator-=(const NumberWithUnits& unit2);
                const NumberWithUnits operator+() const{
                    return NumberWithUnits(+num, the_unit);
                }
                const NumberWithUnits operator-() const{
                    return NumberWithUnits(-num, the_unit);
                } 


                // bool operators
                friend bool operator>(const NumberWithUnits& unit1, const NumberWithUnits& unit2);
                friend bool operator<(const NumberWithUnits& unit1, const NumberWithUnits& unit2);
                friend bool operator>=(const NumberWithUnits& unit1, const NumberWithUnits& unit2);
                friend bool operator<=(const NumberWithUnits& unit1, const NumberWithUnits& unit2);
                friend bool operator==(const NumberWithUnits& unit1, const NumberWithUnits& unit2);
                friend bool operator!=(const NumberWithUnits& unit1, const NumberWithUnits& unit2);
                
                // increment/decrement
                friend NumberWithUnits& operator++( NumberWithUnits& number);       
                friend NumberWithUnits operator++( NumberWithUnits& number, int);     
                friend NumberWithUnits& operator--( NumberWithUnits& number);      
                friend NumberWithUnits operator--( NumberWithUnits& number, int);   

                friend NumberWithUnits operator*(const NumberWithUnits& unit, double n);
                friend NumberWithUnits operator*(double n, const NumberWithUnits& unit);

    };
}