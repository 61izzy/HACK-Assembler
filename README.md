# Hack-Assembler

An assembler written in C++ for the Hack assembly language used in the nand2tetris course.
The assembler will translate Hack assembly programs into executable Hack binary code.

To run:
```
./assembler <filepath>
```
Replace filepath with the path to the intended file, including the .asm extension. For a file
`<folderpath>/<filename>.asm`, outputs the binary code into a file with the name format
`<folderpath>/<filename>.hack`.

There are a few example assembly programs included along with their translated binary programs.

Note: The assembler assumes that the assembly code is error free.