admin :
	gcc process_padministration.c -o padmin -g
	
accueil :
	gcc process_paccueil.c -o paccueil -g
	
direction :
	gcc process_pdirection.c -o pdirection -g
	
guichet :
	gcc process_pguichet.c -o pguichet -g
	
create :
	gcc creation_fichier_transac_admin.c -o create -g
	
lect_voy :
	gcc lecture_voyage.c -o lect_voy -g
	
agence :
	gcc main.c -o agence -g
	
all :
	gcc main.c -o agence -g
	gcc process_padministration.c -o padmin -g
	gcc process_paccueil.c -o paccueil -g
	gcc process_pdirection.c -o pdirection -g
	gcc process_pguichet.c -o pguichet -g
	
clean :
	rm padmin paccueil pdirection pguichet
