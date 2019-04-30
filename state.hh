#include "vector3.hh"

//state for a given 4 planet
//positions and velocities in a 3-dimensional space (r and v vectors)
template<typename T>
struct state
{
    vector3<T> SUN_R;
    vector3<T> SUN_V;
    vector3<T> EARTH_R;
    vector3<T> EARTH_V;
    vector3<T> JUPITER_R;
    vector3<T> JUPITER_V;
    vector3<T> ASTEROID_R;
    vector3<T> ASTEROID_V;
};

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