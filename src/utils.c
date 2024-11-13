#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Retourne le nombre de chiffres d'un nombre
int get_number_length(int number) {
  if (number == 0) {
    return 1; // Cas du zéro
  }

  int result = 0;
  while (number != 0) {
    number /= 10; // Divise par 10 pour compter les chiffres
    result++;
  }
  return result;
}

// Génère un nombre aléatoire sous forme de chaîne de caractères
char *generate_random_number() {
  int random_number = rand() % MAX;

  char *random_number_str = malloc(MAX_INT_DIGITS * sizeof(char));
  if (random_number_str == NULL) {
    printf("Erreur d'allocation.\n");
    exit(1);
  }

  sprintf(random_number_str, "%d", random_number);
  return random_number_str;
}

// Génère une séquence de nombres aléatoires séparés par des espaces
char *generate_random_number_sequence(const char *n) {

  int n_int = atoi(n);
  if (n_int <= 0) {
    printf("Nombre invalide.\n");
    return NULL;
  }

  size_t buffer_size = n_int * (MAX_INT_DIGITS + 1);
  char *sequence = malloc(buffer_size);
  if (sequence == NULL) {
    printf("Erreur d'allocation.\n");
    exit(1);
  }

  char *current_position = sequence;
  for (int i = 0; i < n_int; i++) {
    int random_number = rand() % MAX;

    int written = sprintf(current_position, "%d", random_number);
    if (written < 0) {
      printf("Erreur d'écriture dans la séquence.\n");
      free(sequence);
      return NULL;
    }

    current_position += written;

    if (i < n_int - 1) {
      *current_position = ' ';
      current_position++;
    }
  }

  *current_position = '\0';
  return sequence;
}
