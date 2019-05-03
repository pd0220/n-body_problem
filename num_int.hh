#include <fstream>
#include <array>

//RK4 method implementation for numerical integration
template<typename State,typename T,typename RHS,typename Callback>
auto solve_RK4(State y0,T t0,T t1,T h,RHS f,Callback cb)
{
    //setting initial values
    T t=t0;
    State y=y0;
    //RK4 steps until reaching integration boundary
    while(t<t1)
    {
        if(t+h>t1)
        {
            h=t1-t;
        }
        State k1=f(t,y);
        State k2=f(t+h*(T)0.5,y+(h*(T)0.5)*k1);
        State k3=f(t+h*(T)0.5,y+(h*(T)0.5)*k2);
        State k4=f(t+h,y+h*k3);

        y=y+(k1+k4+(T)2*(k2+k3))*(h/(T)6);
        t=t+h;
        cb(t,y,h);
    }
    return y;
}

//Euler method implementation for numerical integration
template<typename State,typename T,typename RHS,typename Callback>
auto solve_Euler(State y0,T t0,T t1,T h,RHS f,Callback cb)
{
    //setting initial values
    T t=t0;
    State y=y0;
    //Euler steps until reaching integration boundary
    while(t<t1)
    {
        if(t+h>t1)
        {
            h=t1-t;
        }

        y=y+h*f(t,y);
        t=t+h;
        cb(t,y,h);
    }
}

/*
//adaptive RK4 method implementation for numerical integration
//via one Euler and one RK4 step
template<typename State,typename T,typename RHS,typename Callback>
auto solve_RK4_adapt(State y0,T t0,T t1,T h,RHS f,Callback cb,T Delta_0)
{
    //setting initial values
    T t=t0;
    State yE=y0;
    State yRK4=y0;
    State y=y0;
    //adaptive steps until reaching integration boundary
    while(t<t1)
    {
        if(t+h>t1)
        {
            h=t1-t;
        }

        //one Euler step
        yE=yE+h*f(t,yE);

        //one RK4 step
        State k1=f(t,yRK4);
        State k2=f(t+h*(T)0.5,yRK4+(h*(T)0.5)*k1);
        State k3=f(t+h*(T)0.5,yRK4+(h*(T)0.5)*k2);
        State k4=f(t+h,yRK4+h*k3);
        yRK4=yRK4+(k1+k4+(T)2*(k2+k3))*(h/(T)6);

        //difference of the two kinds of steps
        State Delta_state=yRK4-yE;
        T Delta=norm(Delta_state);

        //determine what stepsize to be used
        T h_0=(T)0;
        if(Delta_0>=Delta)
        {
            h_0=h*std::pow(std::abs(Delta_0/Delta),0.2);
        }
        else
        {
            h_0=h*std::pow(std::abs(Delta_0/Delta),0.25);
        }

        //final RK4 step
        State k1_final=f(t,y);
        State k2_final=f(t+h_0*(T)0.5,y+(h_0*(T)0.5)*k1_final);
        State k3_final=f(t+h_0*(T)0.5,y+(h_0*(T)0.5)*k2_final);
        State k4_final=f(t+h_0,y+h_0*k3_final);

        y=y+(k1_final+k4_final+(T)2*(k2_final+k3_final))*(h_0/(T)6);
        t=t+h_0;
        cb(t,y,h_0);
    }
}
*/

//adaptive RK4 method implementation for numerical integration
//via one RK4 and one RK5 step
template<typename State,typename T,typename RHS,typename Callback>
auto solve_RK4_adapt(State y0,T t0,T t1,T h,RHS f,Callback cb,T Delta0)
{
    //setting initial values
    T t=t0;
    State y_test=y0;
    State y=y0;
    //adaptive steps until reaching integration boundary
    while(t<t1)
    {
        if(t+h>t1)
        {
            h=t1-t;
        }

        //fifth order step
        State k1=f(t,y_test);
        State k2=f(t+h*(T)0.2,y_test+(T)0.2*k1);
        State k3=f(t+h*(T)0.3,y_test+(T)0.075*k1+(T)0.225*k2);
        State k4=f(t+h*(T)0.6,y_test+(T)0.3*k1-(T)0.9*k2+(T)1.2*k3);
        State k5=f(t+h,y_test-(T)11/54*k1+(T)2.5*k2-(T)70/27*k3+(T)35/27*k4);
        State k6=f(t+h*(T)0.875,y_test+(T)1631/55296*k1+(T)175/512*k2+(T)575/13824*k3+(T)44275/110592*k4+(T)253/4096*k5);

        //error estimate
        State Delta_state=((T)37/378-(T)2825/27648)*k1+
                          ((T)250/621-(T)18575/48384)*k3+
                          ((T)125/594-(T)13525/55296)*k4+
                          ((T)-277/14336)*k5+
                          ((T)512/1771-(T)0.25)*k6;
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

        //one RK4 step with estimated stepsize
        State k1f=f(t,y);
        State k2f=f(t+h0*(T)0.5,y+(h0*(T)0.5)*k1f);
        State k3f=f(t+h0*(T)0.5,y+(h0*(T)0.5)*k2f);
        State k4f=f(t+h0,y+h0*k3f);

        y=y+(k1f+k4f+(T)2*(k2f+k3f))*(h0/(T)6);        
        t=t+h0;
        cb(t,y,h0);
    }
}