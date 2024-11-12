#include <unistd.h>
#include <stdlib.h> 
#include <stdio.h>
#include <fcntl.h>

#define FIFO1 "tmp/fifo1"
#define FIFO2 "tmp/fifo2"

typedef struct {
    int pid;
    char * content;
} message; 

void create_fifo(char* pfifo); 
void write_fifo(char* pfifo, message* buffer); 
void read_fifo(char* pfifo, message* buffer);
void close_fifo(char* pfifo);

/* 
"pid:<id> "  
"pid:<num>"  
*/ 