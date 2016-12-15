"""
script.py

author: Jack Fletcher
date:   12.14.2016

Analysis script for timing results from data structures.
See /C++/ for data source.
"""
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import csv

df = pd.read_csv('../data/timing_results.csv')

df_sl = df[df.structure == "skip list"]
df_bst = df[df.structure == "binary tree"]
df_ll = df[df.structure == "linked list"]


#plt.figure(figsize=(10,8))

#plt.scatter(df_sl['n'], df_sl['tpo'], c=df_sl['operation'])

groups = df_sl.groupby('operation')

fig, ax = plt.subplots()
ax.margins(0.05) # Optional, just adds 5% padding to the autoscaling
for name, group  in groups:
    ax.plot(group.n, group.tpo, marker='o', linestyle='', ms=12, label=name)
ax.legend()

plt.show()


#plt.plot(x, y)

#plt.xlabel('x')
#plt.ylabel('y')
#plt.title("Title")
#plt.legend()
#plt.show()

