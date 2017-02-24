# LAutopin -Lightweight Autopin-Based Node Health and Performance Monitor

This project is about a simple and pure tool to collect selected health and performance counters. It provides support for hardware sensors, such as cpu temperature and system fan speed, alongside with performance counters which are potentially meaningful for system reliablility and may be indication of pre-failure hardware state.

# Features
* **Lightweight**
  LAutopin is designed to have minimum resource consumption.
* **Daemon**
  LAutopin is a Daemon to be run on node-level. It collects data from different sensors using libraries like lm-sensors. Also, it includes some monitoring implementations from Project [Autopin+](https://github.com/lrr-tum/autopin-plus) such as MegWare ClustSafe.
* **Filtering**
   LAutopin is designed to have configurable data filter in order to reduce communication workload.
* **Data Export**
   Additional to publish data through a selected communication module, LAutopin is also capable of store data to a selected endpoint.
* **Communication**
   LAutopin supports MQTT and Pipe Communication for feeding monitoring data.

# Example


# Modules
## lm-sensors
  Uses the [lm-sensors](https://github.com/groeck/lm-sensors) library to collect trival hardware data such as fan speed and cpu core temperature.
## smart
  Read Hardware SMART Data. This Module is a simple wrapper of [smartmontools](http://smarmontools.org).
  Enabling this module requires preinstalled smartmontools. Also, a Password prompt may appear when using this mode since smartctl requires cap_sys_rawio for reading the system S.M.A.R.T. Data.
## ClustSafe
  Read MegWare ClustSafe Data.
## rpimonitor
  For demostration purpose, this module is used to demonstrate LAutopin's functionality on a RPi. 
## Perf
  Read data from the Linux Perf Counter.
