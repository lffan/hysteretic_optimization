set term epslatex standalone lw 2 color 11
set output "plot.tex"

#--------------------------------------------------
set xlabel '$N$'
set ylabel '$\langle \sigma_E \rangle _N$'
set xrange [30:2100]
#set yrange [0.7:0.8]
set logscale x
#set logscale y

set key right top
set key Left reverse
#set grid back lc rgb "#000000"

# styles for symbol plotting
set style line  1 lt 1 lw 2 pt  7 ps 1.8 lc rgb "#FF0000"
set style line  2 lt 1 lw 2 pt  3 ps 1.8 lc rgb "#2B65EC"
set style line  3 lt 1 lw 2 pt  9 ps 1.8 lc rgb "#347235"
set style line  4 lt 1 lw 2 pt 13 ps 1.8 lc rgb "#571B7E"
set style line  5 lt 1 lw 2 pt 15 ps 1.8 lc rgb "#F88017"
set style line  6 lt 1 lw 2 pt  7 ps 1.8 lc rgb "#B048B5"

# styles for lines
set style line 11 lt 1 lw 2 lc rgb "#FF0000"
set style line 12 lt 1 lw 2 lc rgb "#2B65EC"
set style line 13 lt 1 lw 2 lc rgb "#347235"
set style line 14 lt 1 lw 2 lc rgb "#571B7E"
set style line 15 lt 1 lw 2 lc rgb "#F88017"

# fit
f(x) = a*x**(-w)

fit f(x) '../Data/ACD_ave.dat' u 1:4 via a,w
set label 1 sprintf("$%.3f N^{-%.3f}$ - ACD", a,w) at graph 0.55,0.75

fit f(x) '../Data/HO_10_ave.dat' u 1:4 via a,w
set label 2 sprintf("$%.3f N^{-%.3f}$ - HO 10", a,w) at graph 0.55,0.67

fit f(x) '../Data/HO_100_ave.dat' u 1:4 via a,w
set label 3 sprintf("$%.3f N^{-%.3f}$ - HO 100", a,w) at graph 0.55,0.59

plot \
'../Data/ACD_ave.dat' u 1:4 ls 1 t 'ACD' w p lw 2, \
'../Data/HO_10_ave.dat' u 1:4 ls 2 t 'HO 10' w p lw 2, \
'../Data/HO_100_ave.dat' u 1:4 ls 3 t 'HO 100' w p lw 2, \



set output

#########################################################
# symbols
#########################################################
#               12              empty diamond
#                6              emtpy circle
#                4              empty square
#                8              empty triangle up
#               10              empty triangle down
#               14              empty pentagon
#               13              filled diamond
#                7              filled circle
#                5              filled square
#                9              filled triangle up
#               11              filled triangle down
#               15              filled pentagon
#########################################################
# colors
#########################################################
#		#FF0000		red
#		#347235		dark green
#		#2B65EC		blue
#		#000000		black
#		#571B7E		dark purple
#		#F88017		dark orange
#		#B048B5		dark pink
#		#413839		gray 30 (darkest)
#		#595454		gray 40
#		#747170		gray 50
#########################################################
# line styles
#########################################################
#		0		dotted
#		1		solid
#		3		dashed
#########################################################
