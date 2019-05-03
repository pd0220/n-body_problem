#include "../vector3.hh"

//test for length, squared length, normalize and perpendicular vector calculation functions
int main(int,char**)
{
    //test vector will be v=(1.0,2.0,1.5)
    vector3<double> v{1.,2.,1.5};
    vector3<double> unit=norm(v);
    vector3<double> unit_perp=perp_unit_vec(v);
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

    if(std::abs(length(unit)-1.)>1e5)
    {
        std::cout<<"ERROR in normalizing vectors for vector3."<<std::endl;
        std::exit(-1);
    }

    if((v.x*unit_perp.x+v.y*unit_perp.y+v.z+unit_perp.z)>1e5 || std::abs(length(unit_perp)-1.)>1e5)
    {
        std::cout<<"ERROR in calculating perpendicular unit vector."<<std::endl;
        std::exit(-1);
    }
    return 0;

}