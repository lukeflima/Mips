library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

ENTITY Cout IS PORT(
    a   : IN STD_LOGIC_VECTOR(3 DOWNTO 0); -- input
    b   : IN STD_LOGIC_VECTOR(3 DOWNTO 0); -- input
    addsub   : IN STD_LOGIC_VECTOR(3 DOWNTO 0); -- input
    resultado   : IN STD_LOGIC_VECTOR(3 DOWNTO 0); -- input
    s   : OUT STD_LOGIC_VECTOR(3 DOWNTO 0) -- output
);
END Cout;

architecture Behavioral of Cout is

signal aux;

begin
	if (!addsub) then
		if (((a<=X"7FFFFFFF") && (b <= X"7FFFFFFF") && (resultado > X"7FFFFFFF")) || 
			((a > X"7FFFFFFF") && (b > X"7FFFFFFF") && (resultado <= X"7FFFFFFF")) ) then

			aux <= 1;
		
		else
			aux<=0;	
	else
		if (((a <= X"7FFFFFFF") && (b > X"7FFFFFFF") && (resultado > X"7FFFFFFF")) ||
			((a > X"7FFFFFFF") && (b <= X"7FFFFFFF") && (resultado <= X"7FFFFFFF"))) then

			aux<=1;
			
		end if;
		else
			aux<=0;
										
		end if;
		
	end if;
s<= aux;
	
end architecture Behavioral;