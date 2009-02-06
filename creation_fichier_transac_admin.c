/*
* pour créer le fichier de transaction pour l'administration (un enregistrement par exécution)
* auteur : Sophie
*/

#include "type_definitions.h"


int main(){
	struct transaction t;
	int f,i;
	f = open("ppp", O_WRONLY | O_CREAT,S_IRWXU);
	lseek(f, 0, SEEK_END);
	printf("voyage u\n");
	scanf("%s", t.identu);
	printf("voyage p\n");
	scanf("%s", t.identp);
	printf("mettre 1 pour R, mettre 0 pour libéré\n");
	scanf("%d", &i);
	if ( i == 0 )
	{ 
		t.code = 'L';
	}
	else
	{
		t.code = 'R';
	}
	
	printf("nombre max de places\n");
	scanf("%d", &t.nb_places);
	
	
	write (f, &t, sizeof(t));

    close(f);
	return 0;
}

