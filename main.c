
/* #include <stdio.h> */
/* #include <stdlib.h> */

/* #define MAX_SRC_CODE_SIZE 1024 */

/* void read_src_to_buffer(FILE *src, char *buf) { */
/*   size_t count = 0; */
/*   int c; */
/*   while ((c = fgetc(src)) != EOF && count < MAX_SRC_CODE_SIZE - 1) { */
/*     buf[count++] = (char) c; */
/*   } */
/*   buf[count] = '\0'; */
/* } */

/* void panic_and_exit() { */
/*   fprintf(stderr, "PANIC: Exiting immediately.\n"); */
/*   exit(EXIT_FAILURE); */
/* } */

/* int main(int argc, char *argv[]) { */
/*   if (argc != 2) { */
/*     fprintf(stderr, "Usage: %s <filename>\n", argv[0]); */
/*     panic_and_exit(); */
/*   } */

/*   FILE *src = fopen(argv[1], "r"); */
/*   if (src == NULL) { */
/*     fprintf(stderr, "Error opening file: %s\n", argv[1]); */
/*     panic_and_exit(); */
/*   } */

/*   char src_buffer[MAX_SRC_CODE_SIZE]; */
/*   read_src_to_buffer(src, src_buffer); */

/*   fclose(src); */

/*   printf("%s\n", src_buffer); */

/*   return EXIT_SUCCESS; */
/* } */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TOKEN_LENGTH 64
#define MAX_TOKENS 128
#define MAX_SRC_CODE_SIZE 1024


typedef enum {
  TOK_ERROR,
  TOK_EOF,
  TOK_IDENT,
  TOK_INT,
  TOK_STRING,
  TOK_SYMBOL,
  TOK_LPAREN,
  TOK_RPAREN,
  TOK_LBRACE,
  TOK_RBRACE,
  TOK_COMMA,
  TOK_PERIOD,
  TOK_PLUS,
  TOK_MINUS,
  TOK_MUL,
  TOK_DIV,
  TOK_MOD,
  TOK_EQ,
  TOK_NEQ,
  TOK_LT,
  TOK_GT,
  TOK_LE,
  TOK_GE,
  TOK_ASSIGN,
  TOK_COLON,
  TOK_SEMICOLON,
} TokenType;

typedef struct {
  TokenType type;
  char *lexeme;
} Token;

Token *tokenize(char *src_buffer) {
  Token *tokens = malloc(MAX_TOKENS * sizeof(Token));
  size_t token_count = 0;

  char *ptr = src_buffer;
  while (*ptr != '\0') {
    // Skip whitespace
    while (*ptr == ' ' || *ptr == '\t' || *ptr == '\n' || *ptr == '\r') {
      ptr++;
    }

    // Identifiers
    if (isalpha(*ptr)) {
      char *ident_start = ptr;
      while (isalpha(*ptr) || isdigit(*ptr) || *ptr == '_') {
        ptr++;
      }
      char ident[MAX_TOKEN_LENGTH];
      strncpy(ident, ident_start, ptr - ident_start);
      ident[ptr - ident_start] = '\0';
      tokens[token_count].type = TOK_IDENT;
      tokens[token_count].lexeme = strdup(ident);
      token_count++;
    }

    // Integers
    else if (isdigit(*ptr)) {
      char *int_start = ptr;
      while (isdigit(*ptr)) {
        ptr++;
      }
      char int_str[MAX_TOKEN_LENGTH];
      strncpy(int_str, int_start, ptr - int_start);
      int_str[ptr - int_start] = '\0';
      tokens[token_count].type = TOK_INT;
      tokens[token_count].lexeme = strdup(int_str);
      token_count++;
    }

    // Symbols
    else if (strchr("+-*/%<>=", *ptr) != NULL) {
      tokens[token_count].type = TOK_SYMBOL;
      tokens[token_count].lexeme = strdup(ptr);
      token_count++;
      ptr++;
    }

    // String literals
    else if (*ptr == '"') {
      char *str_start = ptr + 1;
      while (*ptr != '"') {
        ptr++;
      }
      char str[MAX_TOKEN_LENGTH];
      strncpy(str, str_start, ptr - str_start);
      str[ptr - str_start] = '\0';
      tokens[token_count].type = TOK_STRING;
      tokens[token_count].lexeme = strdup(str);
      token_count++;
      ptr++;
    }

    // Other tokens
    else {
      tokens[token_count].type = TOK_ERROR;
      tokens[token_count].lexeme = strdup("Unknown token");
      token_count++;
      ptr++;
    }
  }

  tokens[token_count].type = TOK_EOF;
  tokens[token_count].lexeme = NULL;

  return tokens;
}

void read_src_to_buffer(FILE *src, char *buf) {
  size_t count = 0;
  int c;
  while ((c = fgetc(src)) != EOF && count < MAX_SRC_CODE_SIZE - 1) {
    buf[count++] = (char) c;
  }
  buf[count] = '\0';
}

void panic_and_exit() {
  fprintf(stderr, "PANIC: Exiting immediately.\n");
  exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
    panic_and_exit();
  }

  FILE *src = fopen(argv[1], "r");
  if (src == NULL) {
    fprintf(stderr, "Error opening file: %s\n", argv[1]);
    panic_and_exit();
  }

  char src_buffer[MAX_SRC_CODE_SIZE];
  read_src_to_buffer(src, src_buffer);

  Token *tokens = tokenize(src_buffer);

  for (size_t i = 0; i < MAX_TOKENS; i++) {
    Token token = tokens[i];
    if (token.type != TOK_EOF && token.type != TOK_ERROR) {
      printf("%d: %s (%s)\n", i, token.lexeme, token_type_to_string(token.type));
    }
  }

  return EXIT_SUCCESS;
}
