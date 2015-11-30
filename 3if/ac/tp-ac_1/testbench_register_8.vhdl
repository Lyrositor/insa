-- testbench_register_8
-- A suite of tests for an 8-bit register.

library ieee; 
use ieee.std_logic_1164.all;
library work;


entity testbench_register_8 is
end entity;


architecture behaviorial of testbench_register_8 is
    component register_n is
        generic(n: integer);
        port(
            clk, enable: in std_logic;
            d: in std_logic_vector(n-1 downto 0);
            q: out std_logic_vector(n-1 downto 0)
        );
    end component;
    
    signal clk: std_logic;
    signal d: std_logic_vector(7 downto 0);
    signal enable: std_logic;
    signal q: std_logic_vector(7 downto 0);

    constant clock_period : time := 5 ns;
begin 
    uut: register_n
        generic map(n => 8)
        port map(clk => clk, d => d, enable => enable, q => q);

    test_process: process 
    begin
        d <= "01010010";

        enable <= '0';        
        clk <= '0';
        wait for clock_period/2;
        clk <= '1';
        wait for clock_period/2;
        
        enable <= '1';
        clk <= '0';
        wait for clock_period/2;
        clk <= '1';
        wait for clock_period/2;
        
        
        d <= "10000110";

        enable <= '0';        
        clk <= '0';
        wait for clock_period/2;
        clk <= '1';
        wait for clock_period/2;
        
        enable <= '1';
        clk <= '0';
        wait for clock_period/2;
        clk <= '1';
        wait for clock_period/2;
    end process;
end;

