#include "common.h"

void err_n_die(const char *fmt,...){
    int errno_save;
    va_list ap;

    errno_save=errno;

    //print out fmt and args
    va_start(ap,fmt);
    vfprintf(stdout,fmt,ap);
    fprintf(stdout,"\n");
    fflush(stdout);
    //print error message if error number is set
    if(errno_save!=0){
        fprintf(stdout,"(errno = %d) : %s\n",errno_save,strerror(errno_save));
        fprintf(stdout,"\n");
        fflush(stdout);
    }
    va_end(ap);

    //terminate
    exit(1);
}


char *bin2hex(const unsigned char *input, size_t len){

    char *result;
    char *hexdigits = "0123456789ABCDEF";

    if (input == NULL || len <= 0 ) return NULL; //if input is empty

    int resultlength = (len*3)+1;

    result = malloc(resultlength);
    bzero(result,resultlength);

    for (int i=0; i<len; i++){
        result[i*3] = hexdigits[input[i] >> 4]; //shift out lower 4 bits
        result[(i*3)+1] = hexdigits[input[i] & 0x0F]; //zero top 4 bits
        result[(i*3)+2] = ' ';

    }

    return result;


    
}