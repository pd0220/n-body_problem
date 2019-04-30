#include "vector.hh"
#include "num_int.hh"

//main function
int main(int, char**)
{    
    //3-body problem (Earth+Moon+Sun)
    //parameters
    //gravitational constant -> G
    const double G=6.6741e-11;
    //mass of Earth -> m2
    const double m2=5.9722e24;
    //mass of Jupiter -> m1
    const double m1=1.889e27;
    //mass of Sun -> m3
    const double m3=1.9885e30;

    //RHS Moon->Earth->Sun
    auto kepler=[&](double t,vector<double> s)->vector<double>{return 
    {s[3],s[4],s[5],
    -G*m2*(s[0]-s[6])/std::pow((s[0]-s[6])*(s[0]-s[6])+(s[1]-s[7])*(s[1]-s[7])+(s[2]-s[8])*(s[2]-s[8]),1.5)-G*m3*(s[0]-s[12])/std::pow((s[0]-s[12])*(s[0]-s[12])+(s[1]-s[13])*(s[1]-s[13])+(s[2]-s[14])*(s[2]-s[14]),1.5),
    -G*m2*(s[1]-s[7])/std::pow((s[0]-s[6])*(s[0]-s[6])+(s[1]-s[7])*(s[1]-s[7])+(s[2]-s[8])*(s[2]-s[8]),1.5)-G*m3*(s[1]-s[13])/std::pow((s[0]-s[12])*(s[0]-s[12])+(s[1]-s[13])*(s[1]-s[13])+(s[2]-s[14])*(s[2]-s[14]),1.5),
    -G*m2*(s[2]-s[8])/std::pow((s[0]-s[6])*(s[0]-s[6])+(s[1]-s[7])*(s[1]-s[7])+(s[2]-s[8])*(s[2]-s[8]),1.5)-G*m3*(s[2]-s[14])/std::pow((s[0]-s[12])*(s[0]-s[12])+(s[1]-s[13])*(s[1]-s[13])+(s[2]-s[14])*(s[2]-s[14]),1.5),
    s[9],s[10],s[11],
    -G*m1*(s[6]-s[0])/std::pow((s[6]-s[0])*(s[6]-s[0])+(s[7]-s[1])*(s[7]-s[1])+(s[8]-s[2])*(s[8]-s[2]),1.5)-G*m3*(s[6]-s[12])/std::pow((s[6]-s[12])*(s[6]-s[12])+(s[7]-s[13])*(s[7]-s[13])+(s[8]-s[14])*(s[8]-s[14]),1.5),
    -G*m1*(s[7]-s[1])/std::pow((s[6]-s[0])*(s[6]-s[0])+(s[7]-s[1])*(s[7]-s[1])+(s[8]-s[2])*(s[8]-s[2]),1.5)-G*m3*(s[7]-s[13])/std::pow((s[6]-s[12])*(s[6]-s[12])+(s[7]-s[13])*(s[7]-s[13])+(s[8]-s[14])*(s[8]-s[14]),1.5),
    -G*m1*(s[8]-s[2])/std::pow((s[6]-s[0])*(s[6]-s[0])+(s[7]-s[1])*(s[7]-s[1])+(s[8]-s[2])*(s[8]-s[2]),1.5)-G*m3*(s[8]-s[14])/std::pow((s[6]-s[12])*(s[6]-s[12])+(s[7]-s[13])*(s[7]-s[13])+(s[8]-s[14])*(s[8]-s[14]),1.5),
    s[15],s[16],s[17],
    -G*m1*(s[12]-s[0])/std::pow((s[12]-s[0])*(s[12]-s[0])+(s[13]-s[1])*(s[13]-s[1])+(s[14]-s[2])*(s[14]-s[2]),1.5)-G*m2*(s[12]-s[6])/std::pow((s[12]-s[6])*(s[12]-s[6])+(s[13]-s[7])*(s[13]-s[7])+(s[14]-s[8])*(s[14]-s[8]),1.5),
    -G*m1*(s[13]-s[1])/std::pow((s[12]-s[0])*(s[12]-s[0])+(s[13]-s[1])*(s[13]-s[1])+(s[14]-s[2])*(s[14]-s[2]),1.5)-G*m2*(s[13]-s[7])/std::pow((s[12]-s[6])*(s[12]-s[6])+(s[13]-s[7])*(s[13]-s[7])+(s[14]-s[8])*(s[14]-s[8]),1.5),
    -G*m1*(s[14]-s[2])/std::pow((s[12]-s[0])*(s[12]-s[0])+(s[13]-s[1])*(s[13]-s[1])+(s[14]-s[2])*(s[14]-s[2]),1.5)-G*m2*(s[14]-s[8])/std::pow((s[12]-s[6])*(s[12]-s[6])+(s[13]-s[7])*(s[13]-s[7])+(s[14]-s[8])*(s[14]-s[8]),1.5),
    };};

    //initial condition
    //distance in m
    //velocity in m/s
    double SunEarth_dist=1.52097701e11;
    double Earth_vel=2.9783e4;
    double SunJupiter_dist=8.16081455e11;
    double Jupiter_vel=1.2446e4;

    //initial condition
    //Jupiter:x,y,z,vx,vy,vz
    //Earth:x,y,z,vx,vy,vz
    //Sun:x,y,z,vx,vy,vz
    vector<double> y0{0.,SunJupiter_dist,0.,Jupiter_vel,0.,0.,
                      0.,SunEarth_dist,0.,Earth_vel,0.,0.,
                      0.,0.,0.,0.,0.,0.};

    //to file
    auto to_file=[&](double t,vector<double> y){std::ofstream file;
                                                file.open("num_int.txt",std::fstream::app);
                                                file<<t<<" ";for(int i{0};i<=y.size()-1;i++){file<<y[i]<<" ";}file<<"\n";};

    //RK4
    double t0=0.;
    double t1=5e8;
    double h=1e4;
    solve_RK4(y0,t0,t1,h,kepler,to_file);
    
    return 0;
}
