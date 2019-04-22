#include <iostream>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <vector>
#include <initializer_list>
#include <string>
#include <sstream>

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
        std::transform(d1.cbegin(),d1.cend(),d2.cbegin(),f);
    }
    template<typename T1,typename T2,typename T3,typename F>
    void transform2(T1 const& d1,T2 const& d2,T3 & d3,F f)
    {
        std::transform_vec2(d1.cbegin(),d1.cend(),d2.cbegin(),d3.begin(),f);
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
    T const& operator[](int index)
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


