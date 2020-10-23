import matplotlib.pyplot as plt
# response time, waiting time, turnaround time

algos = ['FCFS', 'Priority-NP', 'Priority-P', 'Round-Robin', 'SJF', 'SRTF']

serialw = [2688.75, 2564.21, 2306.34, 3762.39, 1888.56, 1724.10]
parallelw = [2538.70, 2481.79, 2241.38, 3589.15, 1770.82, 1479.17]
serialt = [2743.89, 2619.35, 2456.45, 3817.97, 1943.70, 1913.21]
parallelt = [2592.07, 2535.16, 2423.83, 3641.71, 1824.19, 1751.62]
serialr = [2688.75, 2564.21, 1810.90, 6408.82, 1888.56, 1403.28]
parallelr = [2538.70, 2481.79, 1820.69, 5287.22, 1770.82, 1393.21]

plt.plot(algos, serialw)
plt.plot(algos, parallelw)
plt.plot(algos, serialt)
plt.plot(algos, parallelt)
plt.plot(algos, serialr)
plt.plot(algos, parallelr)

plt.title("Calculated Average Time for CPU Scheduling", fontsize=15)
plt.xlabel("Scheduling Algorithm", fontsize=15)
plt.ylabel("Time", fontsize=15)

plt.tick_params(axis="both", which="major", labelsize=13)
plt.tick_params(axis="both", which="minor", labelsize=13)

plt.legend(['WaitingSerial', 'WaitingParallel', 'TurnSerial', 'TurnParallel', 'ResponseSerial', 'ResponseParallel'], loc='upper left')

plt.show()
