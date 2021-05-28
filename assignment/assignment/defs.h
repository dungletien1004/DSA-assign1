#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string.h>
using namespace std;

struct ringsignList  
{
	int nRingsign; 
	ringsignList* pNext;
};


struct knight
{
	int HP;
	int level;
	int nInitRingsign;
};


struct eventList 
{
	int nEventCode; 
	eventList* pNext;
};

int checkPalindrome (ringsignList* pRingsign);
ringsignList*  combat (knight& theKnight, eventList* pEvent);
