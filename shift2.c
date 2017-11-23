#include "shift2.h"
#include "genpat.h"
#include <string.h>
#include <stdio.h>
#include <math.h>

char *inttostr(entier)
	int entier;
{
	char *str;
	str = (char*)mbkalloc(32*sizeof(char));
	sprintf(str, "%d",entier);
	return(str);
}

char *inttoHstr(entier)
	int entier;
{
	char *str;
	str = (char *) mbkalloc (32 * sizeof (char));
	sprintf  (str, "0x%X",entier);
	return(str);
}

void TestarShift()
{
	int i;
	int cur_vect = 0;
	DEF_GENPAT("shift2");
	LABEL("SHIFT");

	DECLAR("in", ":2", "B", IN, "25 down to 0","");
	DECLAR("out", ":2", "B", OUT, "27 down to 0","");

	for (i = 0; i < 31; ++i)
	{
		AFFECT (inttostr(cur_vect), "in", inttostr(i));
		AFFECT (inttostr(cur_vect), "out", inttoHstr(shift2(i)));
		cur_vect++;
	}
	SAV_GENPAT ();
}
int main()
{
	TestarShift();
}