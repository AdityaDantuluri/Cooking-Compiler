/*-------------------------------------------------------------------------*
 *---									---*
 *---		MeasuredIngredient.h					---*
 *---									---*
 *---	    This file declares a class that represents a certain	---*
 *---	quantity of an Ingredient instance.				---*
 *---									---*
 *---	----	----	----	----	----	----	----	----	---*
 *---									---*
 *---	Version 1.0		2016 November 1		Joseph Phillips	---*
 *---									---*
 *-------------------------------------------------------------------------*/

class	MeasuredIngredient
{
  //  I.  Member vars:
  //  PURPOSE:  To tell the Ingredient to include.
  const Ingredient*	    	ingredientPtr_;

  //  PURPOSE:  To tell the quantity in liters of the Ingredient
  //	'*ingredientPtr'.
  float				numLiters_;

  //  II.  Disallowed auto-generated methods:
  //  No default constructor:
  MeasuredIngredient		();

protected :
  //  III.  Protected methods:

public :
  //  IV.  Constructor(s), assignment op(s), factory(s) and destructor:
  //  PURPOSE:  To note the quantity 'volume' of 'measure' of
  //	'*newIngredientPtr'.
  MeasuredIngredient		 (const Ingredient*	newIngredientPtr,
  				  float			volume,
				  measurement_t		measure
  				 ) :
				 ingredientPtr_(newIngredientPtr),
				 numLiters_(volume * toLiters(measure))
				 { }

  //  PURPOSE:  To make '*this' a copy of 'source'.  No return value.
  MeasuredIngredient		(const MeasuredIngredient&    source
				) :
				ingredientPtr_(source.getIngredientPtr()),
				numLiters_(source.getNumLiters())
				{ }

  //  PURPOSE:  To release the resources of '*this' and make '*this' a copy of
  //	'source'.  Returns reference to '*this'.
  const MeasuredIngredient&
		operator=	(const MeasuredIngredient&    source
				)
				{
				  //  I.  Application validity check:
				  if  (this == &source)
				    return(*this);

				  //  II.  Release resources:
				  //  Do _not_ delete() ingredientPtr_

				  //  III.  Copy 'source':
				  ingredientPtr_  = source.getIngredientPtr();
				  numLiters_	  = source.getNumLiters();

				  //  IV.  Finished:
				  return(*this);
				}

  //  PURPOSE:  To release the resources of '*this'.  No parameters.  No return
  //	value.
  ~MeasuredIngredient		()
				{
				  //  Do _not_ delete() ingredientPtr_
				}

  //  V.  Accessors:
  //  PURPOSE:  To return the address of the Ingredient to include.  No
  //	parameters.
  const Ingredient*
		getIngredientPtr()
				const
				{ return(ingredientPtr_); }

  //  PURPOSE:  To return the reference to the Ingredient to include.  No
  //	parameters.
  const Ingredient&
		getIngredient	()
				const
				{ return(*ingredientPtr_); }

  //  PURPOSE:  To tell the quantity in liters of the Ingredient
  //	'*ingredientPtr'.
  float		getNumLiters	()
				const
				{ return(numLiters_); }

  float		getTasteComponent
				(tasteComponent_t	i
				)
				const
				{
				  return(getNumLiters() *
					 getIngredient().getTasteComponent(i)
					);
				}

  //  VI.  Mutators:

  //  VII.  Methods that do main and misc work of class:

};
