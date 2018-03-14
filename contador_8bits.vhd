
library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;


entity contador_8bits is
	Port(	Reloj		: IN	std_logic;
			Reset    : IN  std_logic;
			Salida		: OUT	std_logic_vector(7 downto 0));
end contador_8bits;

architecture funcional of contador_8bits IS
signal Contador : std_logic_vector(7 downto 0); --valores 0 a 255;
begin
	process (Reloj, Reset)
	begin
		if Reset = '1' then Contador <= "00000000";
		elsif Reloj'event AND Reloj = '1' then		
			Contador <= Contador + 1;
		end if;
	end process;
	Salida <= Contador;
end funcional;
