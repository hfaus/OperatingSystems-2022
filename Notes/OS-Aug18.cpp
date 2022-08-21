/**
CPU : contains control unit (CU), register, cache
CPU -> connected to memory
-> all above connected to keyboard, mouse, storage (SSD and HD), motherboard, etc.
  -> storage not plugged in, all else is
**/
simple C program
  void if(int x) {
    ++x;
    return x;
  }
  
[0 compile for machine (0 OS)]
#1 OS loads program into memory onto CPU
  (File in file system)
  Program = File
  Process = Running program
  Thread = Individual running prgram
  FETCH, DECODE, EXECUTE
