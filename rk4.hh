#include <iostream>
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
        cb(t,y);
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
    //Euler step until reaching integration boundary
    while(t<t1)
    {
        if(t+h>t1)
        {
            h=t1-t;
        }
        y=y+h*f(t,y);
        t=t+h;
        cb(t,y);
    }
}

//writing to file after every step
template<typename State,typename T>
void to_file(T t,State y)
{
    std::ofstream file;
    file.open("num_int.txt",std::fstream::app);
    file<<t<<" "<<y<<"\n";
    file.close();
}