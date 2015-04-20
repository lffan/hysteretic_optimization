# set executable name
EXECNAME    = TEST

# default compiler settings
CC          =  gcc
OPT         = -O2 
LDFLAGS     = -lm

SRC         = *.c
OBJS        = $*(SRC).o

# compilation for runs
all:
	$(CC) $(OPT) $(SRC) -o $(EXECNAME) $(LDFLAGS) 
	/bin/rm -rf *.o

# clean up
clean:
	rm -rf *.o $(EXECNAME)

