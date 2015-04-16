# plot file name
NAME = Freq_ACD

# set variables
MACRO = Freq_ACD.gp
EPS = plot-inc
TEX = plot

# make eps
plot:
	gnuplot $(MACRO)
	epstopdf $(EPS).eps
	pdflatex $(TEX).tex
	
	mv $(TEX).pdf $(NAME).pdf
	rm -f $(EPS).pdf *.eps *.tex $(TEX).log *.aux

# clean up!
clean:

	rm -rf $(NAME).pdf
