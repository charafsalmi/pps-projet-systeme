/*
 * process_padministration.c
 *
 *  Created on: 23 janv. 2009
 *      Author: Sophie SURMONT
 */


#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define NB_max_voyages            5
#define Tmax_nom_produit        8
#define Tmax_nom_utilisateur    7
#define NB_max_guichets            5

struct Trans_ad
{
    /*
     * Nom du voyage
     */
    char identp[Tmax_nom_produit];
    /*
     * Code de transaction :
     *     - C)réation
     *  - F)ermeture
     */
    char code;
    /*
     * N'est utilisé que pour le code C
     */
    int nb_max_places;
};



int main(int nbarg , char* tbarg[]){
	int fTransac_ad;
    int fVoy;
	int verif_lecture;
	int finAdmin = 0;

	printf("%s \n",tbarg[1]);
	struct Trans_ad Tab_trans;
	fTransac_ad = open(tbarg[1],O_RDONLY);

	do{
		verif_lecture = read(fTransac_ad,&Tab_trans, sizeof(Tab_trans));
		if ( verif_lecture != 0 )
		{
			switch(Tab_trans.code)
			{
				//Creation
				case 'C':
				{
					printf("creation \n");
					break;
				}
				case 'F':
				{
					printf("cloture \n");
					break;
				}
			}
			//printf("%s | %c | %d \n",Tab_trans.identp ,Tab_trans.code, Tab_trans.nb_max_places);
			printf("%8s \n",Tab_trans.identp);
		}
		else
		{
			printf("erreur de lecture \n");
			finAdmin=1;
		}


	}
	while(finAdmin == 0);


	close(fTransac_ad);
	return 0;
}
