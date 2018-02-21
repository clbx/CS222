### Ask if on test:
* Conditional compilation (Slides #5) YES
* System Limits (Slides #6)           NO
* Precedence Table (Slides #6)        NO, but be familiar


# Unix & Linux
Unix was originally Unics **UN**iplexed **I**nformation and **C**omputing **S**ervices.
and is a pun on Multics.

Eventually was named Unix, does not stand for anything.

Unix is a standard for operating systems based on a long, complex, history with many companies and innovators. **The Open Group** has the trademark on Unix

**Linux and FreeBSD** do **not** meet the specification of Unix.

### Development of Unix
Ken Tompson started Unix while at Bell Labs. **Was written assembly for PDP-7 and PDP-11.**

At the same time Dennis Ritchie developed the C language, which in 1979 was mature enough which Unix could be implemented in it. **This has made C be the pre-eminent systems programming language**

Unix is not free, and originally was only used by AT&T. Then they started to give it universities for free. **While at berkley Ken Thompson worked on BSD, a version of Unix for academia** once AT&T's monopoly broke up they started selling UNIX, and led the the creation of **System V Unix, in 1983**

Unix is used in a lot of different hardware

|Corp.      |Use      |Corp.  |Use     |
|-----------|---------|-------|--------|
|Sun|SunOS and Solaris|Apple|NexTStep, A/UX|
|DEC|Ultrix and OSF/1|Intel| XENIX
|IBM|AIX|HP|HP-UX

#### GNU

RMS is the "father" of open source software, started **GNU (GNU's not Unix)** in 1984. GNU created many useful tools that have since been incorporated into Linux such as:

+ emacs
+ gcc
+ bash
+ The glibc

#### Linux

**Linus Torvalds** started work on Linux in 1991. Built Linux under the GPL.


# C

## Types:

|Type|Meaning|Size|Type|Meaning|Size|
|----|-------|----|----|-------|----|
|char|smallest addressable memory| u. 1 byte| short| short signed int| > 2 bytes|
|int|signed int| > 2 bytes, u. 4 bytes| long| long signed int| > 4 bytes|
|float|Single precision float| u. 4 bytes| double| Double precision float| u. 8 bytes|

No bool.

C has signed and unsigned versions of all of it's integer types.

``long long`` and ``long double`` are supported in C99 but not C89.


## File Organization and Features

In C every file is is a list of functions and global variables. To use other files ``#include`` which **copies and pastes the code into the code being compiled.**

In C you get **Basic Math**, **Bitwise Operators**, and **Pointer Manipulation**

There are no built-in operators or language features for composite data. No way to deal with strings, arrays, lists, sets. etc. **The standard library holds that**

C is small. I/O is painful and library driven, there is no garbage collection. C you have to manage your own memory with functions like ``malloc`` and ``free``

**Java was designed, C was implemented**

## Printf and specifiers

Printf is used to print data to the console.
```c
printf("%d fish, %f fish", 1,2.0);
```

specifiers are signified with a ``%``

|Spec.|Output|Spec.|Output|
|-----|------|-----|------|
|d,i|integer|u|unsigned int|
|f|float|e|float w/ exponant|
|g|float in std sci notation|x|unsigned int in hex|
|o|unsigned int in octal|s|Null terminated string|
|c|character|

Its important to be careful with specifiers

```c
printf("%d\n", 13.7);
printf("%x\n", 13.7);
printf("%c\n", 13.7);
```

all output different things.

## Basic command line

``ls`` will list everything in the current directory.

``cd`` to change to another directory

``cd ..`` will change to the parent directory

``gcc`` is the C compiler. and files can be compiled by running ``gcc hello.c`` which will output a executable called ``a.out`` which can be run by running ``./a.out``

## Compilation/Makefiles

``gcc`` or other compilers will take a ``.c`` file and preprocess any ``#include`` and ``#define`` functions. ``#include`` will copy and paste any other C files into the C file.

All **C files** end with ``.c`` Only one C file should have a main function. If you have a function in a ``.c`` file it should be prototyped in a ``.h`` file of the same name.



All **Header Files** end with ``.h``. Header files contain other functions and extern declarations.

The ``.c`` file is then compiled into a ``.o`` file

When compiling multiple files, you can do it all on one line using:
``gcc main.c utility.c wombat.c -o program`` and putting them all as compilation targets.

You can also compile files indiviually then link them all at the end
```
gcc -c main.c
gcc -c utility.c
gcc -c wombat.c
gcc main.o utility.o wombat.o -o program
```

Chain compiling is also very efficent way to compile multi-program files since it only compiles the updated ones:

```
program: main.o utility.o wombat.o
  gcc main.o utility.o wombat.o -o program

main.o: main.c utility.h wombat.h
  gcc -c main.c

utility.o: utility.c utility.h
  gcc -c utilityt.c

wombat.o: wombat.c wombat.h
  gcc -c wombat.c

clean:
  rm -f *.o program
```

#### #include

Use angle brackets (< >) to include standard libraries.

Use quotes (" ") to include anything else.

Don't ``#include *.c`` only ``.h`` files

#### #define
This is the best way to define constants in c

``#define`` is generally put at the top of the file.

You can also creat a macro with ``#define`` that takes arguments.

```c
#include <math.h>
#define TO_DEGREES(x) ((x) * 57.29578)
#define ADD(a,b) ((a) + (b))

int main(){
  double theta = TO_DEGREES(2*M_PI);
  int value = ADD(5*2, 7);
}
```


#### Makefiles

Makefiles are files that can be executed to compile a program. The ``make`` utility is used. And should be called either ``makefile`` or ``Makefile``

Each makefile has a list of tarkets, each target is separated by a colon and a list of it's dependancies.

After the depfencies on a new line, indented is the command it will issue.

```makefile
all: hello
hello: hello.c
  gcc -o hello hello.c
clean:
  rm -f *.o hello
```







## Control Flow
In C there are the standard control flow operators

``if`` statments, ``switch`` statments, for selection.

#### Control Flow
``if`` statements:

```c
if(condition)
  statement1;
else
  statement2
```

``switch`` statements:

```c
switch(data){
  case constant1:
    statement1;
    break;
  case constant2:
    statement2;
    break;
  case constant3:
    statement3;
    break;
  default:
    defaultstatement;
    break;
}
```

``for``, ``while``, and ``do while`` loops for repitition.

``while`` loop:

```c
while(condition)
  statement;
```

``for`` loop:
the initialized variable must be initialized before the loop.

```c
for(initialization; condition; increment)
  statement;
```

``do-while`` loops:
Will run the loop once then check for conditions.

```c
do
  statement
while(condition)
```




There is **no boolean type** all conditionals are **any numer > 0 is True** and **0 = False**.

Type safety is much looser in C, something like this is an example:

```c
double a = 3.4;
int b = 27;
a = b; //legal in Java & C, since it's going simpler
b = a; //Illegal in Java, but C might give a warning, but will still compile.
```

**Declaration Syntax** is also different in C

You cannot declare a variable in the header of a for loop, like you can in java.


#### Literals

A literal is a fixed constant. It cannot be changed once defined. Also called constants

By default every integer is assumed to be a signed int. Put an ``L`` at the end to define it at a literal.

## Other C Features

``sizeof`` is a built in operator that will tell you the size of a data type or variable in bytes.

``const`` creates a constant, though its only a suggestion, they can be changed. Because of that ``#define`` is better to be used.

``getchar()`` will read the next character from input. Will return -1 when it reaches the end of file.

``putchar()`` is the ouput equivielent to ``getchar()`` it outputs a single character at a time.



## Number Systems and 2's Complement

##### Integers in other bases

Hex: begins with 0x ``int a = 0xDEADBEEF``

Oct: beings with 0  ``0765``

No binary literals.

#### Printing in other bases

``%d`` Decimal
``%x`` Hexadecimal
``%X`` Hex, but Capitalizes the A-F
``%o`` Octal

```c
printf("%d", 1050); //prints 1050
printf("%x", 1050); //prints 41a
printf("%o", 1050); //prints 2032
```


### Two's Complement
**Only works with a fixed number of bits.**

**If the MSB is 1 the number is negative, 0 is positive**

**Pos -> Neg**
```
6       is   0110
Flipped is   1001
Add 1   is   1010

1010 is -6
```
**Neg -> Pos**
```
-2      is   1110
Sub 1   is   1101
Flipped is   0010

0010 is 2
```

The flipping is done to make it so that addition can be done without conversion.

```
 0101  5
+1101 -3
---------
 0010  2
```
#### Floating Point Representation

A Floating point number is represented by a sign bit followed by a exponent, followed by a mantissa.

[1] sign bit [8 (float) 11 (double)] exponent [23(f) 52(d)] mantissa.

#### Endian

The Endian is where the most signifigant bit is called. If a the most signifigant bit is first its called little endian, if its last its called big Endian.

It doesnt really matter since it's all internally sonsistent. Mixed Endian is rare for memory but possible in ohter cases

```
http://users.etown.edu/w/wittmanb/cs222
 <----More Specific   More Specific--->
```


## Math Library

(Probably not in exam)

Must add to program by ``#include <math.h>`` and ``-lm`` must be added to the compilation command.

|Function|Result|Function|Result|
|--------|------|--------|------|
|cos(double t)|cos(t)|exp(double x)|e<sup>x</sub>|
|sin(double t)|sin(t)|log(double x)|ln(x)|
|tan(double t)|tan(t)|log10(double x)|Common log of x|
|acos(double x)|arccos(double x)|pow(double base, double exponent)|Raise base to power exp|
|asin(double x)|arcsin(x)|sqrt(double x)|√X|
|atan(double x)|arctan(x)|ceil(double x)|Round up X|
|atan2(double y, double x)|arctan(y/x)|floor(double x)|Round down X|
|fabs(double x)|Absolute Value of X|fmod(double value, double divisor)|Remainder of dividing value by divisor|

## System Limits:

The header ``limits.h`` includes a number of constants helpful for C

|Constant|Typ. Value|Constant|Typ. Value|
|--------|---------|--------|-------|
|SCHAR_MIN|-128|INT_MIN|-2147483648|
|SCHAR_MAX|127|INT_MAX|2147483647|
|UCHAR_MAX|255|UINT_MAX|4294967295|
|CHAR_MIN|-128|LONG_MIN|-2147483648|
|CHAR_MAX|127|LONG_MAX|2147483647|
|SHRT_MIN|-32768|ULONG_MAX|4294967295|
|SHRT_MAX|32767|CHAR_BIT|8|
|USHRT_MAX|65535|

#### Other Limits

Getting other limits like, how many files can be open at once, max name of a filename etc. can all be gotten from calling the sysconf() or pathconf() functions.


## Bitwise Operators

``&``: bitwise AND
``|``: bitwise OR
``~``: bitwise NOT
``^``: bitwise XOR
``<<``: Left Shift
``>>``: Right Shift

Same as 332 Operators

Swapping without a temp:
```c
x = x ^ y;
y = x ^ y;
x = x ^ y;
```


## Things to do not because "style"

``break`` command will break out of a loop. Apparenty loops should only have 1 enterance and 1 exit.

``continue`` is similar to break, but instead of breaking out of the loop, it just makes it restart the loop.

``goto`` will go to a named label. This creates spaghetti code.

```c
goto stop;
somethingElse
stop;
```

## Error handling

There are no exceptions in C like there are in Java.

When a system call fails it just outputs -1.

To find out why something failed you can include the error library  using ``#include <errno.h>``

This creates a var ``errno`` which will hold details of an error if it occurs. Along with it the ``perror()`` function is used to print errors.

## Functions
```c
type name(arguments){
  statements
}
```

In C you don't have too, but should put a return type.

**Prototyping** is where you delcare the function before it's used so it can be used in preceeding functions.

If your method doesnt take any parameters, you should put ``void`` as the arguments like:

```c
double stuff(void){}
```

Passing arrays to functions is slightly different. You also have to pass the lentgh. Arrays don't get returned. Any changes made to an array inside a function affects it outside the function as well.

```c
void func(int array[], int length){
  //Something
  //You don't have to return anything to edit the array.
  //This is because arrays are basically pointers.
}
```

Passing multidimensional arrays only requires the second dimension
```c
func(array[][8]);
```
## Arrays

To declare an array the form
``type name[size]`` is used.

For example ``int list[100]`` will create an array called list of length 100.

When you declare an array you are creating the whole array. No second step like Java. You **must** give a fixed size.

Accessing elements is as you would expect:
```c
list[9] = 142;
printf("%d", list[9]);
```
**Arrays start at 0, if you think otherwise you're wrong**

In C you **must keep track of how long an array is** usually in another variable.
you could use something like ``sizeof`` but that is reliant on you knowing the type **and** that only gives you the length of the total array, not what you have filled.

Arrays start filled with garbage to start off and you wont get a warning about it either. To combat this you *can* use explicit initialization like:

``int primes[10] = {2, 3, 4, 5, 7, 11, 13, 17, 19, 23, 29};``

or without giving a set legnth on delcaration:

``char grades[] = {'A', 'B', 'C', 'D', 'E', 'F'};``

and the compiler will figure out the size.

## Memory Editors

#### memset()

This will just set all the values in a chunk of memory to a set value.

Usage: ``memset(memeory to change, set memory, how much to change);``

```c
int values[100];
memset(values, 0, sizeof(int)*100);
//zeros out an array
char letters[26];
memset(letters, 'A', sizeof(char)*26);
//sets array to all A's
```

#### memcpy()

copies values from other locations in memory, useful for copying arrays.

Usage: ``memcpy(whereitsgoing, whereitscomingfrom, howmuchmemory``

```c
int cubes[100];
int copy[100];
//Fill cubes with stuff
memcpy(copy, cubes, sizeof(cubes)); // Will put the data in cubes in copy.
```

## Strings

C does not have a built-in string type. Instead a string in C is just an array of chars ending in a null terminator: ``/0``

A string can still be assigned as a literal though. Something like ``char word[] = "wombat";`` is still a perfectly vaid way to create a string.

Printing a string can be done in printf by using the ``%s`` modifier like:
```c
printf("%s\n", "Wombats");
```

``string.h`` can be included for some string functions. Most useful are:

``strcpy(char destination[], char source[])``: Pretty self explanatory.

``strcmp(char string1[], char string2[])``: Compares strings alphabetically, returns negative is str1 comes before str2, returns 0 if they are the same, and returns positive if str2 comes before str1.


## Pointers (Not really on exam)

A **pointer** is a variable that holds an address.

``&`` gets the address of something.

``*`` gets the contents of a pointer.

To declare: ``int *pointer``, the whitespace doesnt matter.

You can use this to have a pointer point to another variable something like:

```c
int value = 5;
int *pointer = &value;
```
will point ``pointer`` towards the address of value, and therefore ``value``

Pointers can also edit the value of a variable

```c
int value = 5;
int *pointer = &value;
*pointer = 500; //Changes value to 500
```

Arrays **are** pointers. All operations that can be done with a pointer can be done with an array and vise-versa.

**void pointers** can be used when you don't know what you're going to be pointing at.


## Command line arguments

C has built in arguments into main for command line arguments there are called ``argc`` and ``argv``.

```c
int main(int argc, char** argv){
  //argc shows how many different inputs there are (how many words)
  //argv is a 2D array which it's stored in.
}
```

Everything put into the command line is stored in argv which means the execute command itself is in position 0.





## Systems Programming

#### System Calls:

A system call a way to ask the kernel to do something. Since a lot of things can only be done by the kernel system calls are provided via an API (Application Programming Interface). When making a system call the processor changed from a user mode to a kernel mode. There are a fixed number of systems calls defined for a system.

#### glibc

``glibc`` is the most common C standard library.

#### System Types

C has a feature called ``typedef`` which allows a user to give a new time to a type.

System types are often used for cross compatability where type sized might be different.

The most common is ``size_t`` which is the type that specifies length. There are other things like ``pid_t`` for process ID's

#### The Shell
A shell is a program that takes commands and then does something with them.

Some popular shells:
* sh
* csh
* ksh
* bash

#### Users and Groups
On Linux every user has a login name and UID. ``/etc/passwd`` holds all passwords.
Groups of users exist for administrative purposes and are defined in ``/etc/group``.

The **superuser** has complete control over everything and can do anything. This account is usually called ``root``. It is a bad idea to use root for obvious reasons. Instead users who want to use elevated privledges should use sudo.

#### Single file system.

Unlike Windows in which there is a ``C:`` drive and whatnot. Linux is all contained within one folder the root folder ``/`` and in that has everything else. Common folders which can be found are:

``/bin`` which is for programs (binaries)

``/etc`` which is generally for configurations

``/usr`` is for user programs

``/boot`` is for boot programs

``/dev`` is for devices

``/home`` is for home directories

A **directory** is a kind of file that lists other files. Files can be up to 255 characters in lengt and can contain any ASCII character except ``/`` and ``/0``

#### File I/O

All I/O operations in Linux are treated like file I/O printing to the screen is writing to a file called ``stdout`` and reading from the keybaord is reading from a file ``stdin`` when we get the basic functions needed to open read and write file we'll be able to do almost any kind of I/O.

#### Proceses:

A **process** is a program that is currently executing.

``text`` The executable code.

``Data`` The static variables.

``Heap`` Is dynamically allocated variables

``Stack`` The area that grows and shrinks with function calls

A **segmentation fault** is when your code tries to access a segment it's not supposed too. A process will usually run with the same permissions as the user who started it.






# IN-CLASS TEST REVIEW
(Slides 13)

#### Exam consists of:

* Multiple Choice x10; 2pts each.
* Some short answer;
* 60% are programming questions, each worth 15%.
  * at least one will be a full C program.

#### Things that "might be on it"
- Make a makefile
- Converting between bases (2, 8, 10, 16)
  - Take it in groups of 3 or 4 in binary to get Oct or Hex.
- 2's complement.
- Floating Point
- Not really any pointers.
