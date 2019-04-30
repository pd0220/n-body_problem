#include "vector3.hh"
#include <array>

//state for given 4 planet
//positions and velocities in a 3-dimensional space (r and v vectors)
//used in RK4 method
template<typename T>
struct state_vector
{
    //in order: SUN_R,SUN_V,EARTH_R,EARTH_V,JUPITER_R,JUPITER_V,ASTEROID_R,ASTEROID_V;
    std::array<vector3<T>,8> state;
};