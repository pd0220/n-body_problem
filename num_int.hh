#include <fstream>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//adaptive Cash-Karp method implementation for numerical integration
//via one RK5 and one RK4 step
template<typename State,typename T,typename RHS,typename Callback,typename Collision,typename Dist>
auto solve_RK4_adapt(State y0,T t0,T t1,T h,RHS f,Callback cb,T const& Delta0,Collision col,Dist dist)
{
    //setting initial values
    T t=t0;
    State y=y0;
    T i=(T)0;
    T path=(T)1e20;
    bool collision_marker=false;
    //adaptive steps until reaching integration boundary
    while(t<t1)
    {
        State k1,k2,k3,k4,k5,k6;
        T Delta=(T)0.;

        do
        {
            //fifth order step
            k1=h*f(t,y);
            k2=h*f(t+h*(T)1/5,y+(T)1/5*k1);
            k3=h*f(t+h*(T)3/10,y+(T)3/40*k1+(T)9/40*k2);
            k4=h*f(t+h*(T)3/5,y+(T)3/10*k1-(T)9/10*k2+(T)6/5*k3);
            k5=h*f(t+h,y-(T)11/54*k1+(T)5/2*k2-(T)70/27*k3+(T)35/27*k4);
            k6=h*f(t+h*(T)7/8,y+(T)1631/55296*k1+(T)175/512*k2+(T)575/13824*k3+(T)44275/110592*k4+(T)253/4096*k5);  

            //error estimation
            State Delta_state=((T)37/378-(T)2825/27648)*k1+
                              ((T)250/621-(T)18575/48384)*k3+
                              ((T)125/594-(T)13525/55296)*k4+
                              ((T)-277/14336)*k5+
                              ((T)512/1771-(T)1/4)*k6;

            Delta=norm(Delta_state);
            //Delta=length(Delta_state);
            h=h*std::pow(std::abs(Delta0/Delta),0.2);    

        }while(Delta0<Delta);

        h=h*std::pow(std::abs(Delta0/Delta),0.25);

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

        y=y+(T)37/378*k1+(T)250/621*k3+(T)125/594*k4+(T)512/1771*k6;
        t=t+h;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......        
    
        //simple loading screen
        if(std::abs(i*t1/100-t)<h)
        {
            std::cout<<"Progress: "<<i<<"%"<<std::endl;
            i++;
            if(i>101)
            {
                std::cout<<"ERROR occured in loading screen."<<std::endl;
            }
        }
    
        //inner check functions
        path=dist(y,path);
        cb(t,y,h);
        collision_marker=col(y);
        if(collision_marker)
        {
            break;
        }
    }
    return path;
}
