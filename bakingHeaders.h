/*-------------------------------------------------------------------------*
 *---									---*
 *---		bakingHeaders.h						---*
 *---									---*
 *---	    This file includes types and headers common to the baking	---*
 *---	simulation program.						---*
 *---									---*
 *---	----	----	----	----	----	----	----	----	---*
 *---									---*
 *---	Version 1.0		2016 November 1		Joseph Phillips	---*
 *---									---*
 *-------------------------------------------------------------------------*/

using namespace std;

#include	<cstdlib>
#include	<cstdio>
#include	<cstring>
#include	<string>
#include	<iostream>
#include	<list>
#include	<map>


//  PURPOSE:  To define a macro that computes the minimum of 2 values using the
//	'<' operator.
#define		MIN(x,y)		(((x)<(y)) ? (x) : (y))


//  PURPOSE:  To distinguish among the verbs.
typedef		enum
		{
		  MIX_VERB,
		  POUR_VERB,
		  FLIP_VERB,
		  REMOVE_VERB,
		  BAKE_VERB,
		  ADD_VERB,
		  PREHEAT_VERB,
		  DIVIDE_VERB,
		  NUM_VERBS
		}
		verb_t;

//  PURPOSE:  To distinguish among the adjectives that can describe the
//	Ingredients.
typedef		enum
		{
		  UNSALTED_ADJ,
		  POWDERED_ADJ,
		  SOFT_ADJ,
		  FIRM_ADJ,
		  UNREFINED_ADJ,
		  ORGANIC_ADJ,
		  UNSWEETENED_ADJ,
		  BITTERSWEET_ADJ,
		  SEMISWEET_ADJ
		}
		adjective_t;


//  PURPOSE:  To distinguish among the individual steps.
typedef		enum
		{
	          MIX_STEP,
		  POUR_INTO_STEP,
		  BAKE_STEP,
		  SEPARATE_STEP
		}
		step_t;

//  PURPOSE:  To distinguish among the various components of Ingredient
//		instances.
typedef		enum
		{
		  SUGAR_COMPONENT,
		  STARCH_COMPONENT,
		  LIPID_COMPONENT,
		  PROTEIN_COMPONENT,

		  LIQUID_COMPONENT,
		  SODIUM_COMPONENT,
		  FLAVORING_COMPONENT,
		  LEAVENING_COMPONENT,

		  NUM_COMPONENTS
		}
		tasteComponent_t;


//  PURPOSE:  To distinguish among the various measurements
typedef		enum
		{
		  TEASPOON_MEASURE,
		  TABLESPOON_MEASURE,
		  CUP_MEASURE,
		  EGG_MEASURE
		}
		measurement_t;

//  PURPOSE:  To distinguish among the various time measurements.
typedef		enum
		{
		  SECOND_TIME_MEASURE,
		  MINUTE_TIME_MEASURE,
		  HOUR_TIME_MEASURE
		}
		timeMeasurement_t;

//  PURPOSE:  To distinguish among the various tempurature measurements.
typedef		enum
		{
		  CELSIUS_TEMP_MEASURE,
		  FAHRENHEIT_TEMP_MEASURE
		}
		tempMeasurement_t;


//  PURPOSE:  To tell the maximum length of a line.
const int	LINE_LEN	= 256;

//  PURPOSE:  To hold the input file from which to read the program (if it is
//	not 'stdin').
extern
FILE*		filePtr;

//  PURPOSE:  To point to the beginning of the input yet to read (if being
//	typed from the command line).
extern
char*		textPtr;

//  PURPOSE:  To point to the end of all input (if being typed from the command
//	line).
extern
char*		textEndPtr;

//  PURPOSE:  To hold the text form of the verb.
extern
const char*	verbText[NUM_VERBS];

//  PURPOSE:  To hold the names of the taste components.
extern
const char*	tasteName[NUM_COMPONENTS];

//  PURPOSE:  To return 'true' if the string pointed to by 'firstCPtr' should
//	be ordered before that pointed to by 'secondCPtr', or 'false' otherwise.
extern
bool		compareChapPtr	(const char*	firstCPtr,
				 const char*	secondCPtr
				);

//  PURPOSE:  To return the equivalent number of liters of 1.0 'measure'.
extern
float		toLiters	(measurement_t	measure
				);

//  PURPOSE:  To return the equivalent number of minutes of 1.0 'measure'.
extern
float		toMinutes	(timeMeasurement_t	measure
				);

//  PURPOSE:  To return the equivalent number of degrees Fahrenheit of
//	'degrees' of 'measure'.
extern
float		toFahrenheit	(tempMeasurement_t	measure,
				 float			degrees
				);

//  PURPOSE:  To read the next lexeme, update 'yylval' with its data, and return
//	its corresponding integer.
extern
int		yylex		();

//  PURPOSE:  To show the error message pointed to by 'cPtr'.  Returns '0'.
extern
int		yyerror		(const char *cPtr
				);

extern
FILE*		yyin;


//  PURPOSE:  To parse the input.
extern
int		yyparse		();

class		Recipe;

#include	"Ingredient.h"
#include	"Measure.h"
#include	"Pantry.h"
#include	"MeasuredIngredient.h"
#include	"Mixture.h"
#include	"Step.h"
#include	"Recipe.h"


//  PURPOSE:  To be the global object that tells what Ingredient instances are
//	available.
extern
Pantry		pantry;

//  PURPOSE:  To be the global pointer to the created Recipe instance.
extern
Recipe*		recipePtr;
