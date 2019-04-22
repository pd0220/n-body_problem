#include <array>
#include <iostream>

//main function
int main(int, char**)
{
    //Lotka-Volterra system
    double a=20.;
    double b=1.;
    double c=30.;
    double d=1.;

    auto LV_system=[&](double t,std::array<double,2> s)->std::array<double,2>{return {a*s[0]-b*s[0]*s[1],d*s[0]*s[1]-c*s[1]};};

    return 0;
}