class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
    };

    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
    }
};

class MyCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {

      std::string rxValue = pCharacteristic->getValue();

      if (rxValue.length() > 0) {

        String msg = rxValue.c_str();
         Serial.println("SENT");
        // Do stuff based on the command received from the app
        if(rxValue.length()==7){
          
          SetValues(msg.substring(0, 2).toInt(),msg.substring(3, 7));
        
        }

        
      }

    }
};


void SetValues(int ampt, String motorst){
  
 Serial.println(ampt);
  Serial.println(motorst);

 int amp = ampt*2.5;
if(motorst[0]=='1'){ledcAnalogWrite(MOTOR_CHANNEL_0, amp);}else{ledcAnalogWrite(MOTOR_CHANNEL_0, 0);}
if(motorst[1]=='1'){ledcAnalogWrite(MOTOR_CHANNEL_1, amp);}else{ledcAnalogWrite(MOTOR_CHANNEL_1, 0);}
if(motorst[2]=='1'){ledcAnalogWrite(MOTOR_CHANNEL_2, amp);}else{ledcAnalogWrite(MOTOR_CHANNEL_2, 0);}
if(motorst[3]=='1'){ledcAnalogWrite(MOTOR_CHANNEL_3, amp);}else{ledcAnalogWrite(MOTOR_CHANNEL_3, 0);}
      
      
    
    
  
  }
