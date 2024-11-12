#include "src_cli_fifo.h"
#include "utils.h"
#include <signal.h>
#include <time.h>
volatile int pid=0; 
#include <string.h>
void handle_SIGUSR1( int sigint){ 
    printf("Got data from Server, seding ACK signal \n");
}
int main () {
    srand(time(NULL));
    // send 
    signal(SIGUSR1,handle_SIGUSR1); 
    message* msg = malloc(sizeof(message));
    msg->pid = getpid();
    char* tmp = generate_random_number();
    strncpy(msg->content,tmp,MAX_BUFF);
    printf("sending data %d , %s\n",msg->pid,msg->content); 
    write_fifo(FIFO1, msg); // ecrire dans fifo1
    memset(msg, 0, sizeof(message));
    read_fifo(FIFO2,msg);
    pid=msg->pid;
    printf("received data from server %d , %s\n",msg->pid,msg->content); 
    fflush(stdout); 
    kill(pid,SIGUSR1);
    free(tmp);
    free(msg);
    printf("Goodbye from Client \n");
    fflush(stdout);
    return 0;
}