// Dulhan Maria Alexandra 313CA

#ifndef UTILITARE_H
#define UTILITARE_H

#include <errno.h>

#define DIE(assertion, call_description)                            \
	do {                                                            \
			if (assertion) {                                        \
					fprintf(stderr, "(%s, %d): ",                   \
									__FILE__, __LINE__);            \
					perror(call_description);                       \
					exit(errno);                                    \
			}                                                       \
	} while (0)

char *citire_linie();
char *decupare_descr(char *linie);

#endif
