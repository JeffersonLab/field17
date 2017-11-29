# field17
This contains the field parameterizations for the SHMS from the magnetic field measurements taken during the summer and fall 2017. Experts only should modify this.
Author: **Holly Szumila-Vance**, hszumila@jlab.org

## Compiling
The program must be compiled and the script "compile.sh" may need to be modified to point to the ROOT location on the computer this is used on.

To compile:
```
./compile.sh getSHMS.C
```

## Running

To run:
```
./getSHMS P
```
where P is the desired momentum in [GeV]. This will return the current per magnet in [A].

## Additional notes for experts

SHMSMagnets.h contains all the parameterizations and magnet constants. If there is a change made, this should be done by an expert only, and the version number for a specific magnet constant should be incremented by +1 before committing to gitHub.

There is a debug flag that can be set in the getSHMS.C file if more information is desired. 