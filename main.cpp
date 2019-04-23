#include "vector.hh"
#include "num_int.hh"

//main function
int main(int, char**)
{    
    //Kepler-problem (Earth+Moon)
    //parameters
    const double G=6.67408e-11;
    const double M=5.972e24;
    const double C=-G*M;

    //RHS
    auto kepler=[&](double t,vector<double> s)->vector<double>{return {s[2],s[3],C*s[0]*1/std::pow(s[0]*s[0]+s[1]*s[1],1.5),C*s[1]*1/std::pow(s[0]*s[0]+s[1]*s[1],1.5)};};

    //initial condition
    vector<double> y0{0,4.055e8,964,0};

    //to file
    auto to_file=[&](double t,vector<double> y){std::ofstream file;file.open("num_int.txt",std::fstream::app);file<<t<<" ";for(int i{0};i<=y.size()-1;i++){file<<y[i]<<" ";}file<<"\n";};

    //RK4
    double t0=0.;
    double t1=100000000.;
    double h=10000;
    solve_RK4(y0,t0,t1,h,kepler,to_file);
    
    return 0;
}
