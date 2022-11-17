#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <editline/readline.h>
#include "mpc.h"

// FOR DEBUGGING COMMAND LINE ARGS
void echo_args(int argc, char **argv) {
  printf("argc %d\n", argc);
  for (int i = 0; i < argc; i++) {
    printf("argv[%d]: %s\n", i, argv[i]);
  }
}

// OPT FUNCTIONS
void opt_help(void) {
  printf("\n--- HELP ---\n");
  printf("How to use suss: just use it.\n");
}
void opt_filepath(char *path) {
  printf("\nUSING FILE PATH: %s\n", path);
}
void opt_output(char *path) {
  printf("\nOUTPUTTING TO: %s\n", path);
}

// HANDLE COMMAND LINE ARGS
void opts(int argc, char **argv) {
  int opt;
  while ((opt = getopt(argc, argv, "hf:o:")) != -1) {
    switch(opt) {
    case 'h':
      opt_help();
      break;
    case 'f':
      opt_filepath(optarg);
      break;
    case 'o':
      opt_output(optarg);
      break;
    case ':':
      printf("Option needs value\n");
      break;
    case '?':
      printf("Uknown option: %c\n", optopt);
      break;
    }
  }
  // Extra args
  for (; optind < argc; optind++) {
    printf("Extra arguments: %s\n", argv[optind]);
  }
}

void intro(void) {
  puts("Suss Version 0.0.1\n");
  puts("Press Ctrl+c to exit\n");
}


int main(int argc, char **argv) {
  intro();
  while(1) {
    char *input = readline(">>> ");
    add_history(input);
    printf("No, you're a %s\n", input);

    // DEALLOCATE RESOURCES
    // TODO: I want to eventually implement memory management library
    // remember to look into ARENA.
    free(input);
  }
  return 0;
}
