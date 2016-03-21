

----------------------------------------------------------------------
---  Processor
----------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.all;
use IEEE.Numeric_Std.all;

entity processor is
    port (
        rst     : in  std_logic;
        ck      : in  std_logic;
        we      : out  std_logic; -- write enable
        address : out  std_logic_vector(7 downto 0);
        datain  : in  std_logic_vector(7 downto 0);
        dataout : out std_logic_vector(7 downto 0)
    );
end entity;  

architecture rtl of processor is
    subtype state is std_logic_vector(1 downto 0);

    component register_n is
        generic(n: integer);
        port(
            clk, enable, reset: in std_logic;
            d: in std_logic_vector(n-1 downto 0);
            q: out std_logic_vector(n-1 downto 0)
        );
    end component;
    
    constant fetch: state := "00";
    constant decode: state := "01";
    constant goto: state := "10";
    
    constant i_goto: std_logic_vector := "01111111";
    
    signal pcwe: std_logic;
    signal irwe: std_logic;
    signal pcq_to_adder: std_logic_vector(7 downto 0);
    signal adder_to_pcd: std_logic_vector(7 downto 0);
    signal instruction: std_logic_vector(7 downto 0);
    signal current_state, next_state: state;
begin
    pc: register_n
        generic map(n => 8)
        port map(
            clk => ck,
            enable => pcwe,
            reset => rst,
            d => adder_to_pcd,
            q => pcq_to_adder
        );

    ir: register_n
        generic map(n => 8)
        port map(
            clk => ck,
            enable => irwe,
            reset => rst,
            d => datain,
            q => instruction
        );
    
    next_state <= 
        goto when current_state = fetch and instruction = i_goto else
        decode when current_state = fetch else
        fetch when current_state = goto else
        fetch when current_state = decode else
        fetch; 
    address <= pcq_to_adder;
    pcwe <= '1' when current_state = decode or current_state = goto else '0';
    irwe <= '1';
    we <= '0';
    
    process (ck)
    begin
        if (current_state = goto) then
            adder_to_pcd <= datain;
        else
            adder_to_pcd <= std_logic_vector(unsigned(pcq_to_adder) + 1);
        end if;
        if (rising_edge(ck)) then
            if (rst = '1') then
                current_state <= fetch;
            else
                current_state <= next_state;
            end if;
        end if; 
    end process;
end architecture rtl;
