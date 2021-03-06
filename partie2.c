#include <stdio.h>
#include <stdlib.h>

/*************************************************/
/*                                               */
/*                sucre syntaxique               */
/*                                               */
/*************************************************/

#define AND &&
#define OR ||
#define ISNOT !=
#define NOT !
#define then

typedef enum
  {
    FALSE,
    TRUE
  } bool;

/*************************************************/
/*                                               */
/*          definition type liste                */
/*                                               */
/*************************************************/

typedef struct Bloc {
  int nombre;
  struct Bloc *suivant;
} Bloc;

typedef Bloc *Liste;

/*************************************************/
/*                                               */
/*                predeclarations                */
/*                                               */
/*************************************************/

/* initialise une Liste � vide */
void initVide(Liste *L);

/* renvoie 1 si la Liste en parametre est vide, 0 sinon */
bool estVide(Liste l);

/* renvoie le premier element de la Liste en parametre */
int premier(Liste l);

/* renvoie une nouvelle Liste correspondant a celle en parametre, avec l'element
 * x ajoute en haut de la pile */
Liste ajoute(int x, Liste l);

/* modifie la Liste en parametre: x est ajoute comme premier element */
void empile(int x, Liste *L);

/* renvoie une nouvelle Liste correspondant a celle en parametre sans son
 * premier element */
Liste suite(Liste l);

/* modifie la Liste en parametre: le premier element est retire */
void depile(Liste *l);

/* affichage simple en recursif et en iteratif */
void affiche_rec(Liste l);
void affiche_iter(Liste l);

/* longueur en recursif et en iteratif */
int longueur_rec(Liste l);
int longueur_iter(Liste l);

/*  Elimination du dernier element en recursif et en iteratif  */
/*  VD est la sousprocedure utilitaire de la version recursive */
void VD(Liste *L);
void VireDernier_rec(Liste *L);
void VireDernier_iter(Liste *L);

/*************************************************/
/*                                               */
/*                briques de base                */
/*                                               */
/*************************************************/

void initVide(Liste *L) { *L = NULL; }

bool estVide(Liste l) { return l == NULL; }

int premier(Liste l) { return l->nombre; }

Liste ajoute(int x, Liste l) {
  Liste tmp = (Liste)malloc(sizeof(Bloc));
  tmp->nombre = x;
  tmp->suivant = l;
  return tmp;
}

void empile(int x, Liste *L) { *L = ajoute(x, *L); }

Liste suite(Liste l) { return l->suivant; }

void depile(Liste *L) {
  Liste tmp = *L;
  *L = suite(*L);
  free(tmp);
}

/*************************************************/
/*                                               */
/*     Affiche, avec les briques de base         */
/*                                               */
/*************************************************/

void affiche_rec(Liste l) {
  if (estVide(l))
    printf("\n");
  else {
    printf("%d ", premier(l));
    affiche_rec(suite(l));
  }
}

void affiche_iter(Liste l) {
  Liste L2 = l;
  while (!estVide(L2)) {
    printf("%d ", premier(L2));
    L2 = suite(L2);
  }
  printf("\n");
}

/*************************************************/
/*                                               */
/*     Longueur, sans les briques de base        */
/*                                               */
/*************************************************/

int longueur_rec(Liste l) {
  if (l == NULL)
    return 0;
  else
    return (1 + longueur_rec(l->suivant));
}

int longueur_iter(Liste l) {
  Liste P = l;
  int cpt = 0;
  while (P ISNOT NULL) {
    P = P->suivant;
    cpt++;
  }
  return cpt;
}

/*************************************************/
/*                                               */
/*       VireDernier,                            */
/*               sans les briques de base,       */
/*               ni le "->"                      */
/*                                               */
/*************************************************/

void VD(Liste *L)
// *L non NULL ie liste non vide
{
  if (((**L).suivant) == NULL)
    depile(L); // moralement : depile(& (*L)) ;
  else
    VD(&((**L).suivant));
}

void VireDernier_rec(Liste *L) {
  if ((*L)ISNOT NULL)
    VD(L); // moralement : VD(& (*L)) ;
}

void VireDernier_iter(Liste *L) {
  if ((*L)ISNOT NULL) {
    while (((**L).suivant)ISNOT NULL)
      L = &((**L).suivant);
    free(*L);
    *L = NULL;
  }
}

/*************************************************/
/*                                               */
/*       Libere la memoire                       */
/*                                               */
/*************************************************/

void VideListe(Liste *L) {
  if (NOT(estVide(*L))) {
    depile(L);
    VideListe(L);
  }
}

/*************************************************/
/*                                               */
/*    Listes-Piles et Files                      */
/*                                               */
/*************************************************/

bool ZeroEnDeuxiemePosition(Liste l) {
  if (estVide(l))
    return FALSE;
  return premier(suite(l)) == 0;
}

bool QueDesZeros(Liste l) {
    if (estVide(l))
        return TRUE;
    return premier(l) == 0 ? QueDesZeros(suite(l)) : FALSE;
}

int Compte0InitiauxVRec(Liste l) {
    if (estVide(l) || premier(l) != 0)
        return 0;
    return 1 + Compte0InitiauxVRec(suite(l));
}

int Compte0InitiauxVIte(Liste l) {
  int cpt = 0;
  for (; NOT estVide(l) AND premier(l) != 0; l = suite(l)) {
    cpt++;
  }
  return cpt;
}

int Compte0InitiauxBis(Liste l, int acc) {
  if (estVide(l) || premier(l) != 0)
    return acc;
  return Compte0InitiauxBis(suite(l), acc + 1);
}

int Compte0InitiauxVSsFonc(Liste l) { return Compte0InitiauxBis(l, 0); }

void Compte0InitiauxProBis(Liste l, int *acc) {
  if (NOT estVide(l) && premier(l) == 0) {
    *acc += 1;
    Compte0InitiauxProBis(suite(l), acc);
  }
}

int Compte0InitiauxVSsPro(Liste l) {
  int output = 0;
  Compte0InitiauxProBis(l, &output);
  return output;
}

Liste IntersectionTrieeBis(Liste l1, Liste l2, Liste output) {
  if (estVide(l1) || estVide(l2))
    return output;
  if (premier(l1) > premier(l2))
    return IntersectionTrieeBis(l1, suite(l2), output);
  if (premier(l1) < premier(l2))
    return IntersectionTrieeBis(suite(l1), l2, output);
  return ajoute(premier(l1), IntersectionTrieeBis(suite(l1), suite(l2), output));
}

Liste IntersectionTriee(Liste l1, Liste l2) {
  return IntersectionTrieeBis(l1, l2, NULL);
}

void ElimineKpremiersX(Liste l, int k, int x) {
    Liste prev = NULL;
    while (k > 0 && l != NULL) {
        if (premier(l) == x) {
            prev->suivant = suite(l);
            free(l);
            l = prev->suivant;
            k--; 
        } else {
            prev = l;
            l = l->suivant;
        }
    }
}

void ElimineKderniersXBis(Liste l, Liste post, int *k, int x) {
  if (!estVide(post)) {
    ElimineKderniersXBis(suite(l), suite(post), k, x);
    if ((premier(post) == x) && *k > 0)  {
        l->suivant = post->suivant;
        free(post);
        (*k)--;
    }
  }
}

void ElimineKderniersX(Liste l, int k, int x) {
  if (estVide(l)) return;
  ElimineKderniersXBis(l, suite(l), &k, x);
}

int factorielle(int x) {
  return (if x==0) ? 1 : n * factorielle(x);
}

/*************************************************/
/*                                               */
/*           Main                                */
/*                                               */
/*************************************************/

void poup(Liste l) {
  printf("Double Affichage \n");
  affiche_rec(l);
  affiche_iter(l);

  printf("Longueur en double %d %d \n\n", longueur_rec(l), longueur_iter(l));
}

int main() {
  Liste l;

  initVide(&l);

  poup(l);

  empile(4, &l);

  poup(l);

  empile(5, &l);
  empile(6, &l);
  empile(7, &l);
  empile(8, &l);
  empile(9, &l);

  poup(l);

  VireDernier_rec(&l);
  VireDernier_iter(&l);
  depile(&l);

  poup(l);

  VideListe(&l);
  return 0;
}
