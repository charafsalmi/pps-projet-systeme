/*
* pour créer le fichier de transaction pour l'administration (un enregistrement par exécution)
* auteur : Sophie
*/

#include "type_definitions.h"


int main(){
	struct Transaction_Admin t;
	int f,i;
	f = open("scenar", O_WRONLY | O_CREAT,S_IRWXU);
	lseek(f, 0, SEEK_END);
	printf("voyage\n");
	scanf("%s", t.identp);
	printf("mettre 1 pour C, mettre 0 pour supprimer\n");
	scanf("%d", &i);
	if ( i == 0 )
	{ 
		t.code = 'F';
	}
	else
	{
		t.code = 'C';
	}
	
	printf("nombre max de places\n");
	scanf("%i", &t.nb_max_places);
	
	
	write (f, &t, sizeof(t));

    close(f);
	return 0;
}

