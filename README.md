# nRF9160-UDP-client

##  Installation
* Install [nRF-Connect](https://www.nordicsemi.com/Software-and-tools/Development-Tools/nRF-Connect-for-desktop/Download#infotabs)
* Use nRF-Connect to download Toolchain Manager
* Use Toolchain Manager to install nRF Connect SDK v1.4.0 (This include Nordics version of SEGGER)

## Build and flash to nRF9160-DK 
* Clone repo nRF9160-UDP-client
* Open SEGGER
* File -> Open nRF Connect SDK Project
* Click the "..." next to the "Project:" field and browse to your clone of nRF9160-UDP-client
* "nRF9160-UDP-client" shall been filed into the "Project:" field
* Change "Bord name:" field to "nrf9160dk_nrf9160ns"
* Check "Clean Build Directory" (Can't hurt)
* Plugin nRF9160-DK board to computer with the USB contact
* Build -> Build and Run
* Wait for everything to succeed
* If you have a working SIM card mounted you should be up and running now

## Serial interface
3 COM ports are exposed througth the USB. Test which is connected to the nRF9160 chip
* Speed: 115200
* Data bits: 8
* Stop bits: 1
