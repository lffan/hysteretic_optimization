set terminal epslatex color	# needed to TeX the strings
set output 'base.tex'
set multiplot

# set details about key
set key at graph 0.3, graph 0.3
set key Left reverse
set key samplen 1.5
set key box
set key height 1.0
set key width 2

# set size of plot
set size ratio 0.72
set lmargin at screen 0
set rmargin at screen 0.72
set bmargin at screen 0
set tmargin at screen 0.72

# set plot ranges/axes/ticks
#set format y "%.2f"
#set format x "%.2f"
#set yrange [0.84:0.98] # set range of x axis
#set xrange [-2.0:1.0]		# set range of y axis
#set logscale y
#set logscale x
#set xtics 1e+7     		# set x mayor tics
#set mxtics 10			# set number of x minor tics
#set ytics 5  			# set y mayor tics
#set mytics 1  			# set number of y minor tics
set grid back lc rgb "#000000"	# set visual grid on plot

# set axes labels
set xlabel '$sweep$'		         	# set label x axis
set ylabel '$E$' 		# set label y axis

# styles for symbol plotting
set style line  1 lt 1 lw 1 pt  5 ps 1.8 lc rgb "#FF0000"
set style line  2 lt 1 lw 1 pt  5 ps 1.8 lc rgb "#2B65EC"
set style line  3 lt 1 lw 1 pt  9 ps 1.8 lc rgb "#347235"
set style line  4 lt 1 lw 1 pt 13 ps 1.8 lc rgb "#571B7E"
set style line  5 lt 1 lw 1 pt 15 ps 1.8 lc rgb "#F88017"
set style line  6 lt 1 lw 1 pt  7 ps 1.8 lc rgb "#B048B5"

# styles for lines
set style line 11 lt 1 lw 1 lc rgb "#FF0000"
set style line 12 lt 1 lw 1 lc rgb "#2B65EC"
set style line 13 lt 1 lw 1 lc rgb "#347235"
set style line 14 lt 1 lw 1 lc rgb "#571B7E"
set style line 15 lt 1 lw 1 lc rgb "#F88017"


plot \
'../data/test.dat' u 1:2 ls 11 t '$E$' w l, \
