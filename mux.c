#include "mux.h"
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
  
	 int i=0,j=0,k=0,l=0;
  DEF_GENPAT("mux");

  DECLAR("input", ":2", "B", IN, "31 down to 0","");
  DECLAR("output", ":2", "B", OUT, "31 down to 0","");
  DECLAR("op", ":2", "B", IN, "5 down to 0","");
  DECLAR("vdd", ":2", "B", IN, "","");
  DECLAR("vss", ":2", "B", IN, "","");

  LABEL ("mux");
  AFFECT ("0","vdd","0b1");
  AFFECT ("0","vss","0b0");

int teste[32];
int op[5];
	for(i=0;i<128;i++)
	{
		for (j = 0; j < 32; j++)
		{
			teste[j] = ~ ((i >> j) & 0b1);
		}
		for(k = 0; k < 5 ;k++)
		{
			op[k] = (i >> k) & 0b1;
		}

		AFFECT (inttostr(cur_vect), "input", inttostr(i^(int)pow(2,32)));
		AFFECT (inttostr(cur_vect), "op", inttostr(i&5));
		AFFECT (inttostr(cur_vect), "output", inttoHstr(Mux_32_1(teste,op)));
		cur_vect++;
	
	}
	SAV_GENPAT ();

}