# Getting Started

## One Time Operation

* __*cd ~*__
* __*git clone https://github.com/ajaygarg84/trafficshaper.git*__
* __*cd trafficshaper*__
* __*sh create_ctags.sh*__

## Steps to run the application

### Launching the application

Open a terminal, and run the following commands to see running logs

* __*cd ~/trafficshaper*__
* __*touch logs*__
* __*tail -f logs*__

Open a second terminal, and run the following commands to start the application

* __*cd ~/trafficshaper*__
* __*make*__
* __*./trafficshaper -r 2 -L 50 -t 5 -x 1 -R 5*__

Now, the logs should start appearing in the first-terminal.

### Changing the log-level at runtime 

The log-level can be changed at runtime, which will be picked up on the fly by the application.
To change the log-level, open a third terminal, and run the following commands

* __*cd ~/trafficshaper*__
* __*python tools/linux_desktop_i386/change_log_level.py*__

The usage of the tool is user-friendly.

* If EVENT is chosen, all of EVENT, ERROR logs will be seen. 
* If WARN is chosen, all of WARN, EVENT, ERROR logs will be seen. 
* If INFO is chosen, all of INFO, WARN, EVENT, ERROR logs will be seen. 
* If DEBUG is chosen, all of DEBUG, INFO, WARN, EVENT, ERROR logs will be seen. 



