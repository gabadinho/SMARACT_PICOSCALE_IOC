TOP=../..

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS BELOW HERE 

PROD_IOC = picoScale

#picoScale_CXXFLAGS = -L/home/ABTLUS/allan.bugyi/work/dev/iocs/SMARACT_PICOSCALE_IOC/src/
picoScale_SYS_LIBS += ftchipid
picoScale_SYS_LIBS += ftd2xx
picoScale_SYS_LIBS += smaractio
picoScale_SYS_LIBS += smaractsi

#picoScale_DIR += /home/ABTLUS/allan.bugyi/work/dev/iocs/SMARACT_PICOSCALE_IOC/src/

#PROD_SYS_LIBS += ftchipid
#PROD_SYS_LIBS += ftd2xx
#PROD_SYS_LIBS += smaractio
#PROD_SYS_LIBS += smaractsi

#picoScale_LIBS += ftchipid ftd2xx
#picoScale_LIBS += smaractio smaractsi

# picoScale.dbd will be created and installed
DBD += picoScale.dbd

# picoScale.dbd will include these files:
picoScale_DBD += base.dbd
picoScale_DBD += asyn.dbd
picoScale_DBD += drvAsynIPPort.dbd
picoScale_DBD += genSubRecord.dbd
picoScale_DBD += picoScale_functions.dbd

picoScale_LIBS += asyn genSub

# picoScale_registerRecordDeviceDriver.cpp derives from picoScale.dbd
picoScale_SRCS += picoScaledrv.cpp
picoScale_SRCS += picoScale_registerRecordDeviceDriver.cpp

# Build the main IOC entry point where needed
picoScale_SRCS_DEFAULT += picoScaleMain.cpp
picoScale_SRCS_vxWorks += -nil-

# Add support from base/src/vxWorks if needed
#picoScale_OBJS_vxWorks += $(EPICS_BASE_BIN)/vxComLibrary

#Finally link IOC to the EPICS Base libraries
picoScale_LIBS += $(EPICS_BASE_IOC_LIBS)
include $(TOP)/configure/RULES
#----------------------------------------
#  ADD EXTRA GNUMAKE RULES BELOW HERE
#
