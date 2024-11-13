#include "Handlers_Serv.h"

// Gestion de la fin du serveur
void fin_serveur(int sig) {
  printf("Au revoir cher utilisateur, tu vas me manquer :) \n");
  unlink(FIFO1); // Supprime FIFO1
  unlink(FIFO2); // Supprime FIFO2
  exit(0);       // Quitte le serveur
}

// Gestion du réveil du serveur
void hand_reveil(int sig) {
  printf("Client m'a réveillé!\n"); // Affiche un message de réveil
  fflush(stdout);                 // Vide le buffer de sortie
}
