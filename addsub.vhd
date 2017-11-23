library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

ENTITY AddSub IS PORT(
    op   : IN STD_LOGIC_VECTOR(3 DOWNTO 0); -- input
    s   : OUT STD_LOGIC_VECTOR(3 DOWNTO 0) -- output
);
END AddSub;

ARCHITECTURE Behavioral OF mux IS
  
BEGIN
    	if (op==6 or op==7) then
    		s<=1;
    	else
    	s<=0;
    			
    	end if;
   
END Behavioral;