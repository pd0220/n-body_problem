#include "state.hh"
#include "num_int.hh"

//main function
int main(int, char**)
{    
    //parameters
    //gravitational constant (m^3*kg^-1*s*-2)
    const double G=6.6741e-11;
    //mass of Jupiter (kg)
    const double JUPITER_M=1.889e27;
    //mass of Earth (kg)
    const double EARTH_M=5.9722e24;
    //mass of Sun (kg)
    const double SUN_M=1.9885e30;
    //mas of asteroid (kg)
    const double ASTEROID_M=1e5;
    
    //RHS for Jupiter-Earth-Sun-asteroid
    auto armageddon=[&](double t,state_vector<double> s)->state_vector<double>{return
    {
        s.state[1],

        -G*EARTH_M*(s.state[0]-s.state[2])/std::pow(length(s.state[0]-s.state[2]),3)
        -G*JUPITER_M*(s.state[0]-s.state[4])/std::pow(length(s.state[0]-s.state[4]),3)
        -G*ASTEROID_M*(s.state[0]-s.state[6])/std::pow(length(s.state[0]-s.state[6]),3),

        s.state[3],

        -G*SUN_M*(s.state[2]-s.state[0])/std::pow(length(s.state[2]-s.state[0]),3)
        -G*JUPITER_M*(s.state[2]-s.state[4])/std::pow(length(s.state[2]-s.state[4]),3)
        -G*ASTEROID_M*(s.state[2]-s.state[6])/std::pow(length(s.state[2]-s.state[6]),3),

        s.state[5],

        -G*EARTH_M*(s.state[4]-s.state[2])/std::pow(length(s.state[4]-s.state[2]),3)
        -G*SUN_M*(s.state[4]-s.state[0])/std::pow(length(s.state[4]-s.state[0]),3)
        -G*ASTEROID_M*(s.state[4]-s.state[6])/std::pow(length(s.state[4]-s.state[6]),3),

        s.state[7],

        -G*EARTH_M*(s.state[6]-s.state[2])/std::pow(length(s.state[6]-s.state[2]),3)
        -G*JUPITER_M*(s.state[6]-s.state[4])/std::pow(length(s.state[6]-s.state[4]),3)
        -G*SUN_M*(s.state[6]-s.state[0])/std::pow(length(s.state[6]-s.state[0]),3)};
    };

    //initial conditions
    //distance (m)
    //velocity (m/s)
    const double SunEarth_dist=1.52097701e11;
    const double Earth_vel=2.9783e4;
    const double SunJupiter_dist=8.16081455e11;
    const double Jupiter_vel=1.2446e4;
    const double Asteroidy=1e13;
    const double Asteroidz=1e13/std::sqrt(2);
    
    vector3<double> SUN_R,SUN_V;
    vector3<double> EARTH_R{0.,SunEarth_dist,0.};
    vector3<double> EARTH_V{Earth_vel,0.,0.};
    vector3<double> JUPITER_R{0.,SunJupiter_dist,0.};
    vector3<double> JUPITER_V{Jupiter_vel,0.,0.,};
    vector3<double> ASTEROID_R{0.,Asteroidy,Asteroidz};
    vector3<double> ASTEROID_V{1e4,0.,0.};

    state_vector<double> y0{SUN_R,SUN_V,
                            EARTH_R,EARTH_V,
                            JUPITER_R,JUPITER_V,
                            ASTEROID_R,ASTEROID_V};

    //to file
    auto to_file=[&](double t,state_vector<double> y)
    {
        std::ofstream file;
        file.open("num_int.txt",std::fstream::app);
        file<<t<<" ";for(int i{0};i<=7;i++){file<<y.state[i]<<" ";}file<<"\n";
    };

    //RK4
    double t0=0.;
    double t1=5e8;
    double h=1e4;
    solve_RK4(y0,t0,t1,h,armageddon,to_file);

    return 0;
}
