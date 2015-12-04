-- register_1
-- A 1-bit register.

library ieee; 
use ieee.std_logic_1164.all;
library work;


entity register_1 is
    port(
        enable, clk, d, reset: in std_logic;
        q: out std_logic
    );
end entity;


architecture behaviorial of register_1 is
begin
    clock_process: process(clk)
    begin
        if rising_edge(clk) then
            if reset = '1' then
                q <= '0';
            elsif enable = '1' then
                q <= d;
            end if;
        end if;
    end process;
end;
