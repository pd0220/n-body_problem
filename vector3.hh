#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <random>

//3-dimensional vector structure
template<typename T>
struct vector3
{
    T x=(T)0,y=(T)0,z=(T)0;
    //assignment operator (=)
    auto& operator=(vector3<T> const& v)
    {
        x=v.x;
        y=v.y;
        z=v.z;
        return *this;
    }
    //summation assignment operator (+=)
    auto& operator+=(vector3<T> const& v)
    {
        x+=v.x;
        y+=v.y;
        z+=v.z;
        return *this;
    }
    //substraction assignment operator (-=)
    auto& operator-=(vector3<T> const& v)
    {
        x-=v.x;
        y-=v.y;
        z-=v.z;
        return *this;
    }
    //multiplication by scalar assignment operator (*=)
    auto& operator*=(T const& scl)
    {
        x*=scl;
        y*=scl;
        z*=scl;
        return *this;
    }
    //division by scalar assignment operator (/=)
    auto& operator/=(T const& scl)
    {
        x/=scl;
        y/=scl;
        z/=scl;
        return *this;
    }
};

//output stream
template<typename T>
std::ostream& operator<<(std::ostream& o,vector3<T> const& v)
{
    o<<v.x<<" "<<v.y<<" "<<v.z;
    return o;
}

//input stream
template<typename T>
std::istream& operator>>(std::istream& i,vector3<T> & v)
{
    auto restore_stream=[state=i.rdstate(),pos=i.tellg(),&i](){i.seekg(pos);i.setstate(state);};
    
    std::string tmp;
    std::getline(i,tmp);
    std::stringstream ii(tmp);

    std::getline(ii,tmp,' ');
    if(tmp.size()==0){restore_stream();return i;}
    std::stringstream vx_ss(tmp);
    vx_ss>>v.x;

    std::getline(ii,tmp,' ');
    if(tmp.size()==0){restore_stream();return i;}
    std::stringstream vy_ss(tmp);
    vy_ss>>v.y;

    std::getline(ii,tmp);
    if(tmp.size()==0){restore_stream();return i;}
    std::stringstream vz_ss(tmp);
    vz_ss>>v.z;

    return i;
}

//summation of vectors (+)
template<typename T>
vector3<T> operator+(vector3<T> const& v1,vector3<T> const& v2)
{
    return vector3<T>{v1.x+v2.x,v1.y+v2.y,v1.z+v2.z};
}

//substraction of vectors (-)
template<typename T>
vector3<T> operator-(vector3<T> const& v1,vector3<T> const& v2)
{
    return vector3<T>{v1.x-v2.x,v1.y-v2.y,v1.z-v2.z};
}

//multiplication by scalar (*) (from left)
template<typename T>
vector3<T> operator*(T const& scl,vector3<T> const& v)
{
    return vector3<T>{scl*v.x,scl*v.y,scl*v.z};
}

//multiplication by scalar (*) (from right)
template<typename T>
vector3<T> operator*(vector3<T> const& v,T const& scl)
{
    return vector3<T>{v.x*scl,v.y*scl,v.z*scl};
}

//division by scalar (/)
template<typename T>
vector3<T> operator/(vector3<T> const& v,T const& scl)
{
    return vector3<T>{v.x/scl,v.y/scl,v.z/scl};
}

//squared length of vector
template<typename T>
T sq_length(vector3<T> const& v)
{
    return v.x*v.x+v.y*v.y+v.z*v.z;
}

//length of vector
template<typename T>
T length(vector3<T> const& v)
{
    return std::sqrt(sq_length(v));
}

//random vector with given length (radius of circular orbit)
//will be used to generate randomly chosen initial conditions for planets
template<typename T>
vector3<T> rand_vec_2D(T R)
{
    //random number generation
    std::random_device rd{};
    std::mt19937 gen(rd());
    std::normal_distribution<T> polar((T)0,(T)2*M_PI);
    //polar angle
    T phi=polar(gen);
    return R*vector3<T>{std::cos(phi),std::sin(phi),(T)0};
}

//random vector with given length (radius of circular orbit)
//will be used to generate randomly chosen initial conditions for the asteroid
template<typename T>
vector3<T> rand_vec_3D(T R)
{
    //random number generation
    std::random_device rd{};
    std::mt19937 gen(rd());
    std::normal_distribution<T> polar((T)0,(T)2*M_PI);
    std::normal_distribution<T> azimuthal((T)0,(T)M_PI);
    //polar angle
    T phi=polar(gen);
    //azi
    T theta=azimuthal(gen);

    T sin_theta=std::sin(theta);
    T cos_theta=std::cos(theta);
    T sin_phi=std::sin(phi);
    T cos_phi=std::cos(phi);

    return R*vector3<T>{sin_theta*cos_phi,sin_theta*sin_phi,cos_theta};
}