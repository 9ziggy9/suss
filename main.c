#include <stdio.h>
#include <unistd.h>
#include <assert.h>

// FOR DEBUGGING COMMAND LINE ARGS
void echo_args(int argc, char **argv) {
  printf("argc %d\n", argc);
  for (int i = 0; i < argc; i++) {
    printf("argv[%d]: %s\n", i, argv[i]);
  }
}

// OPT FUNCTIONS
void opt_help() {
  assert(0 && "HELP INFO NOT YET IMPLEMENTED");
}

// HANDLE COMMAND LINE ARGS
void opts(int argc, char **argv) {
  int opt;
  while ((opt = getopt(argc, argv, "h")) != -1) {
    switch(opt) {
    case 'h':
      opt_help();
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

int main(int argc, char **argv) {
  echo_args(argc, argv);
  opts(argc, argv);
  return 0;
}
