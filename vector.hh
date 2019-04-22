#include <iostream>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <vector>
#include <initializer_list>

//general assumptions
//(1) operations will only happen between objects that has the same type
//(2) operations will only happen between equally sized vectors

//-------------------------------------------------------------------------------------------------------

//helper functions
namespace detail
{
    template<typename T1,typename T2,typename F>
    void transform_vec1(T1 const& d1,T2 & d2,F f)
    {
        std::transform(d1.cbegin(),d1.cend(),d2.begin(),f);
    }
    template<typename T1,typename T2,typename T3,typename F>
    void transform_vec2(T1 const& d1,T2 const& d2,T3 & d3,F f)
    {
        std::transform(d1.cbegin(),d1.cend(),d2.cbegin(),d3.begin(),f);
    }
}

//-------------------------------------------------------------------------------------------------------

//common lambdas
auto add=[&](auto const& x,auto const& y){return x+y;};
auto sub=[&](auto const& x,auto const& y){return x-y;};

//-------------------------------------------------------------------------------------------------------

//n-dimensional vector struct
template<typename T>
struct vector
{
    //variables
    std::vector<T> data;

    //constructors
    //default
    vector()=default;
    //copy
    vector(vector const&)=default;
    //move
    vector(vector &&)=default;
    //copy assignment
    vector<T> & operator=(vector const&)=default;
    //move assignment
    vector<T> & operator=(vector &&)=default;
    //from one-index function
    template<typename F>
    vector(F f,int size)
    {
        data.resize(static_cast<size_t>(size));
        for(int i{0};i<=size-1;i++)
        {
            data[i]=f(i);
        }
    }
    //from initializer list
    vector(std::initializer_list<T> const& list):data{list}{}

//-------------------------------------------------------------------------------------------------------

    //indexing
    T & operator[](int index)
    {
        return data[index];
    }
    T const& operator[](int index) const
    {
        return data[index];
    }

//-------------------------------------------------------------------------------------------------------

    //assignment operators
    //addition assignment of vectors (+=)
    vector<T> & operator+=(vector<T> const& v)
    {
        detail::transform_vec2(*this,v,*this,add);
        return *this;
    }
    //substraction assignment of vectors (-=)
    vector<T> & operator-=(vector<T> const& v)
    {
        detail::transform_vec2(*this,v,*this,sub);
        return *this;
    }
    //multiplication by scalar assignment operator (*=)
    vector<T> & operator*=(T const& scl)
    {
        detail::transform_vec1(*this,*this,[&](T const& x){return x*scl;});
        return *this;
    }
    //division by scalar assignment operator (/=)
    vector<T> & operator/=(T const& scl)
    {
        detail::transform_vec1(*this,*this,[&](T const& x){return x/scl;});
        return *this;
    }

//-------------------------------------------------------------------------------------------------------

    //further functions
    //number of elements
    int size() const
    {
        return static_cast<int>(data.size());
    }
    //end and begin of vector
    auto begin()
    {
        return data.begin();
    }
    auto cbegin() const
    {
        return data.cbegin();
    }
    auto end()
    {
        return data.end();
    }
    auto cend() const
    {
        return data.cend();
    }
};

//-------------------------------------------------------------------------------------------------------

//addition operator (+)
//4 types
template<typename T>
vector<T> operator+(vector<T> const& v1,vector<T> const& v2)
{
    vector<T> result;
    result.data.resize(v1.data.size());
    detail::transform_vec2(v1,v2,result,add);
    return result;
}
template<typename T>
vector<T> && operator+(vector<T> && v1,vector<T> const& v2)
{
    detail::transform_vec2(v1,v2,v1,add);
    return std::move(v1);
}
template<typename T>
vector<T> && operator+(vector<T> const& v1,vector<T> && v2)
{
    detail::transform_vec2(v1,v2,v2,add);
    return std::move(v2);
}
template<typename T>
vector<T> && operator+(vector<T> && v1,vector<T> && v2)
{
    detail::transform_vec2(v1,v2,v1,add);
    return std::move(v1);
}

//-------------------------------------------------------------------------------------------------------

//substraction operator (-)
//4 types
template<typename T>
vector<T> operator-(vector<T> const& v1,vector<T> const& v2)
{
    vector<T> result;
    result.data.resize(v1.data.size());
    detail::transform_vec2(v1,v2,result,sub);
    return result;
}
template<typename T>
vector<T> && operator-(vector<T> && v1,vector<T> const& v2)
{
    detail::transform_vec2(v1,v2,v1,sub);
    return std::move(v1);
} 
template<typename T>
vector<T> && operator-(vector<T> const& v1,vector<T> && v2)
{
    detail::transform_vec2(v1,v2,v2,sub);
    return std::move(v2);
}
template<typename T>
vector<T> && operator-(vector<T> && v1,vector<T> && v2)
{
    detail::transform_vec2(v1,v2,v1,sub);
    return std::move(v1);
}

//-------------------------------------------------------------------------------------------------------

//multiplication by scalar (*)
//2 types (from right)
template<typename T>
vector<T> operator*(vector<T> const& v,T const& scl)
{
    vector<T> result;
    result.data.resize(v.data.size());
    detail::transform_vec1(v,result,[&](T const& x){return x*scl;});
    return result;
}
template<typename T>
vector<T> && operator*(vector<T> && v,T const& scl)
{
    detail::transform_vec1(v,v,[&](T const& x){return x*scl;});
    return std::move(v);
}
//2 types (from left)
template<typename T>
vector<T> operator*(T const& scl,vector<T> const& v)
{
    vector<T> result;
    result.data.resize(v.data.size());
    detail::transform_vec1(v,result,[&](T const& x){return scl*x;});
    return result;
}
template<typename T>
vector<T> && operator*(T const& scl,vector<T> && v)
{
    detail::transform_vec1(v,v,[&](T const& x){return scl*x;});
    return std::move(v);
}

//-------------------------------------------------------------------------------------------------------

//division by scalar
//2 types
template<typename T>
vector<T> operator/(vector<T> const& v,T const& scl)
{
    vector<T> result;
    result.data.resize(v.data.size());
    detail::transform_vec1(v,result,[&](T const& x){return x/scl;});
    return result;
}
template<typename T>
vector<T> && operator/(vector<T> && v,T const& scl)
{
    detail::transform_vec1(v,v,[&](T const& x){return x/scl;});
    return std::move(v);
}

//-------------------------------------------------------------------------------------------------------

//length and squared length of a vector
template<typename T>
T sq_length(vector<T> const& v)
{
    return std::accumulate(v.cbegin(),v.cend(),static_cast<T>(0),[&](T const& a,T const& x){return a+x*x;});
}
template<typename T>
T length(vector<T> const& v)
{
    return std::sqrt(sq_length(v));
}

//-------------------------------------------------------------------------------------------------------

//normalizing vector
template<typename T>
vector<T> norm(vector<T> const& v)
{
    T L=length(v);
    if(L>0)
    {
        return v/L;
    }
    else
    {
        std::cout<<"Given vectors length is 0."<<std::endl;
        std::exit(-1);
    }
}
template<typename T>
vector<T> && norm(vector<T> && v)
{
    T L=length(v);
    return std::move(v/L);
}

//-------------------------------------------------------------------------------------------------------

//output stream
template<typename T>
std::ostream& operator<<(std::ostream& o,vector<T> const& v)
{
    int n=v.size();
    if(n>0)
    {
        for(int i{0};i<=n-2;i++)
        {
            o<<v[i]<<",";
        }
        o<<v[n-1];
    }
    return o;
}

//-------------------------------------------------------------------------------------------------------

//testing functions
//if two vectors are equal
template<typename T>
void vec_eq(vector<T> const& v1,vector<T> const& v2)
{
    if(v1.size()!=v2.size())
    {
        std::cout<<"ERROR\nNumber of vector elements are not equal."<<std::endl;
        std:exit(-1);
    }
    T eps=(T)1e-6;
    for(int i{0};i<=v1.size();i++)
    {
        if(std::abs(v1[i]-v2[i])>eps)
        {
            std::cout<<"ERRORS\nVectors are not equal."<<std::endl;
            std::exit(-1);
        }
    }
}

//check if vector size is 0
template<typename T>
void vec_if_zero(vector<T> const& v)
{
    if(v.size()!=0)
    {
        std::cout<<"ERROR\nSize of given vector is not 0."<<std::endl;
        std::exit(-1);
    }
}