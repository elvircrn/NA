----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    17:28:00 11/06/2016 
-- Design Name: 
-- Module Name:    mux4u1 - Behavioral 
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

entity mux4u1 is
PORT(
	I0 : in std_logic;
	I1 : in std_logic;
	I2 : in std_logic;
	I3 : in std_logic;
	S0 : in std_logic (1 downto 0);
	Y : out std_logic;
);
end mux4u1;

architecture Behavioral of mux4u1 is

begin

Y <= I0 when S="00" else
     I1 when S="01" else
	  I2 when S="10" else
	  I3 when S="11" else
	  'Z';

end Behavioral;

