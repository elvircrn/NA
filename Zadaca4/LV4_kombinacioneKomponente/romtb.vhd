
--------------------------------------------------------------------------------
-- Company: 
-- Engineer:
--
-- Create Date:   18:30:42 11/06/2016
-- Design Name:   rom
-- Module Name:   C:/Xilinx92i/LV4_kombinacioneKomponente/romtb.vhd
-- Project Name:  LV4_kombinacioneKomponente
-- Target Device:  
-- Tool versions:  
-- Description:   
-- 
-- VHDL Test Bench Created by ISE for module: rom
--
-- Dependencies:
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
--
-- Notes: 
-- This testbench has been automatically generated using types std_logic and
-- std_logic_vector for the ports of the unit under test.  Xilinx recommends 
-- that these types always be used for the top-level I/O of a design in order 
-- to guarantee that the testbench will bind correctly to the post-implementation 
-- simulation model.
--------------------------------------------------------------------------------
LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.std_logic_unsigned.all;
USE ieee.numeric_std.ALL;

ENTITY romtb_vhd IS
END romtb_vhd;

ARCHITECTURE behavior OF romtb_vhd IS 

	-- Component Declaration for the Unit Under Test (UUT)
	COMPONENT rom
	PORT(
		ADRESA : IN std_logic_vector(2 downto 0);          
		PODACI : OUT std_logic_vector(31 downto 0)
		);
	END COMPONENT;

	--Inputs
	SIGNAL ADRESA :  std_logic_vector(2 downto 0) := (others=>'0');

	--Outputs
	SIGNAL PODACI :  std_logic_vector(31 downto 0);

BEGIN

	-- Instantiate the Unit Under Test (UUT)
	uut: rom PORT MAP(
		ADRESA => ADRESA,
		PODACI => PODACI
	);

	tb : PROCESS
	BEGIN

		-- Wait 100 ns for global reset to finish
		wait for 100 ns;

		ADRESA <= "111";
		wait for 10 ns;
		assert (PODACI = x"0ED00000") report "Greska 1!" severity warning;
		-- Place stimulus here

		wait; -- will wait forever
	END PROCESS;

END;
