library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;


ENTITY Zero IS PORT(
    op   : IN STD_LOGIC_VECTOR(3 DOWNTO 0); -- input
    s   : OUT STD_LOGIC_VECTOR(3 DOWNTO 0) -- output
);
END Zero;

architecture behavioral of Zero is

begin
	s<=!op;
	
end architecture behavioral;