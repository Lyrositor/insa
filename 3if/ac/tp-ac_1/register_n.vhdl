-- register_1
-- An N-bit register.

library ieee; 
use ieee.std_logic_1164.all;
library work;

entity register_n is
    generic(n: integer);
    port(
        clk, enable, reset: in std_logic;
        d: in std_logic_vector(n-1 downto 0);
        q: out std_logic_vector(n-1 downto 0)
    );
end entity;

architecture rtl of register_n is
    component register_1 is
        port(
            enable, clk, d, reset: in std_logic;
            q: out std_logic
        );
    end component;
begin
    addloop: 
    for i in 0 to n-1 generate  
    begin   
        register_1_instance: register_1 port map(  
            clk => clk, 
            d => d(i),
            reset => reset,
            enable => enable,
            q => q(i)
        );  
    end generate;
end architecture;
