#include "vector.hh"
#include "num_int.hh"

//main function
int main(int, char**)
{

    //harmonic oscillator
    auto harm_osc=[&](double t,vector<double> s)->vector<double>{return {s[1],-s[0]};};

    //initial condition
    vector<double> y0{5.,5.};

    //to file
    auto to_file=[&](double t,vector<double> y){std::ofstream file;file.open("num_int.txt",std::fstream::app);file<<t<<" "<<y[0]<<" "<<y[1]<<"\n";file.close();};

    //RK4
    double t0=0.;
    double t1=10.;
    double h=1e-3;
    solve_RK4(y0,t0,t1,h,harm_osc,to_file);
    
    return 0;
}
