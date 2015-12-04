-- testbench_counter
-- A suite of tests for an 8-bit counter.

library ieee; 
use ieee.std_logic_1164.all;
library work;


entity testbench_counter is
end entity;


architecture behaviorial of testbench_counter is
    component counter is
        generic(n: integer);
        port(
            clk, reset: in std_logic;
            count: out std_logic_vector(n-1 downto 0)
        );
    end component;

    component clock_generator is
       port(clk: out std_logic);
    end component;

    signal clk: std_logic;
    signal reset: std_logic;
    signal count: std_logic_vector(7 downto 0);

begin 
    uut: counter
        generic map(n => 8)
        port map(clk => clk, reset => reset, count => count);

    clock_generator_instance: clock_generator
        port map(clk => clk);

    test_process: process 
    begin
        reset <= '1';
        wait for 1 ns;
        reset <= '0';
        wait for 255 ns;
	end process;
end;
