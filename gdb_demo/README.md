## GDB Tutorials

### What is GDB ?

- Gdb is a tool which control your program execution.
- Allows you to stop the flow of execution at desired point of execution.i
- Examine the memory content and register content
- Can print the memory content in variety of forms
   Eg: Decimal, hex, string are  few of them.
-Helps you to debug program with source code level(if compiled with -g) and assembly instruction level(if not provided –g ).


### Levels of debugging

- Debug program with debug information provided.
	- Easy to debug 
	- Line by line execution possible at source code level.
	- Symbol information are provided(access to all variables defined in our program).

- Debug program without debug information
	- Hard to debug
	- No symbol information, hence no access to variables.
	- No line by line execution at source code level.
	- Execution flow can control at assembly instruction level

### Compile and Linking program

```c++

//main.c
#include"sum.h"
#include"print.h"
int main(int argc, char **argv)
{
    int res;
    int num1 = 10;
    int num2 = 20;

    num1 = num1 ^ num2;
    num2 = num1 ^ num2;
    num1 = num1 ^ num2;

    res = sum(num1,num2);
    print_result(num1, num2, res);
    return 0;
}

//print.c
#include<stdio.h>
void print_result(int num1, int num2, int res)
{
    char buf1[] = "sum of";
    char buf2[] = "and";
    char *buf = "is";

    printf("%s %d %s %d %s %d\n",
	buf1, num1, buf2, num2,  buf, res);
}

//sum.c
int sum(int num1, int num2)
{
    int result;
    result = num1 + num2;
    return result;
}

```

#### Compilation Phase

| 	                     command                                | Description     |
|:--------------------------------------------------------------|:----------------|
| gcc -c -g   main.c sum.c                                      | Compiler generates object files namely- main.o and sum.o. Since -g is provided compiler will save aymbol information in object file to assist debugging |
| gcc  –c   print.c                                             | Compiler generates object file print.o. No symbol table is added  |
| file main.o                                                     | main.o: ELF 32-bit LSB  relocatable, Intel 80386, version 1 (SYSV), not stripped     |


#### Linking Phase

| 	command                              | Description     |
|:------------------------------------------|:----------------|
| gcc    main.o  sum.o  print.o  -o my_exe| creates excutable file my_exe |
|file my_exe  |my_exe: ELF 32-bit LSB  executable, Intel 80386, version 1 (SYSV), dynamically linked (uses shared libs), for GNU/Linux 2.6.24, BuildID[sha1]=ac1f7c055cf2b333f1af928053eb2f27280af8e7, not stripped |
| strip --strip-debug  print.o   |Strip debug info from print.o added during linking phase|


### Executable and Linkable Format

[Click here to know more information about ELF](https://en.wikipedia.org/wiki/Executable_and_Linkable_Format)

#### objdump
[Click here to know more information about ojdump ](https://en.wikipedia.org/wiki/Objdump)

**Please note** that the line marked red is correspnding code for each assembly instruction
```markdown
$ objdump -d  sum.o

sum.o:     file format elf32-i386


Disassembly of section .text:

00000000 <sum>:
   0:	`83 ec 10`             	sub    $0x10,%esp
   3:	`8b 54 24 14`          	mov    0x14(%esp),%edx
   7:	`8b 44 24 18`          	mov    0x18(%esp),%eax
   b:	`01 d0`                	add    %edx,%eax
   d:	`89 44 24 0c`          	mov    %eax,0xc(%esp)
  11:	`8b 44 24 0c`          	mov    0xc(%esp),%eax
  15:	`83 c4 10`             	add    $0x10,%esp
  18:	`c3`                   	ret    



**Bold** and _Italic_ and `Code` text

[Link](url) and ![Image](src)
```


### Demo: Executing program using gdb


#### Invoking executable binary using using gdb

```markdown


gdb_demo$gdb main.out
GNU gdb (Ubuntu 8.1-0ubuntu3) 8.1.0.20180409-git
Copyright (C) 2018 Free Software Foundation, Inc.
For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from main...done.
```


```markdown
```
#### Start program from the beginning
```markdown
(gdb) run
Starting program: /.../cso/gdb_demo/main.out
sum of 20 and 10 is 30
[Inferior 1 (process 6827) exited normally]
```


#### Set/delete/show breakpoints
```markdown
(gdb) break main
Breakpoint 1 at 0x565555ae: file main.c, line 7.
(gdb) run
Starting program: /home/nr83/github/cso/gdb_demo/main 

Breakpoint 1, main (argc=1, argv=0xffffd114) at main.c:7
7	    int num1 = 10;

(gdb) info break
Num     Type           Disp Enb Address    What
1       breakpoint     keep y   0x565555ae in main at main.c:7
	breakpoint already hit 1 time

(gdb) delete 1

(gdb) info break
No breakpoints or watchpoints.
```

### gdb-source level debug assistance sub commands

* continue or c
	- Continue program execution
* print or p
	- Print value of expression
* set or s
	- Assign value to variable
* backtrace or bt
	- Print backtrace of all stack frames
* frame or f
	- Select and print a stack frame
* list or l
	- List source code



### gdb-low level debug assistance sub commands: disassemble, nexti, stepi, x

* list or l
	- List source code
* disassemble
	- Disassemble a specified section of memory.
* nexti	
	- Step one instruction, but proceed through subroutine calls 
* stepi
	- Step one instruction exactly.
* x
	- Examine memory


### gdb help sub command
List of classes of commands:

- aliases -- Aliases of other commands
- breakpoints -- Making program stop at certain points
- data -- Examining data
- files -- Specifying and examining files
- internals -- Maintenance commands
- obscure -- Obscure features
- running -- Running the program
- stack -- Examining the stack
- status -- Status inquiries
- support -- Support facilities
- tracepoints -- Tracing of program execution without stopping the program
- user-defined -- User-defined commands


* Type 
	- "help" followed by a class name for a list of commands in that class.
    - "help all" for the list of all commands.
 	- "help" followed by command name for full documentation.
	- "apropos word" to search for commands related to "word".
* Command name abbreviations are allowed if unambiguous. 


```markdown

(gdb) break main
Breakpoint 1 at 0x5ae: file main.c, line 7.
(gdb) break print
Function "print" not defined.
Make breakpoint pending on future shared library load? (y or [n]) n
(gdb) break sum
Breakpoint 2 at 0x603
(gdb) i break
Num     Type           Disp Enb Address    What
1       breakpoint     keep y   0x000005ae in main at main.c:7
2       breakpoint     keep y   0x00000603 <sum>
(gdb) r
Starting program: /home/nr83/github/cso/gdb_demo/main.out 

Breakpoint 1, main (argc=1, argv=0xffffd114) at main.c:7
7	    int num1 = 10;
(gdb) list
2	#include"sum.h"
3	#include"print.h"
4	int main(int argc, char **argv)
5	{
6	    int res;
7	    int num1 = 10;
8	    int num2 = 20;
9	
10	    num1 = num1 ^ num2;
11	    num2 = num1 ^ num2;
(gdb) n
8	    int num2 = 20;
(gdb) 
10	    num1 = num1 ^ num2;
(gdb) 
11	    num2 = num1 ^ num2;
(gdb) 
12	    num1 = num1 ^ num2;
(gdb) 
14	    res = sum(num1,num2);
(gdb) step 

Breakpoint 2, 0x56555603 in sum ()
(gdb) disassemble 
Dump of assembler code for function sum:
=> 0x56555603 <+0>:	sub    $0x10,%esp
   0x56555606 <+3>:	mov    0x14(%esp),%edx
   0x5655560a <+7>:	mov    0x18(%esp),%eax
   0x5655560e <+11>:	add    %edx,%eax
   0x56555610 <+13>:	mov    %eax,0xc(%esp)
   0x56555614 <+17>:	mov    0xc(%esp),%eax
   0x56555618 <+21>:	add    $0x10,%esp
   0x5655561b <+24>:	ret    
End of assembler dump.
(gdb) nexti
0x56555606 in sum ()
(gdb) ni
0x5655560a in sum ()
(gdb) 
0x5655560e in sum ()
(gdb) 
0x56555610 in sum ()
(gdb) 
0x56555614 in sum ()
(gdb) 
0x56555618 in sum ()
(gdb) 
0x5655561b in sum ()
(gdb) 
0x565555dc in main (argc=1, argv=0xffffd114) at main.c:14
14	    res = sum(num1,num2);
(gdb) disassemble 
Dump of assembler code for function main:
   0x5655559d <+0>:	lea    0x4(%esp),%ecx
   0x565555a1 <+4>:	and    $0xfffffff0,%esp
   0x565555a4 <+7>:	pushl  -0x4(%ecx)
   0x565555a7 <+10>:	push   %ebp
   0x565555a8 <+11>:	mov    %esp,%ebp
   0x565555aa <+13>:	push   %ecx
   0x565555ab <+14>:	sub    $0x14,%esp
   0x565555ae <+17>:	movl   $0xa,-0x14(%ebp)
   0x565555b5 <+24>:	movl   $0x14,-0x10(%ebp)
   0x565555bc <+31>:	mov    -0x10(%ebp),%eax
   0x565555bf <+34>:	xor    %eax,-0x14(%ebp)
   0x565555c2 <+37>:	mov    -0x14(%ebp),%eax
   0x565555c5 <+40>:	xor    %eax,-0x10(%ebp)
   0x565555c8 <+43>:	mov    -0x10(%ebp),%eax
   0x565555cb <+46>:	xor    %eax,-0x14(%ebp)
   0x565555ce <+49>:	sub    $0x8,%esp
   0x565555d1 <+52>:	pushl  -0x10(%ebp)
   0x565555d4 <+55>:	pushl  -0x14(%ebp)
   0x565555d7 <+58>:	call   0x56555603 <sum>
=> 0x565555dc <+63>:	add    $0x10,%esp
   0x565555df <+66>:	mov    %eax,-0xc(%ebp)
   0x565555e2 <+69>:	sub    $0x4,%esp
---Type <return> to continue, or q <return> to quit---nexti
   0x565555e5 <+72>:	pushl  -0xc(%ebp)
   0x565555e8 <+75>:	pushl  -0x10(%ebp)
   0x565555eb <+78>:	pushl  -0x14(%ebp)
   0x565555ee <+81>:	call   0x5655561c <print_result>
   0x565555f3 <+86>:	add    $0x10,%esp
   0x565555f6 <+89>:	mov    $0x0,%eax
   0x565555fb <+94>:	mov    -0x4(%ebp),%ecx
   0x565555fe <+97>:	leave  
   0x565555ff <+98>:	lea    -0x4(%ecx),%esp
   0x56555602 <+101>:	ret    
End of assembler dump.
(gdb) nexti
0x565555df	14	    res = sum(num1,num2);
(gdb) b *0x565555ee
Breakpoint 3 at 0x565555ee: file main.c, line 15.
(gdb) c
Continuing.

Breakpoint 3, 0x565555ee in main (argc=1, argv=0xffffd114) at main.c:15
15	    print_result(num1, num2, res);
(gdb) disassemble 
Dump of assembler code for function main:
   0x5655559d <+0>:	lea    0x4(%esp),%ecx
   0x565555a1 <+4>:	and    $0xfffffff0,%esp
   0x565555a4 <+7>:	pushl  -0x4(%ecx)
   0x565555a7 <+10>:	push   %ebp
   0x565555a8 <+11>:	mov    %esp,%ebp
   0x565555aa <+13>:	push   %ecx
   0x565555ab <+14>:	sub    $0x14,%esp
   0x565555ae <+17>:	movl   $0xa,-0x14(%ebp)
   0x565555b5 <+24>:	movl   $0x14,-0x10(%ebp)
   0x565555bc <+31>:	mov    -0x10(%ebp),%eax
   0x565555bf <+34>:	xor    %eax,-0x14(%ebp)
   0x565555c2 <+37>:	mov    -0x14(%ebp),%eax
   0x565555c5 <+40>:	xor    %eax,-0x10(%ebp)
   0x565555c8 <+43>:	mov    -0x10(%ebp),%eax
   0x565555cb <+46>:	xor    %eax,-0x14(%ebp)
   0x565555ce <+49>:	sub    $0x8,%esp
   0x565555d1 <+52>:	pushl  -0x10(%ebp)
   0x565555d4 <+55>:	pushl  -0x14(%ebp)
   0x565555d7 <+58>:	call   0x56555603 <sum>
   0x565555dc <+63>:	add    $0x10,%esp
   0x565555df <+66>:	mov    %eax,-0xc(%ebp)
   0x565555e2 <+69>:	sub    $0x4,%esp
---Type <return> to continue, or q <return> to quit---
   0x565555e5 <+72>:	pushl  -0xc(%ebp)
   0x565555e8 <+75>:	pushl  -0x10(%ebp)
   0x565555eb <+78>:	pushl  -0x14(%ebp)
=> 0x565555ee <+81>:	call   0x5655561c <print_result>
   0x565555f3 <+86>:	add    $0x10,%esp
   0x565555f6 <+89>:	mov    $0x0,%eax
   0x565555fb <+94>:	mov    -0x4(%ebp),%ecx
   0x565555fe <+97>:	leave  
   0x565555ff <+98>:	lea    -0x4(%ecx),%esp
   0x56555602 <+101>:	ret    
End of assembler dump.
(gdb) stepi
0x5655561c in print_result ()
(gdb) disassemble 
Dump of assembler code for function print_result:
=> 0x5655561c <+0>:	sub    $0x2c,%esp
   0x5655561f <+3>:	mov    %gs:0x14,%eax
   0x56555625 <+9>:	mov    %eax,0x1c(%esp)
   0x56555629 <+13>:	xor    %eax,%eax
   0x5655562b <+15>:	movl   $0x206d7573,0x15(%esp)
   0x56555633 <+23>:	movw   $0x666f,0x19(%esp)
   0x5655563a <+30>:	movb   $0x0,0x1b(%esp)
   0x5655563f <+35>:	movl   $0x646e61,0x11(%esp)
   0x56555647 <+43>:	movl   $0x56555710,0xc(%esp)
   0x5655564f <+51>:	sub    $0x4,%esp
   0x56555652 <+54>:	pushl  0x3c(%esp)
   0x56555656 <+58>:	pushl  0x14(%esp)
   0x5655565a <+62>:	pushl  0x40(%esp)
   0x5655565e <+66>:	lea    0x21(%esp),%eax
   0x56555662 <+70>:	push   %eax
   0x56555663 <+71>:	pushl  0x44(%esp)
   0x56555667 <+75>:	lea    0x2d(%esp),%eax
   0x5655566b <+79>:	push   %eax
   0x5655566c <+80>:	push   $0x56555713
   0x56555671 <+85>:	call   0xf7e1f2d0 <printf>
   0x56555676 <+90>:	add    $0x20,%esp
   0x56555679 <+93>:	nop

(gdb) x/s 0x56555710
0x56555710:	"is"
```