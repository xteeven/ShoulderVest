#%% Example code for communicating with the tactile shoulder vest from python using the library pygatt. 

# Imports
import pygatt   # BLE Library
import binascii 
import logging # Library for debugging (Show the current state of the connections)
from time import sleep # Library used to have a delay between instructions (Not necessary in the actual app)

# Verbose Setup
logging.basicConfig()
logging.getLogger('pygatt').setLevel(logging.DEBUG)

# %% Adapter instatiation,
# From the BLE library we select the type of BLE adapter we are using in the computer.
# use pygatt.GATTToolBackend() for using the internal BLE adaptor (Only linux based OS)
# use pygatt.BGAPIBackend() for using Bluegiga external dongles (Available both Windows and Linux), if the program doesnt recognize the serial port automatically, send it as argument (i.e pygatt.BGAPIBackend(serial_port= COM3))
adapter = pygatt.GATTToolBackend()


#%% As we already know the MAC address of the Vest, we gonna pass it as argument to avoid mapping all the devices available.
YOUR_DEVICE_ADDRESS = "30:AE:A4:F5:24:C2" # Shoulder Vest Address

# We also need to declare the value of the characteristic we want to alter
characteristic = '6E400002-B5A3-F393-E0A9-E50E24DCCA9E' # Shoulder Vest TX Characteristic

# Now that we already selected the correct adapter (either Internal or Bluegiga dongle) we can start it
adapter.start()

# Then, from the addapter, we gonna create a device using the mac address we defined before, the address type of the vest is public.
device = adapter.connect(YOUR_DEVICE_ADDRESS, address_type=pygatt.BLEAddressType.public)

# wait 500 ms for the first start (you can remove it if required)
sleep(0.5)

# Then, we gonna send the messages, for this expample I sent 100 values in 100 ms intervals, using the vest codification
for value in range(100): #for cicle of 100 values
    # Encoding:
    # VV;MMMM
    # VV: Intensity from 00 to 99 maximum MMMM: Active motors i.e 1000, 0100, 0010, 0001 activates one motor (check the order)
    # The full message should contain 7 characters (included ";") and should be sent as string
    # i. e. "00;0000" turns off the motors

    s = str(value).zfill(2)+";1111" # In this line we are creating the string using the value variable and fillin with zeros the values below 10
    b = bytearray() # Then, we create a bytearray container to store the string in byte representation
    b.extend(s.encode()) # Finally we convert and store the string in the container
    device.char_write(characteristic, b , wait_for_response=True) # Then we write to the characteristic using the bytearray value
    sleep(0.1) # wait 100 ms and do it again with the next value

# After we finish the comunication we have to stop the adapter so other apps can use the bluetooth and we can reopen it for other uses
adapter.stop()

# %%
