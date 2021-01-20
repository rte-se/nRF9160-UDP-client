# nRF9160-UDP-client

##  Installation
* Install [nRF-Connect](https://www.nordicsemi.com/Software-and-tools/Development-Tools/nRF-Connect-for-desktop/Download#infotabs)
* Use nRF-Connect to download Toolchain Manager
* Use Toolchain Manager to install nRF Connect SDK v1.4.0 (This include Nordics version of SEGGER)
### Extra for command line (West)
* Install [nRF Command Line Tools](https://www.nordicsemi.com/Software-and-Tools/Development-Tools/nRF-Command-Line-Tools)
* Install [Python 3](https://www.python.org/downloads/)
* [Use python pip to install west](https://docs.zephyrproject.org/latest/guides/west/install.html)

## Build and flash to nRF9160-DK
### Segger
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
### West
* nRF-Connect -> Toolchain Manager -> "▼" at nRF Connect SDK v1.4.0 -> Open bash
* Go to desired path
* Clone repo nRF9160-UDP-client
* cd nRF9160-UDP-client
* ```west build -b nrf9160dk_nrf9160ns```
* Plugin nRF9160-DK board to computer with the USB contact
* ```west flash```
* If you have a working SIM card mounted you should be up and running now

## Serial interface
3 COM ports are exposed througth the USB. Test which is connected to the nRF9160 chip
* Speed: 115200
* Data bits: 8
* Stop bits: 1

## Tips
* There are good examples under:
  * ~/ncs/v1.4.0/nrf/samples/nrf9160/
  * ~/ncs/v1.4.0/zephyr/samples/
* [Some use Visual Studio as IDE with West](https://devzone.nordicsemi.com/f/nordic-q-a/66509/setting-up-a-workspace-in-visual-studio-code)
