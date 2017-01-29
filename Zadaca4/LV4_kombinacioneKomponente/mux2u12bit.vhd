----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    17:34:45 11/06/2016 
-- Design Name: 
-- Module Name:    mux2u12bit - Behavioral 
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

entity mux2u12bit is

PORT (
	I00, I01, I02, I03 : in std_logic;
	I10, I11, I12, I13 : in std_logic;
	                 S : in std_logic;
		 Y0, Y1, Y2, Y3 : out std_logic
);

end mux2u12bit;

architecture Behavioral of mux2u12bit is


COMPONENT mux2u1 IS 
PORT (
	I0 : in std_logic;
	I1 : in std_logic;
	 S : in std_logic;
	 Y : out std_logic
);
END COMPONENT;

begin

mux2u1_0 : mux2u1 PORT MAP (I13, I03, S, Y3);
mux2u1_1 : mux2u1 PORT MAP (I12, I02, S, Y2);
mux2u1_2 : mux2u1 PORT MAP (I11, I01, S, Y1);
mux2u1_3 : mux2u1 PORT MAP (I10, I00, S, Y0);

end Behavioral;

