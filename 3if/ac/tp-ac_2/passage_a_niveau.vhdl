-- User-Encoded State Machine

library ieee;
use ieee.std_logic_1164.all;
library work;

entity passage_a_niveau is
  port 
  (
    clock   : in std_logic;
    reset   : in std_logic;
    capteur_droite    : in std_logic;
    capteur_gauche    : in std_logic;
    ampoule   : out std_logic
  );
  
end entity;

architecture rtl of passage_a_niveau is
  -- a type declaration to make the following easier to read
  subtype state is std_logic_vector(2 downto 0);
  -- State encoding:
  constant pdt   : state := "000";
  constant tvdd  : state := "001";
  constant tvdd2 : state := "010";
  constant tvdg  : state := "101";
  constant tvdg2 : state := "110";
  constant cata  : state := "111";

  signal current_state, next_state     : state;
  
  
begin
  -- transition function --
    next_state <= 
      pdt  when current_state = pdt and capteur_gauche = '0' and capteur_droite = '0'    else
      tvdd when current_state = pdt and capteur_gauche = '0' and capteur_droite = '1'    else
      tvdg when current_state = pdt and capteur_gauche = '1' and capteur_droite = '0'    else

      tvdd when current_state = tvdd and capteur_gauche = '0' and capteur_droite = '0'    else
      tvdd when current_state = tvdd and capteur_gauche = '0' and capteur_droite = '1'    else
      tvdd2 when current_state = tvdd and capteur_gauche = '1' and capteur_droite = '0'    else
      tvdd2 when current_state = tvdd and capteur_gauche = '1' and capteur_droite = '1'    else

      -- TODO: fill here 

      cata ; -- all the other cases

  -- output function  -- 
  ampoule <= '0' when current_state = pdt else '1';
    
  -- the state register --
  process (clock)
    begin
      if(rising_edge(clock)) then
        if (reset='1') then
          current_state <= pdt; --initial state
        else
          current_state <= next_state;
        end if;
      end if; 
  end process;

end architecture;









library ieee; 
use ieee.std_logic_1164.all;
library work;

entity testbench is
end entity;

architecture behaviorial of testbench is

  component passage_a_niveau is
   port   (
    clock   : in std_logic;
    reset   : in std_logic;
    capteur_droite    : in std_logic;
    capteur_gauche    : in std_logic;
    ampoule   : out std_logic  );
  end component;  

  signal clock, reset, capteur_droite, capteur_gauche, ampoule: std_logic;

begin 

  --  Instantiate the Unit Under Test (UUT)
  uut: passage_a_niveau port map (
    clock => clock,
    reset => reset,
    capteur_droite => capteur_droite,
    capteur_gauche => capteur_gauche,
    ampoule => ampoule    );      


  -- a clock process
  clock_process : process 
   begin
     clock <= '1';
     wait for 0.5 ns; 
     clock <= '0';
     wait for 0.5 ns; 
   end process;
  
  
  -- A test process
   test_process :process 
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
     
     -- ajoutez un test pour un train long, et un pour une catastrophe
   end process;


end behaviorial;
