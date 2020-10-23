import matplotlib.pyplot as plt

algos = ['FCFS', 'Priority-NP', 'Priority-P', 'Round-Robin', 'SJF', 'SRTF']

serial = [2743.89, 2619.35, 2456.45, 3817.97, 1943.70, 1913.21]
parallel = [2592.07, 2535.16, 2423.83, 3641.71, 1824.19, 1751.62]

plt.plot(algos, serial)
plt.plot(algos, parallel)


plt.title("Turnaround Time for CPU Scheduling", fontsize=15)
plt.xlabel("Scheduling Algorithm", fontsize=15)
plt.ylabel("Time", fontsize=15)

plt.tick_params(axis="both", which="major", labelsize=13)
plt.tick_params(axis="both", which="minor", labelsize=13)

plt.legend(['Serial', 'Parallel'], loc='upper left')

plt.show()
