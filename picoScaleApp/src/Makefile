TOP=../..

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS BELOW HERE 

# Build the IOC application
PROD_IOC = picoScale

picoScale_LIBS += libftchipid.so
picoScale_LIBS += libftd2xx.so.1.4.6
picoScale_LIBS += libsmaractio.so.2.0.3
picoScale_LIBS += libsmaractsi.so.2.0.8

# picoScale.dbd will be created and installed
DBD += picoScale.dbd

# picoScale.dbd will include these files:
picoScale_DBD += base.dbd
picoScale_DBD += asyn.dbd
picoScale_DBD += drvAsynIPPort.dbd
picoScale_DBD += genSubRecord.dbd
picoScale_DBD += picoScale.dbd

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

