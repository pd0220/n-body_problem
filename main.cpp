#include "vector.hh"
#include "num_int.hh"

//main function
int main(int, char**)
{
    vector<double> v{1.,2.};
    std::cout<<length(v)<<std::endl;
    vector<double> w=norm(v);
    std::cout<<w<<std::endl;

    return 0;
}