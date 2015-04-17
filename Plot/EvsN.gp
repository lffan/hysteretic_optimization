set term epslatex standalone lw 2 color 11
set output "plot.tex"

#--------------------------------------------------
set xlabel '$N$'		        # set label x axis
set ylabel '$\langle E \rangle _N$' 				# set label y axis
set xrange [30:2100]
#set yrange [0.7:0.8]
set logscale x
#set logscale y

set key right top
set key Left reverse
#set grid back lc rgb "#000000"

# styles for symbol plotting
set style line  1 lt 1 lw 1 pt  7 ps 1.8 lc rgb "#FF0000"
set style line  2 lt 1 lw 1 pt  5 ps 1.8 lc rgb "#2B65EC"
set style line  3 lt 1 lw 1 pt  9 ps 1.8 lc rgb "#347235"
set style line  4 lt 1 lw 1 pt 13 ps 1.8 lc rgb "#571B7E"
set style line  5 lt 1 lw 1 pt 15 ps 1.8 lc rgb "#F88017"
set style line  6 lt 1 lw 1 pt  7 ps 1.8 lc rgb "#B048B5"

# styles for lines
set style line 11 lt 1 lw 2 lc rgb "#FF0000"
set style line 12 lt 1 lw 2 lc rgb "#2B65EC"
set style line 13 lt 1 lw 2 lc rgb "#347235"
set style line 14 lt 1 lw 2 lc rgb "#571B7E"
set style line 15 lt 1 lw 2 lc rgb "#F88017"

# fit
f(x) = E0 + a*x**(-w)

fit f(x) '../Data/ACD_ave.dat' u 1:3 via E0,a,w
set label 1 sprintf("$%.6f+%.3f N^{-%.3f}$ - ACD", E0,a,w) at graph 0.35,0.70

fit f(x) '../Data/HO_10_ave.dat' u 1:3 via E0,a,w
set label 2 sprintf("$%.6f+%.3f N^{-%.3f}$ - HO 10", E0,a,w) at graph 0.35,0.62

fit f(x) '../Data/HO_100_ave.dat' u 1:3 via E0,a,w
set label 3 sprintf("$%.6f+%.3f N^{-%.3f}$ - HO 100", E0,a,w) at graph 0.35,0.54

plot \
-0.76321 + 0.76 * x ** (-2./3) ls 14 t 'Theoretical', \
'../Data/ACD_ave.dat' u 1:3 ls 1 t 'ACD' w p, \
'../Data/HO_10_ave.dat' u 1:3 ls 2 t 'HO 10' w p, \
'../Data/HO_100_ave.dat' u 1:3 ls 3 t 'HO 100' w p, \



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
