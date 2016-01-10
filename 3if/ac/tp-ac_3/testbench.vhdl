

---------  Test bench -----------------
library ieee; 
use ieee.std_logic_1164.all;
library work;

entity testbench is
end entity;

architecture behaviorial of testbench is
  component memory256x8 is
  port (
    ck      : in  std_logic;
    we      : in  std_logic;
    address : in  std_logic_vector(7 downto 0);
    datain      : in  std_logic_vector(7 downto 0);
    dataout      : out std_logic_vector(7 downto 0)
  );
  end component;
  component processor is
  port (
    rst     : in  std_logic;
    ck      : in  std_logic;
    we      : out  std_logic;
    address : out  std_logic_vector(7 downto 0);
    datain  : in  std_logic_vector(7 downto 0);
    dataout : out std_logic_vector(7 downto 0)
  );
  end component;  

  signal a,dp2m,dm2p : std_logic_vector(7 downto 0);
  signal ck, we,reset : std_logic;
begin 

  --  Instantiate the Unit Under Test (UUT)
  mem:  memory256x8
    port map ( ck => ck, we => we, address => a, datain => dp2m, dataout => dm2p) ;
  proc: processor
    port map ( rst => reset, ck => ck, we => we, address => a, datain => dm2p, dataout => dp2m) ;

  
  clock_process : process 
   begin
     ck <= '1';
     wait for 0.5 ns; 
     ck <= '0';
     wait for 0.5 ns; 
   end process;


  reset_process : process 
  begin
    reset <= '1' ;
    wait for 1.1 ns;
    reset <= '0' ;

    wait;
   end process;

end;
