#--------------------------------------------------------------------------#
#---									---#
#---		makefile						---#
#---									---#
#---	    This file defines a Makefile for Lex, Yacc and CPP files	---#
#---	that implement a baking simulator language.			---#
#---									---#
#---	----	----	----	----	----	----	----	----	---#
#---									---#
#---	Version 1.0		2016 November 2		Joseph Phillips	---#
#---									---#
#--------------------------------------------------------------------------#

# Makefile for bakingLang
bakingSimulator	 : bakingLang.tab.o bakingLang.o bakingMain.o
		   g++ -o $@ bakingLang.tab.o bakingLang.o bakingMain.o


bakingMain.o	 : bakingHeaders.h bakingLang.tab.h bakingLang.c	\
		   bakingHeaders.h Ingredient.h Measure.h Pantry.h	\
		   MeasuredIngredient.h Mixture.h Step.h Recipe.h	\
		   bakingMain.cpp
		   g++ -c bakingMain.cpp -g


bakingLang.o	 : bakingHeaders.h bakingLang.tab.h bakingLang.c	\
		   bakingHeaders.h Ingredient.h Measure.h Pantry.h	\
		   MeasuredIngredient.h Mixture.h Step.h Recipe.h bakingLang.c
		   g++ -c bakingLang.c -g


bakingLang.tab.o : bakingHeaders.h bakingLang.tab.h bakingLang.tab.c	\
		   bakingHeaders.h Ingredient.h Measure.h Pantry.h	\
		   MeasuredIngredient.h Mixture.h Step.h Recipe.h	\
		   bakingLang.tab.c
		   g++ -c bakingLang.tab.c -g


bakingLang.c	 : bakingLang.lex
		   flex -o$@ bakingLang.lex


bakingLang.tab.c : bakingLang.y
		   bison -d bakingLang.y --debug --verbose

bakingLang.tab.h : bakingLang.y
		   bison -d bakingLang.y --debug --verbose
