# Lab02 sigproc
## Status
The program meets most of the requirement for the lab, the only known issue is if you kill the parent process first...
The children process still run in the background until killed. 
However, the program does spawn all child process at once and the parent process will be killed if all child process 
is killed. 
## Known Issues
The only known issue is that you are able to kill the parent process, and the 2 child process will still run. 
## Expected Grade
4/5
