#include "extension.h"
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

int main()
{
	 int cur_vect = 0;
  
	 int i=0;
  DEF_GENPAT("extensor de sinal");

  DECLAR("input", ":2", "B", IN, "15 down to 0","");
  DECLAR("output", ":2", "B", IN, "31 down to 0","");
  DECLAR("vdd", ":2", "B", IN, "","");
  DECLAR("vss", ":2", "B", IN, "","");

  LABEL ("extend");
  AFFECT ("0","vdd","0b1");
  AFFECT ("0","vss","0b0");


	for(i=0;i<pow(2,16);i++)
	{
		AFFECT (inttostr(cur_vect), "input", inttostr(i));
		AFFECT (inttostr(cur_vect), "output", inttoHstr(sign_extension(i)));
		cur_vect++;
	
	}
	SAV_GENPAT ();

}