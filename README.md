# Parallel algorithms for the analysis and synthesis of data

## How to run this code?
To compile the source code on **MacOS** M1 use this command
```
`brew --prefix llvm`/bin/clang++ -L`brew --prefix`/lib -o lab -fopenmp lab.cpp
```
Then you can simply launch the program from the project directory:
```
./lab <ARGS>
```
You can also use this command to compile and run the script on **Linux**
```
g++ -o lab.o lab.cpp -fopenmp && ./lab.o <ARGS>
```
