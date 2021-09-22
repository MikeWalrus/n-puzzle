all: options n-puzzle tests

SRC = main.c utilities.c problem.c bfs.c hash_set.c list.c visual.c
OBJ = ${SRC:.c=.o}

LIBS = -lreadline
LDFLAGS = -g ${LIBS}

all: options n-puzzle

tests: list_test hash_set_test

options:
	@echo build options:
	@echo "CFLAGS   = ${CFLAGS}"
	@echo "LDFLAGS  = ${LDFLAGS}"
	@echo "CC       = ${CC}"

.c.o:
	@echo CC $<
	@${CC} -c ${CFLAGS} $<

n-puzzle: ${OBJ}
	@echo CC -o $@
	@${CC} -o $@ ${OBJ} ${LDFLAGS}

list_test: list.o utilities.o tests/list_test.c
	@echo CC -o $@
	@${CC} ${CFLAGS} $^ -o $@

hash_set_test: hash_set.o utilities.o problem.o tests/hash_set_test.c
	@echo CC -o $@
	@${CC} ${CFLAGS} $^ -o $@

clean:
	@echo "Cleaning"
	@rm ${OBJ} n-puzzle
