# Treasure Manager Project

## Descriere generală

Proiectul "Treasure Manager" este o aplicație scrisă în C, care permite gestionarea unor jocuri (hunts), fiecare conținând mai multe "comori" (treasures). Fiecare comoară este identificată printr-un ID unic și conține informații precum numele utilizatorului care a creat-o, coordonatele GPS, un indiciu și o valoare numerică asociată.

Toate informațiile sunt organizate în fișiere text, structurate pe directoare separate pentru fiecare hunt.

## Structura proiectului

```
phase1/
├── hunts/
│   ├── game1/
│   │   ├── treasures.txt
│   │   └── logged_hunt
│   ├── game2/
│   │   ├── treasures.txt
│   │   └── logged_hunt
│   └── gameN/...
├── src/
|   ├── treasure_manager.c
|   ├── treasure_manager.h
|   ├── add.c
|   ├── list.c
|   ├── view.c
|   ├── removeTreasure.c
|   ├── removeHunt.c
|   └── script_build.sh
├── logged_hunt-game1
├── logged_hunt-game2
├── ....
└── logged_hunt-gameN  
```

## Detalii fișiere și funcții

### treasure_manager.c
Fișier principal care conține funcția `main` și apelurile funcțiilor implementate în alte fișiere. Se ocupă de interpretarea comenzilor din linia de comandă.

### treasure_manager.h
Biblioteca principală a proiectului, conține structurile și prototipurile tuturor funcțiilor.

Structurile utilizate:

- `GPS` - conține coordonate `latitude` și `longitude`
- `TreasureHunt` - conține datele unei comori: `ID`, `username`, `gps_location`, `clue_text` și `value`.

### add.c

**Funcție:** `add_treasure(const char* hunt_id)`

- Creează directorul pentru hunt dacă nu există.
- Adaugă datele unei noi comori în fișierul `treasures.txt` din hunt-ul specificat.
- Creează un fișier de log numit `logged_hunt` și un symbolic link către acesta în directorul părinte al aplicației.

### list.c

**Funcție:** `list_treasure(const char* hunt_id)`

- Listează toate comorile disponibile din hunt-ul specificat.
- Afișează detalii generale despre fișier (dimensiunea și data modificării).

### view.c

**Funcție:** `view_treasure(const char* hunt_id, const char* treasure_id)`

- Caută și afișează detaliile unei anumite comori pe baza ID-ului specificat dintr-un anumit hunt.

### removeTreasure.c

**Funcție:** `remove_treasure(const char* hunt_id, const char* treasure_id)`

- Elimină o anumită comoară din fișierul corespunzător.
- Actualizează fișierul log cu operațiunea efectuată.

### removeHunt.c

**Funcție:** `remove_hunt(const char* hunt_id)`

- Șterge complet un hunt, inclusiv toate comorile și fișierul log asociat.

### script_build.sh

Script Bash care automatizează compilarea și testarea rapidă a tuturor funcțiilor proiectului. Se rulează direct din linia de comandă.

## Compilare și rulare

Pentru compilare și rulare:
```bash
cd phase1/src
gcc treasure_manager.c add.c list.c view.c removeTreasure.c removeHunt.c -o p
./p <comanda> [argumente]
```

Sau utilizează direct script-ul pentru automatizare:
```bash
./script_build.sh
```

## Comenzi disponibile

- Adaugă o comoară:
  ```bash
  ./p add <hunt_id>
  ```

- Listează comori:
  ```bash
  ./p list <hunt_id>
  ```

- Vizualizează detalii comoară:
  ```bash
  ./p view <hunt_id> <treasure_id>
  ```

- Elimină comoară:
  ```bash
  ./p remove_treasure <hunt_id> <treasure_id>
  ```

- Elimină întreg hunt-ul:
  ```bash
  ./p remove_hunt <hunt_id>
  ```

## Detalii adiționale

- Folosește doar apeluri de sistem (`open()`, `read()`, `write()`, `unlink()`, `rmdir()` etc.), fără funcții standard `printf` și `scanf`.
- Sunt utilizate simbolic link-uri pentru acces rapid la log-urile fiecărui joc.

---
