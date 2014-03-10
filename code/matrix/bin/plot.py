#!/usr/bin/python

# Plots graph data that conforms to the format described in
# `doc/plot_format.md`.

import argparse
import json
import math
import sys

import matplotlib.pyplot as plt

parser = argparse.ArgumentParser(description='Plot graph data from a file')
parser.add_argument('infile', help="file containing plot data")
parser.add_argument('outfile', help="name of the file to write to")
args = parser.parse_args()

fig = plt.figure()

with open(args.infile) as f:
    data = json.load(f)

fig.suptitle(data['title'], fontweight='bold')
fig.text(0.5, 0.06, data['x-title'], ha='center', va='center')
fig.text(0.03, 0.5, data['y-title'], ha='center', va='center',
    rotation='vertical')

share_x = data['share-x']
share_y = data['share-y']
share_lines = data['share-lines']

subplots = data['subplots']
# An extra subplot containing a line legend is added to the graph if lines are
# shared
plot_rows = int(math.ceil(math.sqrt(len(subplots)+share_lines)))
plot_cols = int(math.ceil((len(subplots)+share_lines) / float(plot_rows)))

if share_lines:
    labels = set(subplots[0]['lines'].keys())

if share_x or share_y:
    ax = None

i = 0
for subplot in subplots:
    i += 1
    ax = fig.add_subplot(plot_cols, plot_rows, i,
        sharex=(ax if share_x else None), sharey=(ax if share_y else None))

    ax.set_title(subplot['title'], fontsize=10)

    lines = subplot['lines']
    if share_lines and set(lines.keys()) != labels:
        print set(lines.keys())
        print labels
        sys.exit("shared line labels are not the same")

    for label in (labels if share_lines else lines.keys()):
        ax.plot(
            [p['x'] for p in lines[label]['points']],
            [p['y'] for p in lines[label]['points']],
            label=label
        )

        for pos in ['top', 'right']:
            ax.spines[pos].set_color('none')
        ax.get_xaxis().tick_bottom()
        ax.get_yaxis().tick_left()

    if not share_lines:
        ax.legend()

if share_lines:
    ax = fig.add_subplot(plot_cols, plot_rows, plot_cols*plot_rows)
    for label in labels:
        ax.plot([], [], label=label)
    ax.legend()
    ax.set_axis_off()

fig.savefig(args.outfile)
