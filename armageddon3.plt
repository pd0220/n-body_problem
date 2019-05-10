set term png size 1920,1080
set out "armageddon3.png"

set title "Numerical simulation for 3 high mass objects\nwith adaptive Runge-Kutta Cash-Karp method." font ",20"

set autoscale

set xzeroaxis
set yzeroaxis
set zzeroaxis

set xlabel "x" font ",15"
set ylabel "y" font ",15"
set zlabel "z" font ",15"

set xtics font ", 7"
set ytics font ", 7"
set ztics font ", 7"

splot "armageddon3.txt" using 1:2:3 title "Sun" lt rgb 'orange' with line, "armageddon3.txt" using 4:5:6 title "Earth" lt rgb 'blue' with line, "armageddon3.txt" using 7:8:9 title "Asteroid" lt rgb 'black' with line