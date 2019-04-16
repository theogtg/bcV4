#include "general.h"
#include "symTable.h"

/* variable declaration */
Symbol_table table;
char lexeme[100];
char nextChar, peek;
int lexLen;
int num = -1;
string input;

/* lookup - a function to lookup operators and parentheses
 and return the token */
int lookup(char ch, char next)
{
   switch (ch)
   {
   case '(':
      nextToken = LEFT_PAREN;
      addChar();
      break;
   case ')':
      nextToken = RIGHT_PAREN;
      addChar();
      break;
   case '+':
      nextToken = ADD_OP;
      addChar();
      break;
   case '-':
      nextToken = SUB_OP;
      addChar();
      break;
   case '*':
      nextToken = MULT_OP;
      addChar();
      break;
   case '/':
      nextToken = DIV_OP;
      addChar();
      break;
   case '%':
      nextToken = MOD_OP;
      addChar();
      break;
   case '^':
      nextToken = EXPO_OP;
      addChar();
      break;
   case '=':
      addChar();
      if (next == '=')
      {
         nextToken = EQ_OP;
         num++;
         addChar();
      }
      else
         nextToken = ASSIGN_OP;
      break;
   case '>':
      addChar();
      if (next == '=')
      {
         nextToken = GREATEQ_OP;
         num++;
         addChar();
      }
      else
         nextToken = GREAT_OP;
      break;
   case '<':
      addChar();
      if (next == '=')
      {
         nextToken = LESSEQ_OP;
         num++;
         addChar();
      }
      else
         nextToken = LESS_OP;
      break;
   case '!':
      addChar();
      if (next == '=')
      {
         nextToken = NOTEQ_OP;
         num++;
         addChar();
      }
      else
         nextToken = EOF;
      break;
   default:
      nextToken = EOF;
      addChar();
      break;
   }
   return nextToken;
}

/*****************************************************/
/* addChar - a function to add nextChar to lexeme */
void addChar()
{
   if (lexLen <= 98)
   {
      lexeme[lexLen++] = nextChar;
      lexeme[lexLen] = '\0';
   }
   else
      printf("Error - lexeme is too long \n");
}

/*****************************************************/
/* getChar - a function to get the next character of
   input and determine its character class 
   Two globals are set
   nextChar - the next character scanned from the input.
   charClass - the category of the character - LETTER, DiGIT, OPERATOR
*/
void getChar()
{
   if (getString() >= 0)
   {
      nextChar = input[num];
      if (isalpha(nextChar))
      {
         charClass = LETTER;
         peek = input[num + 1];
      }
      else if (isdigit(nextChar))
         charClass = DIGIT;
      else if (nextChar == '\n')
         charClass = NEWLINE;
      else if (nextChar == '#')
         charClass = COMMENT;
      else
         charClass = OPERATOR;
   }
   else
      charClass = EOF;
}

/*****************************************************/
/* getString - a function to get all the input and
               place it into a string.
   Two globals are set
   input - puts the whole input into a string
   charClass - the category of the character - LETTER, DiGIT, OPERATOR
*/
int getString()
{
   if (num + 1 < input.length())
   {
      num++;
      return num;
   }
   else
   {
      string line;
      if (getline(cin, line))
         input += line + '\n';
      num++;
      return num;
   }
}

/*****************************************************/
/* getNonBlank - remove white space characters.
   call getChar until it returns a non-whitespace 
   character.
   nextChar will be set to the next non-whitespace char.
*/
void getNonBlank()
{
   //input.erase(remove(input.begin(), input.end(), ' '), input.end());
   while (nextChar == ' ')
      getChar();
}

/*****************************************************/
/* lex - a simple lexical analyzer for arithmetic
 expressions */
int lex()
{
   token = nextToken;
   lexLen = 0;
   getNonBlank();
   switch (charClass)
   {

   case NEWLINE:
      //cout << "--NEWLINE FOUND--" << endl;
      break;

   case COMMENT:
      nextToken = COMMENT;
      break;

   /* Parse identifiers - once you find the first
      letter, read and add char by char to lexeme. */
   case LETTER:
      addChar();
      getChar();
      /* After first char, you may use either char or digits */
      while (charClass == LETTER || charClass == DIGIT)
      {
         addChar();
         getChar();
      }
      /* handles quit, dump, and print */
      if (strcmp(lexeme, "quit") == 0)
         nextToken = QUIT;
      else if (strcmp(lexeme, "dump") == 0)
         nextToken = DUMP;
      else if (strcmp(lexeme, "print") == 0)
         nextToken = PRINT;
      else if (strcmp(lexeme, "if") == 0)
         nextToken = IF_STMT;
      else if (strcmp(lexeme, "then") == 0)
         nextToken = THEN_STMT;
      else if (strcmp(lexeme, "else") == 0)
         nextToken = ELSE_STMT;
      else if (strcmp(lexeme, "fi") == 0)
         nextToken = FI_STMT;
      else if (strcmp(lexeme, "while") == 0)
         nextToken = WHILE_STMT;
      else if (strcmp(lexeme, "do") == 0)
         nextToken = DO_STMT;
      else if (strcmp(lexeme, "done") == 0)
         nextToken = DONE_STMT;
      /* puts id into symbol table */
      else
      {
         nextToken = IDENT;
      }
      break;

   /* Parse integer literals - once you find the first
      digit, read and add digits to lexeme. */
   case DIGIT:
      addChar();
      getChar();
      while (charClass == DIGIT)
      {
         addChar();
         getChar();
      }
      nextToken = INT_LIT;
      break;

   /* Parentheses and operators */
   case OPERATOR:
      lookup(nextChar, input[num + 1]);
      getChar();
      break;

   /* EOF */
   case EOF:
      nextToken = EOF;
      lexeme[0] = 'E';
      lexeme[1] = 'O';
      lexeme[2] = 'F';
      lexeme[3] = '\0';
      break;

   } /* End of switch */

   return nextToken;
}