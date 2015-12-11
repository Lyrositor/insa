-- This testbench should work unmodified.

library ieee; 
use ieee.std_logic_1164.all;
library work;

entity testbench_diviseur is
end entity;

architecture behaviorial of testbench_diviseur is

  component diviseur is
  port 
  (
    ck  : in std_logic;
    go  : in std_logic;
    n   : in std_logic_vector(7 downto 0);
    p   : in std_logic_vector(7 downto 0);
    q   : out std_logic_vector(7 downto 0);
    ok  : out std_logic
  );
  end component;  

  signal ck, go, ok: std_logic;
  signal n, p, q: std_logic_vector(7 downto 0);

begin 

  --  Instantiate the Unit Under Test (UUT)
  uut: diviseur port map (
    ck => ck,
    go => go,
    n => n,
    p =>p,
    q =>q,
    ok => ok);


  -- a clock process
  clock_process : process 
   begin
     ck <= '1';
     wait for 0.5 ns; 
     ck <= '0';
     wait for 0.5 ns; 
   end process;
  
  
  -- A test process
   test_process :process 
   begin
     n <= "00011001"; -- 25
     p <= "00000101"; -- 5
     go <= '0';
     wait for 2.2 ns;
     go <= '1';
     wait for 100 ns;
   end process;


end behaviorial;
