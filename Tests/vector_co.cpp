#include "../vector.hh"

//test for vector constructors
int main(int,char**)
{
    //default
    vector<double> v0;
    if(v0.size()!=0)
    {
        std::cout<<"ERROR\nDefault constructor."<<std::endl;
        std::exit(-1);
    }

    //initializer list
    vector<double> w0={1.,2.};
    if(w0[0]!=1. || w0[1]!=2. || w0.size()!=2)
    {
        std::cout<<"ERROR\nInitializer list constructor."<<std::endl;
        std::exit(-1);
    }

    //copy
    vector<double> w1{1.,2.};
    vector<double> v1{w1};
    vec_eq(w1,v1);

    //move
    vector<double> w2{w1};
    vector<double> v2{std::move(w2)};
    vec_eq(w1,v2);
    vec_if_zero(w2);

    //assignment
    vector<double> w3{w1};
    vector<double> v3;
    v3=w3;
    vec_eq(w3,v3);

    //move assignment
    vector<double> w4{w1};
    vector<double> v4;
    v4=std::move(w4);
    vec_eq(v4,w1);
    vec_if_zero(w4);

    return 0;
}