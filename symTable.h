#include "general.h"
#ifndef SYM_NODE
#define SYM_NODE
class Symbol_node
{
  friend class Symbol_table;

public:
  Symbol_node(void);
  Symbol_node(char *);
  void putval(VALUE);
  VALUE getval(void);
  char *getid(void);

private:
  char *id;
  int token;
  VALUE value;
  Symbol_node *next;
};
#endif
typedef Symbol_node *Symbol_ptr;
#ifndef SYM_TABLE
#define SYM_TABLE
class Symbol_table
{
public:
  Symbol_table(void);
  ~Symbol_table(void);
  int hash(char *);
  Symbol_ptr insert(char *);
  void remove(char *);
  Symbol_ptr lookup(char *);
  void dump_table(void);
  void print(Symbol_node *);

private:
  Symbol_ptr *table;
};

extern Symbol_table table;

#endif