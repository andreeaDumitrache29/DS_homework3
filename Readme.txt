/*DUMITRACE Daniela Andreea 311CB*/

		f_coada_void.c

	InitQ
Creeaza coada vida cu elemente de dimensiune d. Se aloca memorie pentru noua coada si se intializeaza inceputul si sfarsitul cu NULL.

	IntrQ
 Pune elementul ae la finalul cozii. Creez o noua celula de lista in care copiez informatia din ae si o inserez la sfrsit, apoi mut sfarsitul pe noul element.

 	ExtrQ
Extrage elementul din varful cozii. Copiaza informatia din inceput laadresa ae si actualizeaza inceputul.

	DistrQ
Retin inceputul intr-o noua celula pe care o distrug, aopi trec mai departe, actualizand inceputul. Operatia se repeta pentru fiecare element din coada.

	PrimQ
Copiez in ae informativa din inceputul cozii, fara a-l modifica.

		f_arb.c

	InitNode
Alocamemorie pentru un element de tip TNode; initializeaza legaturile catre frate si fiu cu NULL si introduce in campurile lit si cod parametrii dati.

	add
Insereaza unei literere cu codificarea corespunzatoare in arbore. Deoarece in campul cod al unui nod retin tot codul de la radacina pana in pozitia respectiva, creez un sir auxliar pentru codul literei de inserat, sir care se modifica la fiecare pas pana ajung la codul literei, moment in care se insereaza nodul final.
Initializez nodul de inserat in functie de pasul la care ma aflu. Daca parintele nodului ce trebuie inserat nu are alti fii, il inserez direct si trec mai departe. Altfel, verific daca cumva fiul sau fratii acestuia au deja codul ce trebuie inserat. Daca codul era deja introdus: daca nodul cu codul de inserat nu are litera, atunci doar devine parinte pentru urmatorul nod; altfel, actualizez litera din nodul curent si inserarea s-a incheiat. Daca codul nu exista in arbore, atunci actualizez fratele ultimului fiu al parintelui pentru a insera nodul curent in arbore si trec mai departe.
	
	print_Node
Afiseaza informatia dintr-un nod. Am codificat radacina prin spatii, deoarece stiam ca acestea nu vor fi introduse niciodata in arbore. Ifunctiede informatia din nod, afisez codul/ litera si codul din nodul dat parametru.

	print_Tree
Folosesc o coada pentru a efectua parcurgerea in latime. Introduc radacina in coada. Apoi, cat timp coada este nevida: extrag elementul curent, il afisez si si introduc fiii in coada. Pentru a stii cand am trecut la un nivel nou *deci trebuie sa afisez pe o linie noua* retin primul element introdus de pe un nivel intr-un nod auxiliar si verific la fiecare extragere daca elementul extras este cel retinut sau nu.

	Decode
Afiseaza litera corespunzatoare codului dat ca parametru. Folosesc o coada pentru a parcurge arborele. Introduc radacina in coada. Apoi, cat timp coada este nevida: extrag elementul curent si verific daca are litera corespunzatoare. Daca da, intrerup cautarea si afisez litera. Daca nu, ii inserez fiii in coada si trec la urmatorul nod.


	Reconstruct
Construiesc un arbore care este identic cu cel nou, fara litera de sters. Folosesc doua cozi: una cu care parcurg arborele intial, si una pentru noul arbore. Introduc radacina vechiului arbore in coada. Cat timp coada e nevida: Extrag elemntul curent. Daca nu are litera de sters, il inserez in noua coda. Altfel: daca are fii, atunci nodul nu trebuie sters, deci il introduc in coada. Daca nu are fii, nu il introduc in noua coada. Pentru a putea sterge si calea pana la nod in noul arbore *daca e necesar* retin intr-un vector codificarea pas cu pas pentru calea pana la nodul cu litera de eliminat. Daca nodul curent are fii, ii introduc in coada.
Pentru a construi noul arbore: Extrag elementele din a doua coada. Verific daca codul lor se afla in vectorul de codificari pentru calea spre litera de sters. Daca nu, il introduc in noul arbore. Daca da, verific daca este chiar nodul ce trebuia sters: daca da, inseamna ca are fii, deci nu trebuie sters, asa ca il voi introduce in noul arbore fara litera.
Daca nu, inseamna ca ma afu pe calea spre nodul de sters. prima data verific daca nodul curent are litera, caci daca da, el trebuie sa fie introdus in arbore. Daca nu, verific daca fiii pana la nodul de eliminat mai au vreun frate. Daca nu, atunci toata calea pana la nodul cu litera de eliminat trebuie stearsa. 
Verific apoi daca fiul nodului d inserat sau vreun frate de-al sau are in cpaul lkteraa litera de eliminat. Daca da, atunci actualizez legaturile intre frate si introduc nodul in noul arbore. Daca nodul de eliminat nu se afla printre fii nodului curent, il introduc in noul arbore.


		main.c
	Initializez arborele si deschid fisierele necesare. Citesc apoi numarul de noduri si construiesc arborele. Dupa aceasta, citesc separatorul de litere si numarul de operatii si in functie de operatie  citesc si restul parametrilor si apelez functia corespunzatoare.
	Dupa efectuarea tuturor operatiilor citesc textul de decodificat linie cu linie. Despart textul dupa separatorul de litere si afisez corespunzator in fisierul de iesire litera corespunzatoare codului.



