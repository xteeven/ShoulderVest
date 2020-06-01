# Instructions

Base repository for the Shoulder Vest prototype. This prototype is designed to be ligthweigth, ergonomic and provide a high autonomy. 
It features a ESP32 processor, a LI-Po battery and four coin actuators

![](Shoulder.svg =250x)
![](ShoulderVest.svg =250x)

## Usage

Example code for communicating with the tactile shoulder vest from python using the library pygatt. 

Imports

``` python
import pygatt   # BLE Library
import binascii 
import logging # Library for debugging (Show the current state of the connections)
from time import sleep # Library used to have a delay between instructions (Not necessary in the actual app)
```


Verbose Setup
``` python
logging.basicConfig()
logging.getLogger('pygatt').setLevel(logging.DEBUG)
```

Adapter instatiation,
From the BLE library we select the type of BLE adapter we are using in the computer.
*use pygatt.GATTToolBackend()* for the internal BLE adaptor (Only linux based OS)
*use pygatt.BGAPIBackend()* for  Bluegiga external dongles (Available both Windows and Linux), if the program doesnt recognize the serial port automatically, send it as argument (i.e *pygatt.BGAPIBackend(serial_port= COM3)*)

``` python
adapter = pygatt.GATTToolBackend()
```

As we already know the MAC address of the Vest, we gonna pass it as argument to avoid mapping all the devices available.

``` python
YOUR_DEVICE_ADDRESS = "30:AE:A4:F5:24:C2" # Shoulder Vest Address
```

We also need to declare the value of the characteristic we want to alter
``` python
characteristic = '6E400002-B5A3-F393-E0A9-E50E24DCCA9E' # Shoulder Vest TX Characteristic
```

Now that we already selected the correct adapter (either Internal or Bluegiga dongle) we can start it
``` python
adapter.start()
```

Then, from the addapter, we gonna create a device using the mac address we defined before, the address type of the vest is public.

``` python
device = adapter.connect(YOUR_DEVICE_ADDRESS, address_type=pygatt.BLEAddressType.public)
```

wait 500 ms for the first start (you can remove it if required)
``` python
sleep(0.5)
```


Then, we gonna send the messages, for this expample I sent 100 values in 100 ms intervals, using the vest codification

### Encoding:

>**VV;MMMM**   
**VV**: Intensity from 00 to 99 maximum  
**MMMM**: Active motors, 1 is active, 0 is off

#### Activation
i.e *"99;1000"*, *"99;0100"*, *"99;0010"*, *"99;0001"* activates one motor at time at maximum intensity. 
The full message should contain 7 characters (included ";") and should be sent as string

#### Turning off
i. e. *"00;0000"* turns off the motors

in the following fragment of code we create a *for* cicle with 100 ascendent values. In the first line we are creating the string using the ***value*** variable and filling with zeros the values below 10 (example 8 becomes 08) Then, we create a bytearray container to store the string in byte representation. Finally we convert and store the string in the container Then we write to the characteristic using the bytearray value, wait 100 ms and do it again with the next value

``` python
for value in range(100):

    s = str(value).zfill(2)+";1111" 
    b = bytearray() 
    b.extend(s.encode()) 
    device.char_write(characteristic, b , wait_for_response=True) 
    sleep(0.1) 

```

After we finish the comunication we have to stop the adapter so other apps can use the bluetooth and we can reopen it for other uses

``` python
adapter.stop()
```

See full example at *Communication.py*
