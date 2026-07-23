# Operating System Course Work

A collection of C programs implementing key Operating Systems concepts through practical simulations and implementations. This repository contains solutions for various OS lab tasks focusing on process management, synchronization, memory management, file systems/security, and networking. 

📁 Repository Structure

Task 1/** — Process Management & Synchronization
  Task1.c — Multi-threading with mutex, system info, Round Robin scheduling simulation
  Hospital_Emergency_Room.c — Real-world analogy using threads + mutex (patients & doctor)

Task 2/** — Memory Management
  Task2.c — Page replacement algorithms (FIFO and LRU)

Task 3/** — File Management System with Security
  Task3.c — Role-based access control (Lecturer/Student), file permissions (rwx), encryption (Caesar cipher), audit logging

Task 4/** — Client-Server Application
  server.c — Multi-threaded TCP server with authentication
  client.c — Client to interact with the server

🚀 Features

Task 1: Threads & Scheduling
POSIX threads (pthread)
Mutex synchronization to prevent race conditions
System information retrieval
Round Robin CPU scheduling simulation

Task 2: Page Replacement
FIFO (First In First Out)
LRU (Least Recently Used)
Hit/Miss ratio calculation with frame visualization

Task 3: Secure File Management
User authentication (Lecturer/Student)
File creation, read, write, delete, execute
Permission management (rwx style)
Simple file encryption/decryption
Audit logging (audit.log)

Task 4: Networking
TCP socket programming
Multi-threaded server
Authentication
Commands: TIME, ECHO, QUIT

🛠️ How to Compile and Run

All programs are written in C and can be compiled with gcc:

For any task file
gcc filename.c -o output thread  

Example:
cd Task\ 1
gcc Task1.c -o task1
./task1

Note: Task 4 requires both server and client to be compiled and run.

📋 Requirements

Linux/Unix-like environment (for best compatibility)
GCC compiler
POSIX threads library (-lpthread)

🎯 Learning Objectives

This repository demonstrates practical understanding of:
Process vs Thread management
Concurrency and synchronization issues
Memory management techniques
File system security and permissions
Client-server architecture and socket programming
