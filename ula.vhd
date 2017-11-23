library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

ENTITY ULA IS PORT(
    a   : IN STD_LOGIC_VECTOR(3 DOWNTO 0); -- input
    b   : IN STD_LOGIC_VECTOR(3 DOWNTO 0); -- input
    addsub   : IN STD_LOGIC_VECTOR(3 DOWNTO 0); -- input
    op   : IN STD_LOGIC_VECTOR(3 DOWNTO 0); -- input
    aluResult   : OUT STD_LOGIC_VECTOR(3 DOWNTO 0); -- output
    OVFL : OUT STD_LOGIC_VECTOR(3 DOWNTO 0);
    Zer : OUT STD_LOGIC_VECTOR(3 DOWNTO 0)
);
END ULA;

architecture Behavioral of ULA is

signal aux;
signal aux2;
signal aux3;
signal aux4;
	


component Cout  is
	port (
	a   : IN STD_LOGIC_VECTOR(3 DOWNTO 0); -- input
    b   : IN STD_LOGIC_VECTOR(3 DOWNTO 0); -- input
    addsub   : IN STD_LOGIC_VECTOR(3 DOWNTO 0); -- input
    resultado   : IN STD_LOGIC_VECTOR(3 DOWNTO 0); -- input
    s   : OUT STD_LOGIC_VECTOR(3 DOWNTO 0) -- output
	);
end component;

component Zero is
	port (
	op   : IN STD_LOGIC_VECTOR(3 DOWNTO 0); -- input
    s   : OUT STD_LOGIC_VECTOR(3 DOWNTO 0) -- output
		
	);
end component;

component  AddSub is
	port (
	op   : IN STD_LOGIC_VECTOR(3 DOWNTO 0); -- input
    s   : OUT STD_LOGIC_VECTOR(3 DOWNTO 0) -- output
	);
end component ;

component  SomaSub is
	port (
	a   : IN STD_LOGIC_VECTOR(3 DOWNTO 0); -- input
    b   : IN STD_LOGIC_VECTOR(3 DOWNTO 0); -- input
    addsub   : IN STD_LOGIC_VECTOR(3 DOWNTO 0); -- input
    op   : IN STD_LOGIC_VECTOR(3 DOWNTO 0); -- input
    s   : OUT STD_LOGIC_VECTOR(3 DOWNTO 0) -- output
	);
end component ;

begin
	adds: AddSub(op,aux);
	somas: SomaSub(a,b,aux,op,aux2);
	z: Zero(aux2,aux4);
	co: Cout(a,b,aux,aux2,aux3);

aluResult <= aux2;
OVFL <= aux3;
Zer <= aux4;

end architecture Behavioral;