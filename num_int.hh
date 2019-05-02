#include <fstream>

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

//adaptive RK4 method implementation for numerical integration
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