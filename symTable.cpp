#include <iostream>
#include <string.h>
#include "symTable.h"

using namespace std;

//default node constructor
Symbol_node::Symbol_node()
{
	next = NULL;
}

//node constructor
Symbol_node::Symbol_node(char *id)
{
	this->id = new char[strlen(id) + 1];
	strcpy(this->id, id);
}

//fetch id of an element in the symbol table
char *Symbol_node::getid()
{
	return id;
}

//set value of an element in the symbol table
void Symbol_node::putval(VALUE val)
{
	value = val;
}

//fetch value of an element in the symbol table
VALUE Symbol_node::getval()
{
	return value;
}

//default table constructor
Symbol_table::Symbol_table()
{
	table = new Symbol_ptr[TABLE_SIZE];
	for (int i = 0; i < TABLE_SIZE; i++)
		table[i] = NULL;
}

//table destructor
Symbol_table::~Symbol_table()
{
	delete[] table;
}

//hash function
int Symbol_table::hash(char *id)
{
	int val = 0;

	for (int i = 0; i < strlen(id); i++)
	{
		val += id[i] * (i + 1) * TABLE_SIZE;
	}

	val %= TABLE_SIZE;
	return val;
}

//print function to print symbol table element values
void Symbol_table::print(Symbol_node *head)
{
	cout << "   " << head->id << " = " << head->value.ivalue << endl;
}

//dump table function to print whole table
void Symbol_table::dump_table()
{
	cout << "======================" << endl;
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		Symbol_node *head = table[i];
		while (head != NULL)
		{
			print(head);
			head = head->next;
		}
	}
	cout << "======================" << endl;
}

//lookup an id within the symbol table
Symbol_ptr Symbol_table::lookup(char *id)
{
	int index = hash(id);
	//memory location of the element
	Symbol_ptr head = table[index];

	while (head != NULL)
	{
		//if the two are equal then return the location
		if (strcmp(id, head->id) == 0)
			return head;

		head = head->next;
	}

	return NULL;
}

Symbol_ptr Symbol_table::insert(char *id)
{

	int index = hash(id);
	Symbol_ptr location = lookup(id);

	/*if the id is not found then insert the stuff
	at the beginning of the linked list*/
	if (location == NULL)
	{
		Symbol_ptr stuff = new Symbol_node(id);
		stuff->next = table[index];
		table[index] = stuff;
		return stuff;
	}

	//otherwise return the location of where the id was found
	return location;
}