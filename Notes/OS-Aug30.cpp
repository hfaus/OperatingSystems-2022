/*
Virtualization part of OS
    -Pieces: CPU, I/O-Mouse/Screen (Persistance), Memory
        -CPU
            * Main method of approach: LDE (Limited Direct Execution)
            * Main idea: we run prog on CPU w/ traps to OS
            * What we need: hardware support for priveledged executions, get registers (general, PC, SP)
            * Policy: what to schedule
            * hardware supports context switching
        -Memory
            * Protection: access or change other process memories
            * Efficent: cannot just copy out memory

Base Model
V.1 ------------
    | Memory    |
    |   in      |   * Program imagines AS
    | address   |   * AS can be large
    |  space    |
    |   (AS)    |
    ------------

V.1.1------------
    |   OS      |   * OS needs protection
    ------------
    | Memory    |
    |   in      |
    | address   |
    |  space    |
    |   (AS)    |
    ------------

V.2 ------------
    |    OS     |
    ------------
    |  Free     |
    ------------
    |    P1     |   * 1K
    ------------
    |  Free     |
    ------------
    |    P2     |   * 1K
    ------------
    |  Free     |
    |           |
    ------------
    Dynamic relocation: each process 1K in size
        * P1 loads 300 (base of 2048) -> VA(300) + Base(2048) = PA(2348)
            -> 300 is virtual address
            -> 2048 is base address
        * P2 loads 300 (base of 4096) -> VA(300) + Base(4096) = PA(4396)
            -> 2 new registers (Bounds for protection)
    -Add 2 new registers per CPU (in Memory Management Unit [MMU])
        * Base register - holds start address fro running process
        * Bounds: holds size of AS (for protection)
        * MMU: H/W translates every (VA -> PA) memory reference

        For process Px with
            Base register 2KB (32768)
            Bounds register 1bKB
            Virtual Addy| Physical Addy 
                (VA)    |       (PA)
            ---------------------------
                0       |       32KB
                3KB     |       35KB
                4000    |       36768
                9000    |
                18KB    |

        Zoom in on one process
        ------------
        |   Code    |   * what's wrong here?
        ------------        -Imagine large AS (32B)
        |   Heap    |           -> Hugely wasteful (most processes are much less)
        ------------            -> If AS smaller less waste
        |   Free    |
        |           | <- internal fragmentation (wasted space within allocated memory)
        ------------
    
    -H/W
        * Base and bounds regas (B&B)
        * General priveleged modes and OP
        * VA -> PA translation (MMU circuits)
        * Privelege updated to B&B
        * Privelege instructions to add to exception table (ability to raise exception)
    -OS
        * Memory management
            -> Allocation (hands out memory)
            -> Deallocation/Reallocation
            -> Track memory usage (through freelist)
        * Base and bounds management (regs)
            -> copy in/out on context to PCB
        * Exception handling
            -> when exceptions happen, OS decides what ot do
            -> generally, decide to kill
    
    -Pros/Cons of dynamic reallocation
        -> Pros
            * Fast/simple
            * Minimal overhead (memory wise) - 2 registers
        -> Cons
            * Not very flexible
            * Very wasteful/problematic 
            * Too small -> process runs out of space
            * Too large -> internal fragmentation

Fig 15.5/15.6
    [OS]
    -> starts PA
        * get regs inc. B&B
        * allocate mem @ start
        * return from trap (to A)
    [H/W]
    -> load regs
        * to user made
    [PA]
    -> runs...fetch
        [MMU]
        -> VA -> PA translation
            * check legal w/ bounds
    -> decode and execute
    -> load/store
        * check legal w/ bounds
        * translate VA -> PA
    
    [OS]
    -> switches to PB
        * save PA
        * load B&B regs
        * return from trap (to B)
    [H/W]
    -> load regs
        * to user
    [PB]
    -> B run
    -> load/store
    -> trap
        [HW]
        -> finds
        [OS]
        -> trap/exception handler
        -> kills B
        -> deallocate mem, etc.

Generalized Base & Bounds : Segmentation
    -Address space (AS) has logical pieces/regions/segments
        * Why not allocate those? (separately)
            -> each segment of AS has ptr.length (essential B&B)
            -> each logical region located separately (2 regs B&B for segment)
*/