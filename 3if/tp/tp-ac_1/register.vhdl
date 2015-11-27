library ieee; 
use ieee.std_logic_1164.all;
library work;


entity uregister is
   port (enable, clk, d: in std_logic;
         q: out std_logic);
end entity;


architecture behaviorial of uregister is
begin
    clock_process : process(clk)
    begin
        if rising_edge(clk) then
            if enable = '1' then
                q <= d;
            end if;
        end if;
    end process;
end;

