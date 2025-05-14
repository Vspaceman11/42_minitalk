# Minitalk

**Score: 125/100 ✅**

Minitalk is a small inter-process messaging application written in C as part of the 42 core curriculum.
It allows sending a message from one process (client) to another (server) using only Unix signals.

---

## 🧠 Purpose

This project is designed to strengthen understanding of:

- Unix signals (`SIGUSR1`, `SIGUSR2`)
- Signal handling with `sigaction`
- Bitwise operations
- Process communication without standard IPC mechanisms
- Clean and modular C code structure

---

## 🛠️ How It Works

- The **server** prints its PID on startup and waits for messages.
- The **client** takes the server’s PID and a message as input, then:
  - Sends each character bit-by-bit using signals.
  - `SIGUSR1` represents binary `0`, `SIGUSR2` represents binary `1`.
  - Sends a null byte at the end to signal completion.
- The server reconstructs each byte and prints the full message.
- After receiving the full message, the server sends a `SIGUSR1` back to the client to confirm receipt.

---

## 🧪 Example Usage

In one terminal:
```bash
$ ./server
PID: 12345
```
In another terminal:
```bash
$ ./client 12345 "Hello, 42!"
```
```bash
Hello, 42!
```
## 📁 File Structure

```bash
minitalk/
├── inc/
│   └── minitalk.h         # Header file with common includes and constants
├── src/
│   ├── client.c           # Client logic
│   └── server.c           # Server logic
├── libft_extended/        # Custom extended libft (auto-downloaded by Makefile)
├── Makefile               # Build script
└── README.md              # Project description
```
## 🧰 Building the Project

```bash
make          # Builds both client and server
make clean    # Removes object files
make fclean   # Removes binaries and object files
make re       # Full rebuild
```
## 🧩 Notes

libft_extended is automatically cloned via Makefile if not present.

BUFFER_SIZE can be set at compile time:
```bash
make BUFFER_SIZE=10000
```
## ⚠️ 42 Guidelines

This repository complies with 42's policy:
No code is shared or published with the intent of helping others bypass the learning process.
This README.md only documents the functionality and structure of the project for personal or professional presentation.

## 📈 Final Score
✅ Score: 125/100 — Bonus points were awarded for clarity, robustness, and clean signal handling.


