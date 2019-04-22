#include <iostream>
#include "num_int.hh"
#include "vector2.hh"

//main function
int main(int, char**)
{
//Lotka-Volterra system
    //paramteres
    double a=20.;
    double b=1.;
    double c=30.;
    double d=1.;

    //system RHS
    auto LV_system=[&](double t,vector2<double> s)->vector2<double>{return {a*s.x-b*s.x*s.y,d*s.x*s.y-c*s.x};};

    //initial values
    vector2<double> y0={20.,3.};

//writing to file after every step
auto to_file=[&](double t,vector2<double> y){std::ofstream file;file.open("num_int.txt",std::fstream::app);file<<t<<" "<<y.x<<" "<<y.y<<"\n";file.close();};

    
//RK4    
    double t0=0.;
    double t1=1000.;
    double h=0.1;
    solve_RK4(y0,t0,t1,h,LV_system,to_file);

    return 0;
}