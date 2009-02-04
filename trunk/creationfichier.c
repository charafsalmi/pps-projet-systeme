#include "type_definitions.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
	struct Transaction_Admin t;
	int f;
	f = open("scenar", O_WRONLY);
	printf ("voyage\n");
	scanf("%s", t.identp);
	printf ("code\n");
	scanf("%c", &t.code);
	printf("nombre max de places\n");
	scanf("%i", &t.nb_max_places);
	
	write (f, &t, sizeof(t));

    close(f);
	return 0;
}

