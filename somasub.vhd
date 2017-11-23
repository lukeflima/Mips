library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

ENTITY SomaSub IS PORT(
    a   : IN STD_LOGIC_VECTOR(3 DOWNTO 0); -- input
    b   : IN STD_LOGIC_VECTOR(3 DOWNTO 0); -- input
    addsub   : IN STD_LOGIC_VECTOR(3 DOWNTO 0); -- input
    op   : IN STD_LOGIC_VECTOR(3 DOWNTO 0); -- input
    s   : OUT STD_LOGIC_VECTOR(3 DOWNTO 0) -- output
);
END SomaSub;

architecture behavioral of SomaSub is

signal aux;
signal aux2;
begin

case (op) is
	when 0000 => aux := a & b;
	when 0001 => aux := a | b;
	when 0100 => aux := a & ~b;
	when 0101 => aux := a | ~b; 
	when 0110 => begin if (addsub ==1 ) then
	aux2 := ~b;		
	end if;
	aux2 := (a + b + aux2) & 0xFFFFFFFF;
	end
	when 0111 => aux := a < b;	
	when others =>
		null;

end case;

s<= aux;
	
end architecture behavioral;