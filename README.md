SMARACT PICOSCALE'S EPICS IOC
=============================
Brazilian Synchroton Light National Laboratory - Campinas, 02/28/2019

Author:     Allan S. B. Bugyi. 
Contact:    allan.bugyi@lnls.br

Functionalities
===============
- Polling of data sources;
- Streaming of data sources with 3 modes available:
    1) Simple stream of a single user-defined datasource;
    2) Stream of Position/Velocity/Acceleration data sources from all channels (3 for PicoScale);
    3) Stream of Position data sources from all channels.
- Configurable parameters for streaming/polling (*channel/datasource indexes*, *frame rate*, *buffer number*, *buffer aggregation*, *interleaving*)
- Environmental module stats.

Dependencies
============

- EPICS Base >=3.14;
- SynApps >= 5.8;
- C and C++ compilers;
- Make;
- Asyn (AsynPortDriver) module from SynApps;
- SmarAct Libraries (located under directory 'lib/' of this IOC. Must be installed in appropriate system location, e.g., directory '/usr/lib/x86_64-linux-gnu/' for a Linux 64 bits).