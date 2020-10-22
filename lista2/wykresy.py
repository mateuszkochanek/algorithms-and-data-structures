import matplotlib.pyplot as plt
import os
import sys
import math

def comp_avg(stats,ns):
    comparisons = []
    i = 0
    k = 0
    sum = 0
    for x in stats:
        if int(x[0]) == ns[i]:
            sum += int(x[1])
            k += 1
        else:
            comparisons.append(sum/k)
            i += 1
            sum = int(x[1])
            k = 1
    comparisons.append(sum/k)
    return comparisons

def swap_avg(stats,ns):
    swaps = []
    i = 0
    k = 0
    sum = 0
    for x in stats:
        if int(x[0]) == ns[i]:
            sum += int(x[2])
            k += 1
        else:
            swaps.append(sum/k)
            i += 1
            sum = int(x[2])
            k = 1
    swaps.append(sum/k)
    return swaps

def time_avg(stats,ns):
    times = []
    i = 0
    k = 0
    sum = 0
    for x in stats:
        if int(x[0]) == ns[i]:
            sum += float(x[3])
            k += 1
        else:
            times.append(sum/k)
            i += 1
            sum = float(x[3])
            k = 1
    times.append(sum/k)
    return times

def comp_on_n(carr,ns):
    c_n = []
    i = 0
    while i < len(carr):
        c_n.append(carr[i]/ns[i])
    return c_n

def swap_on_n(sarr,ns):
    s_n = []
    i = 0
    while i < len(sarr):
        s_n.append(sarr[i]/ns[i])
    return s_n


with open('insert_stats1', 'r') as f:
    stats = f.read()
ns = [x*100 for x in range(1,101)]
statarr = []
tab = []
tab = stats.split("\n")
tab.pop(-1)
for stat_block in tab:
    statarr.append(stat_block.split(" "))

comps1 = comp_avg(statarr,ns)

with open('merge_stats1', 'r') as f:
    stats = f.read()
ns = [x*100 for x in range(1,101)]
statarr = []
tab = []
tab = stats.split("\n")
tab.pop(-1)
for stat_block in tab:
    statarr.append(stat_block.split(" "))

comps2 = comp_avg(statarr,ns)

with open('quick_stats1', 'r') as f:
    stats = f.read()
ns = [x*100 for x in range(1,101)]
statarr = []
tab = []
tab = stats.split("\n")
tab.pop(-1)
for stat_block in tab:
    statarr.append(stat_block.split(" "))

comps3 = comp_avg(statarr,ns)
#swaps = swap_avg(statarr,ns)
#comparisons = comp_avg(statarr,ns)
#c_n = comp_on_n(comparisons,ns)
#s_n = swap_on_n(swaps,ns)

plt.figure("InsertMergeQuick_k1000_comparisons")
plt.xlabel('n values')
plt.ylabel('comparisons')
plt.plot(ns, comps1, 'r',ns, comps2,'b',ns,comps3,'g')
plt.legend(('InsertSort compares','MergeSort compares','QuickSort compares'))
plt.show()
