library ieee; 
use ieee.std_logic_1164.all;
library work;

entity testbench_passage_a_niveau is
end entity;

architecture behaviorial of testbench_passage_a_niveau is
    component passage_a_niveau is
        port(
            clock: in std_logic;
            reset: in std_logic;
            capteur_droite: in std_logic;
            capteur_gauche: in std_logic;
            ampoule: out std_logic;
            alert: out std_logic
        );
    end component;  

  signal clock, reset, capteur_droite, capteur_gauche, ampoule, alert: std_logic;
begin 
    --  Instantiate the Unit Under Test (UUT)
    uut: passage_a_niveau port map(
        clock => clock,
        reset => reset,
        capteur_droite => capteur_droite,
        capteur_gauche => capteur_gauche,
        ampoule => ampoule,
        alert => alert
    );      

    -- a clock process
    clock_process: process 
    begin
        clock <= '1';
        wait for 0.5 ns; 
        clock <= '0';
        wait for 0.5 ns; 
    end process;

    -- A test process
    test_process: process 
    begin
        reset <= '1';
        wait for 2.3 ns;
        reset <= '0';
        capteur_gauche <= '0';
        capteur_droite <= '0';
        wait for 12.3 ns;
        
        -- un train court vient de droite
        capteur_droite <= '1';
        wait for 10 ns;
        capteur_droite <= '0';
        wait for 5 ns;
        capteur_gauche <= '1';
        wait for 10 ns;
        capteur_gauche <= '0';
        wait for 20 ns;

        -- un train long vient de droite
        capteur_droite <= '1';
        wait for 20 ns;
        capteur_gauche <= '1';
        wait for 10 ns;
        capteur_droite <= '0';
        wait for 20 ns;
        capteur_gauche <= '0';
        wait for 20 ns;
        
        -- deux trains rentrent en collision
        capteur_droite <= '1';
        capteur_gauche <= '1';
        wait for 10 ns;
        capteur_droite <= '0';
        capteur_gauche <= '0';
        wait for 20 ns;
    end process;

end behaviorial;
