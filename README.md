# field17
This contains the field parameterizations for the SHMS from the magnets and HMS dipole. The hms_quads directory includes the output for the HMS quads. Experts only should modify these scripts.
Author: **Holly Szumila-Vance**, hszumila@jlab.org

## Compiling SHMS magents and HMS dipole
The program must be compiled and the script "compile.sh" may need to be modified to point to the ROOT location on the computer this is used on.

* To compile SHMS code:
```
./compile.sh getSHMS.C
```
* To compile HMS dipole code:
```
./compile.sh getHMS.C
```

* To compile the HMS quads, you must be inside the hms_quads directory:
```
make -f Makefile03
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
* To get the HMS quad settings:
```
./field03 P
```
where P is the desired momentum in [GeV]. This will return the current per magnet in [A]. For the HMS dipole, the recommended current is given for the external NMR setting. 

## Additional notes for experts

SHMSMagnets.h contains all the parameterizations and magnet constants. HMSDipole.h contains all the parameterizations and magnet constants for the HMS dipole. If there is a change made, this should be done by an expert only, and the version number for a specific magnet constant should be incremented before committing to gitHub. 

There is a debug flag that can be set in the getSHMS.C and getHMS.C files if more information is desired. 


## SHMS Version notes:
Version 1: 
Q1, Q2, Q3 at 1.05

Version 2: 
Q1 at 1.03, Q2 at 1.04, Q3 at 1.03

Version 3:
Q1 and Q3 saturations removed

Version 4:
HB, Q1, Q2, Q3 and dipole scaled up by 1/0.983
All version numbers should read 4.

## HMS Version notes:
Version 1:
Saturation correction at 5.3 GeV and above added to dipole model.