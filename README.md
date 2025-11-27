# bcat
Helps to quickly see file content or write something down on it
## Prerequisites
- g++ compiler
## Installation
1. Clone the repository
   ```
   git clone https://github.com/babichgh/bcat.git
   cd bcat
   ```
2. Compile
   ```
   make
   ```
3. Run
   ```
   ./bcat --read/--write [path/to/your/file]
   ```
   or
   ```
   make run --read/--write [path/to/your/file]
   ```
## Project structure
```
cat/
├── .gitignore   # ignores /.vscode
├── Makefile     # helps compile
├── README.md    # You read it right now
└── main.cpp     # C++ source code
```
Almost all this README was created using **bcat**
