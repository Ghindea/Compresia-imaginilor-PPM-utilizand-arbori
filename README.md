# **Compresia imaginilor utilizand arbori**   
Temă realizată în cadrul cursului de Structuri de Date și Algoritmi, anul I  

*made by: Ghindea Daniel 315CB*   
*about: comprimarea și decomprimarea fisierelor .ppm + determinarea unor proprietăți*
#
### Cerinta temei:  
<https://1drv.ms/b/s!Anf80JE8EFUq_WM1K2lQko6SAXHE?e=NZEhCO>
#
### **Structura programului:**

###   - `header.h`
- contine definirea structurilor utilizate in program. tipul "**RGB**" se foloseste pentru a retine culoarea unui bloc, pe canale. "**TArb**"/"**TNod**" sunt folosite pentru implementarea arborelui cuaternar, retinand tipul nodului (1 - frunza/ 0 - parinte), culoarea (tip RGB) si adresele celor 4 fii. "**TCoada**", impreuna cu "**TLista**"/"**TCelula**" au rol in implementarea cozii folosite pentru parcurgerea pe nivel (vezi task 2 si task 3). pe langa acestea se regasesc si antetele functiilor utilizate in program.

###   - `main.c`
- contine initializarea poinerilor de fisier, citirea datelor si apelarea functiilor corespunzatoare fiecarei cerinte

###   - `functions.c`
- contine functii folosite in una sau mai multe cerinte:
    - `[average]`  - determina culoarea medie a blocului de marime "**size**", aflat in matrice la linia "**x**" si coloana "**y**"
    - `[readData]`-  citeste datele din fisierul .ppm (folosita in cerintele 1 si 2)
    - `[makeArb]`  - construieste arborele cuaternar pe baza matricei, conform cerintei
    - alte functii ajutatoare

###   - `task1.c`
- contine rezolvarea primei cerinte:
    - `[nrNiv]`  - returneaza numarul de nivele ale arborelui
    - `[frunze]` - cum datele referitoare la culoarea unui bloc se afla doar pe nodurile terminale ale arborelui cuaternar, pentru a calcula numarul de blocuri din imagine pentru care scorul similaritatii pixelilor este <= decat factorul furnizat este indeajuns sa determinam numarul de frunze ale arborelui
    - `size / (1 << (nrNivMin(img)-1))` - dat fiind ca fiecare nivel al arborelui (cu exceptia radacinii) corespunde unui cvadruplet de blocuri cu lungimile laturilor injumatatite fata de lungimile precedente, se poate determina lungimea unui bloc impartind `lungimea imaginii` ("**size**") la `2^index_nivel` . pentru a determina dimensiunea laturii celui mai mare patrat nedivizat este suficient sa determinam nivelul minim pe care se afla o frunza.

###   - `task2.c`
- contine rezolvarea celei de-a doua cerinte. pentru a parcurge arborele cuaternal pe nivel se implementeaza o coada, sub forma unei liste simplu inlantuite, la inceputul careia se introduce radacina arborelui si care, cat timp coada e nevida, functioneaza dupa cum urmeaza:
    - se adauga in coada adresele copiilor nodului curent
    - se scrie in fisierul binar 0 pentru nod neterminal sau 1 pentru frunza
    - in cazul in care nodul e frunza se scriu datele RGB
    - se elimina primul element al cozii
- astfel, la finalul executarii functiei, se va forma imaginea comprimata.

###   - `task3.c`
- contine rezolvarea celei de-a treia cerinte. pentru a decomprima imaginea se realizeaza procedeul invers celui anterior. se citesc datele radacinii arborelui cuaternar, iar aceasta este inserata in coada. cat timp coada e nevida, se procedeaza in felul urmator:
    - se initializeaza adresele pentru copiii si se citesc datele acestora
    - se adauga copiii in coada
    - se elimina primul element al cozii
- odata format arborele, se apeleaza functia recursiva `[makeMatrix]` care, pe baza acestuia, construieste matricea imaginii. daca nodul este neterminal, in submatricea de marime "**size**", aflata la linia "**x**" si coloana "**y**", se pun datele RGB ale nodului, altfel se face apelul cu "**size**" injumatatit si coordonate aferente celor 4 subzone
- la final, matricea este scrisa in fisierul .ppm, alaturi de ceilalti parametri.
---
