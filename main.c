/*
 *
 * Courtney McGill
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/resource.h>
#include "list.h"

void process_data(FILE *input_file) {

	struct rusage usage;
	char filestream[2000000]; 
	struct node *new_node = malloc(sizeof(struct node*)); // make a new node
	new_node = new_node->next;

	if (input_file == stdin){ // if the user did not pass in a file
//	   printf("Enter input: "); 
	   while(fgets(filestream, 2000000,stdin)!= NULL){
	  
		int slen = strlen(filestream);
//		printf("size of token %c\n", slen);
		filestream[slen-1] = '\0';   
	
		char *token = strtok(filestream, " \t\n"); 	
		if (token != NULL){
		int counter = 0;
		for(int i=0; i<strlen(token); i++){ // check if each of the chars are valid in the first token
			if(i == 0 && (isdigit(token[i]) || token[i]=='-')){
				counter++; 
//				printf("incramented count \n");
			} 
			else if(isdigit(token[i])){
				counter++; 
			}
		}
		if (counter == strlen(token)){ // check if the first token is valid
			int num = atoi(token); // change to an int
		//	printf("number:  %d\n" , num);
			list_append(num, &new_node); // append it to the LL
			}
		}	

		while(token != NULL){
			token = strtok(NULL, " \t\n"); 
			if (token != NULL){
			int counter= 0; 
			for(int i=0; i<strlen(token); i++){ // check if all of the charachters are valid
				if(i == 0 && (isdigit(token[i]) || token[i]=='-')){
					counter++; 
				}	 
				else if(isdigit(token[i])){
					counter++; 
				}
			}
			if (counter == strlen(token)){ // check if the token is a valid token
			int num = atoi(token); // change from a string to an int
	//		printf("token:  %c\n" , token);
			list_append(num, &new_node); // append it to the LL
			}
			}

		}
	   }
	fflush(stdout);

	}
	else{ // if the user passed in a file

	        while(fgets(filestream, 2000000,input_file)!= NULL){ // loop through file

		int slen = strlen(filestream);
//		printf("size of token %c\n", slen);
		filestream[slen-1] = '\0';

		char *token = strtok(filestream, " \t\n"); 	
		if (token != NULL){
		int counter = 0;
		for(int i=0; i<strlen(token); i++){
			if(i == 0 && (isdigit(token[i]) || token[i]=='-')){
				counter++; 
//				printf("incramented count \n");
			} 
			else if(isdigit(token[i])){
				counter++; 
			}
		}
		if (counter == strlen(token)){
			int num = atoi(token);
		//	printf("number:  %d\n" , num);
			list_append(num, &new_node); 
			}
			if (token[0] ==  '#')
			{
			token = strtok(NULL, "\n");
			}
		}	

		while(token != NULL){
			token = strtok(NULL, " \t\n"); 
			if (token != NULL){
			int counter= 0; 
			for(int i=0; i<strlen(token); i++){
				if(i == 0 && (isdigit(token[i]) || token[i]=='-')){
					counter++; 
				}	 
				else if(isdigit(token[i])){
					counter++; 
				}
			}
			if (counter == strlen(token)){
			int num = atoi(token);
	//		printf("token:  %c\n" , token);
			list_append(num, &new_node);
			}
			if (token[0] ==  '#')
			{
			token = strtok(NULL, "\n");
			}
			}
		   }

		}
	   }
  if (getrusage(RUSAGE_SELF, &usage) == -1)
	{
	fprintf(stderr, "Error with getusage");
	exit(1);
	}
  getrusage(RUSAGE_SELF, &usage);
  list_sort(&new_node);
  list_print(new_node);



printf ("System time: %ld.%08ld\n", usage.ru_stime.tv_sec, usage.ru_stime.tv_usec);
printf ("User time: %ld.%08ld\n", usage.ru_utime.tv_sec, usage.ru_utime.tv_usec);



  list_clear(new_node);
  free(new_node);

}

//actual file input function goes here

   
  // !! your code should start here.  the input_file parameter
    // is an already- file.  you can read data from it using
    // the fgets() C library function.  close it with the fclose()
    // built-in function



void usage(char *program) {
    printf(stderr, "usage: %s [<datafile>]\n", program);
    exit(1);
}

#ifndef AUTOTEST
int main(int argc, char **argv) {
    FILE *datafile = NULL;

    /* find out how we got invoked and deal with it */
    switch (argc) {
        case 1:
            /* only one program argument (the program name) */ 
            /* just equate stdin with our datafile */
            datafile = stdin;        
            break;

        case 2:
            /* two arguments: program name and input file */
            /* open the file, assign to datafile */
            datafile = fopen(argv[1], "r");
            if (datafile == NULL) {
                printf("Unable to open file %s: %s\n", argv[1], strerror(errno));
                exit(-1);
            }
            break;

        default:
            /* more than two arguments?  throw hands up in resignation */
            usage(argv[0]);
    }

    /* 
     * you should be able to just read from datafile regardless 
     * whether it's stdin or a "real" file.
     */
    process_data(datafile);
    fclose(datafile);
    return 0;
}
#endif
