
int reg(int data ,int rst,int en, int clk)
{
	static int clk_a =0;
	static int datareg =0;
	
	if (clk== 1 && clk_a == 0)
	{
		clk_a = clk;
		if (rst == 1){ 
			datareg = 0x00000000; 
		}
		else if (en == 1){ 
			datareg = data;
			return data;
		
		} 
		
	}
	clk_a = clk;
	return datareg;
	
}