
--------------------------------------------------------------------------------
-- Company: 
-- Engineer:
--
-- Create Date:   17:52:44 11/06/2016
-- Design Name:   mux2u12bit
-- Module Name:   C:/Xilinx92i/LV4_kombinacioneKomponente/mux2u12bittb.vhd
-- Project Name:  LV4_kombinacioneKomponente
-- Target Device:  
-- Tool versions:  
-- Description:   
-- 
-- VHDL Test Bench Created by ISE for module: mux2u12bit
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

ENTITY mux2u12bittb_vhd IS
END mux2u12bittb_vhd;

ARCHITECTURE behavior OF mux2u12bittb_vhd IS 

	-- Component Declaration for the Unit Under Test (UUT)
	COMPONENT mux2u12bit
	PORT(
		I00 : IN std_logic;
		I01 : IN std_logic;
		I02 : IN std_logic;
		I03 : IN std_logic;
		I10 : IN std_logic;
		I11 : IN std_logic;
		I12 : IN std_logic;
		I13 : IN std_logic;
		S : IN std_logic;          
		Y0 : OUT std_logic;
		Y1 : OUT std_logic;
		Y2 : OUT std_logic;
		Y3 : OUT std_logic
		);
	END COMPONENT;

	--Inputs
	SIGNAL I00 :  std_logic := '0';
	SIGNAL I01 :  std_logic := '0';
	SIGNAL I02 :  std_logic := '0';
	SIGNAL I03 :  std_logic := '0';
	SIGNAL I10 :  std_logic := '0';
	SIGNAL I11 :  std_logic := '0';
	SIGNAL I12 :  std_logic := '0';
	SIGNAL I13 :  std_logic := '0';
	SIGNAL S :  std_logic := '0';

	--Outputs
	SIGNAL Y0 :  std_logic;
	SIGNAL Y1 :  std_logic;
	SIGNAL Y2 :  std_logic;
	SIGNAL Y3 :  std_logic;

BEGIN

	-- Instantiate the Unit Under Test (UUT)
	uut: mux2u12bit PORT MAP(
		I00 => I00,
		I01 => I01,
		I02 => I02,
		I03 => I03,
		I10 => I10,
		I11 => I11,
		I12 => I12,
		I13 => I13,
		S => S,
		Y0 => Y0,
		Y1 => Y1,
		Y2 => Y2,
		Y3 => Y3
	);

	tb : PROCESS
	BEGIN

		-- Wait 100 ns for global reset to finish
		wait for 100 ns;

		-- Place stimulus here

		wait; -- will wait forever
	END PROCESS;

END;
