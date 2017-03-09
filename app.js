/********
* NodeJs code for Wireless Surveilance Rover
* This will send whatever data the mcs receives from the user
* and send it to arduino serial listener
*
* Author : Jeff Paredes
* Version : 1.0
*/

// required npm module to use mcs
var mcs = require('mcsjs');
var exec = require('child_process').exec;


// set variable needs
var deviceId = 'DhniqIi1';  // Input your deviceId.
var deviceKey = 'PWcGGzZiECF9H5X0'; // Input your deviceKey.
var gamepadDataChnId = 'RoverGamepad'; // Input your gamepad data channel Id
var videoDataChnId = 'RoverVideoStream'; // Input your video stream data channel Id
var messageDataChnId = 'RoverMessage'; // Input your message data channel Id

// set video resolution
var videoWidth = 176;
var videoHeight = 144;


// register your device to mcs.
var surveilanceRover = mcs.register({
   deviceId: deviceId,   
   deviceKey: deviceKey, 
   host: 'api.mediatek.com' // leave it unchanged


});

// send streamed video to mcs
exec('ffmpeg -s ' + width + 'x' + height + ' -f video4linux2 -r 30 -i /dev/video0 -f mpeg1video -r 30 -b 800k http://stream-mcs.mediatek.com/' + deviceId + '/' +deviceKey + '/' + dataChnId + '/' + width + '/' + height, function(error, stdout, stderr) {
console.log('stdout: ' + stdout);
console.log('stderr: ' + stderr);
if (error !== null) {
 console.log('exec error: ' + error);
}
});

// get serial receiver of the arduino chip
var SerialPort = require("serialport").SerialPort;
var serialPort = new SerialPort("/dev/ttyS0", {
    baudrate: 57600
});

// communicate with Arduino chip (32U4).
// this will send the date received from mcs to the boards serial (57600)
serialPort.on("open", function () {
    // listen the rover gamepad datachannel command.
    // controller pad for our rover
    surveilanceRover.on(gamepadDataChnId, function(data, time) { // replace roverGamepad with your own gamepad datachannel.
        serialPort.write(data); // send message to Arduino chip serial.
    });
    // listen the rover message datachannel command.
    // send message to Rover and display using 8x8 display matrix
    surveilanceRover.on(messageDataChnId, function(data, time) { // replace RoverMessage with your own message datachannel.
        serialPort.write(data); // send message to Arduino chip serial.
    });
});