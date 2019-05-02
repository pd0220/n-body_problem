#include "../vector3.hh"

//test for multiplication by scalar operators (*,*=) for vector3 structure
int main(int,char**)
{
    //test vector will be v=(1.0,2.0,1.5)
    vector3<double> v{1.,2.,1.5};
    double scl=2.5;
    //v*scl=scl*v=v_res=(2.5,5.0,3.75)
    vector3<double> v_res{2.5,5.,3.75};
    vector3<double> v_test_right=v*scl;
    vector3<double> v_test_left=scl*v;

    if(std::abs(v_res.x-v_test_right.x)>1e5 || std::abs(v_res.y-v_test_right.y)>1e5 || std::abs(v_res.z-v_test_right.z)>1e5)
    {
        std::cout<<"ERROR in multiplication (from right) by scalar operator for vector3."<<std::endl;
        std::exit(-1);
    }

    if(std::abs(v_res.x-v_test_left.x)>1e5 || std::abs(v_res.y-v_test_left.y)>1e5 || std::abs(v_res.z-v_test_left.z)>1e5)
    {
        std::cout<<"ERROR in multiplication (from left) by scalar operator for vector3."<<std::endl;
        std::exit(-1);
    }

    v*=scl;

    if(std::abs(v_res.x-v.x)>1e5 || std::abs(v_res.y-v.y)>1e5 || std::abs(v_res.z-v.z)>1e5)
    {
        std::cout<<"ERROR in multiplication by scalar assignment operator for vector3."<<std::endl;
        std::exit(-1);
    }

    return 0;

}