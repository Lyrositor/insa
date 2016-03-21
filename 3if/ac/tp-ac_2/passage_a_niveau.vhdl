-- User-Encoded State Machine

library ieee;
use ieee.std_logic_1164.all;
library work;

entity passage_a_niveau is
    port(
        clock: in std_logic;
        reset: in std_logic;
        capteur_droite: in std_logic;
        capteur_gauche: in std_logic;
        ampoule: out std_logic;
        alert: out std_logic
    );
end entity;

architecture rtl of passage_a_niveau is
    -- a type declaration to make the following easier to read
    subtype state is std_logic_vector(2 downto 0);

    -- State encoding:
    constant pdt: state := "000";
    constant tvdd: state := "001";
    constant tvdd2: state := "010";
    constant tvdg: state := "101";
    constant tvdg2: state := "110";
    constant cata: state := "111";

    signal current_state, next_state: state;
begin
    -- transition function --
    next_state <= 
        pdt when current_state = pdt and capteur_gauche = '0' and capteur_droite = '0' else
        tvdd when current_state = pdt and capteur_gauche = '0' and capteur_droite = '1' else
        tvdg when current_state = pdt and capteur_gauche = '1' and capteur_droite = '0' else

        tvdd when current_state = tvdd and capteur_gauche = '0' else
        tvdd2 when current_state = tvdd and capteur_gauche = '1' else

        tvdd2 when current_state = tvdd2 and capteur_gauche = '1' else
        pdt when current_state = tvdd2 and capteur_gauche = '0' else
        
        tvdg when current_state = tvdg and capteur_droite = '0' else
        tvdg2 when current_state = tvdg and capteur_droite = '1' else

        tvdg2 when current_state = tvdg2 and capteur_droite = '1' else
        pdt when current_state = tvdg2 and capteur_droite = '0' else
        
        cata; -- all the other cases

    -- output function  -- 
    ampoule <= '0' when current_state = pdt else '1';
    
    -- the state register --
    process (clock)
    begin
        if (rising_edge(clock)) then
            if (current_state = cata) then
                alert <= '1';
            else
                alert <= '0';
            end if;

            if (reset = '1') then
                current_state <= pdt; --initial state
            else
                current_state <= next_state;
            end if;
        end if; 
    end process;
end architecture;
