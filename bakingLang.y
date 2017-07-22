%{

/*-------------------------------------------------------------------------*
 *---									---*
 *---		bakingLang.y						---*
 *---									---*
 *---	    This file defines a grammar for the baking language.	---*
 *---									---*
 *---	----	----	----	----	----	----	----	----	---*
 *---									---*
 *---	Version 1.0		2016 November 21		Aditya Dantuluri	---*
 *---									---*
 *-------------------------------------------------------------------------*/

//  Compile with
//  $ bison --verbose -d --debug bakingLang.y
//  $ gcc bakingLang.tab.c -c
#include  "bakingHeaders.h"

%}

%union
{
	Recipe*								recipe_;
	Step*								step_;
	std::list<MeasuredIngredient*>*		list_;
	MeasuredIngredient*					mIngredient_;
	const Ingredient*					ingredient_;
	char*								char_;
	measurement_t						measurement_t_;
	timeMeasurement_t					timeMeasurement_t_;
	tempMeasurement_t					tempMeasurement_t_;
	float								float_;
	verb_t								verb_t_;
	adjective_t							adj_t_;
	std::list<adjective_t>*					adjList_;
}

%start							recipe
%token							PERIOD INTO TOMAKE FOR AT PORTION
%token	<ingredient_>			INGREDIENT
%token	<char_>					ID
%token	<measurement_t_>		MEASUREMENT
%token	<timeMeasurement_t_>	TIME
%token	<tempMeasurement_t_>	TEMP
%token	<float_>				NUMBER
%token	<verb_t_>				VERB
%token	<adj_t_>				ADJ
%type	<mIngredient_>			subStep
%type	<list_>					list
%type	<step_>					step
%type	<recipe_>				recipe
%type	<adjList_>				adjList
%nonassoc						ERROR

%%

recipe	: recipe step
		{
			$1->addStep($2);
			$$ = $1;
		}
		|	
		{
	    // lambda production
	    $$ = recipePtr = new Recipe;
		};
step	: VERB ID INTO ID PERIOD
		{
			$$ = new CombineStep($1,$4,$2);
		}
		| VERB list TOMAKE ID PERIOD
		{
			$$ = new MixStep($1, $2, $4);
		}
		| VERB ID AT NUMBER TEMP FOR NUMBER TIME PERIOD
		{
			$$ = new BakeStep($1, $2, $5, $4, $8, $7);
		}
		| VERB ID FOR NUMBER TIME AT NUMBER TEMP PERIOD
		{
			$$ = new BakeStep($1, $2, $8, $7, $5, $4);
		}
		| VERB ID INTO NUMBER PORTION PERIOD 
		{
			$$ = new SeparateStep($1, $2, $4);
		}
		;
list	: list subStep
		{
			$1->push_back($2);
			$$ = $1;
		}
		|
		{
			$$ = new std::list<MeasuredIngredient*>;
		};
subStep	: NUMBER MEASUREMENT adjList INGREDIENT
		{
			$$ = new MeasuredIngredient($4, $1, $2);
		}
		| NUMBER adjList INGREDIENT
		{
			$$ = new MeasuredIngredient($3, $1, EGG_MEASURE);
		};
adjList : adjList ADJ
		{
			$1->push_back($2);
			$$ = $1;
		}
		|
		{
			$$ = new std::list<adjective_t>;
		}


%%


//  PURPOSE:  To show the error message pointed to by 'cPtr'.  Returns '0'.
int	yyerror	(const char *cPtr)
{
  printf("%s, sorry!\n",cPtr);

  if  (recipePtr != NULL)
    recipePtr->setWasParseTimeProblemFound();

  return(0);
}
