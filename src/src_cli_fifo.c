#include "src_cli_fifo.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

// Crée un FIFO et un répertoire "tmp"
void create_fifo(const char *fifo) {
  mkdir("./tmp", 0777);
  if (mkfifo(fifo, 0666) == -1) {
    perror("mkfifo"); // Gère les erreurs de création
  } else {
    printf("FIFO créé: %s\n", fifo); // Confirme la création
  }
}

// Écrit un message dans un FIFO
void write_fifo(const char *fifo, message *buffer) {
  int fd = open(fifo, O_WRONLY);
  if (fd == -1) {
    perror("échec écriture dans FIFO");
    exit(1);
  }

  size_t total_size = sizeof(message) + buffer->content_size;

  if (write(fd, buffer, total_size) == -1) {
    perror("échec d'écriture du message");
    close(fd);
    exit(1);
  }

  close(fd); // Ferme le FIFO
}

// Lit un message depuis un FIFO
void read_fifo(const char *fifo, message **buffer) {
  int fd = open(fifo, O_RDONLY);
  if (fd == -1) {
    perror("échec lecture dans FIFO");
    exit(1);
  }

  message temp;
  if (read(fd, &temp, sizeof(message)) == -1) {
    perror("échec lecture en-tête FIFO");
    close(fd);
    exit(1);
  }

  *buffer = malloc(sizeof(message) + temp.content_size);
  if (!*buffer) {
    perror("échec allocation mémoire");
    close(fd);
    exit(1);
  }

  **buffer = temp;

  if (read(fd, (*buffer)->content, (*buffer)->content_size) == -1) {
    perror("échec lecture contenu FIFO");
    free(*buffer);
    close(fd);
    exit(1);
  }

  close(fd); // Ferme le FIFO
}

// Supprime un FIFO
void close_fifo(const char *fifo) {
  unlink(fifo); // Supprime le FIFO
}
