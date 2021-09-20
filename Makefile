all: options n-puzzle

SRC = main.c utilities.c problem.c bfs.c hash_set.c
OBJ = ${SRC:.c=.o}

LIBS = -lreadline
LDFLAGS = -g ${LIBS}

all: options n-puzzle

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

clean:
	@echo "Cleaning"
	@rm ${OBJ} n-puzzle
