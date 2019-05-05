#include "state.hh"
#include "num_int.hh"
#include <chrono>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//main function
int main(int, char**)
{    
    //physical parameters
    //gravitational constant (m^3*kg^-1*s*-2)
    const double G=6.6741e-11;

    //mass of Jupiter (kg)
    const double JUPITER_M=1.889e27;

    //mass of Earth (kg)
    const double EARTH_M=5.9722e24;

    //mass of Sun (kg)
    const double SUN_M=1.9885e30;

    //mas of asteroid (kg)
    const double ASTEROID_M=1e15;

    //average distance of Sun and Earth (m)
    const double EARTH_AVG=1.496e11;

    //average distance of Sun and Jupiter (m)
    const double JUPITER_AVG=7.785e11;

    //average distance of Sun and the inner border of the Oort cloud (m)
    const double ASTEROID_AVG=1e13;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

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

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

    //2e3 m/s sets a relatively stable orbit for the asteroid
    //random perturbation will be added for this value
    //random number generation
    std::random_device rd{};
    std::mt19937 gen(rd());
    std::normal_distribution<double> distr(-500.,500.);
    const double ASTEROID_V_perturbation=distr(gen);
    const vector3<double> ASTEROID_V=(ASTEROID_V_perturbation+2e3)*perp_unit_vec(ASTEROID_R);
    
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

    //RHS for Sun-Earth-Asteroid
    auto armageddon3=[&](double t,state3<double> s)->state3<double>{return
    {
        s.SUN_V,

        -G*EARTH_M*(s.SUN_R-s.EARTH_R)/std::pow(length(s.SUN_R-s.EARTH_R),3)
        -G*ASTEROID_M*(s.SUN_R-s.ASTEROID_R)/std::pow(length(s.SUN_R-s.ASTEROID_R),3),

        s.EARTH_V,

        -G*SUN_M*(s.EARTH_R-s.SUN_R)/std::pow(length(s.EARTH_R-s.SUN_R),3)
        -G*ASTEROID_M*(s.EARTH_R-s.ASTEROID_R)/std::pow(length(s.EARTH_R-s.ASTEROID_R),3),

        s.ASTEROID_V,

        -G*SUN_M*(s.ASTEROID_R-s.SUN_R)/std::pow(length(s.ASTEROID_R-s.SUN_R),3)
        -G*EARTH_M*(s.ASTEROID_R-s.EARTH_R)/std::pow(length(s.ASTEROID_R-s.EARTH_R),3)
    };}; 

    //RHS for Sun-Earth-Jupiter-asteroid
    auto armageddon4=[&](double t,state4<double> s)->state4<double>{return
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
        -G*JUPITER_M*(s.ASTEROID_R-s.JUPITER_R)/std::pow(length(s.ASTEROID_R-s.JUPITER_R),3)
    };};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

    const state4<double> y04{SUN_R,SUN_V,
                    EARTH_R,EARTH_V,
                    JUPITER_R,JUPITER_V,
                    ASTEROID_R,ASTEROID_V};

    const state3<double> y03{SUN_R,SUN_V,
                    EARTH_R,EARTH_V,
                    ASTEROID_R,ASTEROID_V};


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

    //to file
    auto to_file4=[&](double t,state4<double> const& s,double dt)
    {
        std::ofstream file;
        file.open("armageddon4.txt",std::fstream::app);
        file<<s.SUN_R<<" ";
        file<<s.EARTH_R<<" ";
        file<<s.JUPITER_R<<" ";
        file<<s.ASTEROID_R<<" ";
        //file<<length(s.SUN_R-s.ASTEROID_R)<<" ";
        file<<dt<<" ";
        file<<t<<"\n";
    };

    auto to_file3=[&](double t,state3<double> const& s,double dt)
    {
        std::ofstream file;
        file.open("armageddon3.txt",std::fstream::app);
        file<<s.SUN_R<<" ";
        file<<s.EARTH_R<<" ";
        file<<s.ASTEROID_R<<" ";
        //file<<length(s.SUN_R-s.ASTEROID_R)<<" ";
        file<<dt<<" ";
        file<<t<<"\n";
    };
    
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

    //checking  for collisions
    auto col3=[&](state3<double> s)
    {
        double lEA=length(s.EARTH_R-s.ASTEROID_R);
        double lSA=length(s.SUN_R-s.ASTEROID_R);
        if(lEA<6e6)
        {
            std::cout<<"Collision will happen with the Earth.\nCall Bruce Willis ASAP.\nEnd of simulation."<<std::endl;
            return true;
        }
        if(lSA<7e8)
        {
            std::cout<<"Collision will happen with the Sun.\nGoodbye Mr. Asteroid.\nEnd of simulation."<<std::endl;
            return true;
        }
        return false;
    };
    auto col4=[&](state4<double> s)
    {
        double lEA=length(s.EARTH_R-s.ASTEROID_R);
        double lSA=length(s.SUN_R-s.ASTEROID_R);
        double lJA=length(s.JUPITER_R-s.ASTEROID_R);
        if(lEA<6e6)
        {
            std::cout<<"Collision will happen with the Earth.\nCall Bruce Willis ASAP.\nEnd of simulation."<<std::endl;
            return true;
        }
        if(lJA<7e7)
        {
            std::cout<<"Collision will happen with Jupiter.\nThank you bro.\nEnd of simulation."<<std::endl;
            return true;
        }
        if(lSA<7e8)
        {
            std::cout<<"Collision will happen with the Sun.\nGoodbye Mr. Asteroid.\nEnd of simulation."<<std::endl;
            return true;
        }
        return false;
    };


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

    //integration of ODEs
    const double t0=0.;
    const double t1=1e9;
    const double h=1e3;
    const double delta0=1e-6;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

    //clock0
    auto clock0=std::chrono::high_resolution_clock::now();

    //RK4 for 4 planets
    solve_RK4_adapt(y04,t0,t1,h,armageddon4,to_file4,delta0,col4);

    //clock1
    auto clock1=std::chrono::high_resolution_clock::now();

    //"measuring" time
    double time_clock4=(static_cast<std::chrono::duration<double,std::milli>>(clock1-clock0)).count();
    std::cout<<"Overall integration time for 4 planets: "<<time_clock4<<" ms."<<std::endl;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

    //clock2
    auto clock2=std::chrono::high_resolution_clock::now();

    //RK4 for 3 planets
    solve_RK4_adapt(y03,t0,t1,h,armageddon3,to_file3,delta0,col3);

    //clock3
    auto clock3=std::chrono::high_resolution_clock::now();

    //"measuring" time
    double time_clock3=(static_cast<std::chrono::duration<double,std::milli>>(clock3-clock2)).count();
    std::cout<<"Overall integration time for 3 planets: "<<time_clock3<<" ms."<<std::endl;

    return 0;
}
