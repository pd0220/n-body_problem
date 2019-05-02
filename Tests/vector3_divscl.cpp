#include "../vector3.hh"

//test for division by scalar operators (/,/=) for vector3 structure
int main(int,char**)
{
    //test vector will be v=(1.0,2.0,1.5)
    vector3<double> v{1.,2.,1.5};
    double scl=0.5;
    //v/scl=v_res=(2.0,4.0,3.0)
    vector3<double> v_res{2.,4.,3.};
    vector3<double> v_test=v/scl;

    if(std::abs(v_res.x-v_test.x)>1e5 || std::abs(v_res.y-v_test.y)>1e5 || std::abs(v_res.z-v_test.z)>1e5)
    {
        std::cout<<"ERROR in division by scalar operator for vector3."<<std::endl;
        std::exit(-1);
    }

    v/=scl;

    if(std::abs(v_res.x-v.x)>1e5 || std::abs(v_res.y-v.y)>1e5 || std::abs(v_res.z-v.z)>1e5)
    {
        std::cout<<"ERROR in division by scalar assignment operator for vector3."<<std::endl;
        std::exit(-1);
    }

    return 0;

}