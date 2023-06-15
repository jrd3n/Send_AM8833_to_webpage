# SEND AM8833 to webpage

Just a project to explore UDP and websockets.

The RPI gets data from the AM8833 and sends it to the flaskserver which then passes the information to the client, in close to real time.

## Install

upload the the arduino sketch to the arduino.

make sure the flash size is not 100% in the board options.

## features

the user can change the parameters on the rpi pico without having to reflash, the data is stroed as flash.