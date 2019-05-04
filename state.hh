#include "vector3.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//state for 3 planets
//positions and velocities in a 3-dimensional space (r and v vectors) with essential operators only
//used in RK4 method
template<typename T>
struct state3
{
    //in the following order: SUN_R, SUN_V, EARTH_R, EARTH_V, JUPITER_R, JUPITER_V, ASTEROID_R, ASTEROID_V (8 vectors in all)
    vector3<T> SUN_R,SUN_V,EARTH_R,EARTH_V,ASTEROID_R,ASTEROID_V;
    //assignment operator (=)
    auto& operator=(state3 const& s)
    {
        SUN_R=s.SUN_R;
        SUN_V=s.SUN_V;
        EARTH_R=s.EARTH_R;
        EARTH_V=s.EARTH_V;
        ASTEROID_R=s.ASTEROID_R;
        ASTEROID_V=s.ASTEROID_V;
        return *this;
    }
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//state for 4 planets
//positions and velocities in a 3-dimensional space (r and v vectors) with essential operators only
//used in RK4 method
template<typename T>
struct state4
{
    //in the following order: SUN_R, SUN_V, EARTH_R, EARTH_V, JUPITER_R, JUPITER_V, ASTEROID_R, ASTEROID_V (8 vectors in all)
    vector3<T> SUN_R,SUN_V,EARTH_R,EARTH_V,JUPITER_R,JUPITER_V,ASTEROID_R,ASTEROID_V;
    //assignment operator (=)
    auto& operator=(state4 const& s)
    {
        SUN_R=s.SUN_R;
        SUN_V=s.SUN_V;
        EARTH_R=s.EARTH_R;
        EARTH_V=s.EARTH_V;
        JUPITER_R=s.JUPITER_R;
        JUPITER_V=s.JUPITER_V;
        ASTEROID_R=s.ASTEROID_R;
        ASTEROID_V=s.ASTEROID_V;
        return *this;
    }
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//summation (+)
template<typename T>
state3<T> operator+(state3<T> const& s1,state3<T> const& s2)
{
    return state3<T>
    {
        s1.SUN_R+s2.SUN_R,
        s1.SUN_V+s2.SUN_V,
        s1.EARTH_R+s2.EARTH_R,
        s1.EARTH_V+s2.EARTH_V,
        s1.ASTEROID_R+s2.ASTEROID_R,
        s1.ASTEROID_V+s2.ASTEROID_V
    };
}
template<typename T>
state4<T> operator+(state4<T> const& s1,state4<T> const& s2)
{
    return state4<T>
    {               
        s1.SUN_R+s2.SUN_R,
        s1.SUN_V+s2.SUN_V,
        s1.EARTH_R+s2.EARTH_R,
        s1.EARTH_V+s2.EARTH_V,
        s1.JUPITER_R+s2.JUPITER_R,
        s1.JUPITER_V+s2.JUPITER_V,
        s1.ASTEROID_R+s2.ASTEROID_R,
        s1.ASTEROID_V+s2.ASTEROID_V
    };
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//substraction (-)
template<typename T>
state3<T> operator-(state3<T> const& s1,state3<T> const& s2)
{
    return state3<T>
    {   
        s1.SUN_R-s2.SUN_R,
        s1.SUN_V-s2.SUN_V,
        s1.EARTH_R-s2.EARTH_R,
        s1.EARTH_V-s2.EARTH_V,
        s1.ASTEROID_R-s2.ASTEROID_R,
        s1.ASTEROID_V-s2.ASTEROID_V
    };
}
template<typename T>
state4<T> operator-(state4<T> const& s1,state4<T> const& s2)
{
    return state4<T>
    {
        s1.SUN_R-s2.SUN_R,
        s1.SUN_V-s2.SUN_V,
        s1.EARTH_R-s2.EARTH_R,
        s1.EARTH_V-s2.EARTH_V,
        s1.JUPITER_R-s2.JUPITER_R,
        s1.JUPITER_V-s2.JUPITER_V,
        s1.ASTEROID_R-s2.ASTEROID_R,
        s1.ASTEROID_V-s2.ASTEROID_V
    };
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//multiplication by scalar (*) (from right)
template<typename T>
state3<T> operator*(state3<T> const& s,T const& scl)
{
    return state3<T>
    {
        s.SUN_R*scl,
        s.SUN_V*scl,
        s.EARTH_R*scl,
        s.EARTH_V*scl,
        s.ASTEROID_R*scl,
        s.ASTEROID_V*scl
    };
}
template<typename T>
state4<T> operator*(state4<T> const& s,T const& scl)
{
    return state4<T>
    {
        s.SUN_R*scl,
        s.SUN_V*scl,
        s.EARTH_R*scl,
        s.EARTH_V*scl,
        s.JUPITER_R*scl,
        s.JUPITER_V*scl,
        s.ASTEROID_R*scl,
        s.ASTEROID_V*scl
    };
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//multiplication by scalar (*) (from left)
template<typename T>
state3<T> operator*(T const& scl,state3<T> const& s)
{
    return state3<T>
    {
        scl*s.SUN_R,
        scl*s.SUN_V,
        scl*s.EARTH_R,
        scl*s.EARTH_V,
        scl*s.ASTEROID_R,
        scl*s.ASTEROID_V
    };
}
template<typename T>
state4<T> operator*(T const& scl,state4<T> const& s)
{
    return state4<T>
    {
        scl*s.SUN_R,
        scl*s.SUN_V,
        scl*s.EARTH_R,
        scl*s.EARTH_V,
        scl*s.JUPITER_R,
        scl*s.JUPITER_V,
        scl*s.ASTEROID_R,
        scl*s.ASTEROID_V
    };
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//division by scalar (/)
template<typename T>
state3<T> operator/(state3<T> const& s,T const& scl)
{
    return state3<T>
    {
        s.SUN_R/scl,
        s.SUN_V/scl,
        s.EARTH_R/scl,
        s.EARTH_V/scl,
        s.ASTEROID_R/scl,
        s.ASTEROID_V/scl
    };
}
template<typename T>
state4<T> operator/(state4<T> const& s,T const& scl)
{
    return state4<T>
    {
        s.SUN_R/scl,
        s.SUN_V/scl,
        s.EARTH_R/scl,
        s.EARTH_V/scl,
        s.JUPITER_R/scl,
        s.JUPITER_V/scl,
        s.ASTEROID_R/scl,
        s.ASTEROID_V/scl
    };
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//normalize state vector
template<typename T>
T norm(state3<T> const& s)
{
    return (T)std::sqrt(sq_length(s.SUN_R)+sq_length(s.SUN_V)
          +sq_length(s.EARTH_R)+sq_length(s.EARTH_V)
          +sq_length(s.ASTEROID_R)+sq_length(s.ASTEROID_V))/(T)18;
}
template<typename T>
T norm(state4<T> const& s)
{
    return (T)std::sqrt(sq_length(s.SUN_R)+sq_length(s.SUN_V)
          +sq_length(s.EARTH_R)+sq_length(s.EARTH_V)
          +sq_length(s.JUPITER_R)+sq_length(s.JUPITER_V)
          +sq_length(s.ASTEROID_R)+sq_length(s.ASTEROID_V))/(T)24;
}