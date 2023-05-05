# Signals & Pipes under Unix/Linux

## Running the code

```bash
make 
```

## Directory Structure
```bash
.
├── bin
│  ├── child.o
│  └── parent.o
├── src
│  ├── child.c
│  ├── child.h
│  ├── parent.c
│  └── parent.h
├── txt
│  ├── 51841.txt
│  ├── 51842.txt
│  ├── 51843.txt
│  ├── 51844.txt
│  ├── 51845.txt
│  └── range.txt
├── Makefile
├── Project.pdf
└── README.md
```

## Tasks
- [] mkdir before (writing/reading) text files
- [] create a pipe between child 5 and the parent
- [] distinguish the 5th child from the rest (Seperate compilation using ifdef?) or maybe just with signals
- [] figure a way to not lose signals as specfied here (https://stackoverflow.com/a/18442435/8962746)[Stack Overflow]
- [] GUI
- [] CMake?
- [] dockerize if time permits 
