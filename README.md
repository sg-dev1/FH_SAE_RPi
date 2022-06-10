## Client Server
1. UDP client server system consisting of 3 server nodes and one client node
2. client request data (timestamp) from servers
3. If timestamps are > 0, the client calculates the position
   1. if a server sends 0 or nothing measurement failed 

## TODO
- Timestamps are just mockups. 
- implement real measuremnts

## Files server
- server/main.c
- errorCode.c
- errorCode.h
- sharedFunctions.c
- sharedFunctions.h
- 
## Files client
- client/main.c
- client/clientFunctions.c
- client/clientFunctions.h
- errorCode.c
- errorCode.h
- sharedFunctions.c
- sharedFunctions.h

## Used IP addresses and port (hardcoded):
- PI 1: 192.168.8.210
- PI 2: 192.168.8.220
- PI 3: 192.168.8.230
- Pot: 18000

## Usage
- client is run on a PC (could also be a PI)
- compile servers on raspberry PIs
- run and grab popcorn for some epic client server communication