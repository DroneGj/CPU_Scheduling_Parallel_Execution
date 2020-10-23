import matplotlib.pyplot as plt
# response time, waiting time, turnaround time

algos = ['FCFS', 'Priority-NP', 'Priority-P', 'Round-Robin', 'SJF', 'SRTF']

serial = [2688.75, 2564.21, 1810.90, 6408.82, 1888.56, 1403.28]
parallel = [2538.70, 2481.79, 1820.69, 5287.22, 1770.82, 1393.21]

plt.plot(algos, serial)
plt.plot(algos, parallel)

plt.title("Response Time for CPU Scheduling", fontsize=15)
plt.xlabel("Scheduling Algorithm", fontsize=15)
plt.ylabel("Time", fontsize=15)

plt.tick_params(axis="both", which="major", labelsize=13)
plt.tick_params(axis="both", which="minor", labelsize=13)

plt.legend(['Serial', 'Parallel'], loc='upper left')

plt.show()
