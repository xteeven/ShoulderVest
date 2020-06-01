void setup() {
  Serial.begin(115200);

  pinMode(LED, OUTPUT);

  // Create the BLE Device
  BLEDevice::init(nameOfTheVest); // Give it a name

  // Create the BLE Server
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  // Create the BLE Service
  BLEService *pService = pServer->createService(SERVICE_UUID);

  // Create a BLE Characteristic
  pCharacteristic = pService->createCharacteristic(
                      CHARACTERISTIC_UUID_TX,
                      BLECharacteristic::PROPERTY_NOTIFY
                    );
                      
  pCharacteristic->addDescriptor(new BLE2902());

  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID_RX,
                                         BLECharacteristic::PROPERTY_WRITE
                                       );

  pCharacteristic->setCallbacks(new MyCallbacks());

  // Start the service
  pService->start();

  // Start advertising
  pServer->getAdvertising()->start();
  Serial.println("Waiting a client connection to notify...");

  ledcSetup(MOTOR_CHANNEL_0, LEDC_BASE_FREQ, LEDC_TIMER_13_BIT);
  ledcSetup(MOTOR_CHANNEL_1, LEDC_BASE_FREQ, LEDC_TIMER_13_BIT);
  ledcSetup(MOTOR_CHANNEL_2, LEDC_BASE_FREQ, LEDC_TIMER_13_BIT);
  ledcSetup(MOTOR_CHANNEL_3, LEDC_BASE_FREQ, LEDC_TIMER_13_BIT);
  ledcAttachPin(MOTOR1_PIN, MOTOR_CHANNEL_0);
  ledcAttachPin(MOTOR2_PIN, MOTOR_CHANNEL_1);
  ledcAttachPin(MOTOR3_PIN, MOTOR_CHANNEL_2);
  ledcAttachPin(MOTOR4_PIN, MOTOR_CHANNEL_3);



  
}
