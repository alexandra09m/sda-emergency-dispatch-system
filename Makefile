# Compiler setup.
CC=gcc
CFLAGS=-Wall -Wextra -std=c99

# Manually define all targets.
build: tema1

tema1:
	$(CC) $(CFLAGS) main.c sistem.c comenzi.c implementari_date.c utilitare.c -o tema1

check: build
	bash checker.sh

# Pack the solution into a zip file.
pack:
	zip -FSr 313CA_DulhanMariaAlexandra_Tema1.zip README Makefile *.c *.h

# Clean the solution.
clean:
	rm -f tema1

.PHONY: build pack clean
