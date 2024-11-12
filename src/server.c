#include "Handlers_Serv.h"
#include <time.h>
#include "utils.h"
void main_handler(int sigint) { 
    if (sigint == SIGUSR1){ 
        hand_reveil(sigint); 
        return;
    }  
    fin_serveur(sigint);
}

int main (){ 

// init 
create_fifo(FIFO1); 
create_fifo(FIFO2);

// init random seed  
srand(time(NULL)); 

struct sigaction sa;
sigset_t set = {0};
sa.sa_handler = main_handler; 
sa.sa_flags = 0;
sigemptyset(&set);
sa.sa_mask = set;

// handle quelconque signal 
for (int i = 1; i < _NSIG; i++) {  
    if (i != SIGKILL && i != SIGSTOP) {          
        if (sigaction(i, &sa, NULL) == -1) {
            perror("sigaction");
        }
    }
}

while(1) {
    message* question = malloc(sizeof(message));
    read_fifo(FIFO1, question);

    // reponse dans fifo 2
    message* reponse = malloc(sizeof(message));
    reponse->content = generate_random_number_sequence(atoi(question->content));
    reponse->pid = getpid();
    write_fifo(FIFO2, reponse);
    
    // reveiller client
    kill(question->pid, SIGUSR1);

    // liberer
    free(question->content);
    free(question);
    free(reponse->content);
    free(reponse);

    // attendre signal du client
    pause(); 
}

return 0;

}