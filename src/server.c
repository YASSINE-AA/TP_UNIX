#define _XOPEN_SOURCE 700
#include "Handlers_Serv.h"
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
#include <errno.h>

// Gère les signaux reçus
void main_handler(int signum)
{
  fflush(stdout);

  if (signum == SIGUSR1)
  {
    // Appelle le réveil
    hand_reveil(signum);
  }
  else
  {
    // Termine le serveur
    fin_serveur(signum);
    fflush(stdout);
  }
}

int main()
{
  // Crée les canaux FIFO
  create_fifo(FIFO1);
  create_fifo(FIFO2);

  // Configure SIGUSR1 signal
  struct sigaction sa;
  sa.sa_handler = main_handler;
  sa.sa_flags = 0;
  sigemptyset(&sa.sa_mask);
  if (sigaction(SIGUSR1, &sa, NULL) == -1)
  {
    perror("Erreur configuration SIGUSR1");
    exit(1);
  }

  for (int i = 1; i < 32; i++)
  {
    if (i == SIGKILL || i == SIGSTOP)
    {
      continue; 
    }

    if (sigaction(i, &sa, NULL) == -1)
    {
      if (errno == EINVAL)
      {
        fprintf(stderr, "err signal %d \n", i);
      }
      else
      {
        perror("sigaction");
      }
    }
  }

  printf("Serveur démarré, en attente... PID: %d\n", getpid());

  while (1)
  {
    // Lit message client
    message *received_message = NULL;
    read_fifo(FIFO1, &received_message);
    printf("Message reçu du client <%d>: %s\n", received_message->pid,
           received_message->content);

    // Génère une séquence aléatoire
    char *random_sequence =
        generate_random_number_sequence(received_message->content);
    size_t content_size = strlen(random_sequence) + 1;

    // Alloue et remplit message
    message *sent_message = malloc(sizeof(message) + content_size);
    if (!sent_message)
    {
      perror("Erreur allocation mémoire\n");
      exit(1);
    }

    sent_message->pid = getpid();
    sent_message->content_size = content_size;
    strcpy(sent_message->content, random_sequence);
    printf("Envoi du message au client.\n");

    // Envoie le message
    write_fifo(FIFO2, sent_message);

    // Reveiller client
    kill(received_message->pid, SIGUSR1);

    // Libère mémoire
    free(sent_message);
    free(received_message);
    free(random_sequence);
    // Attend prochain signal
    pause();
  }

  // Ferme les canaux FIFO
  close_fifo(FIFO1);
  close_fifo(FIFO2);
  return 0;
}
