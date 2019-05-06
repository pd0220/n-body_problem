set term png size 1920,1080
set out "armageddon4.png"

set title "Numerical simulation for 4 high mass objects\nwith adaptive fourth-order Runge-Kutta method." font ",20"

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

splot "armageddon4.txt" using 1:2:3 title "Sun" with line, "armageddon4.txt" using 4:5:6 title "Earth" with line, "armageddon4.txt" using 7:8:9 title "Jupiter" with line, "armageddon4.txt" using 10:11:12 title "Asteroid" with line