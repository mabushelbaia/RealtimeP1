# Signals & Pipes under Unix/Linux

## Running the code
### 5 rounds
```bash
make # 5 rounds
``` 
### n rounds
```bash
make n=10 # 10 rounds
```
### Want to see what is going on?
```bash
make cli # 5 rounds
```
### Debug mode 
```bash
make debug
```
### GUI
```bash
Not yet implemented
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
│  ├── 26030.txt
│  ├── 26031.txt
│  ├── 26032.txt
│  ├── 26033.txt
│  └── range.txt
├── gmon.out
├── Makefile
├── Project.pdf
└── README.md
```

## Tasks
- [x] mkdir before (writing/reading) text files
- [x] create a pipe between child 5 and the parent
- [x] distinguish the 5th child from the rest (Seperate compilation using ifdef?) or maybe just with signals `Use another signal`
- [x] figure a way to not lose signals as specfied here [Stack Overflow](https://stackoverflow.com/a/18442435/8962746)
- [ ] GUI 

~~- [ ] CMake?~~ `no need` 
- [ ] dockerize if time permits  `once done with the project`
