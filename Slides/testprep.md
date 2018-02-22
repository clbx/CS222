1.) What is Unix **Unix is a standard for Operating systems**

2.) What is Linux **A Unix-Like Operating System, commonly paired with a lot of GNU tools to be what we refer as Linux**

3.) What was FreeBSD for **Academia**

4.) What is GNU **"GNU's not Unix" a collection of tools commonly paired with Linux**

5.) Who made Linux **Linus Torvalds**

6.) Fill out this table:

|Type|Length|
|----|------|
|char|2|
|int|4|
|float|4|
|short|2|
|long|4|
|double|8|

7.) What about ``long long`` and ``long double`` are different **One is supported in C99, the other is not**

8.) What does ``#include`` do internally  **Copies and pastes everything from that file to the program**

9.) What library be usually included in every file  **stdio.h**

10.) What does ``printf`` do? **Prints something out the the user/stdout**

11.) Fill out this table:

|Specifier|Output|
|---------|------|
|d/i|An integer|
|f|A flout|
|u|And unsigned integer|
|x|Hex|
|o|Octal|
|s|String|

12.) Fill out this command line table:

|Command|Result|
|-------|------|
|ls|Lists all files in current directory|
|cd|Changes working directory|
|cd ..|Goes "up" one folder in the directory|
|gcc|The command to run a C compiler|

13.) What is a makefile **A make file holds all of the commands needed to easily compile a C file**

14.) What should you name your makefile **makefile or Makefile**

15.) What does the compiler process first when compiling a ``.c`` file **The header statements (#include, #define, etc.)**

16.) What's the difference between a ``.c`` and ``.h`` file. **A .c file holds main and function, a .h is a header file which can hold external varaibles and functions**

17.) Unless specified what is the default compilation output. **a.out**

18.) How would you use ``gcc`` to output a file named ``animal.c`` with the name ``wombat`` **gcc animal.c -o wombat**

19.) Do file extensions matter? **no**

20.) Write an example makefile that will compile ``animal.c`` into ``wombat`` and also have a clean command.

```makefile
animal: animal.c
  gcc animal.c -o wombat
clean:
  rm -f wombat
```

21.) Write an example makefile that will chain compile ``animal.c`` with ``utility.h``, ``marsupial.c`` with ``utility.h`` and ``australia.c`` with ``earth.h`` and have them all output as ``wombat``

```makefile
wombat: animal.o marsupial.o australia.o
  gcc animal.o marsupial.o australia.o -o program
animal.o: animal.c utility.c
  gcc -c animal.c
marsupial.o: marsupial.c utility.h
  gcc -c marsupial.c
australia.o: australia.c earth.h
  gcc -c australia.c
```

22.) What's the different between using brackets (< >) and quotes (" ") when including something. **Brackets are used for including things from the standard library, quotes are for everything else**

23.) What _shouldnt_ you ever include **A .c file**

24.) What does ``#define`` do **Creates a variable that can never be changed**

25.) Why is it different from declaring a ``const`` **Const is just a suggestion does not stop the program from changing it's data**

26.) What will the output be of this program:

```c
int a = 5;
switch(a){
  case 4:
    printf("Hello World");
  case 5:
    printf("Hello World");
  case 6:
    printf("Hello World");
  case 7:
    printf("Hello World");
}
```

**Hello WorldHello WorldHello World**

27.) What is a boolean in C **There is no boolean type, a 0 is considered false and a positive number is considered true**

28.) What would the be the value of ``x`` be after this runs:

```c
int x = 12;
x = sizeof(x);
```

**48**

29.) Describe ``getchar()`` and ``putchar()`` **Getchar and putchar will put or get a single character**

30.) Turn 56 (Decimal) into Hex: **38**

31.) Turn F4A (Hex) into Octal: **7512**

32.) Turn 56 (Octal) into Decimal: **46**

33.) What is the binary value of -56 **11001000**

34.) How does floating point work. **It takes the first digit as a sign bit, and then divides the rest betwen a mantissa and an exponant.**

35.) What is Big Endian **Bit Endian is when the most signifigant digit is last, little endian is when it is first**

36.) What is Little Endian **See previous answer**

37.) What does the math library give you **More advanced math operators like square root and trig functions**

38.) What are the bitwise operators **& AND | OR ~ NOT ^ XOR << Left Shirt >> Right Shift**

39.) What is the result of ``5 & 12``  (Assuming int for all); **4**

40.) What is the result of ``6 | 13`` **15**

43.) What library should you import for error handling **errno**

44.) What is the varaible that library uses for showing errors **errno**

45.) How can you pass multidimensional arrays into a function **You have to show how big the second size**

46.) Declare an array named ``mammals`` that is 100 long and put ``5`` as the last element.

```c
int mammals[100];
mammals[99] = 5;
```

47.) What do arrays start at. **0**

49.) What must you make sure to do with arrays in C that you dont in most other languages. **Keep track of the length too**

50.) What does ``memset()`` do. **Can set a particular position in memory to a certain value**

51.) What does ``memcpy()`` do. **Copy a certain position on memory to another position in memory**

52.) What is a string in C actually **A string of characters**

53.) How do we show the end of a string **A null terminator '\0'**

54.) What library should we import to get string functions **string.h**

55.) What does ``strcpy()`` do. **Copies a string from another string**

56.) What does ``strcmp()`` do. **Compares two strings, returns -1 if the first string is 'first' 0 if their the same and 1 is when the second string is 'first'**

57.) How do you get the address of a variable. **Use the & operator next to a variable will return it's address**

58.) What signifies a pointer. **A * sign**

59.) Write a program that will edit the value of a variable using a pointer:

```c
int var = 7;
int *pvar = &var;
pvar = 10;
```

60.) What are the 2 generally used variables and their types for accepting command like arguments. **int argc and argv[][]**

61.) Where do these variables go to accept input from the command line. **The arguments of the main function**

62.) What is the ``glibc`` **The most commonly used C library**

63.) What is the shell **The place where users can input commands and interact with the computer**

64.) Name a popular shell **bash**

65.) What is the superuser **A user that can do anything on a computer without restriction**

66.) What is root **The most common default superuser, can do anything on a computer**

67.) What command can be run to temporarily gain superuser privledges **sudo**

68.) What's the difference between Windows and Linux in terms of file systems. **Linux is all in one single folder, while windows can be spread out across different drives. ***

69.) How does input and output work in Linux **Writes to a stdin and stdout file which is read and written to**

70.) What is a process **A program running**

71.) What happens when you get a segmentation fault. **A segmentation fault happens when a program accesses something it is not supposed to**


## Programming Questions:

1.) Write a complete program that will print out the first 100 perfect squares:

```c
#include <stdio.h>

int main(){
  int i = 0;

  for(i = 0; i < 100; i++){
    printf("%d\n", i*i);
  }
}
```

2.) Write a function that takes three doubles and returns the larges of the 3

```c
double topcheck(double x, double y, double z){
  if((x >= y) && (x >= y)){
    return x;
  }
  else if((y >= x) && (y >= z)){
    return y;
  }
  else if((z >= x) && (z >= y)){
    return z;
  }
}

```

3.) Create a prototype for the funtion you just wrote
```c
double topcheck(double x, double y, double z);
```

4.) Complete the function that takes in a char value. If the value is a lower case letter, it returns an uppser case version of the letter. Otherwise it's returned unchanged.

```c
char toupper(char value){
  int difference = 'A' - 'a';
  if((value >= 'a') && (value <= 'z')){
    value = value + difference;
    return value;
  }
}
```

5.) Complete the function so that it returns the largest number of repititions of any character that appears in the input. The input is a null terminated string.

```c
int repeats(char string[]){
  int length = 0;
  while(string[length] != '\0'){
    length++;
  }
  int i = 0, localmax = 1, totalmax = 1;
  for(i = 0; i < length -1; i++){
    if(string[i] == string[i+1]){
      localmax++;
    }
    else
      localmax = 1;
    if(localmax > totalmax){
      totalmax = localmax;
    }
  }
  return totalmax;

}
```
