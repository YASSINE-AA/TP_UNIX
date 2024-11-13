#ifndef HANDLERS_SERV_H
#define HANDLERS_SERV_H

#include "src_cli_fifo.h"
#include <signal.h> 
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

void hand_reveil(int sig);
void fin_serveur(int sig);

#endif