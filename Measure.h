/*-------------------------------------------------------------------------*
 *---									---*
 *---		Measure.h						---*
 *---									---*
 *---	    This file declares a class that represents a measure.	---*
 *---									---*
 *---	----	----	----	----	----	----	----	----	---*
 *---									---*
 *---	Version 1.0		2016 November 1		Joseph Phillips	---*
 *---									---*
 *-------------------------------------------------------------------------*/

class	Measure
{
  //  I.  Member vars:
  //  PURPOSE:  To tell the conversion to liters.
  float		   	    	toLiters_;

  //  II.  Disallowed auto-generated methods:
  //  No default constructor:
  Measure			();

  //  No assignment operator:
  Measure&	operator=	(const Measure&
  				);

protected :
  //  III.  Protected methods:

public :
  //  IV.  Constructor(s), assignment op(s), factory(s) and destructor:
  //  PURPOSE:  To initialize '*this' to tell the conversion from 
  Measure			(float	conversion
				) :
				toLiters_(conversion)
				{ }

  //  PURPOSE:  To release the resources of '*this'.  No parameters.  No return
  //	value.
  ~Measure			()
				{ }

  //  V.  Accessors:
  //  PURPOSE:  To return the conversion to liters.  No parameters.
  float		getToLiters	()
				const
				{ return(toLiters_); }

  //  VI.  Mutators:

  //  VII.  Methods that do main and misc work of class:


};
