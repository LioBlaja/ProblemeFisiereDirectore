# ProblemeFisiereDirectore
A bunch of some solved problems using C and low level functions(read,open,write)


# Cerințe pentru finalizare

## 1. Program pentru citirea și transformarea fișierului de intrare

Să se scrie un program care primește ca și argumente în linie de comandă calea către 2 fișiere:

<program> <fișier-intrare> <fișier-ieșire>


Programul va citi în întregime `<fișier-intrare>`, și va afișa la ieșirea standard octeții transformați după regula următoare:
- Dacă octetul are valoarea între 97 și 122, va fi afișat folosind `printf`, ca și literă mică.
- Altfel, se va afișa în hexadecimal.

La final, programul va scrie în `<fișier-ieșire>` o linie de forma:



---

## 2. Program pentru afisarea detalii fișier/director

Să se scrie un program care primește ca și argument în linie de comandă calea către o intrare de pe disc:
- Tipul intrării: director / fișier obișnuit / legătură simbolică
- Permisiunile pentru owner/user, sub forma: `rwx`, `-` dacă vreuna lipsește
- Dimensiunea în octeți

---

## 3. Program pentru citirea unui fișier binar cu numere întregi

Să se scrie un program care primește ca și argumente în linie de comandă calea către 2 fișiere:
<program> <fișier-intrare> <fișier-ieșire>


Fișierul de intrare va conține un număr necunoscut de numere întregi pe 4 octeți.
Programul va citi fișierul de intrare în întregime și va scrie în fișierul de ieșire, în format text, numărul minim, numărul maxim și media numerelor citite din fișierul de intrare binar.

---

## 4. Program pentru parcurgerea unui director recursiv

Să se scrie un program C care primește ca și argumente în linie de comandă o cale relativă sau absolută de director și o cale către un fișier.

Programul va parcurge recursiv directorul primit ca și parametru:
- Pentru fiecare fișier întâlnit, programul va număra câte litere mici conține acesta.
- Va scrie rezultatul într-un fișier text dat ca și argument în linie de comandă, sub forma:

<cale-director> <dimensiune> <nr-litere-mici> <tip-fișier>


unde `tip-fișier` poate fi: `REG`, `LNK`, `DIR` sau `PIPE`.

Dacă primul argument nu este director, programul va afișa un mesaj de eroare.  
Dacă al doilea argument reprezintă un fișier deja existent pe disc, acesta va fi suprascris.

Programul se va testa folosind un director ce conține directoare, fișiere obișnuite, legături simbolice și named pipes.

---

## 5. Program cu opțiuni pentru afișarea informațiilor

Să se scrie un program care primește un număr variabil de opțiuni din linia de comandă, urmate de minim 2 căi către intrări de pe disc.

În funcție de opțiunile primite, programul va afișa anumite informații pentru fiecare dintre intrările primite ca și argumente.

Opțiunile pot fi următoarele:
- `-i` => afișare număr inode
- `-l` => afișare număr de legături fizice
- `-u` => afișare owner ID
- `-s` => afișare dimensiune în octeți
- `-t` => afișare data ultimei modificări
- `-a` => afișare data ultimului acces
- `-pu` => afișare permisiuni owner (format: `rwx` și `-`)
- `-pg` => afișare permisiuni group (format: `rwx` și `-`)
- `-po` => afișare permisiuni other (format: `rwx` și `-`)
- `-c` => afișare conținut dacă este fișier, tipul intrării în caz contrar

Exemplu:
<program> -s -pu fisier1 fisier2

fisier1 1234 bytes rw- fisier2 345 bytes r--


---

## 6. Program pentru interpretarea fișierului binar

Să se scrie un program care primește ca argument în linie de comandă calea către un fișier ce va fi interpretat în mod binar.

În acest fișier se consideră că există un număr necunoscut de numere întregi pe 1 byte fără semn.

Programul va citi acest fișier și dacă va găsi un octet ce reprezintă un caracter printabil literă mare, literă mică sau cifră, atunci îl va scrie imediat în fișierul de ieșire în format text.  
Calea către fișierul de ieșire este dată de al doilea argument al programului.

Dacă va găsi un octet ce nu este printabil literă mare, literă mică sau cifră, va scrie ca text valoarea în hexazecimal între paranteze rotunde.

Exemplu:
dacă în fișier se găsește la un moment dat octetul cu valorea 0x4E în fișierul de ieșire va scrie N dacă în fișier se găsește la un moment dat octetul cu valorea 0x1A în fișierul de ieșire va scrie (1A)


---

## 7. Program pentru afișarea unui caracter din fișiere

Să se scrie un program C, care primește ca și argumente în linie de comandă: calea către un director de pe disc `<dir>` și un număr natural N.

Programul va parcurge directorul primit în mod recursiv, va identifica toate fișierele obișnuite și va afișa caracterul de pe poziția N din fiecare.  
Dacă fișierul are extensia `.del`, acesta va fi șters de pe disc după afișarea caracterului dorit.  
Dacă se întâlnește o legătură simbolică, programul va elimina permisiunea de `read` pentru ținta legăturii.

---

## 8. Program pentru copierea fișierelor cu extensii și permisiuni specificate

Să se scrie un program C, care primește ca și argumente în linie de comandă 3 elemente:
<program> <cale-dir> <ext> <perm>



- `<cale-dir>` reprezintă calea către un director de pe disc,
- `<ext>` reprezintă un string care conține o extensie aleasă de către utilizator, începând cu punct și urmat de literele alese,
- `<perm>` reprezintă un grup de maxim 3 litere (`r`, `w`, `x`) alese de către utilizator.

Programul va procesa `<cale-dir>` și subdirectoarele acestuia, iar pentru fiecare fișier obișnuit cu extensia `<ext>` și având permisiunile `<perm>` pentru owner, va crea o copie a acelui fișier, având același nume, doar cu `_copy` la final.

---

## 9. Program pentru crearea legăturilor simbolice pe baza unui prag de caractere

Să se scrie un program C ce se va apela în linie de comandă astfel:

./prog <directory> <output_file> <threshold> <ch1> <ch2> .. <chn>


Programul va parcurge recursiv directorul dat ca și argument.  
Pentru fiecare fișier obișnuit (regular) găsit se va număra de câte ori caracterele date ca și argumente apar în conținutul acestuia.  
Dacă numărul total de caractere numărate pentru fiecare fișier depășește numărul `<threshold>`, programul va crea o legătură simbolică în același director cu fișierul procesat, cu același nume, dar cu terminația `_th`.

Se va crea de asemenea și un fișier de statistică referit prin `<output_file>`. Fișierul va avea o formă tabelară, iar capul de tabel va fi generat dinamic în funcție de argumente, astfel:
<file_path>;<nr_ch1>;<nr_ch2>;...;<nr_chn> <total>


---

## Informații adiționale

1. Pentru a genera un fișier cu conținut aleator se poate folosi comanda `dd`:

dd if=/dev/urandom of=<nume-fișier-ieșire> bs=1000 count=<număr-dorit>


2. Pentru citirea și scrierea fișierelor se va folosi `open` + `read/write` + `close`; NU se acceptă soluții prin redirectarea intrărilor standard sau folosind funcțiile de bibliotecă standard C, precum `scanf`, `fgets`, `fgetc`, `fread`, etc.

3. Pentru accesarea informațiilor din inode se va folosi `stat/lstat/fstat`.

4. Pentru testarea programelor se creează un arbore de directoare, fișiere, legături simbolice și named pipes folosind `mkdir`, `touch`, `ln -s` și `mkfifo`.

5. Pentru a construi informații în mod predefinit, se recomandă `snprintf`.

6. Se vor verifica valorile returnate de către toate funcțiile și se vor trata situațiile de eroare.




