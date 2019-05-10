#include "state.hh"
#include "num_int.hh"
#include <chrono>
#include <cstdio>

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

    //average distance of Sun and the asteroid (m)
    const double ASTEROID_AVG=2e12;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

    //initial conditions
    //distance (m)
    //velocity (m/s)
    const double Earth_vel=2.978e4;
    const double Jupiter_vel=1.3071e4; 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

    //RHS for Sun-Earth-Asteroid
    auto armageddon3=[&](double,state3<double> s)->state3<double>
    {
        double SunToEarth=cube_length_diff(s.SUN_R,s.EARTH_R);
        double SunToAsteroid=cube_length_diff(s.SUN_R,s.ASTEROID_R);
        double EarthToAsteroid=cube_length_diff(s.EARTH_R,s.ASTEROID_R);
        return
        {
            s.SUN_V,
            -G*(EARTH_M*(s.SUN_R-s.EARTH_R)/SunToEarth+ASTEROID_M*(s.SUN_R-s.ASTEROID_R)/SunToAsteroid),
            s.EARTH_V,
            -G*(SUN_M*(s.EARTH_R-s.SUN_R)/SunToEarth+ASTEROID_M*(s.EARTH_R-s.ASTEROID_R)/EarthToAsteroid),
            s.ASTEROID_V,
            -G*(SUN_M*(s.ASTEROID_R-s.SUN_R)/SunToAsteroid+EARTH_M*(s.ASTEROID_R-s.EARTH_R)/EarthToAsteroid)
        };
    };

    //RHS for Sun-Earth-Jupiter-asteroid
    auto armageddon4=[&](double,state4<double> s)->state4<double>
    {
        double SunToEarth=cube_length_diff(s.SUN_R,s.EARTH_R);
        double SunToAsteroid=cube_length_diff(s.SUN_R,s.ASTEROID_R);
        double EarthToAsteroid=cube_length_diff(s.EARTH_R,s.ASTEROID_R);
        double SunToJupiter=cube_length_diff(s.JUPITER_R,s.SUN_R);
        double JupiterToEarth=cube_length_diff(s.JUPITER_R,s.EARTH_R);
        double JupiterToAsteroid=cube_length_diff(s.JUPITER_R,s.ASTEROID_R);
        return
        {
            s.SUN_V,
            -G*(EARTH_M*(s.SUN_R-s.EARTH_R)/SunToEarth+JUPITER_M*(s.SUN_R-s.JUPITER_R)/SunToJupiter+ASTEROID_M*(s.SUN_R-s.ASTEROID_R)/SunToAsteroid),
            s.EARTH_V,
            -G*(SUN_M*(s.EARTH_R-s.SUN_R)/SunToEarth+JUPITER_M*(s.EARTH_R-s.JUPITER_R)/JupiterToEarth+ASTEROID_M*(s.EARTH_R-s.ASTEROID_R)/EarthToAsteroid),
            s.JUPITER_V,
            -G*(SUN_M*(s.JUPITER_R-s.SUN_R)/SunToJupiter+EARTH_M*(s.JUPITER_R-s.EARTH_R)/JupiterToEarth+ASTEROID_M*(s.JUPITER_R-s.ASTEROID_R)/JupiterToAsteroid),
            s.ASTEROID_V,
            -G*(SUN_M*(s.ASTEROID_R-s.SUN_R)/SunToAsteroid+EARTH_M*(s.ASTEROID_R-s.EARTH_R)/EarthToAsteroid+JUPITER_M*(s.ASTEROID_R-s.JUPITER_R)/JupiterToAsteroid)
        };
    };

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

    

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

    //to file
    auto to_file3=[&](double t,state3<double> const& s,double dt)
    {
        std::ofstream file;
        file.open("armageddon3.txt",std::fstream::app);
        file<<s.SUN_R<<" ";
        file<<s.EARTH_R<<" ";
        file<<s.ASTEROID_R<<" ";
        file<<dt<<" ";
        file<<t<<"\n";
    };
    auto to_file4=[&](double t,state4<double> const& s,double dt)
    {
        std::ofstream file;
        file.open("armageddon4.txt",std::fstream::app);
        file<<s.SUN_R<<" ";
        file<<s.EARTH_R<<" ";
        file<<s.JUPITER_R<<" ";
        file<<s.ASTEROID_R<<" ";
        file<<dt<<" ";
        file<<t<<"\n";
    };

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

    //checking  for collisions
    auto col3=[&](state3<double> s)
    {
        double lEA=length(s.EARTH_R-s.ASTEROID_R);
        double lSA=length(s.SUN_R-s.ASTEROID_R);
        //Earth-Moon
        if(lEA<10*3.844e8)
        {
            std::cout<<"Collision will happen with the Earth.\nCall Bruce Willis ASAP.\nEnd of simulation."<<std::endl;
            return true;
        }
        //Radius of Sun
        if(lSA<10*6.96342e8)
        {
            std::cout<<"Collision will happen with the Sun.\nGoodbye Mr. Asteroid.\nEnd of simulation."<<std::endl;
            return true;
        }
        //Asteroid moves too far
        if(lSA>5*ASTEROID_AVG)
        {
            std::cout<<"Asteroid left the system.\nWe are safe... until the next simulation."<<std::endl;
            return true;
        }
        return false;
    };
    auto col4=[&](state4<double> s)
    {
        double lEA=length(s.EARTH_R-s.ASTEROID_R);
        double lSA=length(s.SUN_R-s.ASTEROID_R);
        double lJA=length(s.JUPITER_R-s.ASTEROID_R);
        //Earth-Moon
        if(lEA<10*3.844e8)
        {
            std::cout<<"Collision will happen with the Earth.\nCall Bruce Willis ASAP.\nEnd of simulation."<<std::endl;
            return true;
        }
        //Jupiter-Callisto
        if(lJA<10*1.88e9)
        {
            std::cout<<"Collision will happen with Jupiter.\nThank you bro.\nEnd of simulation."<<std::endl;
            return true;
        }
        //Radius of Sun        
        if(lSA<10*6.96342e8)
        {
            std::cout<<"Collision will happen with the Sun.\nGoodbye Mr. Asteroid.\nEnd of simulation."<<std::endl;
            return true;
        }
        //Asteroid moves too far
        if(lSA>5*ASTEROID_AVG)
        {
            std::cout<<"Asteroid left the system.\nWe are safe... until the next simulation."<<std::endl;
            return true;
        }

        return false;
    };

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

    //do nothing
    auto nothing3=[&](double,state3<double>,double)
    {

    };
    auto nothing4=[&](double,state4<double>,double)
    {

    };

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

    //minimum distance statistics
    auto min3=[&](state3<double> s,double path)
    {
        double r=length(s.EARTH_R-s.ASTEROID_R);
        if(r<=path)
        {
            return r;
        }
        else
        {
            return path;
        }    
    };
    auto min4=[&](state4<double> s,double path)
    {
        double r=length(s.EARTH_R-s.ASTEROID_R);
        if(r<=path)
        {
            return r;
        }
        else
        {
            return path;
        }        
    };

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

    //integration of ODEs
    const double t0=0.;
    const double t1=2e9;
    const double h=1e4;
    const double delta0=1e-8;
    const int N=1000;
    int trg=0;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

    //reloading writable files
    std::remove("armageddon3.txt");
    std::remove("armageddon4.txt");
    std::remove("armageddon3.png");
    std::remove("armageddon4.png");
    std::remove("dist.txt");

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
    
    //N runs for 4 planets
    for(int i=0;i<N;i++)
    {
        //initial conditions
        //distance (m)
        //velocity (m/s)
        const vector3<double> SUN_R,SUN_V;
        const vector3<double> EARTH_R=rand_vec_2D(EARTH_AVG);
        const vector3<double> EARTH_V=Earth_vel*perp_unit_vec(EARTH_R);
        const vector3<double> JUPITER_R=rand_vec_2D(JUPITER_AVG);
        const vector3<double> JUPITER_V=Jupiter_vel*perp_unit_vec(JUPITER_R);
        const vector3<double> ASTEROID_R=rand_vec_3D(ASTEROID_AVG);
        
        //5e3 m/s sets a relatively stable orbit for the asteroid
        //random perturbation will be added for this value

        //random number generation
        std::random_device rd{};
        std::mt19937 gen(rd());
        std::normal_distribution<double> distr(-1500.,-2500.);
        const double ASTEROID_V_perturbation=distr(gen);
        const vector3<double> ASTEROID_V=(ASTEROID_V_perturbation+5e3)*perp_unit_vec(ASTEROID_R);

        //initial states
        const state3<double> y03{SUN_R,SUN_V,
                                 EARTH_R,EARTH_V,
                                 ASTEROID_R,ASTEROID_V};

        const state4<double> y04{SUN_R,SUN_V,
                                 EARTH_R,EARTH_V,
                                 JUPITER_R,JUPITER_V,
                                 ASTEROID_R,ASTEROID_V};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......                                

        //first run for illustrative figures
        if(i==0)
        {
            //clock0
            auto clock0=std::chrono::high_resolution_clock::now();

            //RK4 for 3 planets
            double path3=solve_RK4_adapt(y03,t0,t1,h,armageddon3,to_file3,delta0,col3,min3);

            //clock1
            auto clock1=std::chrono::high_resolution_clock::now();

            //"measuring" time
            double time_clock3=(static_cast<std::chrono::duration<double,std::milli>>(clock1-clock0)).count();
            std::cout<<"Overall integration time for the "<<i+1<<". 3 planet simulation with plotting figure: "<<time_clock3<<" ms."<<std::endl;

            //clock2
            auto clock2=std::chrono::high_resolution_clock::now();

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......                                

            //RK4 for 4 planets
            double path4=solve_RK4_adapt(y04,t0,t1,h,armageddon4,to_file4,delta0,col4,min4);

            //clock1
            auto clock3=std::chrono::high_resolution_clock::now();

            //"measuring" time
            double time_clock4=(static_cast<std::chrono::duration<double,std::milli>>(clock3-clock2)).count();
            std::cout<<"Overall integration time for the "<<i+1<<". 4 planet simulation with plotting figure: "<<time_clock4<<" ms."<<std::endl;
        /*
            //minimum distance 
            std::ofstream file;
            file.open("dist.txt",std::fstream::app);
            file<<i<<" ";
            file<<path3<<" ";
            file<<path4<<"\n";
        */
            if(path3>path4)
            {
                trg++;
            }
        }
        else  
        {
        
            //clock0
            auto clock0=std::chrono::high_resolution_clock::now();

            //RK4 for 3 planets
            double path3=solve_RK4_adapt(y03,t0,t1,h,armageddon3,nothing3,delta0,col3,min3);

            //clock1
            auto clock1=std::chrono::high_resolution_clock::now();

            //"measuring" time
            double time_clock3=(static_cast<std::chrono::duration<double,std::milli>>(clock1-clock0)).count();
            std::cout<<"Overall integration time for the "<<i+1<<". 3 planet simulation: "<<time_clock3<<" ms."<<std::endl;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

            //clock2
            auto clock2=std::chrono::high_resolution_clock::now();

            //RK4 for 4 planets
            double path4=solve_RK4_adapt(y04,t0,t1,h,armageddon4,nothing4,delta0,col4,min4);

            //clock1
            auto clock3=std::chrono::high_resolution_clock::now();

            //"measuring" time
            double time_clock4=(static_cast<std::chrono::duration<double,std::milli>>(clock3-clock2)).count();
            std::cout<<"Overall integration time for the "<<i+1<<". 4 planet simulation: "<<time_clock4<<" ms."<<std::endl;
        /*
            //minimum distance 
            std::ofstream file;
            file.open("dist.txt",std::fstream::app);
            file<<i<<" ";
            file<<path3<<" ";
            file<<path4<<"\n";
         */
            if(path3>path4)
            {
                trg++;
            }
        }
    }
    std::cout<<"Distance between Earth and the Asteroid was shorter in "<<trg<<" runs when Jupiter was not present out of "<<N<<" runs."<<std::endl;

    return 0;
}
