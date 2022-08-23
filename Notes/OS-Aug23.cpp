/**
 * Virtualizing CPU(s)
 *  !Remember programs/programming is hard enough
 *      -> progs don't want to handle other progs
 *      -> progs, malicious/bugged can crash
 *  Goal: run N (number) processes on M (number) CPUs (N>>M)
 * 
 * Hardware side of virtualization
 *  CPU: PC/IP, FP/SP, Gen register
 *      -> PC/IP -> Code
 *      -> FP/SP -> Stack
 *  Other: Code, Stack, Fieles/IO
 *  Process: private memory addresss space
 *      (memory virtualizaition)
 *  Also need virtual CPUs
 * 
 * -Emulate CPU for process (No, for safety resons)
 *  (OS as an interpretter)
 * -Direct execution (No, for safety reasons)
 * -Limited direct execution (LDE)
 *  -> hardware privelage levels
 *  --------(process)-------*(trap)->(OS)->[reformatting]--------(process)-----------
 *                            A/B/C              D (kernal mode)
 *      Note: traps sys call or trays (ex- divide by zero)
 *      A) save process state (A/B)
 *      B) delta (change) to kernal mode
 *      C) trap controller loaded
 *      D) OS switches to user mode
 * 
 *      SETUP:
 *      A) computer boots into kernal mode, loads OS
 *      B) OS load trap table (h/w (hardware) ;earns addresses of trap handlers)
 *      C) OS loads regular code in usermade
 * 
 *      Codes:
 *      -User code
 *      -Kernal code
 *      -Trap code
 * 
 *      RUNTIME:
 *      -Trap-
 *      1. Save state (H/W)
 *      2. To kernal mode
 *      3. Jump to kernal code (address in trap table)
 *      -Return-from-trap-
 *      1. User mode
 *      2. Restore registers
 *      3. PC right after trap
 * 
 *      How to stop a running process?
 *      #1 Cooperative approach
 *          Assume: surely processes eventually make a sys call or yield
 *      #2 Noncooperative approach
 *          OS reclaims CPU (OS not running)
 *          Use a timer interrupt
 *              -> fires every x ms and OS loaded
 * 
    *      Context switch (Pa -> Pb)
    *          ----------(process a)---------(timer)---------*(OS)*-----(process b)
    *                               (h/w) regs(a) -> k-stack(a)
    *          -> kernals meet in a separate stack, k(ernal)-stack
    *          -> OS save a's regs; to a k-stack; choose b
    *          -> loads from k-stack(b); to regs(b)
 *      
 *      #3 Problem w I/O
 *          PROCESS LIFECYCLE (drawn in class, may attach pdf)
 *          -Running <- [OS shield] <- Ready
 *          -Running -> [Trap : Descheduled] -> Ready
 *          -Running -> [I/O] -> Blocked/Waiting -> [I/O Finish] -> Ready
 *          -Init/New -> Ready
 *          -Running -> [Exit] -> Terminate/Zombie
 * 
 *          States: Running, Ready, Init/New, Terminate/Zombie, Blocked/Waiting
 * 
 *          ----(Pa)-------*(traps to OS)---(I/O)--------(I/O Done)------(OS)*----(Pa)
 *                          |                  DEAD TIME                     |
 *          -Minimize dead time w/ ~scheduling~
 * 
 * CPU Scheduling
 *  LDE is how, but OS can pick a policy
 *      Assumptions:
 *      1) All processes arrive at the same time
 *      2) Know how long they will take (relax later)
 *      3) CPU intensive
 * 
 *  Policies (which is more efficent based on Taverage):
 *      (Brute Force Policy) FirstComeFirstServe(FIFO) : queue
 *          -> Turnaround time
 *              * Tcompleted - Tarrived
 *      ShortestJobFirst(SJN)
 *          -> Always pick shortest job
 *      ShortestTimeToCompletionFirst(STCF) [Allow Preemption]
 *          -> Run job w/ least time recurring
 *          -> Problems:
 *              * Starvation (long process may never run if new ones keep coming in)
 *              * Response time could be bad
 *              * Hard to measure time cost
 *      RoundRobin
 *          -> Share CPU(evenly) - taking turns
 *              * Using the timer (actual time matters)
 *                  -> too small = many context switch
 *                  -> too large = basically FIFO
 * 
 */        