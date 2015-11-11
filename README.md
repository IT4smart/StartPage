# README #
# TEST ALEX GIT #


## Installation: ##
sudo apt-get install libgtk-3-dev

## Compiling: ##
make config
make clean

## paths: ##
The paths are stored in vars.h
On production enviroment we install it at /opt/IT4S

## image header: ## 
* see function init
* stored in IMAGE_PATH

## function-declaration: ##
* all static functions (only useable in the same file) are definied in their .h file.
* not static functions are defined in the func.h file

## functions: ##
set_layout
* is responsable of the layout of the gui, not more
init
* initialises all the widgets as labels, entries, etc
* pairing button clicks with functions
* the header includes the image
## buttons: ##
all buttons are stored with a mnemonic, so that you press ALT+underlinded letter und you press this button

