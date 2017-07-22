/*-------------------------------------------------------------------------*
 *---									---*
 *---		bakingMain.cpp						---*
 *---									---*
 *---	    This file defines high-level functions used by the baking	---*
 *---	simulator program.						---*
 *---									---*
 *---	----	----	----	----	----	----	----	----	---*
 *---									---*
 *---	Version 1.0		2016 November 1		Joseph Phillips	---*
 *---									---*
 *-------------------------------------------------------------------------*/

#include	"bakingHeaders.h"


//---				Global variables:			---//

float		flourArray[8]		= {.05,.90,.01,.12, .00,.01,.01,.00};
float		wholeWheatFlourArray[8]	= {.05,.90,.01,.12, .00,.01,.01,.00};
float		cinnamonArray[8]	= {.00,.00,.00,.00, .00,.00,.99,.00};
float		bakingSodaArray[8]	= {.00,.00,.00,.00, .00,.27,.00,.50};
float		bakingPowderArray[8]	= {.00,.00,.00,.00, .00,.09,.00,.25};
float		milkArray[8]		= {.05,.00,.05,.05, .98,.01,.01,.01};
float		soyMilkArray[8]		= {.05,.00,.05,.05, .98,.01,.01,.01};
float		peanutOilArray[8]	= {.00,.00,.99,.01, .80,.01,.05,.00};
float		butterArray[8]		= {.00,.00,.99,.01, .20,.01,.05,.00};
float		tofuArray[8]		= {.00,.00,.01,.50, .25,.01,.01,.00};
float		sugarArray[8]		= {.99,.00,.00,.00, .00,.00,.04,.00};
float		eggArray[8]		= {.00,.00,.20,.40, .60,.01,.01,.05};
float		chocChipArray[8]	= {.10,.00,.20,.05, .05,.01,.50,.00};
float		vanillaExtractArray[8]	= {.10,.00,.20,.05, .90,.01,.70,.00};

//  PURPOSE:  To hold the text form of the verb.
const char*	verbText[NUM_VERBS]	=
      		{
		  "mix",		// MIX_VERB
		  "pour",		// POUR_VERB
		  "flip",		// FLIP_VERB
		  "remove",		// REMOVE_VERB
		  "bake",		// BAKE_VERB
		  "add",		// ADD_VERB
		  "preheat",		// PREHEAT_VERB
		  "divide",		// DIVIDE_VERB
		}
;

//  PURPOSE:  To hold the names of the taste components.
const char*	tasteName[NUM_COMPONENTS]
					=
		{
		  "sugar",
		  "starch",
		  "lipid",
		  "protein",
		  "liquid",
		  "sodium",
		  "flavoring",
		  "leavening"
		};


//  PURPOSE:  To be the global object that tells what Ingredient instances are
//	available.
Pantry		pantry;


//  PURPOSE:  To be the global pointer to the created Recipe instance.
Recipe*		recipePtr	= NULL;

//---			Global support functions:			---//

//  PURPOSE:  To return 'true' if the string pointed to by 'firstCPtr' should
//	be ordered before that pointed to by 'secondCPtr', or 'false' otherwise.
bool		compareChapPtr	(const char*	firstCPtr,
				 const char*	secondCPtr
				)
{
  return( strcmp(firstCPtr,secondCPtr) < 0 );
}


//  PURPOSE:  To return the equivalent number of liters of 1.0 'measure'.
float		toLiters	(measurement_t	measure
				)
{
  float	toReturn;

  switch  (measure)
  {
  case TEASPOON_MEASURE :
    toReturn	= 0.00591939;
    break;

  case TABLESPOON_MEASURE :
    toReturn	= 0.0177582;
    break;

  case CUP_MEASURE :
    toReturn	= 0.236588;
    break;

  case EGG_MEASURE :
    toReturn	= 0.046;
    break;

  default :
    throw new std::string
		("Attempt to determine equivalent"
		 " liters of non-volume measure"
		);
  }

  return(toReturn);
}


//  PURPOSE:  To return the equivalent number of minutes of 1.0 'measure'.
float		toMinutes	(timeMeasurement_t	measure
				)
{
  switch  (measure)
  {
  case SECOND_TIME_MEASURE :
    return(1.0/60);

  case MINUTE_TIME_MEASURE :
    return(1.0);

  case HOUR_TIME_MEASURE :
    return(60.0);

  default :
    throw new std::string
		("Attempt to determine equivalent"
		 " degrees F of non-temp measure"
		);
  }
}


//  PURPOSE:  To return the equivalent number of degrees Fahrenheit of
//	'degrees' of 'measure'.
float		toFahrenheit	(tempMeasurement_t	measure,
				 float			degrees
				)
{
  switch  (measure)
  {
  case CELSIUS_TEMP_MEASURE :
    return(degrees * 1.8 + 32.0);

  case FAHRENHEIT_TEMP_MEASURE :
    return(degrees);

  default :
    throw new std::string
		("Attempt to determine equivalent"
		 " degrees F of non-temp measure"
		);
  }
}


//  PURPOSE: To initialize '*this' MixStep to mix the MeasuredIngredient
//	instances of 'listPtr' to make named mixture 'newMixtureNameCPtr'.
//	'verb' must be 'MIX_VERB'.  Becomes the owner of the heap-allocated
//	memory pointed to by 'newMixtureNameCPtr'.  No return value
MixStep::MixStep		(verb_t			verb,
				 std::list<MeasuredIngredient*>*
							listPtr,
				 char*			newMixtureNameCPtr
  				) :
				Step(),
				measuredIngredPtrListPtr_(listPtr),
				mixtureNameCPtr_(newMixtureNameCPtr),
				mixture_(),
				hasBeenUsedUp_(false)
{
  //  I.  Application validity check:
  if  ( (verb != MIX_VERB)  &&  (verb != ADD_VERB) )
    throw new std::string(std::string("To ")	+
			 verbText[verb] 	+
			 std::string(" to mix ingredients makes no sense")
			);

  if  (recipePtr != NULL)
  {
    std::list<Step*>::iterator	iter	= recipePtr->getStepAddrListBegin();
    std::list<Step*>::iterator	end	= recipePtr->getStepAddrListEnd();

    for  ( ;  iter != end;  iter++)
      if  ( (*iter)->doesCreateNamedMixture(getMixtureNameCPtr()) )
        throw new std::string
      	    	(std::string("Attempt to create a mixture named ")	+
		 getMixtureNameCPtr()					+
		 std::string(" twice")
		);

  }

  //  II.  Initialize member vars:
  //  II.A.  Initialize 'mixture_':
  MeasuredIngredPtrList::iterator iter;

  for (iter  = measuredIngredPtrListPtr_->begin();
       iter != measuredIngredPtrListPtr_->end();
       iter++
      )
    for  (int i = 0;  i < NUM_COMPONENTS;  i++)
      mixture_.addVolume(i,(*iter)->getTasteComponent((tasteComponent_t)i));

  //  III.  Finished:
}


//  PURPOSE:  To initialize '*this' to note that the mixture with name
//	'newAddedToCPtr' is being increase by the pouring of (and thus
//	 destruction of) the mixture with name 'newUsedUpCPtr'.  Becomes the
//	owner of both pieces of heap-allocated memory.
CombineStep::CombineStep	(verb_t		verb,
				 char*		newAddedToCPtr,
				 char*		newUsedUpCPtr
				) :
				Step(),
				addedToCPtr_(newAddedToCPtr),
				usedUpCPtr_(newUsedUpCPtr),
				mixture_(),
				hasBeenUsedUp_(false)
{
  //  I.  Application validity check:
  if  ( (verb != MIX_VERB)  &&  (verb != POUR_VERB) )
    throw new std::string(std::string("To ")	+
			  verbText[verb]	+
			  std::string(" to combine two mixtures makes no sense")
			 );

  if  ( strcmp(getAddToCPtr(),getUsedUpCPtr()) == 0 )
    throw new std::string(std::string("Combining ")			+
			  getAddToCPtr()				+
			  std::string(" with itself?  Most peculiar!")
			 );

  if  (recipePtr == NULL)
    throw new std::string("You cannot combine, there is nothing to combine!");

  std::list<Step*>::iterator	iter	= recipePtr->getStepAddrListBegin();
  std::list<Step*>::iterator	end	= recipePtr->getStepAddrListEnd();
  Step* 			foundAddedToPtr	= NULL;
  Step* 			foundUsedUpPtr	= NULL;

  for  ( ;  iter != end;  iter++)
  {
    if  ( (*iter)->doesCreateNamedMixture(getAddToCPtr()) )
      foundAddedToPtr	= *iter;

    if  ( (*iter)->doesCreateNamedMixture(getUsedUpCPtr()) )
      foundUsedUpPtr	= *iter;
  }

  if  (foundAddedToPtr == NULL)
    throw new std::string(getAddToCPtr() + std::string(" was never created"));

  if  (foundAddedToPtr->getHasBeenUsedUp())
    throw new std::string(getAddToCPtr() + std::string(" has been used up"));

  if  (foundUsedUpPtr == NULL)
    throw new std::string(getUsedUpCPtr() + std::string(" was never created"));

  if  (foundUsedUpPtr->getHasBeenUsedUp())
    throw new std::string(getUsedUpCPtr() + std::string(" has been used up"));

  foundUsedUpPtr->setHasBeenUsedUp();

  //  II.  Initialize member vars:
  //  II.A.  Initialize 'mixture_':
  mixture_  = foundAddedToPtr->getMixture();
  mixture_ += foundUsedUpPtr->getMixture();

  //  III.  Finished:
}


//  PURPOSE:  To make '*this' a Step representing the 'verb'-ing of
//	the mixture with name pointed to by 'newMixtureNameCPtr' at 'tempNum'
//	degrees on the 'tempMeasure' scale, for 'timeNum' of 'timeMeasure' time
//	units.
BakeStep::BakeStep		(verb_t			verb,
				 char*			newMixtureNameCPtr,
				 tempMeasurement_t	tempMeasure,
				 float			tempNum,
				 timeMeasurement_t	timeMeasure,
				 float			timeNum
  				) :
				Step(),
				mixtureNameCPtr_(newMixtureNameCPtr),
				cookTempInF_
					(toFahrenheit(tempMeasure,tempNum)),
				cookTimeInMins_
					(timeNum * toMinutes(timeMeasure))
{
  //  I.  Application validity check:
  if (verb != BAKE_VERB)
    throw new std::string(std::string("To ")	+
			  verbText[verb]	+
			  std::string(" to bake a mixture makes no sense")
			 );

  if  (recipePtr == NULL)
    throw new std::string("You cannot bake, there is nothing to bake!");

  std::list<Step*>::iterator iter	= recipePtr->getStepAddrListBegin();
  std::list<Step*>::iterator end	= recipePtr->getStepAddrListEnd();
  Step*			     lastCreationStepPtr= NULL;

  if  (cookTempInF_ < 250)
    throw new std::string("That temperature won't even sterilize!");

  if  (cookTempInF_ >= 2500)
    throw new std::string("You're gonna melt the oven!");
    
  if  (cookTempInF_ >= 451)
    throw new std::string("What are you trying to do?  Burn the house down?");

  if  (cookTimeInMins_ < 5)
    throw new std::string("Not cooked long enough!  You just warm batter!");

  if  (cookTimeInMins_ > 45)
    throw new std::string("Cooked too long!  You have baked-on charcoal!");

  for  ( ;  iter != end;  iter++)
    if  ( (*iter)->doesCreateNamedMixture(getMixtureNameCPtr()) )
      lastCreationStepPtr	= *iter;

  if  (lastCreationStepPtr == NULL)
    throw new std::string
	      (std::string("You cannot bake with ")	+
	       getMixtureNameCPtr()			+
	       std::string(", it has not been made")
	      );

  if  ( lastCreationStepPtr->getHasBeenUsedUp() )
    throw new std::string
		(std::string("You cannot bake with ")	+
		 getMixtureNameCPtr()    		+
		 std::string(", it has already been used up")
		);

  //  II.  Initialize member vars:
  //  II.A.  Initialize 'mixture_':
  mixture_	= lastCreationStepPtr->getMixture();

  //  III.  Finished:
}


//  PURPOSE:  To make '*this' a Step representing the 'verb'-ing of
//	the mixture with name pointed to by 'newMixtureNameCPtr' into
//	'numPortions' portions.
SeparateStep::SeparateStep	(verb_t			verb,
				 char*			newMixtureNameCPtr,
				 float			numPortions
  				) :
				Step(),
				mixtureNameCPtr_(newMixtureNameCPtr),
				numPortions_(numPortions),
				mixture_()
{
  //  I.  Application validity check:
  if (verb != DIVIDE_VERB)
    throw new std::string(std::string("To ")	+
			  verbText[verb]	+
			  std::string(" to divide a mixture makes no sense")
			 );

  if  (recipePtr == NULL)
    throw new std::string("You cannot divide, there is nothing to divide!");

  if  ( (numPortions <= 0)  ||  ((float)((int)numPortions) != numPortions) )
    throw new std::string("Dividing into that number of portions is weird");

  std::list<Step*>::iterator iter	= recipePtr->getStepAddrListBegin();
  std::list<Step*>::iterator end	= recipePtr->getStepAddrListEnd();
  Step*			     lastCreationStepPtr= NULL;

  for  ( ;  iter != end;  iter++)
    if  ( (*iter)->doesCreateNamedMixture(getMixtureNameCPtr()) )
      lastCreationStepPtr	= *iter;

  if  (lastCreationStepPtr == NULL)
    throw new std::string
	      (std::string("You cannot divide ")	+
	       getMixtureNameCPtr()			+
	       std::string(", it has not been made")
	      );

  if  ( lastCreationStepPtr->getHasBeenUsedUp() )
    throw new std::string
		(std::string("You cannot divide ")	+
		 getMixtureNameCPtr()    		+
		 std::string(", it has already been")
		);

  //  II.  Initialize member vars:
  //  II.A.  Initialize 'mixture_':
  mixture_	= lastCreationStepPtr->getMixture();

  //  III.  Finished:
}


//  PURPOSE:  To simulate cooking and tasting '*this' Recipe.  No parameters.
//	No return value.
void		Recipe::cookAndTaste
				()
{
  if  (getWasParseTimeProblemFound())
    return;

  std::list<Step*>::iterator	iter;
  std::list<Step*>::iterator	bakeStepIter;
  std::list<Step*>::iterator	end	= stepAddrList_.end();
  bool				didBake	= false;

  for  (iter  = stepAddrList_.begin();  iter != end;  iter++)
  {
    (*iter)->checkLegitimacy(*this);

    if  ((*iter)->getStepType() == BAKE_STEP)
    {
      bakeStepIter	= iter;
      didBake		= true;
    }
  }

  if  (!didBake)
    throw new std::string("Yuck!  This isn't cooked!\n");

  Mixture bakedGood	= (*bakeStepIter)->getMixture();
  Mixture bakedGoodTest	= bakedGood;

  bakedGoodTest.normalize();
  bakedGoodTest.print();

  std::string	foodName	= "What is this?";
  std::string	description("");

  if  (bakedGoodTest.getVolume(LIQUID_COMPONENT) < 0.02)
  {
    description	= "Too dry!  ";
  }
  else
  if  ( bakedGoodTest.getVolume(LIQUID_COMPONENT) < 0.15)
  {
    //  Assume Cake or cookie:
    foodName	= "cake or cookie";

    if  (bakedGoodTest.getVolume(SUGAR_COMPONENT) < 0.15)
      description	+= "rather bland ";
    else
    if  (bakedGoodTest.getVolume(SUGAR_COMPONENT) > 0.40)
      description	+= "caramelized ";

    if  (bakedGoodTest.getVolume(LIPID_COMPONENT) < 0.1)
      description	+= "falling-apart ";
    else
    if  (bakedGoodTest.getVolume(LIPID_COMPONENT) > 0.25)
      description	+= "too greasy ";

    if  (bakedGoodTest.getVolume(SODIUM_COMPONENT) > 0.02)
      description	+= "too salty ";

    if (bakedGoodTest.getVolume(FLAVORING_COMPONENT) > 0.06)
      description	+= "overly flavored ";

    if (bakedGoodTest.getVolume(LEAVENING_COMPONENT) < 0.003)
      description	+= "too flat ";
    else
    if (bakedGoodTest.getVolume(LEAVENING_COMPONENT) > 0.02)
      description	+= "too puffy ";

    if  (description.empty())
      description	= "Yummy ";

  }
  else
  if   (bakedGoodTest.getVolume(LIQUID_COMPONENT) < 0.3)
  {
    //  Assume Cake or cookie:
    foodName	= "Weird-ass food between a cake and a pancake";
  }
  else
  if  (bakedGoodTest.getVolume(LIQUID_COMPONENT) < 0.5)
  {
    //  Assume pancakes:
    foodName	= "pancakes";

    if  (bakedGoodTest.getVolume(SUGAR_COMPONENT) < 0.05)
      description	+= "rather bland ";
    else
    if  (bakedGoodTest.getVolume(SUGAR_COMPONENT) > 0.15)
      description	+= "caramelized ";

    if  (bakedGoodTest.getVolume(LIPID_COMPONENT) < 0.04)
      description	+= "falling-apart ";
    else
    if  (bakedGoodTest.getVolume(LIPID_COMPONENT) > 0.15)
      description	+= "too greasy ";

    if  (bakedGoodTest.getVolume(SODIUM_COMPONENT) > 0.01)
      description	+= "too salty ";

    if (bakedGoodTest.getVolume(FLAVORING_COMPONENT) > 0.05)
      description	+= "overly flavored ";

    if (bakedGoodTest.getVolume(LEAVENING_COMPONENT) < 0.003)
      description	+= "too flat ";
    else
    if (bakedGoodTest.getVolume(LEAVENING_COMPONENT) > 0.02)
      description	+= "too puffy ";

    if  (description.empty())
      description	= "Yummy ";

  }
  else
  {
    foodName	= "Wet slop!";
  }

  printf("%s%s\n",description.c_str(),foodName.c_str());
}


//  PURPOSE:  To parse and execute the program whose filename is given on the
//	command line at 'argv[1]' (if 'argc' >= 1), or that the user types in.
//	Returns 'EXIT_SUCCESS' on success or 'EXIT_FAILURE' otherwise.
int		main		(int	argc,
				 char*	argv[]
				)
{
  //  I.  Application validity check:

  //  II.  Parse and execute program:
  //  II.A.  Get program source:
  char	line[LINE_LEN];

  if  ( (argc >= 2)  &&  ( (filePtr = fopen(argv[1],"r")) != NULL ) )
  {
    yyin	= filePtr;
   }
  else
  {
    printf("Please enter an expression: ");
    textPtr	= fgets(line,LINE_LEN,stdin);
    textEndPtr	= textPtr + strlen(textPtr);
   }

  //  II.B.  Attempt to parse and execute recipe:
  try
  {
    yyparse();

    if  (recipePtr != NULL)
    {
      recipePtr->cookAndTaste();
      delete(recipePtr);
    }

  }
  catch  (std::string*	errStrPtr)
  {
    fprintf(stderr,"Error: %s.\n",errStrPtr->c_str());
    delete(errStrPtr);
  }
  catch  (const char*	cPtr)
  {
    fprintf(stderr,"Error: %s.\n",cPtr);
  }

  //  II.D. Clean up:
  //  II.D.1.  Close file (if open):
  if  (filePtr != NULL)
    fclose(filePtr);

  fflush(stdout);

  //  III.  Finished:
  return(EXIT_SUCCESS);
}
