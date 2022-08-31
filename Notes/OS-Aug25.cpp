/* Priority Scheduling (Basic)
    -Idea: (Perhaps) Specify which processes have higher/lower priority
        -> Priority specified w/ a number (lower value -> higher priority)
            "first priority"
    -Assume preemptive: (yes when job added to ready queue)
    -Implemetation: Priority queue (ADT) - Heap
    -Adv: can specify priority, perhaps make I/O interactive
    -Disadvantage: starvation

Burst time | Priority       Optimal order for turnaround
    ----------
    | 10 | 3 |  P1          5
    ----------
    | 1 | 1  |  P2          1/2
    ----------
    | 2  | 4 |  P3          3
    ----------
    | 1  | 5 |  P4          2/1
    ----------
    | 5  | 2 |  P5          4
    ----------
    Assumption Px, priority 0 finisher
    Gantt chart: P2 - P5 - P1 - P3 - P4
        Avg turnaround: (1 + 6 + 16 + 18 + 18 + 19)/5 = 60/5 = 12

Real workload = a mix of:
    1. Interactive or I/O-heavy : short CPU bursts
        -> response tiem (I/O - continue working requests)
    2. CPU-intensive (traditional hatch)
        -> encoding video, ML jobs
    Also have A to know (some process change)
        -> video editing S/W; e.g can change "types"
            * interactive -> CPU intensive -> interactive
              <settings>     re-encoding       saving

 Multi-level feedback queue (MFQ)
 [book version - lost of variants turning award corhato]
    Prob 1: How to balance needs for responsiveness and CPU-intensive jobs 
        RR- former, not for
        SJF - latter better (optimal w/out promotion), not responsive
    Prob 2: How does OS "tell"/identify one from other
        Some proesses change between

    MLFQ: assume a new job is interactive and use its history (history, initiallly is whether is used its time slot)
        Start w/ RR, multiple to many queues
            high priority Q2 -> A,B
                          Q1 -> C
            low priority  Q0 -> D,E   
*/