#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#define STACK_CAPACITY 1024

typedef int64_t Word;

typedef enum {
  TRAP_OK = 0,
  TRAP_STACK_OVERFLOW,
  TRAP_STACK_UNDERFLOW,
  TRAP_ILLEGAL_INST
} Trap;

const char *trap_as_cstr(Trap trap) {
  switch (trap) {
  case TRAP_OK:
    return "TRAP_OK";
  case TRAP_STACK_OVERFLOW:
    return "TRAP_STACK_OVERFLOW";
  case TRAP_STACK_UNDERFLOW:
    return "TRAP_STACK_UNDERFLOW";
  case TRAP_ILLEGAL_INST:
    return "TRAP_ILLEGAL_INST";
  default:
    assert(0 && "WTF");
  }
}

typedef struct {
  Word stack[STACK_CAPACITY];
  size_t stack_size;
} Svm;

typedef enum {
  INST_PUSH,
  INST_PLUS,
  INST_MINUS,
  INST_MULT,
  INST_DIV,
} Inst_t;

typedef struct {
  Inst_t type;
  Word operand;
} Inst;

#define MAKE_INST_PUSH(value) {.type = INST_PUSH, .operand = value}
#define MAKE_INST_PLUS() {.type = INST_PLUS}
#define MAKE_INST_MINUS(value) {.type = INST_MINUS}
#define MAKE_INST_MULT() {.type = INST_MULT}
#define MAKE_INST_DIV() {.type = INST_DIV}

#define ARRAY_SIZE(xs) (sizeof(xs) / sizeof((xs)[0]))

Inst program[] = {
  MAKE_INST_PUSH(60),
  MAKE_INST_PUSH(40),
  MAKE_INST_PLUS(),
  MAKE_INST_PUSH(60),
  MAKE_INST_PUSH(40),
  MAKE_INST_MINUS(),
  MAKE_INST_PUSH(10),
  MAKE_INST_PUSH(2),
  MAKE_INST_DIV(),
  MAKE_INST_PUSH(10),
  MAKE_INST_PUSH(2),
  MAKE_INST_MULT()
};

Svm svm = {0};

Trap svm_execute_inst(Svm *svm, Inst inst) {
  switch (inst.type) {
  case INST_PUSH:
    if (svm->stack_size >= STACK_CAPACITY) {
      return TRAP_STACK_OVERFLOW;
    }
    svm->stack[svm->stack_size++] = inst.operand;
    break;
  case INST_PLUS:
    if (svm->stack_size < 2) {
      return TRAP_STACK_UNDERFLOW;
    }
    svm->stack[svm->stack_size - 2] += svm->stack[svm->stack_size - 1];
    svm->stack_size--;
    break;
  case INST_MINUS:
    if (svm->stack_size < 2) {
      return TRAP_STACK_UNDERFLOW;
    }
    svm->stack[svm->stack_size - 2] -= svm->stack[svm->stack_size - 1];
    svm->stack_size--;
    break;
  case INST_MULT:
    if (svm->stack_size < 2) {
      return TRAP_STACK_UNDERFLOW;
    }
    svm->stack[svm->stack_size - 2] *= svm->stack[svm->stack_size - 1];
    svm->stack_size--;
    break;
  case INST_DIV:
    if (svm->stack_size < 2) {
      return TRAP_STACK_UNDERFLOW;
    }
    svm->stack[svm->stack_size - 2] /= svm->stack[svm->stack_size - 1];
    svm->stack_size--;
    break;
  default:
    return TRAP_ILLEGAL_INST;
  }
  return TRAP_OK;
}

void svm_dump(FILE *stream, const Svm *svm) {
  fprintf(stream, "Stack:\n");
  if (svm->stack_size > 0) {
    for (size_t i = 0; i < svm->stack_size; i++) {
      fprintf(stream, "\t%ld\n", svm->stack[i]);
    }
  } else {
    fprintf(stream, "\t<empty>\n");
  }
}

int main(int argc, char **argv) {
  printf("%d %p\n", argc, (void *)argv);

  svm_dump(stdout, &svm);
  for (size_t i = 0; i < ARRAY_SIZE(program); i++) {
    Trap trap = svm_execute_inst(&svm, program[i]);
    if (trap != TRAP_OK) {
      fprintf(stderr, "Trap activated: %s\n", trap_as_cstr(trap));
      svm_dump(stderr, &svm);
      exit(1);
    }
  }
  svm_dump(stdout, &svm);
  return 0;
}
