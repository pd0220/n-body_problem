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
    vector3<double> ASTEROID_V{2e3,0.,0.};

    state<double> y0{SUN_R,SUN_V,
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

    //short run
    //RK4
    double t0=0.;
    double t1=1e11;
    double h=1e5;
    double delta_0=1e11;
    solve_RK4_adapt(y0,t0,t1,h,armageddon,to_file_with_size,delta_0);
    //solve_RK4(y0,t0,t1,h,armageddon,to_file_with_size);

    return 0;
}
