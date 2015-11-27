library ieee; 
use ieee.std_logic_1164.all;
library work;

entity register_nbits is
    generic (n: integer);
    port (clk, enable: in std_logic;
          d: in std_logic_vector(n-1 downto 0);
          q: out std_logic_vector(n-1 downto 0));
end entity;

architecture rtl of register_nbits is
    component uregister is
        port (enable, clk, d: in std_logic;
              q: out std_logic);
    end component;
begin
    addloop: 
    for i in 0 to n-1 generate  
    begin   
        uregisterinstance: uregister port map (  
            clk => clk, 
            d => d(i),
            enable => enable,
            q => q(i)
        );  
    end generate;
end architecture;
