#!/usr/bin/env python

from __future__ import division  # Compatibility for Python 2
import argparse
import random

INPUT_FILE = "tp-oo_2-test.in"
OUTPUT_FILE = "tp-oo_2-test.out"

ADD = "ADD {} {} {} {} {} {} {} {}\n"
OPT = "OPT {} {} {} {} {}\n"
END = """STATS_C {}
JAM_DH {}
STATS_D7 {}
"""
EXIT = "EXIT\n"

STATES = ["V", "J", "R", "N"]

MONTH_DAYS = [31, 30, 31, 31, 30]
NUM_MONTHS = len(MONTH_DAYS)
START_MONTH = 5
END_MONTH = START_MONTH + NUM_MONTHS - 1
YEAR = 2015

MAX_EVENTS = 20000000
MAX_SENSORS = 1500
MAX_TIMESTAMP = sum(MONTH_DAYS)*24*60


def write_input(input_file, events, sensors, opt=False, is_random=False, timestamp=0):
    """Generates events and writes the appropriate input commands to a file."""
    stats = {
        "stats_c": {"id": random.randrange(sensors), "counts": [0] * 4},
        "jam_dh": {"day": 1, "counts": [0] * 24, "totals": [0] * 24},
        "stats_d7": {"day": 1, "counts": [0] * 4}
    }

    f = open(input_file, "w")
    progress = 0
    i = 0

    # Generate events until the max number of events is reached or the timestamp
    # exceeds the maximum timestamp.
    while i < events and timestamp < MAX_TIMESTAMP:
        # Generate the date.
        if is_random:
            timestamp = random.randrange(MAX_TIMESTAMP)
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

        # Generate an event for every sensor.
        for sensor_id in range(sensors):
            state = random.choice(STATES)
            if i >= events:
                break
            if sensor_id == stats["stats_c"]["id"]:
                stats["stats_c"]["counts"][STATES.index(state)] += 1
            if d7 == stats["jam_dh"]["day"]:
                stats["jam_dh"]["totals"][hour] += 1
                if state in STATES[2:]:
                    stats["jam_dh"]["counts"][hour] += 1
            if d7 == stats["stats_d7"]["day"]:
                stats["stats_d7"]["counts"][STATES.index(state)] += 1

            f.write(ADD.format(sensor_id, YEAR, month, day, hour, minute, d7, state))
            i += 1

        # Update the progress.
        if i/events * 100 - progress >= 1:
            progress = int(i/events * 100)
            print("{}%".format(progress))

        # If not calculating timestamps randomly, increment the timestamp.
        if not is_random:
            timestamp += 1

    f.write(END.format(stats["stats_c"]["id"], stats["jam_dh"]["day"], stats["stats_d7"]["day"]))
    if opt:
        n = random.randint(1, sensors - 1)
        f.write(OPT.format(
            random.randint(1, 7),
            random.randint(0, 12),
            random.randint(12, 24),
            n,
            " ".join([str(random.randrange(sensors)) for i in range(n)])
        ))
    f.write(EXIT)
    f.close()

    return stats


def write_output(output_file, stats):
    """"Writes the expected output corresponding to the provided statistics."""
    f = open(output_file, "w")

    # STATS_C
    stats_c_total = sum(stats["stats_c"]["counts"])
    for i, s in enumerate(STATES):
        try:
            p = int(stats["stats_c"]["counts"][i]/stats_c_total*100)
        except ZeroDivisionError:
            p = 0
        f.write("{} {}%\n".format(s, p))

    # JAM_DH
    for i, s in enumerate(stats["jam_dh"]["counts"]):
        try:
            p = int(stats["jam_dh"]["counts"][i]/stats["jam_dh"]["totals"][i]*100)
        except ZeroDivisionError:
            p = 0
        f.write("{} {} {}%\n".format(stats["jam_dh"]["day"], i, p))

    # STATS_D7
    stats_d7_total = sum(stats["stats_d7"]["counts"])
    for i, s in enumerate(STATES):
        try:
            p = int(stats["stats_d7"]["counts"][i]/stats_d7_total*100)
        except ZeroDivisionError:
            p = 0
        f.write("{} {}%\n".format(s, p))

    f.close()


def main(events, sensors, input_file, output_file, opt, isRandom, timestamp):
    stats = write_input(input_file, events, sensors, opt, isRandom, timestamp)
    write_output(output_file, stats)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Generate many commands.")
    parser.add_argument(
        "input_file", metavar="INPUT", default=INPUT_FILE, nargs="?",
        help="the input file to create")
    parser.add_argument(
        "output_file", metavar="OUTPUT", default=OUTPUT_FILE, nargs="?",
        help="the output file to create")
    parser.add_argument(
        "-e", "--events", type=int, default=MAX_EVENTS,
        help="number of events")
    parser.add_argument(
        "-s", "--sensors", type=int, default=MAX_SENSORS,
        help="number of sensors")
    parser.add_argument(
        "-o", "--opt", action="store_true",
        help="add an OPT command to the input"
    )
    parser.add_argument(
        "-r", "--random", action="store_true",
        help="randomize timestamps")
    parser.add_argument(
        "-t", "--timestamp", type=int, default=0,
        help="the initial timestamp (unused in random mode)"
    )
    args = parser.parse_args()

    main(
        args.events, args.sensors, args.input_file, args.output_file,
        args.opt, args.random, args.timestamp)