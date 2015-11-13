define print_t
  printf "t[p1] = %d, t[p2] = %d\n", t[p1], t[p2]
end

break exchange 

run

step
print_t
step
print_t
step
print_t
clear exchange
continue

