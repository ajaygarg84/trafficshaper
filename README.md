# Getting Started

## One Time Operation

* __*cd \~*__
* __*git clone https://github.com/ajaygarg84/trafficshaper.git*__
* __*cd trafficshaper*__
* __*sh create_ctags.sh*__

## Steps to run the application

### Launching the application

Open a terminal, and run the following commands to see running logs:

* __*cd ~/trafficshaper*__
* __*touch logs*__
* __*tail -f logs*__

Open a second terminal, and run the following commands to start the application:

* __*cd ~/trafficshaper*__
* __*make*__
* __*./trafficshaper -r 2 -L 50 -t 5 -x 1 -R 5*__

Now, the logs should start appearing in the first terminal.    
__Since we are doing file-based logging, so only one instance of ./trafficshaper can be running at a time.__

   
   
### Changing the log-level at runtime 

The log-level can be changed at runtime, which will be picked up on the fly by the application.      
To change the log-level, open a third terminal, and run the following commands:

* __*cd ~/trafficshaper*__
* __*python tools/linux_desktop_i386/change_log_level.py*__

The usage of the tool is user-friendly.

* If EVENT is chosen, all of EVENT, ERROR logs will be seen. 
* If WARN is chosen, all of WARN, EVENT, ERROR logs will be seen. 
* If INFO is chosen, all of INFO, WARN, EVENT, ERROR logs will be seen. 
* If DEBUG is chosen, all of DEBUG, INFO, WARN, EVENT, ERROR logs will be seen. 

When WARN/INFO/DEBUG level is selected, dummy logs for these levels are shown by tailing __logs__ file:
    
    
### Capturing logs for a particular request number

The __logs__ file collects all the logs cumulatively.      
To filter out logs for a particular request (let's say request number 3), we can use the following tool:

* __*sh tools/linux_desktop_i386/get_logs_by_request_number.sh 3*__


# Code 

## Architecture

The code has been layered out broadly into two components:

* Bare-Metal C code
   * This code is compilable via any C-compiler. Once written, it ought never to be changed for any new device.
   * This code resides in __src/bare__       
   
* Device-Specific C code
   * This code is device-specific, and needs to be potentially ported for a new device.
   * The stubs for all such code are present in __src/device/stub__
   * When a new device comes in (let's say __proprietary_xyz_soc__), following needs to be done:    
   
       * __*cp -r src/device/stub src/device/proprietary_xyz_soc*__
       * Thereafter, all files in __src/device/proprietary_xyz_soc__ need to be ported.
       
   * Following are some of the modules which are candidates for residing in device-specific section:
       * __socket__, as a device may have any permutation of one or more of Wifi/GPRS/Ethernet for IP-connectivity.
       * __time__, as there is no universal way to get/set time on a system.
       * __persistent_storage__, as a device may either have a posix-filesystem, or a persistent-storage via bare-metal SPI.
       
 Note that the device-specific code for linux-desktop on a 32-bit machine is already ported, and part of the repository at __src/device/linux_desktop_i386__
 
## Documentation
 
The code-files are documented in consistency with doxygen.     
         
To start navigating the html-version documentation, please start by opening the file __*~/trafficshaper/html/files.html*__ in a local browser.     
     
To regenerate/update the doxygen documentation, following commands should be run:

* __*cd ~/trafficshaper*__
* __*doxygen doxygen.cfg*__



