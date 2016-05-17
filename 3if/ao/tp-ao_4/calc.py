ppm = lambda f: abs((round(f*0.010)/(f*0.010) - 1) * 1000000)
s_day = lambda f: ppm(f) * 3600 * 24 / 1000000

print("ACLK: {:.2f} ppm, {:.2f} seconds/day".format(ppm(32768), s_day(32768)))
print("SMCLK: {:.2f} ppm, {:.2f} seconds/day".format(ppm(32768*32), s_day(32768*32)))