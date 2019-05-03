#include "state.hh"
#include "num_int.hh"
#include <chrono>

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

    //average distance of Sun and Earth (m)
    const double EARTH_AVG=1.496e11;

    //average distance of Sun and Jupiter (m)
    const double JUPITER_AVG=7.785e11;

    //average distance of Sun and the inner border of the Oort cloud (m)
    const double ASTEROID_AVG=1e13;

    //initial conditions
    //distance (m)
    //velocity (m/s)
    const double Earth_vel=2.978e4;
    const double Jupiter_vel=1.3071e4;
    
    const vector3<double> SUN_R,SUN_V;
    const vector3<double> EARTH_R=rand_vec_2D(EARTH_AVG);
    const vector3<double> EARTH_V=Earth_vel*perp_unit_vec(EARTH_R);
    const vector3<double> JUPITER_R=rand_vec_2D(JUPITER_AVG);
    const vector3<double> JUPITER_V=Jupiter_vel*perp_unit_vec(JUPITER_R);
    const vector3<double> ASTEROID_R=rand_vec_3D(ASTEROID_AVG);
    const vector3<double> ASTEROID_V=2e3*perp_unit_vec(ASTEROID_R);

    //RHS for Jupiter-Earth-Sun-asteroid
    auto armageddon=[&](double t,state<double> s)->state<double>{return
    {
        s.SUN_V,

        -G*EARTH_M*(s.SUN_R-s.EARTH_R)/std::pow(length(s.SUN_R-s.EARTH_R),3)
        -G*JUPITER_M*(s.SUN_R-s.JUPITER_R)/std::pow(length(s.SUN_R-s.JUPITER_R),3)
        -G*ASTEROID_M*(s.SUN_R-s.ASTEROID_R)/std::pow(length(s.SUN_R-s.ASTEROID_R),3),

        s.EARTH_V,

        -G*SUN_M*(s.EARTH_R-s.SUN_R)/std::pow(length(s.EARTH_R-s.SUN_R),3)
        -G*JUPITER_M*(s.EARTH_R-s.JUPITER_R)/std::pow(length(s.EARTH_R-s.JUPITER_R),3)
        -G*ASTEROID_M*(s.EARTH_R-s.ASTEROID_R)/std::pow(length(s.EARTH_R-s.ASTEROID_R),3),

        s.JUPITER_V,

        -G*SUN_M*(s.JUPITER_R-s.SUN_R)/std::pow(length(s.JUPITER_R-s.SUN_R),3)
        -G*EARTH_M*(s.JUPITER_R-s.EARTH_R)/std::pow(length(s.JUPITER_R-s.EARTH_R),3)
        -G*ASTEROID_M*(s.JUPITER_R-s.ASTEROID_R)/std::pow(length(s.JUPITER_R-s.ASTEROID_R),3),

        s.ASTEROID_V,

        -G*SUN_M*(s.ASTEROID_R-s.SUN_R)/std::pow(length(s.ASTEROID_R-s.SUN_R),3)
        -G*EARTH_M*(s.ASTEROID_R-s.EARTH_R)/std::pow(length(s.ASTEROID_R-s.EARTH_R),3)
        -G*JUPITER_M*(s.ASTEROID_R-s.JUPITER_R)/std::pow(length(s.ASTEROID_R-s.JUPITER_R),3)};};

    const state<double> y0{SUN_R,SUN_V,
                    EARTH_R,EARTH_V,
                    JUPITER_R,JUPITER_V,
                    ASTEROID_R,ASTEROID_V};

    //to file
    auto to_file_with_size=[&](double t,state<double> s,double dt)
    {
        std::ofstream file;
        file.open("armageddon.txt",std::fstream::app);
        file<<s.SUN_R<<" ";
        file<<s.EARTH_R<<" ";
        file<<s.JUPITER_R<<" ";
        file<<s.ASTEROID_R<<" ";
        file<<t<<" ";
        file<<dt<<"\n";
    };

    //integration of ODEs
    const double
    t0=0.;
    const double t1=1e10;
    const double h=1e3;
    const double delta0=1e-4;

    //clock0
    auto clock0=std::chrono::high_resolution_clock::now();

    //RK4
    solve_RK4_adapt(y0,t0,t1,h,armageddon,to_file_with_size,delta0);

    //clock1
    auto clock1=std::chrono::high_resolution_clock::now();

    //"measuring" time
    double time_clock=(static_cast<std::chrono::duration<double,std::milli>>(clock1-clock0)).count();
    std::cout<<"Overall integration time: "<<time_clock<<" ms."<<std::endl;

    return 0;
}
