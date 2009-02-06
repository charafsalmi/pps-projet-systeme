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

void journalisation(const char* name, const char* msg)
{

	int fd;

	time_t tm;

	char tmp[512], day[30];
	tm = time(NULL);
	strcpy(day, ctime(&tm));

	day[strlen(day)-1] = '\0';

	sprintf(tmp, "(%s)  [%s] >> %s\n", day, name, msg);
	fd = open("journal.log", O_WRONLY | O_APPEND | O_CREAT, 0770);

	/* Doute sur ces flock */
	flock(fd, LOCK_EX);

	write(fd, tmp, (strlen(tmp))*sizeof(char));

	flock(fd, LOCK_UN);

	close(fd);
}
