#include "../vector.hh"

//test for substraction operators (-,-=)
int main(int,char**)
{
    //(-)
    //test vectors will be v=(1.0,2.0) and w=(3.0,4.0)
    vector<double> v{1.,2.};
    vector<double> v_ref1{v};
    vector<double> v_ref2{v};
    vector<double> w{3.,4.};
    vector<double> w_ref1{w};
    vector<double> w_ref2{w};
    //substraction result is w-v=(2.0,2.0)
    vector<double> result{2.,2.};

    //const&-const&
    vector<double> v_sub1=w-v;
    vec_eq(result,v_sub1);

    //const&-&&
    vector<double> v_sub2=w-std::move(v_ref1);
    vec_eq(result,v_sub2);
    vec_if_zero(v_ref1);

    //&&-const&
    vector<double> v_sub3=std::move(w_ref1)-v;
    vec_eq(result,v_sub3);
    vec_if_zero(w_ref1);

    //&&-&&
    vector<double> v_sub4=std::move(w_ref2)-std::move(v_ref2);
    vec_eq(result,v_sub4);
    vec_if_zero(w_ref1);

    //(-=)
    w-=v;
    vec_eq(result,w);

    return 0;
}