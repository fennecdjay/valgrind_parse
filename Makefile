CFLAGS += -Wall -Wextra
PREFIX ?= /usr/local
PRG    := valgrind_parse
ERR    := error_program

LOG := example_log
MEMOK := "All heap blocks were freed -- no leaks are possible"
_check = (echo "ok" || (echo "not ok" && exit 1))


${PRG}: ${PRG}.c
	${CC} ${CFLAGS} $< -o $(<:.c=)

clean:
	rm -f ${PRG} ${ERR}

install: valgrind_parse
	install ${PRG} ${PREFIX}/bin

uninstall:
	rm -f ${PREFIX}/bin/${PRG}

${ERR}: ${ERR}.c
	${CC} ${CFLAGS} $< -o $(<:.c=)

test: error_program
	@valgrind --log-file=example_log ./error_program &>/dev/null || exit 0
	@valgrind ./${PRG} ${LOG} 2>&1 | grep ${MEMOK} && $(call _check)
	@rm -f error_program example_log
