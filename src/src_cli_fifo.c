#include "src_cli_fifo.h"
#define PERMISSION 0666
void create_fifo(char* pfifo){ 
    int st = mkfifo(pfifo,PERMISSION) ; 
    if( st == -1 ){ 
        perror("Creation failed FiFO"); 
        exit(1); 
    }
    printf("FiFo created: %s", pfifo); 
} 
void write_fifo(char* fifo, message* buffer)
{

    int fd = open(fifo, O_WRONLY);
    if ( fd == -1){
        perror("failed writing fifo");
        exit(1);
    }
    write(fd, buffer, sizeof(buffer));
    close(fd);
}

void read_fifo(char* fifo ,message* buffer) {
    int fd = open(fifo, O_RDONLY);
    if (fd < 0) {
        perror("failed reading fifo.");
        exit(1);
    } 
    read(fd, buffer, sizeof(buffer));
    close(fd);
}
