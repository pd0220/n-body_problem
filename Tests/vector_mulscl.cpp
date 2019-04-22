#include "../vector.hh"

//test for multiplication by scalar operators (*,*=)
int main(int,char**)
{
    //(*)
    //test vector will be v=(1.0,2.0)
    vector<double> v{1.,2.};
    vector<double> v_ref1{v};
    vector<double> v_ref2{v};
    double scl=2.5;
    //division result is w*scl=(2.5,5.0)
    vector<double> result{2.5,5.};

    //const& (from right)
    vector<double> v_mulscl1=v*scl;
    vec_eq(result,v_mulscl1);

    //&& (from right)
    vector<double> v_mulscl2=std::move(v_ref1)*scl;
    vec_eq(result,v_mulscl2);
    vec_if_zero(v_ref1);

    //const& (from left)
    vector<double> v_mulscl3=scl*v;
    vec_eq(result,v_mulscl3);

    //&& (from left)
    vector<double> v_mulscl4=scl*std::move(v_ref2);
    vec_eq(result,v_mulscl4);
    vec_if_zero(v_ref2);

    //(*=)
    v*=scl;
    vec_eq(result,v);

    return 0;
}
