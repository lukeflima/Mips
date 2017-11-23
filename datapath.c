#include "genpat.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "FSM.h"
#include <string.h>
int e = 0x00000000,e1 = 0x00000000,i,j=1,cod1,k;


char *inttostr(entier)
	int entier;
{
	char *str;
	str = (char*)mbkalloc(32*sizeof(char));
	sprintf(str, "%u",entier);
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

/* *********************************************************************** */
/* Registradores */
int Registrador(int clock, int clockA, int reset, int enable, int dado){

	if (clock==1 && clockA == 0){
		if (reset){
			e1 = 0x00000000;
		}
		else if (enable){
			e1 = dado;

		}
                                }
    return e1;
}

/* *********************************************************************** */
/* Register File*/

int RegisterFile(int clock, int clockA, int RegWrite, int WD3, int A1, int A2, int A3, int *RD1, int *RD2){

	static int unsigned registers[32];

	if (clock==1 && clockA == 0){
		if (RegWrite){
			registers[A3] = WD3;
		}
    	*RD1 = registers[A1];                           
    	*RD2 = registers[A2];
	}
	printf("Register 9 %u\n", registers[9]);
	if(RegWrite) printf("A3 %u WD3 %u\n", A3, WD3);
    return registers[A3];
}	

/* *********************************************************************** */
/* Intruction and Data Memory*/

int InstrDataMemory(int clock, int clockA, int MemWrite, int A, int WD, int *RD){
	static int read = 0;
	static unsigned int registers[128];

	if(!read){
		FILE *memory = fopen("memory.txt", "r");
		i = 0;
		while(!feof(memory)){
			fscanf(memory, "%x", &registers[i]);
			i++;
		}
		read = 1;
		fclose(memory);
	}
	A = (int) A/4;
	if (clock==1 && clockA == 0){
		if (MemWrite){
			registers[A] = WD;
		}
		printf("A RD %d %u\n", A, registers[A]);
		*RD = registers[A];
	}
	FILE *memory = fopen("memory.txt", "w");
	for(i = 0; i < 128; i ++){
		fprintf(memory, "0x%08x\n", registers[i]);
	}
	fclose(memory);
}

/* *********************************************************************** */
/* Registrador PC */

int RegistradorPC(int clock, int clockA, int reset, int enable, int dado){
	static int a = 0;

	if (clock==1 && clockA == 0){
		if (reset){
			a = 0x00000000;
		}
		else if (enable){
			a = dado;
		}
    }
    return a;
}

/* *********************************************************************** */
/* Registrador PC */

int RegistradorALUout(int clock, int clockA, int reset, int enable, int dado){
	static int a = 0;

	if (clock==1 && clockA == 0){
		if (reset){
			a = 0x00000000;
		}
		else if (enable){
			a = dado;
		}
    }
    return a;
}

/* *********************************************************************** */
/* Registrador PC */

int RegistradorInstr(int clock, int clockA, int reset, int enable, int dado){
	static int a = 0;

	if (clock==1 && clockA == 0){
		if (reset){
			a = 0x00000000;
		}
		else if (enable){
			a = dado;
		}
    }
    return a;
}

/* *********************************************************************** */
/* Registrador PC */

int RegistradorData(int clock, int clockA, int reset, int enable, int dado){
	static int a = 0;

	if (clock==1 && clockA == 0){
		if (reset){
			a = 0x00000000;
		}
		else if (enable){
			a = dado;
		}
    }
    return a;
}
/* *********************************************************************** */
/* Registrador PC */

int RegistradorA(int clock, int clockA, int reset, int enable, int dado){
	static int a = 0;

	if (clock==1 && clockA == 0){
		if (reset){
			a = 0x00000000;
		}
		else if (enable){
			a = dado;
		}
    }
    return a;
}
/* *********************************************************************** */
/* Registrador PC */

int RegistradorB(int clock, int clockA, int reset, int enable, int dado){
	static int a = 0;

	if (clock==1 && clockA == 0){
		if (reset){
			a = 0x00000000;
		}
		else if (enable){
			a = dado;
		}
    }
    return a;
}
/* *********************************************************************** */
/* Mux de uso geral */

int Mux_2_1(int* a, int s){
	if(s == 0) return a[0];
	else return a[1];
}

int Mux_4_1(int* a,  int *S){
	int y[2];
	y[0] = Mux_2_1(a ,S[0]);
	y[1] = Mux_2_1(&a[2], S[0]);
	return Mux_2_1(y ,S[1]);
}
/*
int Mux_2_1(int a_0, int a_1, int s){
	if(s == 0) return a_0;
	else return a_1;
}
int Mux_4_1(int a_0, int a_1, int a_2, int a_3, int *S){
	int y_0, y_1;
	y_0 = Mux_2_1(a_0, a_1, S[0]);
	y_1 = Mux_2_1(a_2, a_3, S[0]);
	return Mux_2_1(y_0, y_1, S[1]);
}
*/
/* *********************************************************************** */
/* ULA */

int AddSub(int op){
	if(op == 6) return 1;
	else return 0;
}

unsigned int SomaSub(int a, int b,int addsub, int op){
	long int AluResult;
	switch (op){
		case 0: return a & b;
		case 1: return a | b;
		case 2: return a + b;
		case 6: return a - b;
		case 4: return a & ~b;
		case 5: return a | ~b;
		case 7: return a < b;
		default:
			break;
	}
}

int Zero(int resultado){
	return !resultado;
}

int Cout(unsigned int a, unsigned int b, unsigned int addsub, unsigned int resultado){
	if(!addsub)
		if(((a <= 0x7FFFFFFF) && (b <= 0x7FFFFFFF) && (resultado > 0x7FFFFFFF)) ||
			((a > 0x7FFFFFFF) && (b > 0x7FFFFFFF) && (resultado <= 0x7FFFFFFF)))
			return 1;
		else
			return 0;
	else
		if(((a <= 0x7FFFFFFF) && (b > 0x7FFFFFFF) && (resultado > 0x7FFFFFFF)) ||
			((a > 0x7FFFFFFF) && (b <= 0x7FFFFFFF) && (resultado <= 0x7FFFFFFF)))
			return 1;
	else
			return 0;
}

/* *********************************************************************** */
/* Sign Extender */

int sign_extension(int number)
{
    int result = number;
    number >>= 15;
    if(number == 1)
    {
  
        result += 0xFFFF0000;
        return result;
    }
   
    return result;
    	
}


/* *********************************************************************** */
/* Função Principal */
void datapathFetch(int clock, int clockA, int IorD, int MemWrite, int MemToReg, int IRWrite, int RegDst, int PCWrite, int Branch, int PCSrc, int ALUControl, int AluSrcA, int AluSrcB, int RegWrite, int PCen, int Reset, int CODIGO)
{	
		printf("clock %d %d\n", clock, clockA );
		//if(MemWrite) printf("###############################\n");
		//printf("IRWrite %d\n", IRWrite);
		//printf("IorD, MemWrite, IRWrite, RegDst, PCWrite, Branch, PCSrc, AluControl, AluSrcA,AluSrcB, RegWrite, PCEn \n");
		//printf("%d %d %d %d %d %d %d %d %d %d %d %d \n", IorD, MemWrite, IRWrite, RegDst, PCWrite, Branch, PCSrc, AluControl, AluSrcA,AluSrcB, RegWrite, PCEn);
		int	mux2[] = {0,0};
		int	mux4[] = {0,4,2,3};
		//if (clock==1 && clockA == 0) Pc = RegistradorPC(clock,clockA,Reset,PCen,PcN);
		mux2[0] = Pc;
		mux2[1] = AlUOut;
		unsigned int muxAdr = Mux_2_1(mux2,IorD);

		mux2[0] = (Instr >> 16) & 31;
		mux2[1] = (Instr >> 11) & 31;
		unsigned int muxA3 = Mux_2_1(mux2, RegDst);

		mux2[0] = AlUOut;
		mux2[1] = Data;
		unsigned int muxWD3 = Mux_2_1(mux2, MemToReg);

		mux2[0] = Pc;
		mux2[1] = A;
		unsigned int muxSrcA = Mux_2_1(mux2,AluSrcA);

		mux4[0] = B;
		mux4[2] = sign_extension(Instr & 32767);
		mux4[3] = mux4[2] << 2;
		unsigned int muxSrcB = Mux_4_1(mux4,aluSrcB);

		mux2[0] = aluResult;
		mux2[1] = AlUOut;
		unsigned int muxPcN = Mux_2_1(mux2, PCSrc);

		Pc = RegistradorPC(clock,clockA,Reset,PCen,PcN);
		//printf("PC %u\n", Pc);
		
		Adr = muxAdr;
		//printf("Adr %u\n", Adr );
		//printf("Adr\n");
		InstrDataMemory(clock, clockA, MemWrite, Adr, B, &InstrData);
		//printf("InstrData %u\n", InstrData);
		Instr = RegistradorInstr(clock,clockA,Reset,IRWrite,InstrData);
		//printf("Instr\n");
		Data = RegistradorData(clock,clockA,Reset, 1 ,InstrData);
		
		//printf("Data\n");
		//printf("Instr %u\n", Instr);
		A1 = (Instr >> 21) & 31;
		//printf("A1 %u\n", A1);
		A2 = (Instr >> 16) & 31;
		//printf("A2 %u\n", A2);
		A3 = muxA3;
		WD3 = muxWD3;
		RegisterFile(clock, clockA, RegWrite, WD3, A1, A2, A3, &RD1, &RD2);
		//printf("RegisterFile\n");
		A = RegistradorA(clock,clockA,Reset, 1 ,RD1);
		B = RegistradorB(clock,clockA,Reset, 1 ,RD2);
		SrcA = muxSrcA;
		aluSrcB[0] = AluSrcB>>0&1;
		aluSrcB[1] = AluSrcB>>1&1;
		
		SrcB = muxSrcB;
		aluResult = SomaSub(SrcA,SrcB,0,ALUControl);
		//printf("aluResult %u SrcA %u SrcB %u\n", aluResult, SrcA, SrcB);
		AlUOut = RegistradorALUout(clock, clockA, Reset, 1, aluResult);
		//printf("AlUOut\n");
		PcN = muxPcN;
		printf("\n");
		//Pc = RegistradorPC(clock,clockA,Reset,PCen,PcN);


		/*
		AFFECT(inttostr(cur_vect), "pc",         		inttostr(Pc));
		AFFECT(inttostr(cur_vect), "clk",         		inttostr(clock));
		//AFFECT(inttostr(cur_vect), "rst",         		inttostr(Reset));
		AFFECT(inttostr(cur_vect), "pcN",         		inttoHstr(PcN));
		AFFECT(inttostr(cur_vect), "SrcA",         		inttoHstr(SrcA));
		AFFECT(inttostr(cur_vect), "SrcB",         		inttoHstr(SrcB));
		AFFECT(inttostr(cur_vect), "Adr",        		inttoHstr(Adr));
		AFFECT(inttostr(cur_vect), "Instr",         	inttoHstr(Instr));
		AFFECT(inttostr(cur_vect), "ALUResult",         inttoHstr(aluResult));
	
		LABEL("Fetch");
		*/
		clka = clk;
		clk = !clka;    
		//cur_vect++;

	
      
        
}
/*
void datapatch(int clock, int clockA, int IorD, int IRWrite, int PCSrc, int ALUControl, int AluSrcA, int AluSrcB, int PCen, int Reset, int CODIGO)
{	


		Pc = RegistradorPC(clock,clockA,Reset,PCen,PcN);
		Adr = Mux_2_1(Pc,0,IorD);
		Instr = Registrador(clock,clockA,Reset,IRWrite,CODIGO);
		SrcA = Mux_2_1(Pc,0,AluSrcA);
		aluSrcB[0]=AluSrcB>>0&1;
		aluSrcB[1]=AluSrcB>>1&1;
		SrcB = Mux_4_1(0,4,2,3,aluSrcB);
		aluResult = SomaSub(SrcA,SrcB,0,ALUControl);
		AlUOut = Mux_2_1(aluResult,0,PCSrc);
		PcN = RegistradorPC(clock,clockA,Reset,PCen,AlUOut);
		//Pc = RegistradorPC(clock,clockA,Reset,PCen,PcN);



		AFFECT(inttostr(cur_vect), "pc",         inttostr(Pc));
		AFFECT(inttostr(cur_vect), "clk",         inttostr(clock));
		AFFECT(inttostr(cur_vect), "rst",         inttostr(Reset));
		AFFECT(inttostr(cur_vect), "pcN",         inttoHstr(PcN));
		AFFECT(inttostr(cur_vect), "SrcA",         inttoHstr(SrcA));
		AFFECT(inttostr(cur_vect), "SrcB",         inttoHstr(SrcB));
		AFFECT(inttostr(cur_vect), "Adr",         inttoHstr(Adr));
		AFFECT(inttostr(cur_vect), "Instr",         inttoHstr(Instr));
		AFFECT(inttostr(cur_vect), "ALUResult",         inttoHstr(aluResult));
		LABEL("Reset");

		clka = clk;
		clk = !clka;    
		cur_vect++;

	
      
        
}

*/
int main(){
 
	/*DEF_GENPAT("DataPath");

 
 
	
	
        DECLAR ("clk",        ":2", "B", IN, "", "" );
        DECLAR ("rst",        ":2", "B", IN, "", "" );
        DECLAR ("pc",        ":2", "B", IN, "31 downto 0", "" );
        
        DECLAR ("SrcA",        ":2", "B", IN, "31 downto 0", "" );
        DECLAR ("SrcB",        ":2", "B", IN, "31 downto 0", "" );

        DECLAR ("Adr",        ":2", "B", OUT, "31 downto 0", "" );
        DECLAR ("Instr",        ":2", "B", OUT, "31 downto 0", "" );
        DECLAR ("ALUResult",        ":2", "B", OUT, "31 downto 0", "" );
        DECLAR ("pcN",        ":2", "B", IN, "31 downto 0", "" );

        DECLAR ("vdd", ":2", "B", IN, "", "" );
        DECLAR ("vss", ":2", "B", IN, "", "" );

        AFFECT ("0", "vdd", "0b1");
        AFFECT ("0", "vss", "0b0");
      */           
	rst = 1;
	AfctFSM(rst, opcode, funct);
	printf("Reset\n");
	while(scanf("%s", cod) == 1){
		printf("%d%c instrucao: %s\n", qtd++, 166, cod);
		funct = 0;
		opcode = 0;
		pot = 1;
		for (i=5; i>=0; i--){
			opcode += pot*(cod[i] - 48) ;
			funct += pot*(cod[26+i] - 48) ;
			pot = pot*2;
		}
		printf("Opcode: %d, Funct: %d\n\n", opcode, funct);
		for(k=31;k>=0;k--)
		{
			cod1 += j*(cod[k]-48);
			j=j*2;
		}
		printf("\n");
		
		//printf("%u\n", cod1);
		MaquinaDeEstados(rst, opcode, funct,cod1);
		j=1;
		cod1=0;
		rst = 0;
	}
     
        
     
       

/*
	SAV_GENPAT ();*/
}
