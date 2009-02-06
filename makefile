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
	
agence : agence.o journal.o
	gcc -o agence agence.o journal.o
	
agence.o : main.c type_definitions.h
	gcc -o agence.o -c main.c

journal.o : journal.c journal.h
	gcc -o journal.o -c journal.c
	
all :
	make agence
	make admin
	make accueil
	make direction
	make guichet
	
clean :
	rm padmin paccueil pdirection pguichet
