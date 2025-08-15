# minitalk

This project is part of the 42 School curriculum. It consists of implementing a client-server communication system using UNIX signals to transmit messages between processes. The client sends a string to the server using only SIGUSR1 and SIGUSR2 signals, demonstrating low-level inter-process communication.

## Table of Contents
- [About](#about)
- [Project Structure](#project-structure)
- [Functionality](#functionality)
- [Usage](#usage)
- [Compiling](#compiling)
- [License](#license)

## About

`minitalk` is a communication system that implements a client and server architecture using only UNIX signals for data transmission. The project demonstrates how to use signal handling to create a communication protocol between two separate processes. Each character of the message is converted to its binary representation and transmitted bit by bit using signals.

The server waits for incoming connections and listens for signals from clients. When it receives a message, it reconstructs the original string and displays it on stdout.

## Project Structure

The project is organized as follows:

```
minitalk/
├── client.c              # Client implementation
├── server.c              # Server implementation
├── client_bonus.c        # Client bonus implementation
├── server_bonus.c        # Server bonus implementation
├── Makefile              # Build script
├── LICENSE               # License file
├── libft/                # Custom C library (submodule)
│   ├── libft.h           # Library header
│   ├── Makefile          # Library build system
│   └── *.c               # Library functions
```

## Functionality

The minitalk system works by transmitting each character of a message as a sequence of 8 bits:

- **SIGUSR1** represents a binary 0 bit
- **SIGUSR2** represents a binary 1 bit

The transmission process:
1. Client converts each character to its 8-bit binary representation
2. For each bit, the client sends either SIGUSR1 (0) or SIGUSR2 (1) to the server
3. Server receives the signals and reconstructs each character bit by bit
4. When a complete character (8 bits) is received, it's displayed on stdout
5. Transmission ends when the null terminator is sent

## Usage

1. **Clone the repository:**
   ```bash
   git clone https://github.com/Ferreira-Jefferson/minitalk
   cd minitalk
   ```

2. **Build the project:**
   ```bash
   make
   ```

3. **Run the server:**
   ```bash
   ./server
   ```
   Note the PID displayed by the server.

4. **Run the client (in another terminal):**
   ```bash
   ./client [server_PID] "Your message here"
   ```

5. **Example usage:**
   ```bash
   # Terminal 1
   ./server
   PID Server: 12345
   
   # Terminal 2
   ./client 12345 "Hello, World!"
   PID client: 12346
   ```

## Compiling

- To compile the project:
  ```bash
  make
  ```

- To compile with bonus features:
  ```bash
  make bonus
  ```

- To clean object files:
  ```bash
  make clean
  ```

- To remove all binaries:
  ```bash
  make fclean
  ```

- To recompile from scratch:
  ```bash
  make re
  ```

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

---

*Project developed as part of the 42 School curriculum.*