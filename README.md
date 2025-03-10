In cadrul acestei teme am invatat sa lucrez cu arborii. M-am condus mai mult dupa laboratoare si curs si de asemenea am folosit draw_tree pentru a vizualiza copacul meu si greselile la crearea acestuia.

# Cerinta 1

La aceasta cerinta am avut urmatoarea logica:
In primul rand am creat o functie (desp_sufixe) care sa imi ia sirul si sa il desparta in sufixe adaugand direct $ la sfarsit. Aici am implimentat si functia (cmp) pentru a compara lungimea sufixelor si a le sorta cu (qsort), deoarece dupa felul cum am implimentat eu functia primeam $ ca primul caracter si dupa veneau sufixele in ordine descrescatoare, ceea ce m-ar fi incurcat pe parcurs.
In al doilea rand am creat functia (insert_sir), unde inserez caracterele, avand la baza indexul calculat prin formula(idx = sir[i] - 'a' + 1; ) astfel incat a sa aiba indexul 1, b- 2 si tot asa, intruncat indexul 0 e pastrat pentru $.
La final creez arborele utilizand functiile de mai sus.
Printarea am realizato prin implimentarea unei cozi folosite in algoritmul de BFS. Am folosit si niste flaguri, deoarece obtineam un rand gol si spatiu la inceput de rand si am avut nevoie sa scap de ele.

# Cerinta 2

Pentru Numararea Nodurilor din frunza am vur sa incerc ceva nou si sa o fac prin recursivitate. M-am chinuit mult prea mult asa ca restul cerintelor le-am facut print BFS. Aici am incremenetat contorul cand gasea $ , deoarece acesta marcheaza frunzele.

Cat calcularea sufixelor de lungime K atat si MaxDescendenti am facut prin BFS. Am parcurs tot arborele si cat faceam asta fie calculam lungimea si adancimea si verificam daca copilul e $ pentru sufixul ajuns la adincimea K, fie prin parcurgerea fiecarui copil al său și numararea directa si pastreaza intro variabila auxiliara, care se tot actualizeaza.

# Cerinta 3

La vericiarea apartenentei sufixului am folosit aceeasi logica ca si la inserarea sirurilor, unde umpic am schimbat cerinta. pentru a primi fie 0 sau 1 dupa necesitate. Am adaugat si o verificare daca exista un nod cu $ ca fiu al nodului curent pentru a trata toate cazurile posibile.

# MAIN

Pentru a primi comenzi din linia de comanda am utilizat argc si *argv[].
In urma selectarii comenzii(argv[1]) fiecare din ele actioneaza diferit.
-c1: Citesc cu fscanf nr de siruri de caractere de pe prima linie si crearea un arbore cu sirurile date pe urmatoarele linii, printandule cu print_tree_by_levels.
-c2: aici deja avand si parametrul K a trebuie sa schimb fisierele de input si output cu un argument mai mult.De asemenea am citit cu fscanf si am utilizat functiile noduri_frunza,calc_sufix_lungime_K,maxDirectDesc pe arborele creat anterior de create_tree.
-c3: folosind fscanf am citit ambele numere de pe prima linie salvandule in variabile aparte si pe baza acestora am folosit functia verif_sufix pe arborele precedent(create_tree).

# punctaj
Am obtinut 70 de puncte pentru primele 3 taskuri.