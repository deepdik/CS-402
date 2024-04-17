## Prerequisites
- C compiler (e.g., GCC)

## Building the Program
To build the program, open your terminal and navigate to the project directory. Then, compile the source files using the C compiler (e.g., GCC):

```bash
gcc -o basicstats main.c statsFunctions.c readFile.c
```
## Running the Program
To run the build file use below command:
```bash
# <build file name> <input data file name>
./basicstats small.txt
./basicstats large.txt
```

## Note:
For mode calculation these assumptions are made:
1. If all the elements have same frequency then No mode found.
2. If input has one unique element with frequency one or more than one then No mode found.