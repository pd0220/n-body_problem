#include "../vector.hh"

//test for special vector functions: length, squared length and normalizing
int main(int,char**)
{
    //test vector will be v=(1.0,2.0)
    vector<double> v{1.,2.};

    //length of v is |v|=sqrt(5)
    double v_length=length(v);
    if(std::abs(v_length-std::sqrt(5))>1e-10)
    {
        std::cout<<"Lengths are not equal."<<std::endl;
        std::exit(-1);
    }

    //squared length of v is |v|^2=5
    double v_sq_length=5.;
    if(std::abs(v_sq_length-sq_length(v))>1e-10)
    {
        std::cout<<"Squared lengths are not equal."<<std::endl;
        std::exit(-1);
    }

    //normalized v is v_norm=(0.447213,0.894427)
    vector<double> v_norm{0.447213,0.894427};
    vec_eq(v_norm,norm(v));

    return 0;
}