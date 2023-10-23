const int ledPin1 = 27;  
const int ledPin2 = 26;  
const int ledPin3 = 25;  

const int channel1 = 0;
const int channel2 = 1;
const int channel3 = 2;

const int freq = 5000;
const int resolution = 8;

void setup() {
  ledcSetup(channel1, freq, resolution);
  ledcAttachPin(ledPin1, channel1);

  ledcSetup(channel2, freq, resolution);
  ledcAttachPin(ledPin2, channel2);

  ledcSetup(channel3, freq, resolution);
  ledcAttachPin(ledPin3, channel3);
}

void loop() {
  breathe(channel1);
  breathe(channel2);
  breathe(channel3);
  breathe(channel2);
}

void breathe(int channel) {
  for (int i = 0; i <= 255; i++) {
    int brightness = (i * i * i) / (255 * 255);
    ledcWrite(channel, brightness); 
    delay(10); 
  }

  for (int i = 255; i >= 0; i--) {
    int brightness = (i * i * i) / (255 * 255);
    ledcWrite(channel, brightness); 
    delay(10); 
  }
}
