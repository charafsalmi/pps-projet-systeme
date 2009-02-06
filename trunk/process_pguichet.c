/*
 * process_pguichet.c
 *
 *  Created on: 23 janv. 2009
 *      Author: François HAURIT
 */

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <signal.h>

#include "type_definitions.h"
int voy_places_act(int fVoyages,char* identp){
	int i;
	lseek(fVoyages,0,SEEK_SET);
	struct produit tmp;
	int tem=0;
	while(tem!=-1 && (strcmp(tmp.identp,identp)!=0) ){
		tem=read(fVoyages,&tmp,sizeof(Produit));
	}
	i = atoi(tmp.nb_places_libres);
	return i;
}


int voy_places_max(int fVoyages,char* identp){
	int i;
	lseek(fVoyages,0,SEEK_SET);
	struct produit tmp;
	int tem=0;
	while(tem!=-1 && (strcmp(tmp.identp,identp)!=0)){
		tem=read(fVoyages,&tmp,sizeof(Produit));
	}
	i = atoi(tmp.nb_max_places);
	return i;
}

void maj_fvoyages(int fVoyages, int places){
	struct produit tmp;
	lseek(fVoyages,-sizeof(Transaction),SEEK_CUR);
	read(fVoyages,&tmp,sizeof(Produit));
	tmp.nb_places_libres=places;
	lseek(fVoyages,-sizeof(Transaction),SEEK_CUR);
	write(fVoyages,&tmp,sizeof(Produit));
}

void supp_reserv(int fReserv,char* identu){
	lseek(fReserv,0,SEEK_SET);
	struct reservation tmp;
	int tem=read(fReserv,&tmp,sizeof(Reservation));
	while(tem!=-1 && (strcmp(tmp.identu,identu)!=0)){
		tem=read(fReserv,&tmp,sizeof(Reservation));
		if (strcmp(tmp.identu, " ")==0)
		{ tem=-1; }
	}
	while((read(fReserv,&tmp,sizeof(Reservation))) > 0){
		lseek(fReserv,(-sizeof(Reservation))*2,SEEK_CUR);
		write(fReserv,&tmp,sizeof(Reservation));
		lseek(fReserv,(sizeof(Reservation)),SEEK_CUR);
	}
	strcpy(tmp.identu," ");
	lseek(fReserv,-(sizeof(Reservation)),SEEK_CUR);
	write(fReserv,&tmp,sizeof(Reservation));
	
}


int main(int nbarg, char *tbarg[])
{
        /*
         * Début du programme
         */
	/*
	struct transaction trcli;
	//Déclarations fichiers
	int fVoyages;
	int fReserv;
	int fFa;
	int fTransac;
	fVoyages=open("fVoyages",O_RDWR,S_IRWXU);
	fTransac=open("fTransactions_clients",O_WRONLY | O_APPEND,S_IRWXU);
	
	char nomFreserv[Tmax_nom_produit + 20];
	char nomFfa[Tmax_nom_produit + 16];
	printf("guichet %s\n",tbarg[1]);
	//c'est parti
	int tAccu_lecture=atoi(tbarg[2]);
	while(read(tAccu_lecture,&trcli,sizeof(Transaction)) > 0){
		//On lock fVoyages (il ne faudrait pas qu'un petit malin modifie nos données en cours de route...)
		flock(fVoyages,LOCK_EX);
		//on prépare les fichiers
		sprintf(nomFreserv,"Reservations/%s.reserv",trcli.identp);
		sprintf(nomFfa,"Reservations/%s.fa",trcli.identp);
		if(trcli.code=='R'){//on a une réservation
			//on va chercher des renseignement sur les places dispo
			int places_act=voy_places_act(fVoyages, trcli.identp);
			int places_max=voy_places_max(fVoyages, trcli.identp);
			//on verifie la disponibilité
			if((places_act - atoi(trcli.nb_places))>= 0){
				//On a assez de places !!!
				//On MAJ le fichier fVoyages
				maj_fvoyages(fVoyages,(places_act - atoi(trcli.nb_places)));
				flock(fVoyages,LOCK_UN);
				//On MAJ le fichier Voy.reserv
				fReserv=open(nomFreserv,O_WRONLY | O_APPEND,S_IRWXU);
				struct reservation tmp;
				strcpy(tmp.identu,trcli.identu);
				tmp.nb_places=trcli.nb_places;
				flock(fReserv,LOCK_EX);
				write(fReserv,&tmp,sizeof(Reservation));
				flock(fReserv,LOCK_UN);
				close(fReserv);

			}
			else{
				//On libère fVoyages
				flock(fVoyages,LOCK_UN);
				//On MAJ le fichier Voy.fa
				fFa=open(nomFfa,O_WRONLY | O_APPEND,S_IRWXU);
				struct reservation tmp;
				strcpy(tmp.identu,trcli.identu);
				tmp.nb_places=trcli.nb_places;
				flock(fFa,LOCK_EX);
				write(fFa,&tmp,sizeof(Reservation));
				flock(fFa,LOCK_UN);
				close(fFa);
			}
		}
		else if(trcli.code=='L'){//on a une liberation
			//On supprime l'article de Voy.reserv
			fReserv=open(nomFreserv,O_RDWR,S_IRWXU);
			flock(fReserv,LOCK_EX);
			supp_reserv(fReserv,trcli.identu);
			flock(fReserv,LOCK_UN);
			
			//On met à jour fVoyages
			int places_act=voy_places_act(fVoyages, trcli.identp);
			maj_fvoyages(fVoyages,(places_act + atoi(trcli.nb_places)));
			flock(fVoyages,LOCK_UN);
			//On fait passer le contenu de Voy.fa à la fin de fTransactions_clients
			fFa=open(nomFfa,O_RDWR,S_IRWXU);
			flock(fFa,LOCK_EX);
			struct reservation Rtmp;
			struct transaction Ttmp;
			flock(fTransac,LOCK_EX);
			
			while((read(fFa,&Rtmp,sizeof(Reservation))) > 0){
				strcpy(Ttmp.identp,trcli.identp);
				strcpy(Ttmp.identu,Rtmp.identu);
				Ttmp.code='R';
				Ttmp.nb_places=Rtmp.nb_places;
				write(fTransac,&Ttmp,sizeof(Transaction));
			}
			lseek(fFa,0,SEEK_SET);
			char* s=EOF;
			write(fFa,&s,sizeof(s));
			flock(fTransac,LOCK_UN);
			flock(fFa,LOCK_UN);
			close(fFa);
		}


	}
	close(fVoyages);
	close(fTransac);
	*/

	

        /*
         * Fin du programme
         */
        return 0;
}
