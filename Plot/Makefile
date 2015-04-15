# plot file name
NAME = plot

# set variables
MACRO = plot.gp
TEX	= gnuplot

# make eps
paper:

	echo "\documentclass{article}" 		>  $(TEX).tex
	echo "\usepackage{graphics}"		>> $(TEX).tex
	echo "\usepackage[usenames]{color}" 	>> $(TEX).tex
	echo "\uegin{document}" 		>> $(TEX).tex
	echo "\uegin{center}" 			>> $(TEX).tex
	echo "\input{./base.tex}" 		>> $(TEX).tex
	echo "\end{center}" 			>> $(TEX).tex
	echo "\end{document}" 			>> $(TEX).tex
	perl -pi -e 's/uegin/begin/g' $(TEX).tex

	gnuplot $(MACRO)
	latex 	$(TEX).tex
	dvips	$(TEX).dvi -o $(TEX).ps
	ps2pdf14  $(TEX).ps
	mv      $(TEX).pdf $(NAME).pdf
	/bin/rm	base.eps base.tex $(TEX).* 

# clean up!
clean:

	rm -rf $(NAME).pdf
