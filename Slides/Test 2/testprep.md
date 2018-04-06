# Review for Test 2 CS222 Systems Programming

* Creating a 2D Array
* Random Numbers
* Pointers (a lot)
* Write atoi() functions
* time
* No Trees, No File IO

#### Things to practice
* Creating 2D Array [ ] [ ]
* Using Random Numbers [ ] [ ]
* Write atoi and itoa [X] [ ]
* Deal with pointers. [ ] [ ]


## Pointers

#### Returning Pointers

Functions can return pointers

If you get a pointer back you can update the value it points to.

Pointers can also be used to give you a different view into an array

#### strdup();
Something like ``strdup()`` is an exaple of this. It takes in a character array and returns a character array.

``char* new = strdup(old)`` will copy all of old into new. It calls malloc internally, no need to allocate the memory yourself.


## Dynamic Memory allocation

#### malloc()
Memory can be dynamically allocated using ``malloc()``. Requires ``stdlib.h``.

Specify how many bytes of memory is wanted to allocation:
``int* data = (int*)malloc(sizeof(int)*20)`` Will allocate enough for 20 integers

#### calloc()
Clear and allocate memory using ``calloc(size_t itmes, size_t size)`` memory is zeroed out and allocated

#### realloc()
Resize a block of memory pointed at by the pointer, usually to be longer using ``realloc(void* pointer, size_t size);``

#### free()
C does not collect it's own garbage, you must free allocated memory.

```c
char* things = (char*)malloc(100);           //Will Allocate 100 bytes of memory
free(things);                           	 //Will then free those 100 bytes.
```
If you try and free something that's already been freed, you'll probably crash.

#### 2-D Array Allocation
**Ragged Approach**: Allocating each row individually
```c
int** table = (int**)malloc(sizeof(int*)*rows);
int i = 0;
for(i = 0 i < rows; i++)
	table[i] = (int*)malloc(sizeof(int))*columns);
```

Then can be accessed by using ``table[x][y] = 14``

Then freeing the ragged approach:
```c
for(i = 0; i < rows; i++)
	free(table[i]);

free(table);
```

**Contiguous Approach**

You can allocate the memory for the rows at once, then make each row point to the right place
```c
int** table = (int**)malloc(sizeof(int*)*rows);
int* data = (int*)malloc(sizeof(int)*rows*columns);

for(i = 0; i < rows; i++)
	table[i] = &data[i*colums];
```
Will be continuous in memory.

Freeing the array is much easier, just:
```c
free(table[0]);
free(table);
```

|Type|Pros|Cons|
|----|----|----|
|Ragged|Each row can be allocated and freed independantly, rows can be shuffled with pointer changes, rows can be different lengths|Fragmented memory. Less locatilty, requires a loop to free|
|Contiguous|Better locatilty, easier free, shuffling rows is possible but you have to keep track of the beginning|Large allocations can fail (OOM), can't free individual rows|

## Random Numbers

Requires ``stdlib.h`` and ``time.h``

Using ``rand() % n`` to get values between ``0`` and ``n-1``

Call ``srand(time(NULL))`` once before calling ``rand()``


## Inputs

#### scanf();
``scanf`` uses the same formatting as ``printf`` to get inputs

```c
int number;
scanf("%d", &number);
```
must use the ``&`` to reference the variable its editing


## Software Engineering

#### Unit Testing
Unit tests are the testing for certain portion of code. Different tests are:

* Positive Test Cases: Cases that should work
* Boundary condition test cases: Special cases like first or last item in a list. Called "corner cases" or "fringe cases".
* Negative Test Cases: Cases we know will fail

**Regression Testing** When a bug is found keep the test case that demonstrated the bug. Then always include that test case in future tests

**Black Box Testing** Black box testing is when you only know the input and the output.

**White Box Testing** When you know the internals and work testing based off that.

Traces are using things like printf to show where a program runs.

#### Debugging

printf() works well as a basic debugger. However it may not be availble to programs with a GUI, it might mess up output and it may not work in deep sysstems programming.

Another approach is using ``fprintf(stderr, "")`` which will pipe the output to another stream.

#### GDB
The GNU Debugger

It is a command line utility that is availble on Linux & Unix.

Requires the source code of a program to debug.

**Basic GDB Commands**

|Command|Shortcut|Description|
|-------|--------|-----------|
|run|r|Start the program running|
|list 135|l|List the code near 135|
|list function|l|List the code near the start of function()|
|print variable|p|print the value of an expression|
|backtrace|bt|List a stack trace|
|break 29|b|Sets a breakpoint on line 29|
|break function|b|Set a breakpoint a the start of function()|
|continue|c|start running again after stopping at a breakpoint|
|next|n|Execute next line of code, skipping over a function|
|step|s|Execute next line of code, stepping into function|
|quit|q|Exits GDB|

## String Functions

Using the ``atoi()`` function we can turn a string into a integer

Using the ``itoa()`` function we can turn a int into a string

## Time

There are 2 different types of time:

**Real Time**  Also known as wall-clock or calendar time. Its the common notion of time

Usually stored as a number of seconds since January 1st 1970. Known as the Unix Epoch. Problem with this is that when its stored as a 32bit int is that it will roll around on January 19, 2038.

**Process Time** Process time is the amount of time your process has spend on the CPU.

There is usually no correlation between system time and calendar time
Go to the settings, edit your

``time()`` gives the amount of seconds since the Unix Epoch

``gettimeofday()`` gives a more specific output of time

``ctime()`` takes a time_t and returns a readable string showing the time

#### Structs

A struct is similar to a class in Java. A collection of one or more variables.

Example:
```c
struct point{
	double x;
	double y;
}
```

Declaring a struct is used by ``struct student bob``, struct is needed first!

Accessing parts of structs is used by a dot notation.

``bob.GPA = 3.67`` sets the part of ``bob`` called ``GPA`` to 3.37

#### Putting arrays and pointers into structs

```c
struct triangles{
	struct point vertices[3];
}
```

With a pointer in a struct copy the scruct will copy the pointer, but will not make a copy of the contents. Changing a pointer in one struct can affect it in another.

#### Pointers to struct

We can define a pointer to struct

```c
struct student bob;
struct student* studentPointer;
strcpy(bob.name, "Blob Blobberwob");

studentPointer = &bob;
```

if we wanted to change something in that pointer, we would need to do ``(*studentPointer).GPA = 2.8`` but thats lame so instead we can do ``studentPointer->GPA = 2.8``


#### Naming Types
Using ``typedef`` you can create types.

They are most useful with structs

Using typedef, you can make it so that you don't need to use struct every time you call a struct

```c
typedef struct _wombat{
	char name[100];
	double weight;
}wombat;

```
