#ifndef LAB9_H
#define LAB9_H

#include <stdio.h>	 // printf, scanf
#include <stdlib.h>	 // malloc, realloc, free
#include <ctype.h>   // toupper, isalpha, isdigit, isspace
#include <string.h>  // strcmp, strdup

#define NAME_LENGTH  32
#define EMAIL_LENGTH  20

/************* Data Types *************/
typedef struct
{
	char*	name;	// Full name of contact
	char*	email;	// E-mail address of contact
	int	age;	// Age of contact
} Contact;

typedef struct
{
	Contact*	contacts;	// Dynamically allocated array of contacts
	int		size;		// Total contacts stored in the list
	int		capacity;	// Size of the array (never less than size)
} ContactList;


/************* Functions You Have to Write *************/

/* Adds a contact
 * Resizes the array to fit the new contact, if necessary
 * If a new contact requires the array to be reallocated, it should be doubled in size
 */
void addContact(char* name, char* email, int age, ContactList* list);

/* Searches the list for the contact name's passed in.
 * Returns the position of the contact by that name.
 */
Contact* findContact(char* name, const ContactList* list);


/************* Functions Defined for You *************/

/* Print the contact given as a parameter
 * The format should be:
 * Name: (name) <(email)> is (age) years old.
*/
void printContact(const Contact* toPrint);
/* Prints the entire list of contacts
 * This function calls your printContact() function
 * The format should be:
\t(name) <(email)> is (age) years old.
\t----------------
\t(name) <(email)> is (age) years old.
\t----------------
     ...
\t----------------
\t(name) <(email)> is (age) years old.
\t----------------
*/
void printAllContacts(const ContactList* list);

/* Displays a menu.
 * Reads input until it sees a non-space character, and then flushes the rest of the line
 * Returns uppercase version of input character.
 */
char menu();

/* Fills the buffer with characters from stdin until the end of the line is reached
 * It calls getchar() internally
 * Puts a null character at the end of the buffer
 */
void getLine(char buffer[]);

#endif
