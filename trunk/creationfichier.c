#include "type_definitions.h"

/*
* pour créer le fichier de transaction pour l'administration
*/
int main(){
	struct Transaction_Admin t;
	int f;
	f = open("scenar", O_WRONLY | O_CREAT,S_IRWXU);
	lseek(f, 0, SEEK_END);
	printf ("voyage\n");
	scanf("%s", t.identp);
	t.code='F';
	printf("nombre max de places\n");
	scanf("%i", &t.nb_max_places);
	
	write (f, &t, sizeof(t));

    close(f);
	return 0;
}

