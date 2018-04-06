#ifndef LAB11_H
#define LAB11_H

#include <stdio.h>	 // printf, scanf
#include <stdlib.h>	 // malloc, realloc, free
#include <ctype.h>   // toupper, isalpha, isdigit, isspace
#include <string.h>  // strcmp, strdup

#define NAME_LENGTH  32
#define EMAIL_LENGTH  20

/************* Data Types *************/
typedef struct _Contact
{
	char*	name;	// Full name of contact
	char*	email;	// E-mail address of contact
	int	age;	// Age of contact

	struct _Contact* left;
	struct _Contact* right;
} Contact;

/************* Functions You Have to Write *************/

/* Add contact information to the correct location in the tree and return a pointer to the root node.
   Use strdup() to allocate copies of the name and email strings.
*/
Contact* addContact(char* name, char* email, int age, Contact* root);

/* Find a node in your tree. Return a pointer to the node if successful or NULL on failure. */
Contact* findContact(char* name, Contact* root);

/* Prints all the contacts in your tree, sorted lexicographically (like a dictionary). */
void printSortedContacts(Contact* root);

/* Deletes the tree, freeing everything you have allocated.
   Note that the name and email fields for each contact must be freed since they were also allocated by strdup().
*/
void cleanUp(Contact* root);


/************* Functions Defined for You *************/

/* Print the contact given as a parameter
 * The format should be:
 * Name: (name) <(email)> is (age) years old.
 */
void printContact(const Contact* toPrint);


/* Displays a menu.
 * Reads input until it sees a non-space character, and then flushes the rest of the line
 * Returns uppercase version of input character.
 */
char menu();

/* Read a line from stdin into buffer */
void readLine(char buffer[]);

#endif
