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
│  ├── local.c
│  ├── local.h
│  ├── parent.c
│  └── parent.h
├── txt
│  ├── 46160.txt
│  ├── 46161.txt
│  ├── 46162.txt
│  ├── 46163.txt
│  └── range.txt
├── Makefile
├── Project.pdf
└── README.md

```

## Tasks
- [x] mkdir before (writing/reading) text files
- [ ] create a pipe between child 5 and the parent
- [ ] distinguish the 5th child from the rest (Seperate compilation using ifdef?) or maybe just with signals `Use another signal`
- [x] figure a way to not lose signals as specfied here [Stack Overflow](https://stackoverflow.com/a/18442435/8962746)
- [ ] GUI
~~- [ ] CMake?~~ `no need` 
- [ ] dockerize if time permits  `once done with the project`
