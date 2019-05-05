#include "../vector3.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//test for length, squared length, normalize, cross product finding third power for the length of a difference vector and perpendicular vector calculation functions
int main(int,char**)
{
    //test vectors will be v=(1.0,2.0,1.5) and w=(1.0,2.0,1.0)
    vector3<double> v{1.,2.,1.5};
    vector3<double> w{1.,2.,1.};
    vector3<double> unit=norm(v);
    vector3<double> unit_perp=perp_unit_vec(v);
    //third power of |v-w| is 
    //its length is 2.69258
    //its squared length is 7.24999
    double l=2.69258;
    double sq_l=7.24998;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

    if(std::abs(l-length(v))>1e-4)
    {
        std::cout<<"ERROR in length of vector for vector3."<<std::endl;
        std::exit(-1);
    }

    if(std::abs(sq_l-sq_length(v))>1e-4)
    {
        std::cout<<"ERROR in squared length assignment operator for vector3."<<std::endl;
        std::exit(-1);
    }

    if(std::abs(length(unit)-1.)>1e-4)
    {
        std::cout<<"ERROR in normalizing vectors for vector3."<<std::endl;
        std::exit(-1);
    }

    vector3<double> cross_test=cross_prod(v,w);
    vector3<double> cross_ref{-1.,0.5,0.};

    if(std::abs(cross_test.x-cross_ref.x)>1e-4 || std::abs(cross_test.y-cross_ref.y)>1e-4 || std::abs(cross_test.z-cross_ref.z)>1e-4)
    {
        std::cout<<"ERROR in cross product"<<std::endl;
        std::exit(-1);
    }

    if((v.x*unit_perp.x+v.y*unit_perp.y+v.z*unit_perp.z)>1e-4 || std::abs(length(unit_perp)-1.)>1e-4)
    {
        std::cout<<"ERROR in calculating perpendicular unit vector."<<std::endl;
        std::exit(-1);
    }

    if(std::abs(cube_length_diff(v,w)-0.125)>1e-4)
    {
        std::cout<<"ERROR in finding third power for the length of a difference vector."<<std::endl;
        std::exit(-1);
    }

    return 0;

}