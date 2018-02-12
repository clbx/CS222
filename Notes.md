# CS 222 Systems Programming Notes
## Clay Buxton
### Spring 2018

## Jump To


# Makefiles
Uses the "Make" Utility, tells it what to makefile

```makefile
all: hello
hello: hello.c
  gcc -o hello hello.c

  clean:
    rm -rf *.o hello
```


# Escape Sequences

|*Op*|*What it does*|*Operator*|*What it does*|
|----------|--------------|----------|--------------|
|\a|Alert Character|\\| Backslash|
|\b|Backspace|\?|Question Mark|
|\f|Formfeed|\'|Single Quote|
|\n|New Line|\"|Doubel Quote|
|\r|Carriage Return|\ooo|Octal Number|
|\t|Horizontal Tab|\xhh| Hex Number|
|\v|Vertical Tab|\0|Null Term for String|

# Bitwise Operators

|*Operator*|*Effect*|
|----------|--------|
|&  | Bitwise AND|
| Pipe| Bitwise OR
|~  |  Bitwise NOT
|^  | Bitwise XOR
|<< | Left Shift
|\>> |  Right Shift

### Bitwise AND


```
5 & 2   101
        010  -> 000
```
In comparison '5 && 2' would return true

# Error Handling
```c
#include <errno.h>
```
Creates a integer called errno which has error codes
perror(""), prints when there is an error

# External declaration
if you want a global variable from another file needs to be defined with ```extern```

```static``` does not allow for other files to use the varaible

# Registers
This shows the compiler what will be used a lot and will put it in a CPU Registers


# Pointers and Arrays

A pointer is a varible that contains the address of a variable

```p = &c``` will assign the address of c to the varible p

This only applies to objects in memory.

```c
int x = 1, y = 2, z[10];
int *ip                  //ip is a poiter to an integer
ip = &x                  //ip is now pointing to the location of x making ip = x
y = *ip                  //y now = x which is 1.
*ip = 0                  //X is now equal to 0, since we set the data x is
                         //referencing to 0
ip = &z[0]               //ip now points to z[0]
```
Any operation done to a pointer will also happen to the variable's data it points too

```c
int *ip = &x
*ip = *ip + 10;

```
Will increment X by 10, uniary operators work too, however ```(*ip)++``` must be done to prevent it incrementing ```ip```

### Pointers and Functions Arguments
Pointers allow functions to edit varaibles outside it's scope. A swap is a good example

```c
void swap(int *px, int *py){
  int temp;
  temp = px;
  *px = *py;
  *py = temp;
}

```
**
It doesnt switch the varibles themselves or the numbers, but just the things it points too

### Pointers and Arrays

**Any** operaton done by Array Subscripting can be done with pointers

for example
```int a [10]``` will define an array of size 10

then we can define int ```int *pa = &a[0]``` and that sets that pointer to the first element of the array

The assignment ```x = *pa``` will copy the contents of ```a[0]``` into ```x```

Since ```pa``` points to an element in the array ```pa+i``` will point to next or previous points in the array so ```pa+2``` will point to ```a[2]```

References to Array locations can also be used by referring to the array as a pointer, ```*(a+i)``` is a legal way to access data in ```a[i]``` the inverse is also true ```*(pa+i)``` can be accessed by doing ```pa[i]```

Passing to a function is identical too ```f(&a[2])``` is the same as ```f(a+2)```

### Address Arthmetic
