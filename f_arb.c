/*DUMITRACHE Daniela Andreea 311CB*/
#include "Tarb.h"

/*Aloca memorie si construieste un nod cu informatia data*/
TArb InitNode(char c1, char *c2)
{
	TArb a = (TArb) malloc(sizeof(TNode));	/*alocare si verificare */

	if (!a)
		return NULL;

	a->fiu = NULL;
	a->frate = NULL;	/*intializez legaturile */
	a->lit = c1;		/*litera si codul pentru nod */
	a->cod = strdup(c2);
	return a;
}

void distruge(void *ae)
{
	TArb a = ae;
	if (!a)
		return;

	distruge(a->frate);
	distruge(a->fiu);
	free(a->cod);
	free(a);
}

void DistrArb(AArb a)
{
	if (!(*a))
		return;

	distruge(*a);
	*a = NULL;
}

/*insereaza o noua litera in arbore*/
int add(TArb a, char *cod, char l)
{
	char *s = strdup(cod);
	int i;
	TArb aux, b = InitNode(' ', " ");	/*noduri auxiliare */
	char *x = calloc(20, sizeof(char));

	if (strcmp(cod, " ") == 0 && l == ' ')	/*pentru a nu introduce un nod cu codificarea radacinii */
		return 0;

	for (i = 0; i < strlen(s); i++) {
		x[i] = s[i];	/*la fiecare pas refac codul nodului  de inserat */

		if (i == strlen(s) - 1)
			aux = InitNode(l, x);	/*daca am ajuns la ultimul caracter din cod, introduc si litera */
		else
			aux = InitNode(' ', x);

		if (!aux)
			return 0;

		if (a->fiu == NULL) {	/*daca parintele nodului de inserat nu are fiu,il inserez direct si trec mai departe */
			a->fiu = aux;
			a = a->fiu;
		} else {	/*parintele are deja alti fii */

			int ok = 0;
			b = a->fiu;	/*altfel, verific sa nu existe deja un nod cu codificarea ce trebuie inserata */

			/*verific intai fiu */
			if (strcmp(b->cod, aux->cod) == 0 && aux->lit == ' ')	/*exista deja nodul, deci mai departe doar devine parinte */
				ok = 1;
			else if (strcmp(b->cod, aux->cod) == 0 && aux->lit != ' ' && b->lit == ' ') {	/*exista codul, dar fara litera */
				b->lit = aux->lit;
				ok = 2;	/*nu trebuie sa inserez mai departe */
			} else {	/*verific si fratii pentru a nu exista deja codificarea de inserat la pasul curent in arbore */
				while (b->frate != NULL) {	/*parcurg nivelul pana parintele nu mai are fii */
					b = b->frate;

					if (strcmp(b->cod, aux->cod) == 0 && aux->lit == ' ') {	/*exista nodul, deci devine parinte */
						ok = 1;
						break;
					} else if (strcmp(b->cod, aux->cod) == 0 && aux->lit != ' ') {	/*exista codul, dar fara litera */
						b->lit = aux->lit;
						ok = 2;	/*nu mai am nimic de inserat */
						break;
					}
				}

			}

			if (ok == 0) {
				b->frate = aux;	/*parintele avea alt fiu, deci de la ultimul frate mai introduc un fiu */
				a = aux;
			} else if (ok == 1) {	/*nodul de inserat devine parinte */
				a = b;
			}
		}
	}
	free(x);
	free(s);
	return 1;
}

/*afiseaza un nod*/
void print_Node(TArb a, FILE * f)
{
	/*am codificat radacina prin spatii, deoarece stiam ca acestea nu vor fi introduse niciodata in arbore */
	if (a->lit == ' ' && strcmp(a->cod, " ") == 0)	/*afiseaza radacina */
		fprintf(f, "(:)");
	else if (a->lit == ' ' && strcmp(a->cod, " ") != 0)	/*afiseaza un nod fara litera */
		fprintf(f, "(%c:)", a->cod[strlen(a->cod) - 1]);
	else
		fprintf(f, "(%c:%c)", a->cod[strlen(a->cod) - 1], a->lit);	/*afiseaza un nod cu litera */
}

void print_Tree(TArb a, FILE * f)
{
	ACoada q = InitQ(sizeof(TNode));	/*folosesc o coada pentru a parcurge arborele */
	if (!q)
		return;
	TArb aux = InitNode(' ', " ");	/*nodul in care voi extrage infromatii din coada */
	TArb x = InitNode(' ', ":=alala");	/*nod in care voi retine ultimul nod de pe un nivel */

	if (a != NULL)		/*introduc radacina in coada dacaarborele este nevid */
		IntrQ(q, a);
	else
		return;

	int ok = 0;
	while (IC(q) != NULL) {	/*cat timp coada e nevida */
		ExtrQ(q, aux);	/*extrag primul element */
		if (x->lit == aux->lit && strcmp(x->cod, aux->cod) == 0) {	/*primul element de pe noul nivel */
			fprintf(f, "\n");	/*trec la nivel nou, deci afisez pe linie noua */
			ok = 0;
		}
		print_Node(aux, f);	/*aiseaza informatia din nod */

		if (aux->fiu != NULL) {
			IntrQ(q, aux->fiu);	/*daca nodul are fii, ii introduc in coada */
			if (ok == 0) {
				x = aux->fiu;	/*retin primul iu de pe acest nivel */
				ok = 1;
			}
			while (aux->fiu->frate != NULL) {	/*introduc in coada si restul fiilor nodul curent */
				IntrQ(q, aux->fiu->frate);
				aux->fiu = aux->fiu->frate;
			}
		}
	}
	fprintf(f, "\n");	/*se termina afisarea */
	DistrQ(q, distruge);
}

void Decode(char *cod_cuvant, TArb a, FILE * f)
{
	if (!a)			/*arbore vid */
		return;

	char *cuvant = calloc(5, sizeof(char));	/*litera de decodificat */

	ACoada q = InitQ(sizeof(TNode));	/*parcurg pe nivel si caut litera folosind o coada */
	if (!q)
		return;

	TArb aux = InitNode(' ', " ");	/*nodul in care voi extrage inormatia din coada */
	IntrQ(q, a);		/*introduc radacina arborelui in coada */

	while (IC(q) != NULL) {
		ExtrQ(q, aux);	/*nodul curent */

		if (strcmp(aux->cod, cod_cuvant) == 0) {	/*daca are codul cautat */
			cuvant[0] = aux->lit;	/*retin litera si opresc cautarea */
			break;
		}

		if (aux->fiu != NULL) {	/*nodul extras nu era cel cautat, deci ii introduc fiii in coada */
			IntrQ(q, aux->fiu);

			while (aux->fiu->frate != NULL) {
				IntrQ(q, aux->fiu->frate);
				aux->fiu = aux->fiu->frate;
			}
		}
	}
	if (cuvant != NULL) {	/*daca s-a gasit litera, o afisez */
		fprintf(f, "%s", cuvant);
	}

}

TArb Reconstruct(TArb a, char litera)
{				/*construiesc un arbore care este identic cu cel nou, fara litera de sters */

	if (!a)			/*test arbore vid */
		return NULL;

	ACoada q = InitQ(sizeof(TNode));	/*coada cu care voi parcurge aroborele vechi */
	if (!q)
		return NULL;

	ACoada c = InitQ(sizeof(TNode));	/*coada cu care construiesc noul arbore */
	if (!c)
		return NULL;

	TArb aux = InitNode(' ', " "), fr = InitNode(' ', " ");	/*noduri auxiliare */
	TArb b = InitNode(' ', " ");	/*noul arbore */
	char *code, **v;
	int i, j, ok;

	IntrQ(q, a);		/*introdul in coada radacina vechiului arbore */

	while (IC(q) != NULL) {
		ExtrQ(q, aux);	/*extrag elementul curent din coada */

		if (aux->lit != litera) {	/*daca nu are litera cautat, il introduc in noua coada */
			IntrQ(c, aux);
		} else {
			code = strdup(aux->cod);	/*salvez codul literei de eliminat */
			v = calloc((strlen(code) + 1), sizeof(char *));
			for (i = 0; i < strlen(code) + 1; i++) {	/*salvez codul la fiecare pas pana la final pentru a putea gasi calea catre nodul cu litera de eliminat */
				v[i] = calloc((i + 1), sizeof(char));
				for (j = 0; j < i; j++)
					v[i][j] = code[j];
			}

			if (aux->fiu != NULL) {
				IntrQ(c, aux);	/*introduc nodul in noua coada daca are fii, deoarece nu trebuie sters */
			}
		}

		if (aux->fiu != NULL) {
			IntrQ(q, aux->fiu);	/*inserez in coada fii elementului curent */

			while (aux->fiu->frate != NULL) {
				IntrQ(q, aux->fiu->frate);
				aux->fiu = aux->fiu->frate;
			}
		}
	}

	/*coada pentru noul arbore */
	while (IC(c) != NULL) {
		ExtrQ(c, aux);	/*extrag elementul curent */

		i = 1;

		for (j = 0; j < strlen(code) + 1; j++) {
			if (strcmp(aux->cod, v[j]) == 0) {	/*daca codul elementului se afla in vectorul de codificari */
				i = 0;	/*ma aflu pe calea spre nodul cu litera de eliminat */
				break;
			}
		}

		if (i == 0) {	/*sunt pe calea spre nodul de sters */
			if (aux->lit != litera) {	/*nodul curent nu este cel cu litera de eliminat */
				if (aux->lit != ' ')	/*daca nodul are o litera in informatie, il introduc in noul arbore */
					add(b, aux->cod, aux->lit);
				else {
					ok = 0;
					fr = aux->fiu;	/*parcurg fii pana la nodul de eliminat */
					while (fr != NULL) {
						if (fr->frate != NULL) {	/* toata calea trebuie stearsa daca niciunul dintre fii nu mai are alt frate */
							ok = 1;	/*am gasit un alt frate, deci nu trebuie stearsa toata calea */
							break;
						}
						fr = fr->fiu;
					}

					if (ok == 1) {	/*cazul cand nu se sterge toata calea pana la nodul de eliminat */
						if (aux->fiu->lit == litera && aux->fiu->frate != NULL) {	/*fiul nodului curent este litera de eliminat, dar aceasta mai are si alti frati */
							aux->fiu = aux->fiu->frate;	/*fiu devine fratele nodului de eliminat */
							add(b, aux->cod, aux->lit);	/*introdul noul nod in arbore */
						} else if (aux->fiu->lit != litera) {	/*fiul nu are litera de eliminat, deci verifc fratii */
							ok = 0;	/*nu am gasit litera de eliminat */
							fr = aux->fiu;

							while (fr->frate != NULL) {	/*caut cat timp exista frati */
								if (fr->frate->lit == litera) {	/*am gasit litera de eliminat */
									ok = 1;
									fr->frate = fr->frate->frate;	/*actualizez fratele pentru nodul ce avea drept frate litera de eliminat */
									add(b, aux->cod, aux->lit);	/*introduc nodul in arbore */
									break;
								}
								fr = fr->frate;
							}
							if (ok == 0)
								add(b, aux->cod, aux->lit);	/*nodul de introdus nu are ca fii nodul de eliminat */
						}
					}
				}
			} else if (aux->lit == litera && aux->fiu != NULL)	/*am gasit nodul cu litera de sters, dar are fii deci nu trebuie sters */
				add(b, aux->cod, ' ');

		} else
			add(b, aux->cod, aux->lit);	/*nu ma aflu pe calea spre nodul de eliminat */
	}

	for (i = 0; i < strlen(code) + 1; i++)
		free(v[i]);
	free(v);

	DistrQ(q, distruge);
	DistrQ(c, distruge);
	DistrArb(&aux);
	DistrArb(&fr);
	return b;
}
