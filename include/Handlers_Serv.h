#include <signal.h> 
#include "src_cli_fifo.h"
#include "utils.h"

void hand_reveil(int sig) 
{

// disable SIGUSER1  
// read fifo 1 to get user input 
// write to fifo2 the user output 
// send signal wake to user occoding to pid 
// enable signals 

signal(SIGUSR1, SIG_IGN);

message* msg;

// Read fifo 1
read_fifo(FIFO1, msg);
int pid = msg->pid; // dest
char* content = msg->content; // trait

 



// string ... 
//  process string -> struct 
// process struct -> string format 

signal(SIGUSR1, SIG_DFL);
}

void fin_serveur(int sig); 
