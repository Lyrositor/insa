

----------------------------------------------------------------------
---  A synchronous memory
----------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.all;
use IEEE.Numeric_Std.all;

entity memory256x8 is
  port (
    ck   : in  std_logic;
    we      : in  std_logic; -- write enable
    address : in  std_logic_vector(7 downto 0);
    datain  : in  std_logic_vector(7 downto 0);
    dataout : out std_logic_vector(7 downto 0)
  );
end entity memory256x8;

architecture rtl of memory256x8 is
  type ram_array is array (0 to 255) of std_logic_vector(7 downto 0);
  -- this ram has its first two bytes initialized, you may add more 
  signal ram : ram_array := (
    x"20", x"21", x"22", x"23", x"24", x"7F", x"01",
    others => x"00");

begin

  ram_process: process(ck) is
  begin
    if rising_edge(ck) then
      -- note that the two following statements are sequential
      if we = '1' then -- write enable
        ram(to_integer(unsigned(address))) <= datain;
      end if;
      dataout <= ram(to_integer(unsigned(address)));
    end if;
  end process ram_process;


end architecture rtl;

