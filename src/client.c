#include "src_cli_fifo.h"
#include "utils.h"
#include <signal.h>
#include <time.h>

void handle_SIGUSR1( int sigint){ 
    printf("Got data from Server \n");
}
int main () {
    srand(time(NULL));
    // send 
    signal(SIGUSR1,handle_SIGUSR1); 
    message* msg = malloc(sizeof(message));
    msg->pid = getpid();
    msg->content = generate_random_number();
    printf("sending data %d\n",msg->pid); 
    write_fifo(FIFO1, msg); // ecrire dans fifo1
    memset(msg, 0, sizeof(message));
    read_fifo(FIFO2,msg);
    printf("received data from server %d , %s\n",msg->pid,msg->content); 
    kill(SIGUSR1,msg->pid);
    free(msg->content);
    free(msg);
    return 0;
}