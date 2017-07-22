/*-------------------------------------------------------------------------*
 *---									---*
 *---		Recipe.h						---*
 *---									---*
 *---	    This file declares a class the represents an ingredient.	---*
 *---									---*
 *---	----	----	----	----	----	----	----	----	---*
 *---									---*
 *---	Version 1.0		2016 November 1		Joseph Phillips	---*
 *---									---*
 *-------------------------------------------------------------------------*/

class	Recipe
{
  //  I.  Member vars:
  //  PURPOSE:  To list the addresses of Step instances of '*this' Reciepe.
  std::list<Step*>		stepAddrList_;

  //  PURPOSE:  To hold 'true' if a parse-time problem was found, or 'false'
  //	otherwise.
  bool				wasParseTimeProblemFound_;

  //  II.  Disallowed auto-generated methods:
  //  No copy constructor:
  Recipe			(const Recipe&
				);

  //  No assignment operator:
  Recipe&	operator=	(const Recipe&
  				);

protected :
  //  III.  Protected methods:

public :
  //  IV.  Constructor(s), assignment op(s), factory(s) and destructor:
  //  PURPOSE:  To initialize '*this' Recipe to have no steps.
  Recipe			() :
				wasParseTimeProblemFound_(false)
				{ }

  //  PURPOSE:  To release the resources of '*this'.  No parameters.   No
  //	return value.
  ~Recipe			()
				{
				  std::list<Step*>::iterator	iter;

				  for  (iter  = stepAddrList_.begin();
					iter != stepAddrList_.end();
					iter++
				       )
				    delete(*iter);
				}

  //  V.  Accessors:
  //  PURPOSE:  To return 'true' if a parse-time problem was found, or 'false'
  //	otherwise.  No parameters.
  bool		getWasParseTimeProblemFound
				()
				const
				{ return(wasParseTimeProblemFound_); }

  //  PURPOSE:  To begin iterator of the list the addresses of Step instances
  //	of '*this' Reciepe.
  std::list<Step*>::iterator
		getStepAddrListBegin
				()
				{ return(stepAddrList_.begin()); }

  //  PURPOSE:  To end iterator of the list the addresses of Step instances
  //	of '*this' Reciepe.
  std::list<Step*>::iterator
		getStepAddrListEnd
				()
				{ return(stepAddrList_.end()); }

  //  VI.  Mutators:
  //  PURPOSE:  To note that a problem was found at parse-time.  No parameters.
  //	No return value.
  void		setWasParseTimeProblemFound
				()
				{ wasParseTimeProblemFound_ = true; }

  //  VII.  Methods that do main and misc work of class:
  //  PURPOSE:  To add the step pointed to by 'stepPtr' to '*this' Recipe.
  //	No return value.
  void		addStep		(Step*	stepPtr
  				)
				{ stepAddrList_.push_back(stepPtr); }

  //  PURPOSE:  To simulate cooking and tasting '*this' Recipe.  No parameters.
  //	No return value.
  void		cookAndTaste	();

};
