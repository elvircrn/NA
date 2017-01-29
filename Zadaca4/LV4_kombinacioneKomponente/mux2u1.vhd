----------------------------------------------------------------------------------
-- Company: ETF
-- Engineer: H
-- 
-- Create Date:    17:24:21 11/06/2016 
-- Design Name: 
-- Module Name:    mux2u1 - Behavioral 
-- Project Name: 
-- Target Devices: 
-- Tool versions: 
-- Description: 
--
-- Dependencies: 
--
-- Revision: 
-- Revision 0.01 - File Created
-- Additional Comments: 
--
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

---- Uncomment the following library declaration if instantiating
---- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity mux2u1 is
	PORT (
		I0 : in std_logic;
		I1 : in std_logic;
		 S : in std_logic;
		 Y : out std_logic
	);
end mux2u1;

architecture Behavioral of mux2u1 is

begin

Y <= I0 when S='0' else
	  I1 when S='1' else
	  'Z';
end Behavioral;

