set term png size 1280,720
set out "armageddon.png"

set title "Numerical simulation of the solar system."

set autoscale

set xlabel "x"
set ylabel "y"
set zlabel "z"

splot "armageddon.dat" using 1:2:3, "armageddon.dat" using 4:5:6, "armageddon.dat" using 7:8:9, "armageddon.dat" using 10:11:12 with lines