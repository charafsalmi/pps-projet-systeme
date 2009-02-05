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
#include "type_definitions.h"



void creation_voyage(struct Transaction_Admin t/*s, int tube, int pid*/){

	struct produit p;
	struct reservation r;
	char nomfichier [Tmax_nom_produit + 20];
	int f;
	
	strcpy(p.identp, t.identp);
	p.nb_max_places = t.nb_max_places;
	p.nb_places_libres = t.nb_max_places;
	
	flock(f,LOCK_EX);
	f = open("fVoyages", O_WRONLY | O_CREAT,S_IRWXU);
	lseek(f, 0, SEEK_END);
	
	write (f, &p, sizeof(p));
    close(f);
    flock(f,LOCK_UN);
    
    
    // création des fichiers pour le voyage en question
    sprintf(nomfichier, "Reservations/%s.reserv", p.identp);
    f = open(nomfichier, O_CREAT,S_IRWXU);
    close(f);
    sprintf(nomfichier, "Reservations/%s.fa", p.identp);
    f = open(nomfichier, O_CREAT,S_IRWXU);
    close(f);
     
    //envoyer dans le tube 
    /*
    write(tube, &t, sizeof(t));
    kill(pid, SIGUSR1);
    */

}

void sup_voyage(struct Produit tmp){
	int f;
	f = open("fVoyages", O_RDWR);
	lseek(f, 0, SEEK_SET);
	int erreur=0;
	
	while(erreur!=-1 && (strcmp(tmp.identp, voy)!=0){
		erreur=read(f, &erreur, sizeof(Produit));
	}
	while((read(f, &tmp, sizeof(Produit))) > 0){
		lseek(f, (-sizeof(Produit))*2, SEEK_CUR);
		write(f, &tmp, sizeof(Produit));
		lseek(fReserv,(sizeof(Produit))*2, SEEK_CUR);
	}
	char* s=EOF;
	write (f, &s, sizeof(s));
	
	close(f);
}




int main(int nbarg , char* tbarg[]){
	int fTransac_ad;
    int fVoy;
	int verif_lecture;
	int finAdmin = 0;

	printf("%s \n",tbarg[1]);
	struct Transaction_Admin Tab_trans;
	fTransac_ad = open(tbarg[1],O_RDONLY);

	do{
		
		verif_lecture = read(fTransac_ad,&Tab_trans, sizeof(Tab_trans));
		
		if ( verif_lecture > 0)
		{
			switch(Tab_trans.code)
			{
				//Creation
				case 'C':
				{
					printf("creation : \n");
					creation_voyage(Tab_trans);
					break;
				}
				case 'F':
				{
					printf("cloture : \n");
					break;
				}
			}
			printf("%s | %c | %d \n",Tab_trans.identp ,Tab_trans.code, Tab_trans.nb_max_places);

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


