Projet système IUT Descartes informatique groupe 204 année 2008/2009 (S4)


---


Le thème de l'application est une agence de voyage.

L'architecture de l'application et des ses données est décrite dans le sujet. Le développement se fait en C, sous linux.

L'application est composée de 4 services principaux : direction, administration, accueil, et les guichets.

> - Direction est le service qui gère les autres services en les créant, les suspendant, les reprenant ou les arrêtant.

> - Administration crée et tient à jour un catalogue de voyages.

> - Accueil reçoit les clients et les oriente vers les guichet adéquate. Administration affiche aussi les réservations closes.

- Guichet[i](i.md) traite les demandes des clients sur les voyages existants dans le catalogue.

On lance l'application comme cela :
$ agence f[nom\_fichier\_administration](nom_fichier_administration.md) f[nom\_fichier\_clients](nom_fichier_clients.md) [nombre\_guichets](nombre_guichets.md)