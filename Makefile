all: options driver

SRC = main.c utilities.c
OBJ = ${SRC:.c=.o}

LIBS = -lreadline
LDFLAGS = -g ${LIBS}

all: options driver

options:
	@echo build options:
	@echo "CFLAGS   = ${CFLAGS}"
	@echo "LDFLAGS  = ${LDFLAGS}"
	@echo "CC       = ${CC}"

.c.o:
	@echo CC $<
	@${CC} -c ${CFLAGS} $<

driver: ${OBJ}
	@echo CC -o $@
	@${CC} -o $@ ${OBJ} ${LDFLAGS}


