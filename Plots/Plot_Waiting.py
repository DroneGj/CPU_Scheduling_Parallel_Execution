import matplotlib.pyplot as plt
# response time, waiting time, turnaround time

algos = ['FCFS', 'Priority-NP', 'Priority-P', 'Round-Robin', 'SJF', 'SRTF']

serial = [2688.75, 2564.21, 2306.34, 3762.39, 1888.56, 1724.10]
parallel = [2538.70, 2481.79, 2241.38, 3589.15, 1770.82, 1479.17]

plt.plot(algos, serial)
plt.plot(algos, parallel)


plt.title("Waiting Time for CPU Scheduling", fontsize=15)
plt.xlabel("Scheduling Algorithm", fontsize=15)
plt.ylabel("Time", fontsize=15)

plt.tick_params(axis="both", which="major", labelsize=13)
plt.tick_params(axis="both", which="minor", labelsize=13)

plt.legend(['Serial', 'Parallel'], loc='upper left')

plt.show()
