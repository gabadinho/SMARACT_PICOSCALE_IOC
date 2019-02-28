#!../../bin/linux-x86_64/picoScale

## You may have to change picoScale to something else
## everywhere it appears in this file

< envPaths

cd "${TOP}"

## Register all support components
dbLoadDatabase "dbd/picoScale.dbd"
picoScale_registerRecordDeviceDriver pdbbase

## Load record instances
#dbLoadTemplate "db/userHost.substitutions"
dbLoadRecords ("$(ASYN)/db/asynRecord.db", "P=CATERETE:, R=asyn1, PORT=eth0, ADDR=0, OMAX=80, IMAX=80")
dbLoadRecords ("db/picoScale_Channel_Common.db", "Ch=0, C=CATERETE, P=PICOSCALE, PORTNAME=eth0, ADDRESS=0, TIMEOUT=1")
dbLoadRecords ("db/picoScale_Channel_Common.db", "Ch=1, C=CATERETE, P=PICOSCALE, PORTNAME=eth0, ADDRESS=0, TIMEOUT=1")
dbLoadRecords ("db/picoScale_Channel_Common.db", "Ch=2, C=CATERETE, P=PICOSCALE, PORTNAME=eth0, ADDRESS=0, TIMEOUT=1")
dbLoadRecords ("db/picoScale_Channel0.db", "C=CATERETE, P=PICOSCALE, PORTNAME=eth0, ADDRESS=0, TIMEOUT=1")
dbLoadRecords ("db/picoScale_Commmunication.db", "C=CATERETE, P=PICOSCALE, PORTNAME=eth0, ADDRESS=0, TIMEOUT=1")

## Set this to see messages from mySub
#var mySubDebug 1

## Run this to trace the stages of iocInit
#traceIocInit

PicoScaleCreateDriver("eth0", "10.0.9.68")

cd "${TOP}/iocBoot/${IOC}"
iocInit

## Start any sequence programs
#seq sncExample, "user=rootHost"
