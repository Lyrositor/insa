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

    signal clk: std_logic;
    signal reset: std_logic;
    signal count: std_logic_vector(7 downto 0);

    constant clock_period: time := 1 ns;
begin 
    uut: counter
        generic map(n => 8)
        port map(clk => clk, reset => reset, count => count);
    reset <= '0';

    test_process: process 
    begin
        clk <= '0';
        wait for clock_period/2;
        clk <= '1';
        wait for clock_period/2;
    end process;
end;
