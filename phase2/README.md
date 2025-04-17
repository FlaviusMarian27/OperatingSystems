# 🗺️ Treasure Manager (Phase 2)

Acest proiect extinde aplicația din Etapa 1 (`Treasure Manager`) prin introducerea unui nou modul interactiv, numit `treasure_hub`, care comunică cu un proces de fundal (`monitor`) folosind **semnale Unix**.

---

## 📁 Structura proiectului

```
phase2/
├── src/
│   ├── treasure_hub.c       # programul principal cu meniu interactiv
│   ├── treasure_hub.h       # prototipuri funcții și variabile globale
│   ├── start_monitor.c      # lansează procesul monitor (fork + execl)
│   ├── stop_monitor.c       # trimite semnal de oprire către monitor
│   ├── monitor.c            # proces de fundal care așteaptă semnale
│   ├── script_build2.sh     # script de compilare și lansare
│   └── (alte fișiere - dacă e cazul)
```

---

## 🔧 Descriere module

### ✅ `treasure_hub.c`
- Meniu interactiv:
  - Start monitor
  - Stop monitor
  - (viitor) List hunts
  - (viitor) List treasures
  - (viitor) View treasure
  - Exit
- Comunicarea se face prin semnale Unix (`kill`, `sigaction`).

### ✅ `monitor.c`
- Proces de fundal care:
  - Așteaptă semnale.
  - Se oprește la `SIGUSR2`.
  - Va putea trata și `SIGUSR1`, `SIGUSR2`, etc., pentru a afișa hunt-uri sau comori.

### ✅ `start_monitor.c`
- Creează un nou proces `monitor` folosind `fork()` și `execl()`.

### ✅ `stop_monitor.c`
- Trimite semnal `SIGUSR2` către `monitor`.
- Așteaptă închiderea cu `waitpid()` și afișează statusul.

---

## 🛠️ Compilare și rulare

Scriptul `script_build2.sh`:

```bash
cd src
chmod +x script_build2.sh
./script_build2.sh
```

Scriptul va:
- Compila toate fișierele `.c`
- Crea executabilele `p` (hub-ul) și `monitor`
- Lansa automat programul `p`

---

## 🧪 Exemplu rulare

```bash
=== Treasure Hub Menu ===
1. Start monitor
2. Stop monitor
3. List hunts
4. List treasures
5. View treasure
6. Exit
Select: 1
Monitor pornit cu PID: 7623
```

Dacă monitorul este deja pornit, va apărea un mesaj corespunzător.
Când alegi `Stop monitor`, se trimite semnalul `SIGUSR2` către monitor, iar acesta se închide elegant.

---

## 💡 Tehnologii folosite

- 📌 Apeluri de sistem:
  - `fork()`, `execl()`, `kill()`, `waitpid()`, `sigaction()`, `pause()`
- 📌 Semnale:
  - `SIGUSR2` (pentru oprire)
  - `SIGUSR1`, `SIGTERM`, etc. (posibilități de extindere)
- 📌 `volatile sig_atomic_t`:
  - Utilizat pentru ca handler-ul să poată modifica variabile globale în siguranță.

---

