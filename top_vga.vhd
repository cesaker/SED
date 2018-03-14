
-- Descripción que visualiza franjas de colores en un monitor VGA
--
-- Basado en ejemplo de Hamblen, J.O., Hall T.S., Furman, M.D.:
-- Rapid Prototyping of Digital Systems : SOPC Edition, Springer 2008.
-- (Capítulo 10) 


LIBRARY IEEE;
USE  IEEE.STD_LOGIC_1164.all;
USE IEEE.STD_LOGIC_ARITH.all;
USE  IEEE.STD_LOGIC_UNSIGNED.all;
LIBRARY lpm;
USE lpm.lpm_components.ALL;


ENTITY top_vga IS

PORT(	
     	clock			: IN STD_LOGIC;
		vga_red			: OUT STD_LOGIC;
		vga_green		: OUT STD_LOGIC;
		vga_blue		: OUT STD_LOGIC;
		vga_blank		: OUT STD_LOGIC;
		vga_hs			: OUT STD_LOGIC;
		vga_vs			: OUT STD_LOGIC;
		vga_clk			: OUT STD_LOGIC
		);

END top_vga;

ARCHITECTURE funcional OF top_vga IS


	COMPONENT vga_PLL
		PORT(
			inclk0		: IN STD_LOGIC  := '0';
			c0			: OUT STD_LOGIC );
	END COMPONENT;
	
	COMPONENT controlador_vga_640_x_480
		PORT(	
			clock_25Mhz		: 	IN	STD_LOGIC;
			red,green,blue	: 	IN	STD_LOGIC;
			vga_red			:	OUT	STD_LOGIC;
			vga_green		:	OUT	STD_LOGIC;
			vga_blue		:	OUT	STD_LOGIC;
			vga_blank		:	OUT	STD_LOGIC;
			vga_hs			:	OUT STD_LOGIC;
			vga_vs			:	OUT STD_LOGIC;
			vga_clk			:	OUT STD_LOGIC;
			pixel_y			:	OUT STD_LOGIC_VECTOR(9 DOWNTO 0);
			pixel_x		:	OUT	STD_LOGIC_VECTOR(9 DOWNTO 0));		
	END COMPONENT;
	


SIGNAL clock_25MHz : STD_LOGIC;
SIGNAL Red_Data, Green_Data, Blue_Data : STD_LOGIC;
SIGNAL pixel_x, pixel_y	: STD_LOGIC_VECTOR(9 DOWNTO 0);



BEGIN

Red_data   <= pixel_y(7);
Green_data <= pixel_y(6);
Blue_data  <= pixel_y(5);


	-- PLL para generar el reloj de 25 MHz
PLL: vga_pll PORT MAP (
		inclk0 => clock,
		c0 => clock_25Mhz);
		

	-- Controlador de la VGA
VGA:  controlador_vga_640_x_480 PORT MAP (	
		clock_25Mhz	=> clock_25MHz,
		red => red_data,
		green => green_data,
		blue => blue_data,	
		vga_red	=> vga_red,
		vga_green => vga_green,
		vga_blue => vga_blue,
		vga_blank => vga_blank,
		vga_hs => vga_hs, 
		vga_vs => vga_vs, 
		vga_clk	=> vga_clk,
		pixel_y => pixel_y, 
		pixel_x => pixel_x);		
			
			 	

END funcional;

