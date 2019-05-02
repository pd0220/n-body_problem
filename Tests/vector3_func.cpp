#include "../vector3.hh"

//test for length and squared length functions
int main(int,char**)
{
    //test vector will be v=(1.0,2.0,1.5)
    vector3<double> v{1.,2.,1.5};
    //its length is 2.69258
    //its squared length is 7.24999
    double l=2.69258;
    double sq_l=7.24998;

    if(std::abs(l-length(v))>1e5)
    {
        std::cout<<"ERROR in length of vector for vector3."<<std::endl;
        std::exit(-1);
    }

    if(std::abs(sq_l-sq_length(v))>1e5)
    {
        std::cout<<"ERROR in squared length assignment operator for vector3."<<std::endl;
        std::exit(-1);
    }

    return 0;

}