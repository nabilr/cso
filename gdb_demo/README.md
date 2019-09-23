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

### gdb demo

```markdown

nr83@Nabil-Dell:~/github/cso/gdb_demo$ gdb main.out 
For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from main.out...done.
(gdb) break main
Breakpoint 1 at 0x8048456: file main.c, line 4.
(gdb) break sum
Breakpoint 2 at 0x80484b9: file sum.c, line 2.
(gdb) break  print_result 
Breakpoint 3 at 0x80484d2

(gdb) info break
Num     Type           Disp Enb Address    What
1       breakpoint     keep y   0x08048456 in main at main.c:4
2       breakpoint     keep y   0x080484b9 in sum at sum.c:2
3       breakpoint     keep y   0x080484d2 <print_result>


(gdb) r
Starting program: /home/nr83/github/cso/gdb_demo/main.out 

Breakpoint 1, main (argc=1, argv=0xffffd114) at main.c:4
4	    int num1 = 10;
(gdb) n
5	    int num2 = 20;
(gdb) 
7	    num1 = num1 ^ num2;
(gdb) 
8	    num2 = num1 ^ num2;
(gdb) 
9	    num1 = num1 ^ num2;
(gdb) 
11	    res = sum(num1,num2);
(gdb) step

Breakpoint 2, sum (num1=20, num2=10) at sum.c:2
2	{
(gdb) n
4	    result = num1 + num2;
(gdb) n
5	    return result;
(gdb) 
6	}
(gdb) 
main (argc=1, argv=0xffffd114) at main.c:12
12	    print_result(num1, num2, res);
(gdb) stepi
0x0804849a	12	    print_result(num1, num2, res);
(gdb) 
0x0804849e	12	    print_result(num1, num2, res);
(gdb) 
0x080484a2	12	    print_result(num1, num2, res);
(gdb) stepi
0x080484a6	12	    print_result(num1, num2, res);
(gdb) stepi
0x080484aa	12	    print_result(num1, num2, res);
(gdb) stepi
0x080484ad	12	    print_result(num1, num2, res);
(gdb) stepi

Breakpoint 3, 0x080484d2 in print_result ()
(gdb) bt
#0  0x080484d2 in print_result ()
#1  0x080484b2 in main (argc=1, argv=0xffffd114) at main.c:12
(gdb) disassemble 
Dump of assembler code for function print_result:
=> 0x080484d2 <+0>:	sub    $0x3c,%esp
   0x080484d5 <+3>:	movl   $0x206d7573,0x29(%esp)
   0x080484dd <+11>:	movw   $0x666f,0x2d(%esp)
   0x080484e4 <+18>:	movb   $0x0,0x2f(%esp)
   0x080484e9 <+23>:	movl   $0x646e61,0x25(%esp)
   0x080484f1 <+31>:	mov    0x48(%esp),%eax
   0x080484f5 <+35>:	mov    %eax,0x1c(%esp)
   0x080484f9 <+39>:	movl   $0x80485c0,0x18(%esp)
   0x08048501 <+47>:	mov    0x44(%esp),%eax
   0x08048505 <+51>:	mov    %eax,0x14(%esp)
   0x08048509 <+55>:	lea    0x25(%esp),%eax
   0x0804850d <+59>:	mov    %eax,0x10(%esp)
   0x08048511 <+63>:	mov    0x40(%esp),%eax
   0x08048515 <+67>:	mov    %eax,0xc(%esp)
   0x08048519 <+71>:	lea    0x29(%esp),%eax
   0x0804851d <+75>:	mov    %eax,0x8(%esp)
   0x08048521 <+79>:	movl   $0x80485c3,0x4(%esp)
   0x08048529 <+87>:	movl   $0x1,(%esp)
   0x08048530 <+94>:	call   0x8048310 <__printf_chk@plt>
   0x08048535 <+99>:	add    $0x3c,%esp
   0x08048538 <+102>:	ret    
End of assembler dump.
(gdb) nexti
0x080484d5 in print_result ()
(gdb) nexti
0x080484dd in print_result ()
(gdb) disassemble 
Dump of assembler code for function print_result:
   0x080484d2 <+0>:	sub    $0x3c,%esp
   0x080484d5 <+3>:	movl   $0x206d7573,0x29(%esp)
=> 0x080484dd <+11>:	movw   $0x666f,0x2d(%esp)
   0x080484e4 <+18>:	movb   $0x0,0x2f(%esp)
   0x080484e9 <+23>:	movl   $0x646e61,0x25(%esp)
   0x080484f1 <+31>:	mov    0x48(%esp),%eax
   0x080484f5 <+35>:	mov    %eax,0x1c(%esp)
   0x080484f9 <+39>:	movl   $0x80485c0,0x18(%esp)
   0x08048501 <+47>:	mov    0x44(%esp),%eax
   0x08048505 <+51>:	mov    %eax,0x14(%esp)
   0x08048509 <+55>:	lea    0x25(%esp),%eax
   0x0804850d <+59>:	mov    %eax,0x10(%esp)
   0x08048511 <+63>:	mov    0x40(%esp),%eax
   0x08048515 <+67>:	mov    %eax,0xc(%esp)
   0x08048519 <+71>:	lea    0x29(%esp),%eax
   0x0804851d <+75>:	mov    %eax,0x8(%esp)
   0x08048521 <+79>:	movl   $0x80485c3,0x4(%esp)
   0x08048529 <+87>:	movl   $0x1,(%esp)
   0x08048530 <+94>:	call   0x8048310 <__printf_chk@plt>
   0x08048535 <+99>:	add    $0x3c,%esp
   0x08048538 <+102>:	ret    
End of assembler dump.
(gdb) x/1s  $0x80485c0
Value can't be converted to integer.
(gdb) x/1s  0x80485c0
0x80485c0:	"is"
(gdb) x/1s  0x29(%esp)
A syntax error in expression, near `%esp)'.
(gdb) x/1s  0x29+$esp
0xffffd039:	"sum \346\337\367\374c\372", <incomplete sequence \367>
(gdb) disassemble sum 
Dump of assembler code for function sum:
   0x080484b9 <+0>:	sub    $0x10,%esp
   0x080484bc <+3>:	mov    0x18(%esp),%eax
   0x080484c0 <+7>:	mov    0x14(%esp),%edx
   0x080484c4 <+11>:	add    %edx,%eax
   0x080484c6 <+13>:	mov    %eax,0xc(%esp)
   0x080484ca <+17>:	mov    0xc(%esp),%eax
   0x080484ce <+21>:	add    $0x10,%esp
   0x080484d1 <+24>:	ret    
End of assembler dump.
(gdb) 

```