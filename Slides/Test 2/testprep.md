# Review for Test 2 CS222 Systems Programming

* Creating a 2D Array
* Random Numbers
* Pointers (a lot)
* Write atoi() functions
* time
* No Trees, No File IO


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


## Inputs

#### scanf();
``scanf`` uses the same formatting as ``printf`` to get inputs

```c
int number;
scanf("%d", &number);
```
must use the ``&`` to reference the variable its editing

