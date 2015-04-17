# plot file name
NAME = EvsN

# set variables
EPS = plot-inc
TEX = plot

# make eps
plot:
	gnuplot $(NAME).gp
	epstopdf $(EPS).eps
	pdflatex $(TEX).tex
	
	mv $(TEX).pdf $(NAME).pdf
	rm -f $(EPS).pdf *.eps *.tex $(TEX).log *.aux

# clean up!
clean:

	rm -rf $(NAME).pdf
