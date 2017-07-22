/*-------------------------------------------------------------------------*
 *---									---*
 *---		Step.h							---*
 *---									---*
 *---	    This file declares a class that represents a step in a	---*
 *---	Recipe instance.						---*
 *---									---*
 *---	----	----	----	----	----	----	----	----	---*
 *---									---*
 *---	Version 1.0		2016 November 2		Joseph Phillips	---*
 *---									---*
 *-------------------------------------------------------------------------*/

typedef	std::list<MeasuredIngredient*>
				MeasuredIngredPtrList;

class	Step
{
  //  I.  Member vars:

  //  II.  Disallowed auto-generated methods:

protected :
  //  III.  Protected methods:

public :
  //  IV.  Constructor(s), assignment op(s), factory(s) and destructor:
  //  PURPOSE:  To initialize '*this' Step.  No parameters.  No return value.
  Step				()
				{ }

  //  PURPOSE:  To make '*this' Step a copy of 'source'.  No return value.
  Step				(const Step&	source
				)
				{ }

  //  PURPOSE:  To release the resouces of '*this'.  No parameters.  No return
  //	value.
  virtual
  ~Step				()
				{ }

  //  V.  Accessors:
  //  PURPOSE:  To tell what type of Step '*this' is.  No parameters.
  virtual
  step_t	getStepType	()
				const
				= 0;

  //  PURPOSE:  To return the Mixture that results from '*this' Step.  No
  //	parameters.
  virtual
  Mixture	getMixture	()
  				= 0;

  //  PURPOSE:  To return 'true' after the Mixture manipulated by '*this' Step
  //	has been used up, or 'false' beforehand.
  virtual
  bool	    	getHasBeenUsedUp()
				const
				{ return(true); }

  //  VI.  Mutators:
  //  PURPOSE:  To note that the Mixture used by '*this' has been used up.
  virtual
  void		setHasBeenUsedUp()
				{ }

  //  VII.  Methods that do main and misc work of class:
  //  PURPOSE:  To return 'true' if '*this' Step creates a mixture named
  //	'cPtr', or 'false' otherwise.
  virtual
  bool		doesCreateNamedMixture
				(const char*	nameCPtr
				)
				= 0;

  //  PURPOSE:  To return 'true' if '*this' Step destroys a mixture named
  //	'cPtr', or 'false' otherwise.
  virtual
  bool		doesDestroyNamedMixture
				(const char*	nameCPtr
				)
				= 0;

  //  PURPOSE:  To check the legitimacy of '*this' Step in Recipe 'Recipe'.
  //	Throws string telling problem on error.  No return value.
  virtual
  void		checkLegitimacy	(Recipe&	Recipe
				)
				= 0;

};



class	MixStep : public Step
{
  //  I.  Member vars:
  //  PURPOSE:  To hold the address of the list of measured ingredients.
  MeasuredIngredPtrList*	measuredIngredPtrListPtr_;

  //  PURPOSE:  To tell the name of the named mixture.
  char*				mixtureNameCPtr_;

  //  PURPOSE:  To hold the created mixture.
  Mixture			mixture_;

  //  PURPOSE:  To hold 'true' after the Mixture made by '*this' Step has been
  //	used up, and 'false' before then.
  bool				hasBeenUsedUp_;

  //  II.  Disallowed auto-generated methods:
  //  No default constructor:
  MixStep			();

  //  No assignment operator:
  MixStep&	operator=	(const MixStep&
				);

protected :
  //  III.  Protected methods:

public :
  //  IV.  Constructor(s), assignment op(s), factory(s) and destructor:
  //  PURPOSE: To initialize '*this' MixStep to mix the MeasuredIngredient
  //	instances of 'listPtr' to make named mixture 'newMixtureNameCPtr'.
  //	'verb' must be 'MIX_VERB'.  Becomes the owner of the heap-allocated
  //	memory pointed to by 'newMixtureNameCPtr'.  No return value
  MixStep			(verb_t			verb,
				 std::list<MeasuredIngredient*>*
							listPtr,
				 char*			newMixtureNameCPtr
  				);

  //  PURPOSE:  To release the resources of '*this'.  No parameters.  No return
  //	value.
  ~MixStep			()
				{
				  MeasuredIngredPtrList::iterator	iter;

				  for  (iter  = measuredIngredPtrListPtr_->
								begin();
					iter != measuredIngredPtrListPtr_->
								end();
					iter++
				       )
				    delete(*iter);

				  free(mixtureNameCPtr_);
				}

  //  V.  Accessors:
  //  PURPOSE:  To tell what type of Step '*this' is.  No parameters.
  step_t	getStepType	()
				const
				{ return(MIX_STEP); }

  //  PURPOSE:  To hold the address of the list of measured ingredients.
  MeasuredIngredPtrList::const_iterator
		getMeasuredIngredPtrListBegin
				()
				const
				{ return(measuredIngredPtrListPtr_->begin()); }

  //  PURPOSE:  To hold the address of the list of measured ingredients.
  MeasuredIngredPtrList::const_iterator
		getMeasuredIngredPtrListEnd
				()
				const
				{ return(measuredIngredPtrListPtr_->end()); }

  //  PURPOSE:  To return the name of the named mixture.  No parameters.
  const char*	getMixtureNameCPtr
				()
				const
				{ return(mixtureNameCPtr_); }

  //  PURPOSE:  To return the Mixture that results from '*this' Step.  No
  //	parameters.
  Mixture	getMixture	()
  				{ return(mixture_); }

  //  PURPOSE:  To return 'true' after the Mixture manipulated by '*this' Step
  //	has been used up, or 'false' beforehand.
  bool	    	getHasBeenUsedUp()
				const
				{ return(hasBeenUsedUp_); }

  //  VI.  Mutators:
  //  PURPOSE:  To note that the Mixture used by '*this' has been used up.
  void		setHasBeenUsedUp()
				{ hasBeenUsedUp_ = true; }

  //  VII.  Methods that do main and misc work of class:
  //  PURPOSE:  To return 'true' if '*this' Step creates a mixture named
  //	'cPtr', or 'false' otherwise.
  bool		doesCreateNamedMixture
				(const char*	nameCPtr
				)
				{ return(strcmp(getMixtureNameCPtr(),nameCPtr)
					 == 0
					);
				}

  //  PURPOSE:  To return 'true' if '*this' Step destroys a mixture named
  //	'cPtr', or 'false' otherwise.
  bool		doesDestroyNamedMixture
				(const char*	nameCPtr
				)
				{ return(false); }

  //  PURPOSE:  To check the legitimacy of '*this' Step in Recipe 'Recipe'.
  //	Throws string telling problem on error.  No return value.
  void		checkLegitimacy	(Recipe&	Recipe
  				)
				{ }

};



class	CombineStep : public Step
{
  //  I.  Member vars:
  //  PURPOSE:  To tell the name of the mixture to which something is added.
  char*				addedToCPtr_;

  //  PURPOSE:  To tell the name of the mixture being combined into that of
  //	'addedToCPtr_', and thus being used up.
  char*				usedUpCPtr_;

  //  PURPOSE:  To hold the created mixture.
  Mixture			mixture_;

  //  PURPOSE:  To hold 'true' after the Mixture made by '*this' Step has been
  //	used up, and 'false' before then.
  bool				hasBeenUsedUp_;

  //  II.  Disallowed auto-generated methods:
  //  No default constructor:
  CombineStep			();

  //  No copy constructor:
  CombineStep			(const CombineStep&
				);

  //  No copy assignment op:
  const CombineStep&
		operator=	(const CombineStep&
				);

protected :
  //  III.  Protected methods:

public :
  //  IV.  Constructor(s), assignment op(s), factory(s) and destructor:
  //  PURPOSE:  To initialize '*this' to note that the mixture with name
  //	'newAddedToCPtr' is being increase by the pouring of (and thus
  //	 destruction of) the mixture with name 'newUsedUpCPtr'.  Becomes the
  //	owner of both pieces of heap-allocated memory.
  CombineStep			(verb_t		verb,
				 char*		newAddedToCPtr,
				 char*		newUsedUpCPtr
				);

  //  PURPOSE:  To release the resources of '*this'.  No parameters.  No return
  //	value.
  ~CombineStep			()
				{
				  free(usedUpCPtr_);
				  free(addedToCPtr_);
				}

  //  V.  Accessors:
  //  PURPOSE:  To tell what type of Step '*this' is.  No parameters.
  step_t	getStepType	()
				const
				{ return(POUR_INTO_STEP); }

  //  PURPOSE:  To return the name of the mixture to which something is added.
  //	No parameters.
  const char*	getAddToCPtr	()
				const
				{ return(addedToCPtr_); }

  //  PURPOSE:  To return the name of the mixture being combined into that of
  //	'addedToCPtr_', and thus being used up.  No parameters.
  const char*	getUsedUpCPtr	()
				const
				{ return(usedUpCPtr_); }

  //  PURPOSE:  To return 'true' after the Mixture manipulated by '*this' Step
  //	has been used up, or 'false' beforehand.
  bool	    	getHasBeenUsedUp()
				const
				{ return(hasBeenUsedUp_); }

  //  PURPOSE:  To return the Mixture that results from '*this' Step.  No
  //	parameters.
  Mixture	getMixture	()
  				{ return(mixture_); }

  //  VI.  Mutators:
  //  PURPOSE:  To note that the Mixture used by '*this' has been used up.
  void		setHasBeenUsedUp()
				{ hasBeenUsedUp_ = true; }

  //  VII.  Methods that do main and misc work of class:
  //  PURPOSE:  To return 'true' if '*this' Step creates a mixture named
  //	'cPtr', or 'false' otherwise.
  bool		doesCreateNamedMixture
				(const char*	nameCPtr
				)
				{ return(strcmp(getAddToCPtr(),nameCPtr)
					 == 0
					);
				}

  //  PURPOSE:  To return 'true' if '*this' Step destroys a mixture named
  //	'cPtr', or 'false' otherwise.
  bool		doesDestroyNamedMixture
				(const char*	nameCPtr
				)
				{ return(strcmp(getUsedUpCPtr(),nameCPtr)
					 == 0
					);
				}

  //  PURPOSE:  To check the legitimacy of '*this' Step in Recipe 'Recipe'.
  //	Throws string telling problem on error.  No return value.
  void		checkLegitimacy	(Recipe&	Recipe
  				)
				{ }

};


class	BakeStep : public Step
{
  //  I.  Member vars:
  //  PURPOSE:  To hold the name of what was baked.
  char*				mixtureNameCPtr_;

  //  PURPOSE:  To tell the temperature at which to cook in degrees Fahrenheit.
  float				cookTempInF_;
	
  //  PURPOSE:  To tell the length of time to cook in minutes.
  float				cookTimeInMins_;

  //  PURPOSE:  To hold the created mixture.
  Mixture			mixture_;

  //  II.  Disallowed auto-generated methods:

protected :
  //  III.  Protected methods:

public :
  //  IV.  Constructor(s), assignment op(s), factory(s) and destructor:
  //  PURPOSE:  To make '*this' a Step representing the 'verb'-ing of
  //	the mixture with name pointed to by 'newMixtureNameCPtr' at 'tempNum'
  //	degrees on the 'tempMeasure' scale, for 'timeNum' of 'timeMeasure' time
  //	units.
  BakeStep			(verb_t			verb,
				 char*			newMixtureNameCPtr,
				 tempMeasurement_t	tempMeasure,
				 float			tempNum,
				 timeMeasurement_t	timeMeasure,
				 float			timeNum
  				);

  //  PURPOSE:  To release the resources of '*this'.  No parameters.  No return
  //	value.
  ~BakeStep			()
  				{
				  free(mixtureNameCPtr_);
				}

  //  V.  Accessors:
  //  PURPOSE:  To tell what type of Step '*this' is.  No parameters.
  step_t	getStepType	()
				const
				{ return(BAKE_STEP); }

  //  PURPOSE:  To return the name of what was baked.
  const char*	getMixtureNameCPtr
				()
				const
				{ return(mixtureNameCPtr_); }

  //  PURPOSE:  To return the temperature at which to cook in degrees
  //	Fahrenheit.
  float		getCookTempInF	()
				const
				{ return(cookTempInF_); }
	
  //  PURPOSE:  To return the length of time to cook in minutes.
  float		getCookTimeInMins
				()
				const
				{ return(cookTimeInMins_); }

  //  VI.  Mutators:

  //  VII.  Methods that do main and misc work of class:
  //  PURPOSE:  To return 'true' if '*this' Step creates a mixture named
  //	'cPtr', or 'false' otherwise.
  bool		doesCreateNamedMixture
				(const char*	nameCPtr
				)
				{ return(false); }

  //  PURPOSE:  To return 'true' if '*this' Step destroys a mixture named
  //	'cPtr', or 'false' otherwise.
  bool		doesDestroyNamedMixture
				(const char*	nameCPtr
				)
				{ return(strcmp(getMixtureNameCPtr(),nameCPtr)
					 == 0
					);
				}

  //  PURPOSE:  To check the legitimacy of '*this' Step in Recipe 'Recipe'.
  //	Throws string telling problem on error.  No return value.
  void		checkLegitimacy	(Recipe&	Recipe
  				)
				{ }

  //  PURPOSE:  To return the Mixture that results from '*this' Step.  No
  //	parameters.
  Mixture	getMixture	()
				{ return(mixture_); }

};


class		SeparateStep : public Step
{
  //  I.  Member vars:
  //  PURPOSE:  To hold the name of what was baked.
  char*				mixtureNameCPtr_;

  //  PURPOSE:  To tell the number of portions to divide the mixture into.
  float				numPortions_;

  //  PURPOSE:  To hold the created mixture.
  Mixture			mixture_;

  //  II.  Disallowed auto-generated methods:

protected :
  //  III.  Protected methods:

public :
  //  IV.  Constructor(s), assignment op(s), factory(s) and destructor:
  //  PURPOSE:  To make '*this' a Step representing the 'verb'-ing of
  //	the mixture with name pointed to by 'newMixtureNameCPtr' at 'tempNum'
  //	degrees on the 'tempMeasure' scale, for 'timeNum' of 'timeMeasure' time
  //	units.
  SeparateStep			(verb_t			verb,
				 char*			newMixtureNameCPtr,
				 float			numPortions
  				);

  //  PURPOSE:  To release the resources of '*this'.  No parameters.  No return
  //	value.
  ~SeparateStep			()
  				{
				  free(mixtureNameCPtr_);
				}

  //  V.  Accessors:
  //  PURPOSE:  To tell what type of Step '*this' is.  No parameters.
  step_t	getStepType	()
				const
				{ return(SEPARATE_STEP); }

  //  PURPOSE:  To return the name of what was baked.
  const char*	getMixtureNameCPtr
				()
				const
				{ return(mixtureNameCPtr_); }

  //  PURPOSE:  To return the temperature at which to cook in degrees
  //	Fahrenheit.
  float		getNumPortions	()
				const
				{ return(numPortions_); }
	
  //  VI.  Mutators:

  //  VII.  Methods that do main and misc work of class:
  //  PURPOSE:  To return 'true' if '*this' Step creates a mixture named
  //	'cPtr', or 'false' otherwise.
  bool		doesCreateNamedMixture
				(const char*	nameCPtr
				)
				{ return(false); }

  //  PURPOSE:  To return 'true' if '*this' Step destroys a mixture named
  //	'cPtr', or 'false' otherwise.
  bool		doesDestroyNamedMixture
				(const char*	nameCPtr
				)
				{ return(strcmp(getMixtureNameCPtr(),nameCPtr)
					 == 0
					);
				}

  //  PURPOSE:  To check the legitimacy of '*this' Step in Recipe 'Recipe'.
  //	Throws string telling problem on error.  No return value.
  void		checkLegitimacy	(Recipe&	Recipe
  				)
				{ }

  //  PURPOSE:  To return the Mixture that results from '*this' Step.  No
  //	parameters.
  Mixture	getMixture	()
				{ return(mixture_); }

};
