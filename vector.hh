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
    void transform1(T1 const& d1,T2 & d2,F f)
    {
        std::transform(d1.cbegin(),d1.cend(),d2.cbegin(),f);
    }

    template<typename T1,typename T2,typename T3,typename F>
    void transform2(T1 const& d1,T2 const& d2,T3 & d3,F f)
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
    T const& operator[](int index)
    {
        return data[index];
    }

//-------------------------------------------------------------------------------------------------------

    //assignment operators
    



}


