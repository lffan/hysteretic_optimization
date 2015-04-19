/* program computes semi-random seed from the system time and PID        */
/* copyrght 2014 -- helmut g. katzgraber under no common license         */

#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>

long getpid();			/* returns process ID of running program  */

long seedgen(){

    long int 	seconds;
    
    return ((time(&seconds)*181)*((getpid() - 83)*359))%104729; 

}

