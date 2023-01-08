#include "common.h"


int main(int argc, char **argv){

    int sockfd, n, sendbytes;
    struct sockaddr_in servaddr;
    char sendline[MAXLINE],recvline[MAXLINE];

    //ensure correct number of args input
    if(argc != 2) err_n_die("usage: %s <server address>",argv[0]);

    //create new socket, check if created properly, handle it if not
    //SOCK_STREAM used as this is TCP implementation, last arg 0 is for TCP also
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0))<0) err_n_die("Error creating the socket!");
    
    bzero(&servaddr, sizeof(servaddr)); //zero out servaddr
    servaddr.sin_family = AF_INET; //internet address
    servaddr.sin_port = htons(SERVER_PORT); //changes port byte order from host set to network standard

    //converts string bound ip addr to binary 
    if(inet_pton(AF_INET, argv[1], &servaddr.sin_addr)<=0) err_n_die("inet_pton error for %s", argv[1]);

    //connect to server
    if(connect(sockfd, (SA *) &servaddr, sizeof(servaddr))<0) err_n_die("connect failed!");

    //at this point we are connected to the server
    //create line to send to server
    sprintf(sendline, "GET / HTTP/1.1\r\n\r\n");
    sendbytes=strlen(sendline);

    //write req to server
    if(write(sockfd,sendline,sendbytes)!=sendbytes) err_n_die("error writing request!");

    //prepare memory space for server response by setting entire mem space to 0
    memset(recvline,0,MAXLINE);

    //read server response.
    while((n=read(sockfd,recvline,MAXLINE-1))>0){
    //print response
    printf("%s",recvline);
    //clear memory for response again
    memset(recvline,0,MAXLINE);
    } if(n<0)err_n_die("error reading response!");

    exit(0);

}

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
