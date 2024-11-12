#ifndef HANDLERS_SERV_H_ 
#define HANDLERS_SERV_H_
#define _XOPEN_SOURCE 700
#define __USE_POSIX 

#include <signal.h> 
#include "src_cli_fifo.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

void hand_reveil(int sig) {
   printf("Client m'a reveille!");
}



void fin_serveur(int sig){ 

    printf("Goodbye Dear user, i will miss you :) \n");
    unlink(FIFO1);
    unlink(FIFO2);
} 
#endif