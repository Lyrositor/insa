#!/usr/bin/env python

from __future__ import division
import argparse
import random

EVENT = "ADD {} {} {} {} {} {} {} {}\n"
END = """STATS_C {}
JAM_DH {}
STATS_D7 {}
EXIT"""

INPUT_FILE = "tp-oo_2-test.in"
OUTPUT_FILE = "tp-oo_2-test.out"

MAX_EVENTS = 20000000
MAX_SENSORS = 1500
STATES = ["V", "J", "R", "N"]
NUM_MONTHS = 5
START_MONTH = 5
END_MONTH = START_MONTH + NUM_MONTHS - 1
MONTH_DAYS = [31, 30, 31, 31, 30];
YEAR = 2015

parser = argparse.ArgumentParser(description="Generate many commands.")
parser.add_argument(
        "events", metavar="EVENTS", type=int, default=MAX_EVENTS, nargs="?",
        help="number of events")
parser.add_argument(
        "sensors", metavar="SENSORS", type=int, default=MAX_SENSORS, nargs="?",
        help="number of sensors")
parser.add_argument(
        "input_file", metavar="INPUT", default=INPUT_FILE, nargs="?",
        help="the input file to create")
parser.add_argument(
        "output_file", metavar="OUTPUT", default=OUTPUT_FILE, nargs="?",
        help="the output file to create")
parser.add_argument("-r", "--random", action="store_true",
        help="randomize timestamps, instead of generating events sequentially")
args = parser.parse_args()

stats = {
    "stats_c": {
        "id": 0,
        "counts": [0] * 4
    },
    "jam_dh": {
        "day": 1,
        "counts": [0] * 24,
        "totals": [0] * 24
    },
    "stats_d7": {
        "day": 1,
        "counts": [0] * 4
    }
}

f = open(args.input_file, "w")
progress = 0
timestamp = 0
i = 0
while i < args.events:
    if args.random:
        timestamp = random.randrange((31+30+31+31+30)*24*60)
    minute = int(timestamp % 60)
    hour = int(((timestamp - minute)/60) % 24)
    days = int((timestamp - minute - hour*60)/(24 * 60))
    month = 0
    day = days
    for k in range(0, NUM_MONTHS):
        if MONTH_DAYS[k] > day:
            day += 1
            month = k + START_MONTH
            break
        else:
            day -= MONTH_DAYS[k]
    d7 = int(days % 7 + 1)

    for sensor_id in range(args.sensors):
        state = random.choice(STATES)
        if i >= args.events:
            break
        if sensor_id == stats["stats_c"]["id"]:
            stats["stats_c"]["counts"][STATES.index(state)] += 1
        if d7 == stats["jam_dh"]["day"]:
            stats["jam_dh"]["totals"][hour] += 1
            if state in STATES[2:]:
                stats["jam_dh"]["counts"][hour] += 1
        if d7 == stats["stats_d7"]["day"]:
            stats["stats_d7"]["counts"][STATES.index(state)] += 1

        f.write(EVENT.format(sensor_id, YEAR, month, day, hour, minute, d7, state))
        i += 1

    if i/args.events * 100 - progress >= 1:
        progress = int(i/args.events * 100)
        print("{}%".format(progress))
    if not args.random:
        timestamp += 1

f.write(END.format(stats["stats_c"]["id"], stats["jam_dh"]["day"], stats["stats_d7"]["day"]))
f.close()
f = open(args.output_file, "w")

stats_c_total = sum(stats["stats_c"]["counts"])
for i, s in enumerate(STATES):
    try:
        p = int(stats["stats_c"]["counts"][i]/stats_c_total*100)
    except ZeroDivisionError:
        p = 0
    f.write("{} {}%\n".format(s, p))

for i, s in enumerate(stats["jam_dh"]["counts"]):
    try:
        p = int(stats["jam_dh"]["counts"][i]/stats["jam_dh"]["totals"][i]*100)
    except ZeroDivisionError:
        p = 0
    f.write("{} {} {}%\n".format(stats["jam_dh"]["day"], i, p))

stats_d7_total = sum(stats["stats_d7"]["counts"])
for i, s in enumerate(STATES):
    try:
        p = int(stats["stats_d7"]["counts"][i]/stats_d7_total*100)
    except ZeroDivisionError:
        p = 0
    f.write("{} {}%\n".format(s, p))