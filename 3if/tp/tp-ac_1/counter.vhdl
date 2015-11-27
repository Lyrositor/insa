library ieee; 
use ieee.std_logic_1164.all;
library work;


-- Counter (N bits) declaration
entity counter is
    generic (n: integer);
    port (clk, reset: in std_logic;
          count: out std_logic_vector(n-1 downto 0));
end entity;


architecture behaviorial of counter is
    -- Register (N bits) declaration
    component register_nbits is
        generic (n: integer);
        port (clk, enable: in std_logic;
              d: in std_logic_vector(n-1 downto 0);
              q: out std_logic_vector(n-1 downto 0));
    end component;

    -- Adder (N bits) declarations
    component adder is
        generic (n: integer);
        port(x: in std_logic_vector(n-1 downto 0);
             y: in std_logic_vector(n-1 downto 0);
             cin: in std_logic;
             s: out std_logic_vector(n-1 downto 0);
             cout: out std_logic );
    end component;

    signal d: std_logic_vector(n-1 downto 0);
    signal x: std_logic_vector(n-1 downto 0);
    signal cout: std_logic;
    signal zero: std_logic_vector(n-1 downto 0);

    constant enable : std_logic := '1';
begin

    zero <= (n-1 downto 0 => '0');
    
    register_bits_instance: register_nbits
        generic map (n => n)
        port map (clk => clk, d => d, enable => enable, q => x);

    adder_instance: adder
        generic map ( n => n )
        port map (x => x, y => zero, s => count, cin => '1', cout => cout);

    clock_process: process(clk)
    begin
        if rising_edge(clk) then
            if reset = '1' then
                d <= zero;
            else
                d <= count;
            end if;
        end if;
    end process;
end;


