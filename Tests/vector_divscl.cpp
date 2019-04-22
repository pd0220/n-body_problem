#include "../vector.hh"

//test for division by scalar operators (/,/=)
int main(int,char**)
{
    //(/)
    //test vector will be v=(1.0,2.0)
    vector<double> v{1.,2.};
    vector<double> v_ref1{v};
    double scl=0.5;
    //division result is w/scl=(2.0,4.0)
    vector<double> result{2.,4.};

    //const&
    vector<double> v_divscl1=v/scl;
    vec_eq(result,v_divscl1);

    //&&
    vector<double> v_divscl2=std::move(v_ref1)/scl;
    vec_eq(result,v_divscl2);
    vec_if_zero(v_ref1);

    //(/=)
    v/=scl;
    vec_eq(result,v);

    return 0;
}
