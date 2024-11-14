#define _XOPEN_SOURCE 700

#include "src_cli_fifo.h"
#include "utils.h"
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

void main_handler(int signum) { printf("Serveur m'a reveille! \n"); }

int main(int argc, char *argv[]) {

  srand(time(NULL));
  struct sigaction sa;
  sa.sa_handler = main_handler;
  sa.sa_flags = 0;
  sigemptyset(&sa.sa_mask);
  if (sigaction(SIGUSR1, &sa, NULL) == -1) {
    perror("Erreur configuration SIGUSR1");
    exit(1);
  }

  // Construire et envoyer message
  char *n = generate_random_number();
  size_t content_size = strlen(n) + 1;
  message *msg = malloc(sizeof(message) + content_size);
  if (!msg) {
    perror("échec allocation mémoire");
    exit(1);
  }
  msg->pid = getpid();              // Inclut le PID
  msg->content_size = content_size; // Taille du contenu
  strcpy(msg->content, n);
  write_fifo(FIFO1, msg); // Envoie à FIFO1

  // Recevoir réponse du serveur
  message *received_message = NULL;
  read_fifo(FIFO2, &received_message);
  printf("Reçu message du serveur: %s \n", received_message->content);

  // Envoyer signal SIGUSR1 au serveur
  printf("Envoyer signal au serveur: %d\n", received_message->pid);
  if (kill(received_message->pid, SIGUSR1) == -1) {
    perror("Erreur en envoyant SIGUSR1");
  }

  // Libère mémoire
  free(received_message);
  free(msg);
  return 0;
}
