#include <string.h>

unsigned int Adr,Instr,SrcA,SrcB,aluSrcB[2],AlUOut,r=0,PCEn,InstrData, Data, RD1, RD2, A1, A2, A3, WD3, A, B;
long int aluResult,cur_vect = 0,PcN,Pc=0;

typedef enum{ S0, S1, S2, S3, S4, S5, S6, S7, S8, S9, S10, S11, S6_0, S6_1, S6_2, S6_3, S6_4};
int estado = S1, AluControl, FSMAluOp, clk=0, clka=1;
int FSMIorD, FSMIRWrite, FSMRegDst, FSMMemToReg, FSMAluSrcA, FSMAluSrcB = 0, FSMPCSrc, FSMPCWrite, 
	FSMBranch, FSMRegWrite, FSMMemWrite, FSMALUZero;
	char cod[32];
	int opcode = 0, rst, funct = 0, i, pot, qtd = 1;
	int esperaClock = 1;

/*char *inttostr(entier)
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
*/


void AfctFSM(int reset, int opcode, int Funct){
    	
	if (FSMPCWrite == 1 || (FSMBranch && FSMALUZero)) PCEn = 1;
	else PCEn = 0;
	while (!esperaClock){
	if (clka == 1 && clk == 0){
	   /* AFFECT(inttostr(cur_vect), "rst",         inttostr(reset));
	    AFFECT(inttostr(cur_vect), "Opcode",      inttostr(opcode));
	    AFFECT(inttostr(cur_vect), "Funct",       inttostr(Funct));
	    AFFECT(inttostr(cur_vect), "ALUZero",     inttostr(0)); // Necessário o Datapath*/
	    esperaClock = 1;
	}
	/*AFFECT(inttostr(cur_vect), "Estado",         inttostr(estado));
	AFFECT(inttostr(cur_vect), "clk",         inttostr(clk));
	AFFECT(inttostr(cur_vect), "MemWrite",    inttostr(FSMMemWrite));
	AFFECT(inttostr(cur_vect), "IorD",        inttostr(FSMIorD));
	AFFECT(inttostr(cur_vect), "IRWrite",     inttostr(FSMIRWrite));
	AFFECT(inttostr(cur_vect), "RegDst",      inttostr(FSMRegDst));
	AFFECT(inttostr(cur_vect), "MemToReg",    inttostr(FSMRegDst));
	AFFECT(inttostr(cur_vect), "RegWrite",    inttostr(FSMRegWrite));
	AFFECT(inttostr(cur_vect), "ALUSrcA",     inttostr(FSMAluSrcA));
	AFFECT(inttostr(cur_vect), "ALUSrcB",     inttostr(FSMAluSrcB));
	AFFECT(inttostr(cur_vect), "PCSrc",       inttostr(FSMPCSrc));
	AFFECT(inttostr(cur_vect), "ALUOp",       inttostr(FSMAluOp));
	AFFECT(inttostr(cur_vect), "PCWrite",     inttostr(FSMPCWrite));
	AFFECT(inttostr(cur_vect), "Branch",      inttostr(FSMBranch));
	AFFECT(inttostr(cur_vect), "ALUControl",  inttostr(AluControl));
	AFFECT(inttostr(cur_vect), "PCEn",        inttostr(PCEn));*/
	/*clka = clk;
	clk = !clka; 
	cur_vect++;*/
	}
}

int MaquinaDeEstados(int rst, int opcode, int funct, int codigo){
	char label[20];
	int proxEstado, executou = 0;
	while (!executou){
		if (rst){ 
			FSMIorD = 0b0;
			FSMAluSrcA =   0b00;
			FSMAluSrcB =   0b01;
			FSMPCSrc   =   0b00;
			FSMAluOp   =   0b00;
			FSMIRWrite =   0b1;
			FSMPCWrite =   0b1;
			estado = S0;
			AluControl = 2;
			 
			//printf("%u\n",codigo);
			
			strcpy(label, "Rclock, clockA, eset");
			datapathFetch(clk,clka,FSMIorD, FSMMemWrite, FSMMemToReg, FSMIRWrite, FSMRegDst, FSMPCWrite, FSMBranch, FSMPCSrc, AluControl, FSMAluSrcA,FSMAluSrcB, FSMRegWrite, PCEn, rst, codigo );
			AfctFSM(rst, opcode, funct);
			
			strcpy(label, "Reset"); 
			datapathFetch(clk,clka,FSMIorD, FSMMemWrite, FSMMemToReg, FSMIRWrite, FSMRegDst, FSMPCWrite, FSMBranch, FSMPCSrc, AluControl, FSMAluSrcA,FSMAluSrcB, FSMRegWrite, PCEn, rst, codigo );
			strcpy(label, "Reset"); 

			rst = 0;
	    	}
		else {
			switch(estado){
				case S0:
					printf("S0\n");
					FSMPCWrite =   0b0;
					FSMBranch  =   0b0;
					FSMRegWrite =  0b0;
					FSMMemWrite =  0b0; 
					FSMIorD = 0b0;
					FSMAluSrcA =   0b00;
					FSMAluSrcB =   0b01;
					FSMPCSrc   =   0b00;
					FSMAluOp   =   0b00;
					FSMIRWrite =   0b1;
					FSMPCWrite =   0b1;
					AluControl = 2;
					printf("%d\n",codigo);					
					proxEstado = S1;
					strcpy(label, "Fetch");
					break;
				case S1:
					FSMIRWrite =   0b0;
					FSMPCWrite =   0b0; 
					printf("S1\n"); 
				    FSMAluSrcA =   0b00;
					FSMAluSrcB =   0b11;
					FSMAluOp   =   0b00;
				    
					switch (opcode){
						case 0: 
							proxEstado = S6;
							break;
						case 35:
						case 43:
							proxEstado = S2;
							break;
						case 4: 
							proxEstado = S8;
							break;	
						case 8:			
							proxEstado = S9;
							break;
						case 2: 
							proxEstado = S11;
							break;
					}
					strcpy(label, "Decode");
					break;
				case S2:
					printf("S2\n");  
					FSMAluSrcA =   0b01;
		        		FSMAluSrcB =   0b10;
		        		FSMAluOp   =   0b00;
		        
					switch (opcode){	
						case 35:
							proxEstado = S3;
							break;
						case 43:
							proxEstado = S5;
							break;
					}
					strcpy(label, "MemAdr");
					break;
				case S3:
					printf("S3\n");  
					FSMIorD = 0b1;
					proxEstado = S4;
					strcpy(label, "MemRead");
					break;
				case S4: 
					printf("S4\n"); 
					FSMRegDst   =  0b0;
					FSMMemToReg =  0b1;
					FSMRegWrite =  0b1;
					proxEstado = S0;
					strcpy(label, "MemWriteback");
					break;
				case S5:
					printf("S5\n"); 
					FSMIorD = 0b1;
					FSMMemWrite =  0b1;
					proxEstado = S0;
					strcpy(label, "MemWrite");
					break;
				case S7:
					printf("S7\n"); 
					FSMRegDst   =  0b1;
					FSMMemToReg =  0b0;
					FSMRegWrite =  0b1;
					proxEstado = S0;
					strcpy(label, "ALUWriteback");
					break;
				case S8:
					printf("S8\n"); 
				   	FSMAluSrcA =   0b01;
		        		FSMAluSrcB =   0b00;
		        		FSMPCSrc   =   0b01;
		        		FSMAluOp   =   0b01;
					FSMBranch  =   0b1;
					proxEstado = S0;
					strcpy(label, "Branch");
					break;
				case S10:
					printf("S10\n"); 
					FSMRegDst   =  0b0;
					FSMMemToReg =  0b0;
					FSMRegWrite =  0b1;
					proxEstado = S0;
					strcpy(label, "ADDIWriteback");
					break;
				case S11:
					printf("S11\n"); 
				    FSMPCSrc   =   0b10;
					FSMPCWrite =   0b1;
					proxEstado = S0;
					strcpy(label, "Jump");
					break;
				case S9:
					printf("S9\n");  
					FSMAluSrcA =   0b01;
		        		FSMAluSrcB =   0b10;
		        		FSMAluOp   =   0b00;
					proxEstado = S10;
					strcpy(label, "ADDIExecute");
					break;
				case S6:
					printf("S6\n");  
					FSMAluSrcA = 0b1;
					FSMAluSrcB = 0b00;
					FSMAluOp = AluOp(opcode);
					AluControl = setAluControl(AluOp(opcode), funct);
					switch(funct){
						case 0b100000: proxEstado = S7; strcpy(label, "Execute_Add"); break;
						case 0b100010: proxEstado = S7; strcpy(label, "Execute_Sub"); break;
						case 0b100100: proxEstado = S7; strcpy(label, "Execute_And"); break;
						case 0b100101: proxEstado = S7; strcpy(label, "Execute_Or"); break;
						case 0b101010: proxEstado = S7; strcpy(label, "Execute_Slt"); break;
						default: printf("Operação inexistente!"); break;
					}
					break;
				case S6_0: 
				case S6_1: 
				case S6_2: 
				case S6_3: 
				case S6_4: proxEstado = S7; break;
			}
			datapathFetch(clk,clka,FSMIorD, FSMMemWrite, FSMMemToReg, FSMIRWrite, FSMRegDst, FSMPCWrite, FSMBranch, FSMPCSrc, AluControl, FSMAluSrcA,FSMAluSrcB, FSMRegWrite, PCEn, rst, codigo );
			datapathFetch(clk,clka,FSMIorD, FSMMemWrite, FSMMemToReg, FSMIRWrite, FSMRegDst, FSMPCWrite, FSMBranch, FSMPCSrc, AluControl, FSMAluSrcA,FSMAluSrcB, FSMRegWrite, PCEn, rst, codigo );
			
			if (proxEstado == S0) executou = 1;
			/*LABEL(label);*/
			AfctFSM(rst, opcode, funct);
			estado = proxEstado;					
		}
	}
}

int AluOp(int opcode){
	int result;
	if (opcode == 8 || opcode == 9)
		result = 0b00;
	else if(opcode == 4 || opcode == 20 || opcode == 5)
		result = 0b01;
	else result = 0b10;
	return result;	
}
/*	
	opcode 			AluOp
	001000	ADDI(ADD)	00
	001001	ADDIU(ADD)	00
	000100	BEQ(SUB)	01
	010100	BEQL(SUB)	01
	000101	BNE(SUB)	01						
*/
int setAluControl(int AluOP, int Funct){

	int AluControl = 0b0, aluOp;
	aluOp = AluOP;
	switch (aluOp){
		case 0b00: AluControl = 0b010; break;//Add
		case 0b01: AluControl = 0b110; break;//Sub
		case 0b10: 
			switch(Funct){
				case 0b100000: AluControl = 0b010; break; // Add
				case 0b100010: AluControl = 0b110; break; // Sub
				case 0b100100: AluControl = 0b000; break; // And
				case 0b100101: AluControl = 0b001; break; // Or
				case 0b101010: AluControl = 0b111; break; // Slt
				default: 
					printf("\nFunct = %d é inválido!", Funct);
					break;
			}
			break;	
		default:
			AluControl = 0b101; // Undefined
			printf("\nAluOP = %d  é inválido!", AluOP);
	}
	return AluControl;
}


/*int main(){
	char cod[32];
	int opcode = 0, rst, funct = 0, i, pot, qtd = 1;
	//DEF_GENPAT("FSM_LW");

	/* interface */
	/*
	DECLAR ("clk",        ":2", "B", IN, "", "" );
	DECLAR ("rst",        ":2", "B", IN, "", "" );
	DECLAR ("Opcode",     ":2", "B", IN, "5 downto 0", "" );
	DECLAR ("Funct",      ":2", "B", IN, "5 downto 0", "" );
	DECLAR ("ALUZero",    ":2", "B", IN, "", "");

	DECLAR ("Estado",     ":2", "B", OUT, "4 downto 0", "");
	DECLAR ("MemWrite",   ":2", "B", OUT, "", "" );
	DECLAR ("IorD",       ":2", "B", OUT, "", "" );
	DECLAR ("IRWrite",    ":2", "B", OUT, "", "" );
	DECLAR ("RegDst",     ":2", "B", OUT, "", "" );
	DECLAR ("MemToReg",   ":2", "B", OUT, "", "" );
	DECLAR ("RegWrite",   ":2", "B", OUT, "", "" );
	DECLAR ("ALUSrcA",    ":2", "B", OUT, "1 downto 0", "" );
	DECLAR ("ALUSrcB",    ":2", "B", OUT, "1 downto 0", "" );
	DECLAR ("PCSrc",      ":2", "B", OUT, "1 downto 0", "" );
	DECLAR ("ALUOp",      ":2", "B", OUT, "1 downto 0", "" );
	DECLAR ("PCWrite",    ":2", "B", OUT, "", "" );
	DECLAR ("Branch",     ":2", "B", OUT, "", "" );
	DECLAR ("ALUControl", ":2", "B", OUT, "2 downto 0", "" );
	DECLAR ("PCEn",       ":2", "B", OUT, "", "" );
	
	DECLAR ("vdd", ":2", "B", IN, "", "" );
	DECLAR ("vss", ":2", "B", IN, "", "" );

	AFFECT ("0", "vdd", "0b1");
	AFFECT ("0", "vss", "0b0");
	
	//Testando reset
	LABEL("Reset");
	rst = 1;
	AfctFSM(rst, opcode, funct);
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
		MaquinaDeEstados(rst, opcode, funct);
		rst = 0;
	}
	
	//SAV_GENPAT ();
}*/
