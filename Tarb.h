#include "TCoada.h"

/*DUMITRACE Daniela Andreea 311CB*/

/*structura pentru un nod din arbore*/
typedef struct Node {
	char lit, *cod;		/*litera si codul */
	struct Node *fiu, *frate;	/*pentru fiecare nod retin primul fiu si primul frate */
} TNode, *TArb, **AArb;

/*functii arbore*/
TArb InitNode(char c1, char *c2);
int add(TArb a, char *cod, char l);
void print_Tree(TArb a, FILE * f);
void print_Node(TArb a, FILE * f);
void Decode(char *cod_cuvant, TArb a, FILE * f);
TArb Reconstruct(TArb a, char litera);
void distruge(void *ae);
void DistrArb(AArb a);
