----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    17:58:07 11/06/2016 
-- Design Name: 
-- Module Name:    rom - Behavioral 
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

entity rom is
PORT (
	ADRESA : in std_logic_vector (2 downto 0);
	PODACI : out std_logic_vector (31 downto 0)
);
end rom;

architecture Behavioral of rom is
TYPE romtabela IS ARRAY (0 to 7) of std_logic_vector (31 downto 0);
CONSTANT rompodaci : romtabela := (
x"0E500000",
x"0E600000",
x"0E700000",
x"0E800000",
x"0E900000",
x"0EA00000",
x"0EF00000",
x"0ED00000"
);
begin

PROCESS (ADRESA)
BEGIN
PODACI <= rompodaci (conv_integer(adresa));
END PROCESS;
end Behavioral;

