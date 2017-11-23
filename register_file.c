#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "genpat.h"
#include "decoder.h"
#include "mux.h"
#include "reg.h"
#define ENTRADA a,S
#define ENTRADA1 a,S2
/******************************/
/*Serie 11318316             */
/****************************///a[32]
/*declaração de variaveis*/

int Wr = 0, clk = 0, rst = 0, D, En,S[5],a[32],S2[5],S3[5];
unsigned int cur_vect = 0;
int *c;
int i,j,k,l,m,n;  
int x;
char N[17], *V[32] = {"Reg_0","Reg_1","Reg_2","Reg_3","Reg_4","Reg_5","Reg_6","Reg_7","Reg_8","Reg_9","Reg_10","Reg_11",
						"Reg_12","Reg_13","Reg_14","Reg_15","Reg_16","Reg_17","Reg_18","Reg_19","Reg_20","Reg_21","Reg_22",
						"Reg_23","Reg_24","Reg_25","Reg_26","Reg_27","Reg_28","Reg_29","Reg_30","Reg_31"}; 





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

/**************************************************/

void TestarRegistrador(){

int Reg_a,Reg_b;
AFFECT (inttostr(cur_vect), "clk", inttostr(clk) );
AFFECT (inttostr(cur_vect), "rst", inttostr(rst) );
AFFECT (inttostr(cur_vect), "WD3", inttoHstr(D) );
AFFECT (inttostr(cur_vect), "WE3", inttostr(En) );
/*verifica se o registrador selecionado foi o ReG_0*/
if(c[0]==1)
{	
		
	/*Chama os registradores de saida e joga o valor lá*/
	AFFECT (inttostr(cur_vect), "Reg_A", inttoHstr(0x00000000) );
	AFFECT (inttostr(cur_vect), "Reg_B", inttoHstr(0x00000000) );
}
else
{
/*joga o dado em todos os 32 registradores e apenas o que estiver  
habilitado pra gravar é que fixa o valor*/ 
	for(n=0;n<32;n++)
	{
	        a[n] = reg(D,rst,En,clk);
	}
		Reg_a = Mux_32_1(ENTRADA);
		Reg_b = Mux_32_1(ENTRADA1);

		AFFECT(inttostr(cur_vect), "Reg_A", inttoHstr(reg(Reg_a,rst,En,clk)));
		AFFECT(inttostr(cur_vect), "Reg_B", inttoHstr(reg(Reg_b,rst,En,clk)));
	}

cur_vect++;
clk = !clk;
}


int main(){
    c  = (int*) malloc(32*sizeof(int));

	DEF_GENPAT("Register_File");

	/* interface */
	DECLAR ("A1", ":3", "B", IN, "4 downto 0", "" );
	DECLAR ("A2", ":3", "B", IN, "4 downto 0", "" );
	DECLAR ("A3", ":3", "B", IN, "4 downto 0", "" );
	DECLAR ("clk", ":2", "B", IN, "", "" );
	DECLAR ("rst", ":2", "B", IN, "", "" );
	DECLAR ("WD3", ":2", "B", IN, "31 DOWNTO 0", "" );
	DECLAR ("WE3", ":2", "B", IN, "", "" );
	DECLAR ("Reg_A", ":2", "B", OUT, "31 DOWNTO 0", "" );
	DECLAR ("Reg_B", ":2", "B", OUT, "31 DOWNTO 0", "" );

        
	DECLAR ("vdd", ":2", "B", IN, "", "" );
	DECLAR ("vss", ":2", "B", IN, "", "" );
        

	AFFECT ("0", "vdd", "0b1");
	AFFECT ("0", "vss", "0b0");
	AFFECT ("0", "clk", "0b0");
     	
       /*geração do valores para as entradas de seleção*/
	for (i=0 ; i<2 ; i++){
	    for (j=0 ; j<2 ; j++){
              for (k=0; k<2; k++){
                for (l=0; l<2; l++){
                    for (m=0; m<2; m++){
                    /*Habilitador de gravação*/
						for(Wr=0 ; Wr<2 ; Wr++){
			 
                        	AFFECT(inttostr(cur_vect), "A1", inttostr(16*i+8*j+4*k+2*l+m));
							AFFECT(inttostr(cur_vect), "A2", inttostr(16*i+8*j+4*k+2*l+m));
							AFFECT(inttostr(cur_vect), "A3", inttostr(16*i+8*j+4*k+2*l+m));
                       
                         
							/* Seletor do Primeiro MUX */   
                        
                        	S[0] = m;
                        	S[1] = l;
                        	S[2] = k;
                        	S[3] = j;
                        	S[4] = i;
                        	/* Seletor do Primeiro MUX */ 
	          
	                        S2[0] = m;
	                        S2[1] = l;
	                        S2[2] = k;
	                        S2[3] = j;
	                        S2[4] = i;
	                        /* Seletor do Decodificador*/
	                        
	                        S3[0] = m;
	                        S3[1] = l;
	                        S3[2] = k;
	                        S3[3] = j;
	                        S3[4] = i;       
	         
	     
	     /*Chamada da Função decodificador*/

		c=decodificador(S3);
	        
	        for (x=0; x<32; x++)
	        {
	        
		/*Verifica qual registrador foi selecionado pelo decoder*/
		if(c[x]== 1 ){
		/*verifica se o resgistrador selecionado pelo decoder esta habilitado para gravação*/
	        if(c[x]== 1 && Wr== 1 )
		{
		
		En =c[x];
		D = 0xFFFFFFFF;
		rst = 0;
		TestarRegistrador(); //clk = 0
		LABEL ("EN_1");
		TestarRegistrador(); //clk = 1
		
		D = 0x00000000; 
		rst = 0;
		TestarRegistrador(); //clk = 0
		LABEL ("D_0");
		TestarRegistrador(); //clk = 1
		//En = 0xFFFFFFFF;  
		             }
		else
		{
		rst = 1;
		En = Wr ;
		D = 0xFFFFFFFF; 
		strcpy(N, "Seleciona_");
	        strcat(N, V[16*i+8*j+4*k+2*l+m]);
	        LABEL(N);
		TestarRegistrador(); //clk = 0
		
		TestarRegistrador(); //clk = 1
		LABEL ("EN_0");
	        rst = 0;
		D =0x00000000;
		TestarRegistrador(); //clk = 0
		LABEL ("D_0");
		TestarRegistrador(); //clk = 1
	}
    
 	}

        }

	}
		}
			}
				}
					}   
					        }

	printf ("\n FIM\n");

	SAV_GENPAT ();
}

