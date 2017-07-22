/*-------------------------------------------------------------------------*
 *---									---*
 *---		Ingredient.h						---*
 *---									---*
 *---	    This file declares a class that represents an ingredient.	---*
 *---									---*
 *---	----	----	----	----	----	----	----	----	---*
 *---									---*
 *---	Version 1.0		2016 November 1		Joseph Phillips	---*
 *---									---*
 *-------------------------------------------------------------------------*/

class	Ingredient
{
  //  I.  Member vars:
  //  PURPOSE:  To tell the values of the taste component of '*this' Ingredient.
  const float*			array_;

  //  II.  Disallowed auto-generated methods:
  //  No default constructor:
  Ingredient			();

  //  No assignment operator:
  Ingredient&	operator=	(const Ingredient&
  				);

protected :
  //  III.  Protected methods:

public :
  //  IV.  Constructor(s), assignment op(s), factory(s) and destructor:
  //  PURPOSE:  To initialize '*this' from the tastes components of
  //	'newTasteArray'.  No return value.
  Ingredient			(const float*	newTasteArray
				) :
				array_(newTasteArray)
				{ }

  //  PURPOSE:  To release the resources of '*this'.  No parameters.  No return
  //	value.
  ~Ingredient			()
				{ }

  //  V.  Accessors:
  //  PURPOSE:  To return the value of the taste component of 'index'.
  float		getTasteComponent
				(tasteComponent_t	index
				)
				const
				{ return(array_[index]); }

  //  VI.  Mutators:

  //  VII.  Methods that do main and misc work of class:

};
