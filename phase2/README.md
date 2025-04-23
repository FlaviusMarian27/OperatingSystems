# Treasure Manager (Phase 2)

Acest proiect extinde aplicația din Etapa 1 (`Treasure Manager`) prin introducerea unui nou modul interactiv, numit `treasure_hub`, care comunică cu un proces de fundal (`monitor`) folosind **semnale Unix**.

---

## 📁 Structura proiectului

```
phase2/
├── src/
│   ├── treasure_hub.c          # Programul principal cu meniul interactiv
│   ├── treasure_hub.h          # Header cu prototipuri și variabile globale
│   ├── start_monitor.c         # Lansează procesul monitor
│   ├── stop_monitor.c          # Trimite semnal SIGINT pentru a opri monitorul
│   ├── list_hunts.c            # Trimite semnal SIGUSR1 (afișează toate hunt-urile)
│   ├── list_treasure.c         # Trimite semnal SIGUSR2 (afișează comorile unui hunt)
│   ├── view_treasure.c         # Trimite semnal SIGTERM (afișează detalii despre o comoară)
│   ├── monitor.c               # Procesul monitor – rulează în fundal și răspunde la semnale
│   ├── script_build2.sh        # Script de compilare (generează `p` și `monitor`)
|
```

---

## 🔧 Descriere module

### ✅ `treasure_hub.c`
- Meniu interactiv:
  - Start monitor
  - Stop monitor
  - List hunts
  - List treasures
  - View treasure
  - Exit
- Comunicarea se face prin semnale Unix (`kill`, `sigaction`).

### ✅ `monitor.c`
- Proces de fundal care:
  - Așteaptă semnale.
  - Se oprește la `SIGTERM`.
  - Va putea trata și `SIGUSR1`, `SIGUSR2`, etc., pentru a afișa hunt-uri sau comori.

### ✅ `start_monitor.c`
- Creează un nou proces `monitor` folosind `fork()` și `execl()`.

### ✅ `stop_monitor.c`
- Trimite semnal `SIGTERM` către `monitor`.
- Așteaptă închiderea cu `waitpid()` și afișează statusul.

### ✅ `list_hunts.c`, `list_treasure.c`, `view_treasure.c`
- Fiecare din aceste fișiere trimite semnale către `monitor` pentru operații specifice.

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
Când alegi `Stop monitor`, se trimite semnalul `SIGTERM` către monitor, iar acesta se închide elegant.

---

## 💡 Tehnologii folosite

- 📌 Apeluri de sistem: fork(), execl(), kill(), waitpid(), sigaction(), pause()
- 📌 Semnale: SIGUSR1, SIGUSR2, SIGTERM, SIGINT
- 📌 Comunicare prin fișiere: open(), read(), write(), dprintf()
- 📌 Variabilă globală volatile sig_atomic_t running pentru control terminare

---

