# Hack-Assembler

An assembler written in C++ for the Hack programming language used in the nand2tetris course.
The assembler will translate Hack assembly programs into executable Hack binary code, assuming
that the assembly code is error-free.

To run:
```
g++ -Wall -o assembler assembler.cpp -static
./assembler <filepath>
```
Replace filepath with the path to the intended file, including the .asm extension. For a file
`<folderpath>/<filename>.asm`, outputs the binary code into a file with the name format
`<folderpath>/<filename>.hack`.