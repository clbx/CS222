#### Things to know
* Unix/Linux
* Types
* Layers
* Declaring pointer to function

#### Format of Exam
Tuesday at 11
* Like 1 and 2, but longer
* Final will take ~2 hours


#### Programming Questions
* Converts an int to string representation in hex
* Function that converts a string representation of an integer in hex to an int



#### Things to review from quizzes
* 2's Complement
* Random
* Linked Lists
* Seven Layers of OSI reference

#### Things to review from Exams
* Powers
* Merge Arrays
* To Octal, Hex, Bin, and Dec
* Linked Lists


### Slides

**Unix** is a standard for operating systems, Linux and Free BSD are not Unix, they are Unix-like
**Linux** Linus Torvalds made it in 1991 for the i386 under GPL. BSD also came to life, but not as much

|Type|Meaning|Size|
|----|-------|----|
|char|Smallest addressable chunk of memory|1 Byte|
|short|Short signed integer type|2 Bytes|
|int|signed integer|4 Bytes|
|long|Long signed integer|4 Bytes|
|float|single precision floating point|4 Bytes|
|double|double precision floating point|8 bytes|
No Bool!

Can add ``unsigned`` to a lot to make it unsigned.

**Makefile**
```makefile
all: hello

hello: hello.c
	gcc -o hello hello.c

clean:
	rm -f *.o hello
```

**Litals in other bases**
```c
int a = 0xB432D //Hex
int b = 0323 //Octal
```

No binary representation


**Endian**
Big endian meaning the most significant bit is the first bit
Little meaning the least significant is first.
