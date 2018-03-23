#include "lab9.h"

int main()
{
	char input;
	char name[NAME_LENGTH];
	char email[EMAIL_LENGTH];
	int age;
	ContactList list;
	Contact* contactPointer = NULL;

	list.capacity = 5;
	list.contacts = (Contact*)malloc(list.capacity*sizeof(Contact));
	list.size = 0;

	while( (input = menu()) != 'Q' )
	{
		switch( input )
		{
			case 'A':	//add contact
				printf("\tEnter name: ");
				getLine(name);
				printf("\tEnter e-mail: ");
				getLine(email);
				printf("\tEnter age: ");
				scanf("%d", &age);
				addContact(name, email, age, &list);
				break;
			case 'F':	//find contact
				printf("\tEnter name: ");
				getLine(name);
				contactPointer = findContact(name, &list);
				if( contactPointer == NULL )
					printf("\t\"%s\" not found\n", name);
				else
					printContact( contactPointer );
				break;
			case 'P': 	//print all contacts
				printAllContacts(&list);
				break;
		}
	}

	return 0;
}

char menu()
{
	int choice;  // input

	// print menu
	printf("A - Add a contact\n");
	printf("F - Find and display a contact\n");
	printf("P - Print contact list\n");
	printf("Q - Quit\n");
	printf("Your choice: ");

	// Get input
	while( isspace(choice = getchar()) );
	while( getchar() != '\n');

	return toupper(choice);
}

void addContact(char* name, char* email, int age, ContactList* list){
	if(list->size == list->capacity){
		//printf("Increasing Contacts Array\n");
		list->contacts = (Contact*)realloc(list->contacts, list->capacity*sizeof(Contact)*2);
		list->capacity = list->capacity * 2;
	}
	list->contacts[list->size].name = strdup(name);
	list->contacts[list->size].email = strdup(email);
	list->contacts[list->size].age = age;
	list->size++;
}

Contact* findContact(char* name, const ContactList* list){
	int i;
	//printf("%d", list->size);
	for(i = 0; i < list->size; i++){
		if(!strcmp(list->contacts[i].name,name)){
			//printf("\tFound name: %s\n", name);
			return &list->contacts[i];
		}
	}
	return NULL;
}


void printAllContacts(const ContactList* list)
{
	int i = 0;

	if( list->size > 0 )
	{
		// print everything
		for(i = 0; i < list->size; i++)
		{
		  printContact(&list->contacts[i]);
		  printf("\t----------------\n");
		}
	}
	else
		printf("\tContact list is empty!\n");
}

void printContact(const Contact* contact){
	printf("\t%s ", contact->name);
	printf("<%s> ", contact->email);
	printf("is %d years old.\n", contact->age);
}


void getLine(char buffer[])
{
	int i = 0;
	char c;
	while( (c = getchar()) != '\n' && c != EOF )
		buffer[i++] = c;
	buffer[i] = '\0';
}