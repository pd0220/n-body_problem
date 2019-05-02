set term png size 1280,720
set out "armageddon.png"

set title "Numerical simulation of the solar system via adaptive fourth-order Runge-Kutta method." font ",20"

set autoscale

set xlabel "x" font ",15"
set ylabel "y" font ",15"
set zlabel "z" font ",15"

set xtics font ", 7"
set ytics font ", 7"
set ztics font ", 7"

splot "armageddon.txt" using 1:2:3 title "Sun" with line, "armageddon.txt" using 4:5:6 title "Earth" with line, "armageddon.txt" using 7:8:9 title "Jupiter" with line, "armageddon.txt" using 10:11:12 title "Asteroid" with line