/*-------------------------------------------------------------------------*
 *---									---*
 *---		Pantry.h						---*
 *---									---*
 *---	    This file declares a class that holds the available		---*
 *---	Ingredient instances.						---*
 *---									---*
 *---	----	----	----	----	----	----	----	----	---*
 *---									---*
 *---	Version 1.0		2016 November 1		Joseph Phillips	---*
 *---									---*
 *-------------------------------------------------------------------------*/

extern	float	flourArray[8];
extern	float	wholeWheatFlourArray[8];
extern	float	cinnamonArray[8];
extern	float	bakingPowderArray[8];
extern	float	bakingSodaArray[8];
extern	float	milkArray[8];
extern	float	soyMilkArray[8];
extern	float	peanutOilArray[8];
extern	float	butterArray[8];
extern	float	tofuArray[8];
extern	float	sugarArray[8];
extern	float	eggArray[8];
extern	float	chocChipArray[8];
extern	float	vanillaExtractArray[8];

typedef	std::map<const char*,Ingredient*,bool(*)(const char*,const char*)>
				PantryMap;

class	Pantry
{
  //  I.  Member vars:
  //  PURPOSE:  To hold the mapping of names of ingredients to addresses of
  //	Ingredient instances telling about them.
  PantryMap				map_;

  //  II.  Disallowed auto-generated methods:
  //  No copy constructor:
  Pantry			(const Pantry&
				);

  //  No assignment operator:
  Pantry&	operator=	(const Pantry&
  				);

protected :
  //  III.  Protected methods:

public :
  //  IV.  Constructor(s), assignment op(s), factory(s) and destructor:
  //  PURPOSE:  To initialize '*this' Pantry instance with its 
  Pantry			() :
				map_(compareChapPtr)
				{
				  map_["flour"]			=
					new Ingredient(flourArray);
				  map_["wholeWheatFlour"]	=
					new Ingredient(wholeWheatFlourArray);
				  map_["cinnamon"]		=
					new Ingredient(cinnamonArray);
				  map_["bakingPowder"]		=
					new Ingredient(bakingPowderArray);
				  map_["bakingSoda"]		=
					new Ingredient(bakingSodaArray);
				  map_["milk"]			=
					new Ingredient(milkArray);
				  map_["soyMilk"]		=
					new Ingredient(soyMilkArray);
				  map_["peanutOil"]		=
					new Ingredient(peanutOilArray);
				  map_["butter"]		=
					new Ingredient(butterArray);
				  map_["tofu"]			=
					new Ingredient(tofuArray);
				  map_["sugar"]			=
					new Ingredient(sugarArray);
				  map_["egg"]			=
					new Ingredient(eggArray);
				  map_["chocChips"]		=
					new Ingredient(chocChipArray);
				  map_["vanillaExtract"]	=
					new Ingredient(vanillaExtractArray);
				}

  //  V.  Accessors:

  //  VI.  Mutators:

  //  VII.  Methods that do main and misc work of class:
  //  PURPOSE:  To return the address of the Ingredient whose name is 'namePtr'
  //	if one is found in '*this' Pantry, or 'NULL' otherwise.
  const Ingredient*
		getIngredient	(const char*	namePtr
				)
				const
				{
				  PantryMap::const_iterator	iter	=
				  	map_.find(namePtr);

				  return( (iter == map_.end())
				  	  ? NULL
					  : iter->second
					);
				}

};