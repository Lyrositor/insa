-- counter
-- An N-bit counter, with reset functionality.

library ieee;
use ieee.std_logic_1164.all;
library work;


entity counter is
    generic(n: integer);
    port(
        clk, reset: in std_logic;
        count: out std_logic_vector(n-1 downto 0)
    );
end entity;


architecture behaviorial of counter is
    component adder is
        generic(n: integer);
        port(
            x: in std_logic_vector(n-1 downto 0);
            y: in std_logic_vector(n-1 downto 0);
            cin: in std_logic;
            s: out std_logic_vector(n-1 downto 0);
            cout: out std_logic
        );
    end component;

    component register_n is
        generic(n: integer);
        port(
            clk, enable: in std_logic;
            d: in std_logic_vector(n-1 downto 0);
            q: out std_logic_vector(n-1 downto 0)
        );
    end component;

    signal adder_to_register: std_logic_vector(n-1 downto 0);
    signal cout: std_logic;
    signal enable: std_logic;
    signal temp_count: std_logic_vector(n-1 downto 0);
    signal zero: std_logic_vector(n-1 downto 0);
    signal one: std_logic_vector(n-1 downto 0);
begin
    zero <= (n-1 downto 0 => '0');
    one <= zero;
    one(0) <= '1';
    
    adder_instance: adder
        generic map(n => n)
        port map(x => temp_count, y => one, s => adder_to_register, cin => '0', cout => cout);
    
    register_bits_instance: register_n
        generic map(n => n)
        port map(clk => clk, enable => enable, d => adder_to_register, q => temp_count);

    clock_process: process(clk)
    begin
        if rising_edge(clk) then
            if reset = '1' then
                temp_count <= zero;
                enable <= '0';
            else
                enable <= '1';
            end if;
        end if;
        count <= temp_count;
    end process;
end;
