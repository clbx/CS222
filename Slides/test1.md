### Ask if on test:
* Conditional compilation (Slides #5)
* System Limits (Slides #6)
* Precedence Table (Slides #6)


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

The ``.c`` file is then compiled into a ``.o`` file

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

Makefiles are files that can be executed to compile a program. The ``make`` utility is used.

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
Only works with a fixed number of bits.

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





## Systems Programming

#### System Calls:

A system call a way to ask the kernel to do something. Since a lot of things can only be done by the kernel system calls are provided via an API (Application Programming Interface). When making a system call the processor changed from a user mode to a kernel mode. There are a fixed number of systems calls defined for a system.

#### glibc

``glibc`` is the most common C standard library.

#### System Types

C has a feature called ``typedef`` which allows a user to give a new time to a type.

System types are often used for cross compatability where type sized might be different.

The most common is ``size_t`` which is the type that specifies length. There are other things like ``pid_t`` for process ID's