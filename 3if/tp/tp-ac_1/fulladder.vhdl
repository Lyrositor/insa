---------  A full adder ------------------

library ieee; 
use ieee.std_logic_1164.all;
library work;


entity fulladder is
    port(
        x, y, cin: in std_logic;
        cout, sum: out std_logic
    );
end fulladder;


architecture rtl of fulladder is
begin
    sum <= x xor y xor cin after 15 ps;
    cout <= (x and y) or (cin and x) or (cin and y) after 10 ps;
end rtl;
