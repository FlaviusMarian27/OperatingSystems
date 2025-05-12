# Treasure Manager Project (Phase 3)

## Pipes & External Processes

## 🧭 Scopul proiectului
În această fază, sistemul Treasure Hunt este extins pentru a permite comunicarea între procese folosind **pipe-uri** și lansarea de **procese externe**, pe lângă semnalele deja implementate în fazele anterioare.

---

## ✅ Funcționalități implementate

- ✅ Pornirea și oprirea procesului `monitor` din `treasure_hub`.
- ✅ Comunicarea între `treasure_hub` și `monitor` se face prin:
  - Semnale: `SIGUSR1`, `SIGUSR2`, `SIGTERM`, `SIGINT`
  - **Pipe** pentru a citi rezultatul procesat din stdout-ul `monitor`
- ✅ Comenzi disponibile:
  - `List Hunts`
  - `List Treasures`
  - `View Treasure`
  - `Score Users` – fiecare scor este calculat cu un **proces extern** pentru fiecare hunt
- ✅ Programul extern `calculate_scores`:
  - Primește ca argument un `hunt_id`
  - Parcurge `treasures.dat`
  - Calculează scorurile per utilizator
  - Trimite rezultatul în stdout (preluat prin pipe)

---

## 🧱 Structură directoare

```
phase3/
├── src/
│   ├── treasure_hub.c
│   ├── monitor.c
│   ├── start_monitor.c
│   ├── stop_monitor.c
│   ├── list_hunts.c
│   ├── list_treasure.c
│   ├── view_treasure.c
│   ├── score_pipe.c
│   ├── calculate_scores.c
│   ├── treasure_hub.h
│   └── script_build3.sh
├── ../../phase1/
│   ├── src/
│   │   ├── list.c
│   │   └── view.c
│   └── hunts/
│       ├── game1/treasures.dat
│       ├── game2/treasures.dat
│       └── game3/treasures.dat
```

---

## ▶️ Cum se rulează

1. Compilează tot:
```bash
cd phase3/src
chmod +x script_build3.sh
./script_build3.sh
```

2. Rulează programul:
```bash
./p
```

3. Meniu:
```
1. Start monitor
2. Stop monitor
3. List hunts
4. List treasures
5. View treasure
6. Score users
7. Exit
```

---

## 💬 Exemplu output scoruri

```
--- Scoruri pentru game1 ---
User: Flavius | Score: 130
User: Geo     | Score: 50
```

---

## ⚙️ Tehnologii folosite

- Limbaj: C
- Sisteme Unix:
  - `pipe()`, `fork()`, `dup2()`, `execl()`
  - `signal()`, `kill()`, `waitpid()`
  - `open()`, `read()`, `write()`
  - `dprintf()`, `snprintf()`, `fgets()`, `fflush()`

---


