/*
 * journal.c
 *
 *  Created on: 6 févr. 2009
 *      Author: charaf
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>

#include "journal.h"

void journalisation(const char* nom, const char* message) {
	int fd;
	time_t temps;
	char tmp[512], jour[30];
	temps = time(NULL);
	strcpy(jour, ctime(&temps));
	jour[strlen(jour)-1] = '\0';
	sprintf(tmp, "(%s)  [%s] >> %s\n", jour, nom, message);
	fd = open("journal.log", O_WRONLY | O_APPEND | O_CREAT, 0770);
	flock(fd, LOCK_EX);
	write(fd, tmp, (strlen(tmp))*sizeof(char));
	flock(fd, LOCK_UN);
	close(fd);
}
