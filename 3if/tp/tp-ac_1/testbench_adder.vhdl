-- testbench_adder
-- A suite of tests for an 8-bit adder.

library ieee; 
use ieee.std_logic_1164.all;
library work;

entity testbench_adder is
end entity;

architecture behaviorial of testbench_adder is
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

  signal x, y, s: std_logic_vector(7 downto 0);
  signal cin, cout: std_logic;
begin 
    uut: adder
        generic map(n => 8)
        port map(x => x, y => y, s => s, cin => cin, cout => cout);

    test_process: process 
    begin
        cin <= '0';
        x <= "00000000";
        y <= "00000000"; 
        wait for 10 ns;  
        cin <= '0';
        x <= "11111111"; 
        y <= "00000001"; 
        wait for 10 ns;  
        cin <= '1';
        x <= "11101011"; 
        y <= "01010001"; 
        wait for 10 ns;  
        cin <= '0';
        x <= "11111100"; 
        y <= "11000001"; 
        wait for 10 ns;  
        cin <= '1';
        x <= "11111011"; 
        y <= "00100001"; 
        wait for 10 ns;  
        cin <= '0';
        x <= "01111111"; 
        y <= "00000001"; 
        wait for 10 ns;  
    end process;
end;
