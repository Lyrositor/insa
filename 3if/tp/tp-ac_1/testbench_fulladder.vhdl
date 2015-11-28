library ieee; 
use ieee.std_logic_1164.all;
library work;


entity testbench_fulladder is
end entity;


architecture behaviorial of testbench_fulladder is
    component fulladder is
        port(
            x, y, cin: in std_logic;
            cout, sum: out std_logic
        );
    end component;

    signal testx, testy, testcin, testcout, testsum: std_logic;
begin 
    uut: fulladder port map(
        x => testx,
        y => testy,
        cin => testcin,
        sum => testsum,
        cout => testcout 
    );      

    test_process: process 
    begin
        testx <= '0';
        testy <= '0';
        testcin <= '0';
        wait for 1 ns;  
        testx <= '0';
        testy <= '0';
        testcin <= '1';
        wait for 1 ns;
        testx <= '0';
        testy <= '1';
        testcin <= '0';
        wait for 1 ns;
        testx <= '0';
        testy <= '1';
        testcin <= '1';
        wait for 1 ns;
        testx <= '1';
        testy <= '0';
        testcin <= '0';
        wait for 1 ns;
        testx <= '1';
        testy <= '0';
        testcin <= '1';
        wait for 1 ns;
        testx <= '1';
        testy <= '1';
        testcin <= '0';
        wait for 1 ns;
        testx <= '1';
        testy <= '1';
        testcin <= '1';
        wait for 1 ns;
    end process;
end;
