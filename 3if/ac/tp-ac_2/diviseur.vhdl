library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
library work;

entity diviseur is
    port (
        ck: in std_logic;
        go: in std_logic;
        n: in std_logic_vector(7 downto 0);
        p: in std_logic_vector(7 downto 0);
        q: out std_logic_vector(7 downto 0);
        ok: out std_logic
    );
end entity;

architecture rtl of diviseur is
    -- a type declaration to make the following easier to read
    subtype state is std_logic_vector(1 downto 0);

    -- State encoding:
    constant waiting: state := "00"; -- rem: wait is a reserved word...
    constant increment: state := "01";
    constant done1: state := "10";
    constant done2: state := "11";

    signal current_state, next_state: state;

    signal rN, rX, rP, rQ, newX, newQ: unsigned(7 downto 0);

    -- unsigned/signed is a std_logic_vector interpreted as an integer:
    -- we can use +, - and * on it. Defined in numeric_std
    signal diff: signed(8 downto 0); -- one bit more for the sign bit
    signal loadX, loadQ, loadN, loadP, resetX, resetQ, pp: std_logic;
begin -- Reminder: all that follows are parallel statements
------- Combinatorial parts of the datapath -------- 
    newX <= rX + rP; -- this + is defined in the numeric_std library
    q <= std_logic_vector(rQ - 1);
    newQ <= rQ + 1;

    -- comparison by subtracting, then observing the sign bit 
    -- we first cast each (unsigned) input into a signed,
    -- with sign bit 0 (the & is a concatenation)
    -- then perform the subtraction.
    diff <= signed('0' & rN) - signed('0' & newX); 
    pp <= not diff(8);

    -------- datapath registers --------
    -- the register for N
    process (ck)
    begin
        if (rising_edge(ck)) then
            if (loadN='1') then
                rN <= unsigned(N); 
            end if;
        end if; 
    end process;

    -- the register for X, it has a reset
    process (ck)
    begin
        if (rising_edge(ck)) then
            if (resetX = '1') then
                rX <= "00000000"; -- written like this, it is a synchronous reset
            elsif (loadX = '1') then
                rX <= newX; 
            end if;
        end if; 
    end process;

    -- the register for P
    process (ck)
    begin
        if (rising_edge(ck)) then
            if (loadP='1') then
                rP <= unsigned(P); 
            end if;
        end if; 
    end process;
    
    -- the register for Q, it has a reset
    process (ck)
    begin
        if (rising_edge(ck)) then
            if (resetQ = '1') then
                rQ <= "00000000";
            elsif (loadQ = '1') then
                rQ <= newQ; 
            end if;
        end if; 
    end process;

------------------ Now the automaton ------------------

    -- transition function -- 
    next_state <=
        waiting when go = '0' else
        
        increment when current_state = waiting and go = '1' else
        
        increment when current_state = increment and pp = '1' else
        done1 when current_state = increment and pp = '0' else
        
        done2 when current_state = done1;

    -- output function --
    loadN <= '1' when current_state = waiting else '0';
    loadP <= '1' when current_state = waiting else '0';
    resetX <= '1' when current_state = waiting else '0';
    resetQ <= '1' when current_state = waiting else '0';

    loadX <= '1' when current_state = increment else '0';
    loadQ <= '1' when current_state = increment else '0';
    
    ok <= '1' when current_state = done1 or current_state = done2 else '0';

    -- the state register --
    -- Since we use go as a reset, we do not strictly follow the specification of the
    -- TD, where go is allowed to go back to 0 during the computation.
    -- But then the TD misses the reset signal...
    process (ck)
    begin
        if (rising_edge(ck)) then
            if (go = '0') then -- here we use go as a reset, active low
                current_state <= waiting;
            else
                current_state <= next_state;
            end if;
        end if;
    end process;

end architecture;
