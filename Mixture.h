/*-------------------------------------------------------------------------*
 *---									---*
 *---		Mixture.h						---*
 *---									---*
 *---	    This file declares a class that keeps track of the contents	---*
 *---	of a mixture.							---*
 *---									---*
 *---	----	----	----	----	----	----	----	----	---*
 *---									---*
 *---	Version 1.0		2016 November 3		Joseph Phillips	---*
 *---									---*
 *-------------------------------------------------------------------------*/

class	Mixture
{
  //  I.  Member vars:
  float				tasteVolume_[NUM_COMPONENTS];

  //  II.  Disallowed auto-generated methods:

protected :
  //  III.  Protected methods:

public :
  //  IV.  Constructor(s), assignment op(s), factory(s) and destructor:
  //  PURPOSE:  To initialize '*this' to empty.  No parameters.  No return
  //	value.
  Mixture			()
				{
				  for  (int i = 0;  i < NUM_COMPONENTS;  i++)
				    tasteVolume_[i]	= 0.0;
				}

  //  PURPOSE:  To make '*this' a copy of 'source'.  No return value.
  Mixture			(const Mixture&	     source
  				)
				{
				  for  (int i = 0;  i < NUM_COMPONENTS;  i++)
				    tasteVolume_[i]	= source.getVolume(i);
				}

  //  PURPOSE:  To release the resources of '*this', make '*this' a copy of
  //	'source', and return a reference to '*this'.
  Mixture&	operator=	(const Mixture&	     source
				)
				{
				  if  (this == &source)
				    return(*this);

				  for  (int i = 0;  i < NUM_COMPONENTS;  i++)
				    tasteVolume_[i]	= source.getVolume(i);

				  return(*this);
				}

  //  PURPOSE:  To release the resources of '*this'.  No parameters.  No return
  //	value.
  ~Mixture			()
				{ }

  //  V.  Accessors:
  //  PURPOSE:  To return the volume of component with index 'index'.
  float		getVolume	(int	index
				)
				const
				{ return(tasteVolume_[index]); }

  //  VI.  Mutators:
  //  PURPOSE:  To add 'volumne' to the taste component at 'index'.  No return
  //	value.
  void		addVolume	(int	index,
				 float	volume
				)
				{ tasteVolume_[index]	+= volume; }

  //  VII.  Methods that do main and misc work of class:
  //  PURPOSE:  To add '*this' the contents of 'source' to '*this' and return
  //	a reference to '*this'.
  Mixture&	operator+=	(const Mixture&	     source
				)
				{
				  for  (int i = 0;  i < NUM_COMPONENTS;  i++)
				    tasteVolume_[i]	+= source.getVolume(i);

				  return(*this);
				}

  //  PURPOSE:  To print '*this'.  No parameters.  No return value.
  void		print		()
				const
				{
				  for  (int i = 0;  i < NUM_COMPONENTS;  i++)
				    printf("%10s\t%g\n",
					   tasteName[i],tasteVolume_[i]
					  );
				}

  //  PURPOSE:  To normalize '*this'.  No parameters.  No return value.
  void		normalize	()
				{
				  float	sum	= 0.0;
				  int	i;

				  for  (i = 0;  i < NUM_COMPONENTS;  i++)
				    sum += tasteVolume_[i];

				  if  (sum > 0.0)
				    for  (i = 0;  i < NUM_COMPONENTS;  i++)
				      tasteVolume_[i] /= sum;
				}
};