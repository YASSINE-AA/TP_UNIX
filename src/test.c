#include <stdlib.h> 
#include <stdio.h>
#include <string.h>
#include <time.h>




int get_number_length(int number) {
   
    if(number == 0) {
        return 0;
    }

    int result = 0;

    while(number != 0) 
    {
        number /= 10;char* generate_random_number() {

    int random_number = rand() % 10;
    char* random_number_str = malloc(get_number_length(random_number)*sizeof(char)); // maximum 2 chars
    if(random_number_str == NULL) {
        printf("Error allocating.");
        exit(1);
    }
    return random_number_str; 
}

        result++;
    }

    return result;
}
char* generate_random_number() {

    int random_number = rand() %  10;
    char* random_number_str = malloc(get_number_length(random_number)*sizeof(char)); // maximum 2 chars
    if(random_number_str == NULL) {
        printf("Error allocating.");
        exit(1);
    }
        sprintf(random_number_str, "%d",  random_number);

    return random_number_str; 
}


char*  generate_random_number_sequence_char(int n){ 

    char* sequence = malloc(n*2*sizeof(char));
    if(sequence == NULL) {
        printf("Error allocating.");
        exit(1);
    }
    

    for ( int i = 0 ; i<n ; i++ ){ 
        int random_number = (int)rand()%n;
        char* tmp = malloc(get_number_length(random_number) * sizeof(char)); 
        sprintf(tmp,  "%d", random_number);
        strcat(sequence, tmp);

        if(i < n-1) strcat(sequence, " "); 
        printf("%s ",tmp); 

     }
    return sequence;
}

int main ( ){ 
    srand(time(NULL)); 
    char * seq = generate_random_number(); 
    if ( seq == NULL){ 
        free (seq); 
    }
    printf("%s \n",seq);
}
  