#include "../vector3.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//test for substraction operators (-,-=) for vector3 structure
int main(int,char**)
{
    //test vectors will be v1=(1.0,2.0,1.5) and v2=(1.5,2.0,1.0)
    vector3<double> v1{1.,2.,1.5};
    vector3<double> v2{1.5,2.,1.};
    //v1-v2=v3=(-0.5,0.0,0.5)
    vector3<double> v3{-0.5,0.0,0.5};
    vector3<double> v_test=v1-v2;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

    if(std::abs(v3.x-v_test.x)>1e5 || std::abs(v3.y-v_test.y)>1e5 || std::abs(v3.z-v_test.z)>1e5)
    {
        std::cout<<"ERROR in substraction operator for vector3."<<std::endl;
        std::exit(-1);
    }

    v1-=v2;

    if(std::abs(v3.x-v1.x)>1e5 || std::abs(v3.y-v1.y)>1e5 || std::abs(v3.z-v1.z)>1e5)
    {
        std::cout<<"ERROR in substraction assignment operator for vector3."<<std::endl;
        std::exit(-1);
    }

    return 0;

}