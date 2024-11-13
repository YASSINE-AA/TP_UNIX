#ifndef SRC_CLI_FIFO_H
#define SRC_CLI_FIFO_H

#include <unistd.h>
#include <stdlib.h> 
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>

#define FIFO1 "tmp/fifo1"
#define FIFO2 "tmp/fifo2"
typedef struct {
    pid_t pid;
    int content_size;  
    char content[];     
} message;

void create_fifo(const char* pfifo); 
void write_fifo(const char* pfifo, message* buffer); 
void read_fifo(const char* pfifo, message** buffer);
void close_fifo(const char* pfifo);

#endif