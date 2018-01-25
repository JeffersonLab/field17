# field17
This contains the field parameterizations for the SHMS from the magnetic field measurements taken during the summer and fall 2017. Experts only should modify this.
Author: **Holly Szumila-Vance**, hszumila@jlab.org

## Compiling
The program must be compiled and the script "compile.sh" may need to be modified to point to the ROOT location on the computer this is used on.

* To compile SHMS code:
```
./compile.sh getSHMS.C
```
* To compile HMS dipole code:
```
./compile.sh getHMS.C
```

## Running

* To get HMS magnet settings:
```
./getSHMS P
```
* To get HMS dipole setting:
```
./getHMS P
```
where P is the desired momentum in [GeV]. This will return the current per magnet in [A]. For the HMS dipole, the recommended current is given for the external NMR setting. 

## Additional notes for experts

SHMSMagnets.h contains all the parameterizations and magnet constants. HMSDipole.h contains all the parameterizations and magnet constants for the HMS dipole. If there is a change made, this should be done by an expert only, and the version number for a specific magnet constant should be incremented by +1 before committing to gitHub. 

There is a debug flag that can be set in the getSHMS.C and getHMS.C files if more information is desired. 


## Version notes:
Version 1: 
Q1, Q2, Q3 at 1.05
Version 2: 
Q1 at 1.03, Q2 at 1.04, Q3 at 1.03