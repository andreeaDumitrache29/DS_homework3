#include "Tarb.h"

#define max 6800

/*DUMITRACHE Daniela Andreea 311CB*/

int main(int argc, char const *argv[])
{
	TArb a = InitNode(' ', " ");	/*initializez radacina arborelui */
	TArb b = InitNode(' ', " ");

	FILE *f1, *f2, *f3, *f4;	/*deschid fisierele cu care vom lucra */
	f1 = fopen(argv[1], "rt");
	f2 = fopen(argv[2], "rt");
	f3 = fopen(argv[3], "wt");
	f4 = fopen(argv[4], "wt");

	int n, m, i;
	char litera;
	char *sir = malloc(500 * sizeof(char));
	char separator, *op = (char *)malloc(20 * sizeof(char));

	fscanf(f1, "%d", &n);	/*citesc numarul de noduri */
	fgetc(f1);

	for (i = 0; i < n; ++i) {	/*pentru fiecare nod */
		fscanf(f1, "%c", &litera);	/*litera de introdus */
		fgetc(f1);
		fscanf(f1, "%s", sir);	/*citesc codul literei */
		fgetc(f1);
		add(a, sir, litera);	/*introduc litera in arbore */
	}

	print_Tree(a, f3);	/*afisez arborele dupa creare */
	fscanf(f1, "%c", &separator);	/*citesc separatorul si numarul de operatii */
	fscanf(f1, "%d", &m);

	for (i = 0; i < m; i++) {	/*pentru fiecare operatie */
		fscanf(f1, "%s", op);
		if (strcmp(op, "add") == 0) {	/*avem de adaugat un nou nod in arbore */
			fgetc(f1);	/*citesc litera si coudl nodului de introdus */
			fscanf(f1, "%c", &litera);
			fgetc(f1);
			fscanf(f1, "%s", sir);
			add(a, sir, litera);	/*il inserez in arbore si afisez arborele */
			print_Tree(a, f3);

		} else if (strcmp(op, "delete") == 0) {	/*avem de sters un nod */
			fgetc(f1);
			fscanf(f1, "%c", &litera);	/*citesc liera de sters */
			b = Reconstruct(a, litera);	/*construiesc noul arbore, fara litera ce trebuia eliminata */
			a = b;
			print_Tree(a, f3);	/*afisez arborele */

		}
	}

	char *text = malloc(max * sizeof(char));
	char *aux = NULL, *p;

	/*citesc textul de decodificat */
	while (fgets(text, max, f2) != NULL) {	/*cat timp se citesc linii din fisier */
		aux = strdup(text);
		if (strcmp(aux, "\n") == 0)	/*s-a citit o linie goala */
			fprintf(f4, "\n");
		else if (strcmp(aux, "\n") != 0) {	/*linia nu e goala */
			p = strtok(aux, &separator);	/*codificarea primei litere */
			while (p) {
				if (p[0] == ' ') {	/*daca codul are un spatiu la inceput inseamna ca s-a trecut la un cuvant nou */
					fprintf(f4, " ");	/*afisez spatiul */
					Decode(p + 1, a, f4);	/*elimin spatiul si decodifc litera corespunzatoare */
				} else
					Decode(p, a, f4);	/*afisez litera */

				p = strtok(NULL, &separator);	/*trec mai departe */
			}
			fprintf(f4, "\n");	/*trec la linie noua */
		}
	}

	free(op);
	free(text);
	free(aux);
	free(sir);

	DistrArb(&a);
	DistrArb(&b);

	fclose(f1);
	fclose(f2);
	fclose(f3);
	fclose(f4);

	return 0;
}
