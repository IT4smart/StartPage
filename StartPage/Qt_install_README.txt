-lGL Error:
===========
Execute the following command to install OpenGL libraries:

sudo apt-get install mesa-common-dev

Note: Just installing the above-mentioned mesa-common-dev kit is not sufficient for more recent Ubuntu versions. Based on this comment in the forum an additional package needs installation. Execute following command:

sudo apt-get install libglu1-mesa-dev -y

Tested with Qt5.3.1 and Ubuntu 14.04 and it solved the problem with missing -lGL. 
