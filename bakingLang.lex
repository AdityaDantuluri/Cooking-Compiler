%{

/*-------------------------------------------------------------------------*
 *---									---*
 *---		bakingLang.lex						---*
 *---									---*
 *---	    This file defines lexemes for the baking language.		---*
 *---									---*
 *---	----	----	----	----	----	----	----	----	---*
 *---									---*
 *---	Version 1.0		2016 November 21		Aditya Dantuluri	---*
 *---									---*
 *-------------------------------------------------------------------------*/

//  Compile with
//  unix> flex -o bakingLang.c bakingLang.lex
//  unix> gcc bakingLang.c -c
//  unix> gcc -o bakingLang bakingLang.tab.o bakingLang.o

#include	"bakingHeaders.h"
#include	"bakingLang.tab.h"

#undef		YY_INPUT
#define		YY_INPUT(buffer,result,maxSize)		\
		{ result = ourInput(buffer,maxSize); }

extern
int		ourInput(char* buffer, int maxSize);

%}

%%

" "|\t|\n|\r|","									{}//Ignore

(\-|\+)?[0-9]+|([0-9]*\.[0-9]+)						{ yylval.float_	= strtod(yytext,NULL);
													  return(NUMBER);}

"into"												{return (INTO);}
"toMake"											{return (TOMAKE);}
"for"												{return (FOR);}
"at"												{return (AT);}

"mix"|"Mix"											{yylval.verb_t_ = MIX_VERB ;
													return (VERB);}
"pour"|"Pour"										{yylval.verb_t_ = POUR_VERB;
													return (VERB);}
"flip"|"Flip"										{yylval.verb_t_ = FLIP_VERB;
													return (VERB);}
"remove"|"Remove"									{yylval.verb_t_ = REMOVE_VERB;
													return (VERB);}
("bake"|"Bake")|("cook"|"Cook")						{yylval.verb_t_ = BAKE_VERB;
													return (VERB);}
"add"|"Add"											{yylval.verb_t_ = ADD_VERB;
													return (VERB);}
"preheat"|"Preheat"									{yylval.verb_t_ = PREHEAT_VERB;
													return (VERB);}
("divide"|"Divide")|("separate"|"Separate")			{yylval.verb_t_ = DIVIDE_VERB;
													return (VERB);}

"tsp"|"teaspoon"|"teaspoons"						{yylval.measurement_t_ = TEASPOON_MEASURE;
													return (MEASUREMENT);}
"tbsp"|"tablespoon"|"tablespoons"					{yylval.measurement_t_ = TABLESPOON_MEASURE;
													return (MEASUREMENT);}
"cup"|"cups"										{yylval.measurement_t_ = CUP_MEASURE;
													return (MEASUREMENT);}
													
"second"|"seconds"									{yylval.timeMeasurement_t_ = SECOND_TIME_MEASURE;
													return (TIME);}
"minute"|"minutes"									{yylval.timeMeasurement_t_ = MINUTE_TIME_MEASURE;
													return (TIME);}
"hour"|"hours"										{yylval.timeMeasurement_t_ = HOUR_TIME_MEASURE;
													return (TIME);}

"Celsius"|"C"										{yylval.tempMeasurement_t_ = CELSIUS_TEMP_MEASURE;
													return (TEMP);}
"Fahrenheit"|"F"									{yylval.tempMeasurement_t_ = FAHRENHEIT_TEMP_MEASURE;
													return (TEMP);}

"unsalted"|"Unsalted"								{yylval.adj_t_ = UNSALTED_ADJ;
													return (ADJ);}
"powdered"|"Powdered"								{yylval.adj_t_ = POWDERED_ADJ;
													return (ADJ);}
"soft"|"Soft"										{yylval.adj_t_ = SOFT_ADJ;
													return (ADJ);}
"firm"|"Firm"										{yylval.adj_t_ = FIRM_ADJ;
													return (ADJ);}
"unrefined"|"Unrefined"								{yylval.adj_t_ = UNREFINED_ADJ;
													return (ADJ);}
"organic"|"Organic"									{yylval.adj_t_ = ORGANIC_ADJ;
													return (ADJ);}
"unsweetened"|"Unsweetened"							{yylval.adj_t_ = UNSWEETENED_ADJ;
													return (ADJ);}
"bittersweet"|"Bittersweet"							{yylval.adj_t_ = BITTERSWEET_ADJ;
													return (ADJ);}
"semisweet"|"Semisweet"								{yylval.adj_t_ = SEMISWEET_ADJ;
													return (ADJ);}

("portion"|"Portion")(("s")?)						{return (PORTION);}

[a-z]+[a-zA-Z]*[0-9]*								{
														const Ingredient* temp_lex = pantry.getIngredient(yytext);
														if(temp_lex != NULL)
														{
															yylval.ingredient_ = temp_lex;
															return(INGREDIENT);
														}
															yylval.char_ = strdup(yytext);
															return(ID);
													}
"."													{return(PERIOD);}

.													{printf( "Unrecognized character: %s\n", yytext );
													return(ERROR);}


%%

//  PURPOSE:  To hold the input file from which to read the program (if it is
//	not 'stdin').
FILE*		filePtr		= NULL;

//  PURPOSE:  To point to the beginning of the input yet to read (if being
//	typed from the command line).
char*		textPtr		= NULL;

//  PURPOSE:  To point to the end of all input (if being typed from the command
//	line).
char*		textEndPtr	= NULL;


//  PURPOSE:  To return 1 if the tokenizer should quit after EOF is reached.
//	Returns 0 otherwise.  No parameters.
int	yywrap	()
{
  return(1);
}


//  PURPOSE:  To get up to 'maxSize' more characters of input and put them
//	into 'buffer'.   Returns how many characters were obtained.
int		ourInput	(char*	     buffer,
				 int	     maxSize
				)
{
  unsigned int	n;

  if  (filePtr == NULL)
  {
    n	= MIN(maxSize,textEndPtr - textPtr);

    if  (n > 0)
    {
      memcpy(buffer,textPtr,n);
      textPtr	+= n;
    }
  }
  else
  {
    errno	= 0;

    while  ( (n = fread(buffer,1,maxSize,yyin)) == 0 && ferror(yyin))
    {
      if  (errno != EINTR)
      {
        fprintf(stderr,"Reading file failed: %s\n",strerror(errno));
	exit(EXIT_FAILURE);
      }

      errno	= 0;
      clearerr(yyin);
    }

  }

  return(n);
}
