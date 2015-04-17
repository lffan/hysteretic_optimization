set term epslatex standalone lw 2 color 11
set output "plot.tex"

set key right top
set key Left reverse
#set grid back lc rgb "#000000"

# styles for symbol plotting
set style line  1 lt 1 lw 2 pt  7 ps 1.8 lc rgb "#FF0000"
set style line  2 lt 1 lw 2 pt  5 ps 1.8 lc rgb "#2B65EC"
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

##########################################################
set xlabel '$E$'
set ylabel 'Frequency'
set format x "%.2f"
#set format y "%.3f"
set xrange [-0.77:-0.72]
#set yrange [0.98:1.02]
set xtics 0.01
#set logscale x
#set logscale y

set key at graph 0.9,0.9

set label 1 "N = 1024" at graph 0.7,0.65

# frequency
nint(x)=(x>0.)?floor(x+0.5):ceil(x-0.5)
bin(x,s)=s*nint(x/s)

plot \
'../Data/ACD_1024.dat' u (bin($1, 0.0005)):(1) s f t 'ACD' lw 2, \
'../Data/HO_10_1024.dat' u (bin($1, 0.0005)):(2.0) s f t 'HO 10' lw 2, \
'../Data/HO_100_1024.dat' u (bin($1, 0.0005)):(4.0) s f t 'HO 100' lw 2, \


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
