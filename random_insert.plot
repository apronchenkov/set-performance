set terminal png
set output "random_insert.png"
set xlabel "n"
set ylabel "time (sec)"
set logscale x 2
set logscale y 10

set xtics 64, 8, 1048576

plot \
     'random_insert.log' using 1:2 with lines title "btree set", \
     'random_insert.log' using 1:3 with lines title "unordered set (reserved)", \
     'random_insert.log' using 1:4 with lines title "unordered set", \
     'random_insert.log' using 1:5 with lines title "set", \