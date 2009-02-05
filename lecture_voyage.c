/*
* code ne servant que à regarder ce qu'il y a dans le fichier binaire fVoyages.
* auteur : Sophie
*/
#include "type_definitions.h"

int main(){
	int f;
	int verif_lecture;
	int finf = 0;
	struct produit p;

	f = open("fVoyages",O_RDONLY);

	do{
		
		verif_lecture = read(f,&p, sizeof(Produit));
		
		if ( verif_lecture > 0)
		{
			printf("%s | %d \n",p.identp, p.nb_max_places);
		}
		else
		{
			printf("erreur de lecture \n");
			finf = 1;
		}

	}
	while(finf == 0);


	close(f);
	return 0;
}
