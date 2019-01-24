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
dbLoadRecords ("db/picoScale_Channel_Common.db", "Ch=1, C=CATERETE:, P=PICOSCALE:")
dbLoadRecords ("db/picoScale_Channel_Common.db", "Ch=2, C=CATERETE:, P=PICOSCALE:")
dbLoadRecords ("db/picoScale_Channel_Common.db", "Ch=3, C=CATERETE:, P=PICOSCALE:")
dbLoadRecords ("db/picoScale_Channel0.db", "C=CATERETE:, P=PICOSCALE:")
dbLoadRecords ("db/picoScale_Commmunication.db", "ADDR=10.0.9.68, C=CATERETE:, P=PICOSCALE:")
dbLoadRecords ("db/picoScale_Adjustment.db", "ADDR=10.0.9.68, C=CATERETE:, P=PICOSCALE:")

## Set this to see messages from mySub
#var mySubDebug 1

## Run this to trace the stages of iocInit
#traceIocInit

PicoScaleCreateDriver("10.0.9.68")
PicoScaleInitializingRoutinesRun()

cd "${TOP}/iocBoot/${IOC}"
iocInit

## Start any sequence programs
#seq sncExample, "user=rootHost"
