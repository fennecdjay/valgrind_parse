CFLAGS += -Wall -Wextra
PREFIX ?= /usr/local
PRG    := valgrind_parse

${PRG}: valgrind_parse.c
	${CC} ${CFLAGS} $< -o $(<:.c=)

clean:
	rm -f ${PRG}

install: valgrind_parse
	install ${PRG} ${PREFIX}/bin

uninstall:
	rm -f ${PREFIX}/bin/${PRG}

error_program: error_program.c
	${CC} ${CFLAGS} $< -o $(<:.c=)

test: error_program
	@valgrind ./valgrind_parse example_log 2>&1 | ./valgrind_parse
	rm error_program
