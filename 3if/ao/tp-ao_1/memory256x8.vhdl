

----------------------------------------------------------------------
---  An asynchronous memory
----------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.all;
use IEEE.Numeric_Std.all;

entity memory256x8 is
  port (
    ck   : in  std_logic;
    we      : in  std_logic;
    address : in  std_logic_vector(7 downto 0);
    datain  : in  std_logic_vector(7 downto 0);
    dataout : out std_logic_vector(7 downto 0)
  );
end entity memory256x8;

architecture rtl of memory256x8 is
  type ram_array is array (0 to 255) of std_logic_vector(7 downto 0);
  signal ram : ram_array := (
    "01001100", "00010001",
    "01001101", "00000111",
    "00110010", "11100010",
    "01000010", "10011111",
  
    others => "UUUUUUUU");

begin
  dataout <= "UUUUUUUU" when address="UUUUUUUU"
             else ram(to_integer(unsigned(address))) after 0.2 ns ;

  ram_process: process(ck) is
  begin
    if rising_edge(ck) then
      if we = '1' then
        ram(to_integer(unsigned(address))) <= datain;
      end if;
    end if;
  end process ram_process;
end architecture rtl;


