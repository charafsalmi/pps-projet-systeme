/*
 * process_padministration.c
 *
 *  Created on: 23 janv. 2009
 *      Author: Sophie SURMONT
 */


#include "type_definitions.h"

int id_tube;
int finAdmin;


void creation_voyage(struct Transaction_Admin t/*, int pid*/){

	struct produit p;
	struct produit tmp;
	struct reservation r;
	char nomfichier [Tmax_nom_produit + 20];
	int f;
	
	
	strcpy(p.identp, t.identp);
	p.nb_max_places = t.nb_max_places;
	p.nb_places_libres = t.nb_max_places;
	

	f = open("fVoyages", O_RDWR | O_CREAT,S_IRWXU);
	flock(f,LOCK_EX);
	lseek(f, -sizeof(p), SEEK_END);
	read(f, &tmp, sizeof(p));
	if (strcmp(tmp.identp, " ")==0)
	{
		lseek(f, -sizeof(p), SEEK_END);
	}
	else
	{
		lseek(f, 0, SEEK_END);	
	}
	
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
    write(id_tube, &t, sizeof(t));
    kill(pid, SIGUSR1);
    */

}

void sup_voyage(char* voy/*, int pid*/){
	int f;
	
	f = open("fVoyages", O_RDWR);
	flock(f,LOCK_EX);
	lseek(f, 0, SEEK_SET);
	int erreur=0;
	Produit tmp;
	

	while(erreur!=-1 && (strcmp(tmp.identp, voy))!=0)
	{
		erreur=read(f, &tmp, sizeof(Produit));
		if (strcmp(tmp.identp, " ")==0)
		{ erreur=-1; }
	}
	while((read(f, &tmp, sizeof(Produit))) > 0)
	{
		lseek(f, (-sizeof(Produit))*2, SEEK_CUR);
		write(f, &tmp, sizeof(Produit));
		lseek(f,(sizeof(Produit)), SEEK_CUR);
	}
	lseek(f,-sizeof(Produit), SEEK_END);
	strcpy(tmp.identp, " ");
	write (f, &tmp, sizeof(Produit));
	
	
	
	close(f);
	flock(f,LOCK_UN); 
	
	/*
    write(id_tube, &t, sizeof(t));
    kill(pid, SIGUSR1);
    */
}

/*
* cette fonction sera appelé quand le processus Padmin recevra un signal pour qu'il s'arrète
*/

void argh(){
	printf("arggggg\n");
	finAdmin=1;
}


int main(int nbarg , char* tbarg[]){
	int fTransac_ad;
    int fVoy;
	int verif_lecture;
	finAdmin = 0;
	struct sigaction sigCreve;

	sigCreve.sa_handler=argh;
	sigCreve.sa_flags=0;
	sigCreve.sa_restorer=NULL;

	sigaction(SIGUSR1,&sigCreve,NULL);

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
					creation_voyage(Tab_trans/*, tbarg[2]*/);
					break;
				}
				case 'F':
				{
					sup_voyage(Tab_trans.identp/*, tbarg[2]*/);
					break;
				}
			}
			printf("%s - %c - %d \n",Tab_trans.identp ,Tab_trans.code, Tab_trans.nb_max_places);

		}
		else
		{
			printf("Fin de lecture (ou erreur)\n");
			finAdmin=1;
		}

	}
	while(finAdmin == 0);


	close(fTransac_ad);
	close(id_tube);
	return 0;
}


