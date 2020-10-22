import matplotlib.pyplot as plt
# response time, waiting time, turnaround time

algos = ['FCFS', 'Priority-NP', 'Priority-P', 'Round-Robin', 'SJF', 'SRTF']

serial = [10.445440, 9.415920, 8.772490, 8.790760, 9.538690, 8.154810]
parallel = [8.302670, 8.803790, 8.466490, 8.486900, 8.485330, 8.478980]

plt.plot(algos, serial)
plt.plot(algos, parallel)


plt.title("Response Time for CPU Scheduling", fontsize=15)
plt.xlabel("Scheduling Algorithm", fontsize=15)
plt.ylabel("Time", fontsize=15)

plt.tick_params(axis="both", which="major", labelsize=13)
plt.tick_params(axis="both", which="minor", labelsize=13)

plt.legend(['Serial', 'Parallel'], loc='upper left')

plt.show()
