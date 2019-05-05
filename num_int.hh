#include <fstream>
#include <array>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//adaptive RK4 method implementation for numerical integration
//via one RK4 and one RK5 step
template<typename State,typename T,typename RHS,typename Callback,typename Collision>
auto solve_RK4_adapt(State y0,T t0,T t1,T h,RHS f,Callback cb,T const& Delta0,Collision col)
{
    //setting initial values
    T t=t0;
    State y_test=y0;
    State y=y0;
    T i=(T)0;
    bool collision_marker=false;
    //adaptive steps until reaching integration boundary
    while(t<t1)
    {
        if(t+h>t1)
        {
            h=t1-t;
        }

        //fifth order step
        State k1=f(t,y_test);
        State k2=f(t+h*(T)1/5,y_test+(T)1/5*k1);
        State k3=f(t+h*(T)3/10,y_test+(T)3/40*k1+(T)9/40*k2);
        State k4=f(t+h*(T)3/5,y_test+(T)3/10*k1-(T)9/10*k2+(T)6/5*k3);
        State k5=f(t+h,y_test-(T)11/54*k1+(T)5/2*k2-(T)70/27*k3+(T)35/27*k4);
        State k6=f(t+h*(T)7/8,y_test+(T)1631/55296*k1+(T)175/512*k2+(T)575/13824*k3+(T)44275/110592*k4+(T)253/4096*k5);

        //error estimate
        State Delta_state=((T)37/378-(T)2825/27648)*k1+
                          ((T)250/621-(T)18575/48384)*k3+
                          ((T)125/594-(T)13525/55296)*k4+
                          ((T)-277/14336)*k5+
                          ((T)512/1771-(T)1/4)*k6;
                          
        T Delta=norm(Delta_state);

        //determine what stepsize to be used
        T h0=(T)0;
        if(Delta0>=Delta)
        {
            h0=h*std::pow(std::abs(Delta0/Delta),0.2);
        }
        else
        {
            h0=h*std::pow(std::abs(Delta0/Delta),0.25);
        }

        if(t+h0>t1)
        {
            h0=t1-t;
        }

        //one RK5 step with estimated stepsize
        State k1f=f(t,y);
        State k2f=f(t+h0*(T)1/5,y+(T)1/5*k1f);
        State k3f=f(t+h0*(T)3/10,y+(T)3/40*k1f+(T)9/40*k2f);
        State k4f=f(t+h0*(T)3/5,y+(T)3/10*k1f-(T)9/10*k2f+(T)6/5*k3f);
        State k5f=f(t+h0,y-(T)11/54*k1f+(T)5/2*k2f-(T)70/27*k3f+(T)35/27*k4f);
        State k6f=f(t+h0*(T)7/8,y+(T)1631/55296*k1f+(T)175/512*k2f+(T)575/13824*k3f+(T)44275/110592*k4f+(T)253/4096*k5f);

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

        //simple loading screen
        if(std::abs(i*t1/100-t)<h0)
        {
            std::cout<<"Progress: "<<i<<"%"<<std::endl;
            i++;
            if(i>101)
            {
                std::cout<<"ERROR occured in loading screen."<<std::endl;
            }
        }

        y=y+h0*((T)37/378*k1f+(T)250/621*k3f+(T)125/594*k4f+(T)512/1771*k6f);
        y_test=y;
        t=t+h0;
        cb(t,y,h0);
        collision_marker=col(y);
        if(collision_marker)
        {
            break;
        }
    }
}