#include "../vector.hh"

//test for addition operators (+,+=)
int main(int,char**)
{
    //(+)
    //test vectors will be v=(1.0,2.0) and w=(3.0,4.0)
    vector<double> v{1.,2.};
    vector<double> v_ref1{v};
    vector<double> v_ref2{v};
    vector<double> w{3.,4.};
    vector<double> w_ref1{w};
    vector<double> w_ref2{w};
    //addition result is v+w=(4.0,6.0)
    vector<double> result{4.,6.};

    //const&-const&
    vector<double> v_add1=v+w;
    vec_eq(result,v_add1);

    //const&-&&
    vector<double> v_add2=v+std::move(w_ref1);
    vec_eq(result,v_add2);
    vec_if_zero(w_ref1);

    //&&-const&
    vector<double> v_add3=std::move(v_ref1)+w;
    vec_eq(result,v_add3);
    vec_if_zero(v_ref1);

    //&&-&&
    vector<double> v_add4=std::move(v_ref2)+std::move(w_ref2);
    vec_eq(result,v_add4);
    vec_if_zero(v_ref2);
    
    //(+=)
    v+=w;
    vec_eq(result,v);

    return 0;
}