#include <hp_BH1750.h>
#include <DHT.h>

// DHT
#define DHTTYPE DHT22
DHT dht(DHT22_SENSOR_PIN, DHTTYPE);

// Light Sensitivity sensor
hp_BH1750 lux_sensor;  

enum HUM_STAT {
  HUM_NORMAL = 0,
  HUM_COMFORTABLE = 1,
  HUM_DRY = 2,
  HUM_WET = 3
};

void setup_sensors() {
  dht.begin();
  lux_sensor.begin(BH1750_TO_GROUND);
  lux_sensor.calibrateTiming();
  lux_sensor.start();
}

void get_dht_sensor_value(float &humidity, float &temperature, HUM_STAT &humidity_status) {
  //Read data and store it to variables hum and temp
  humidity = dht.readHumidity(); // in percentages
  temperature = dht.readTemperature(); // in degrees Celsius
  humidity_status = HUM_NORMAL;
  if (humidity < 40) {
    humidity_status = HUM_DRY; // dry
  } else if (humidity < 60) {
    humidity_status = HUM_COMFORTABLE; // comfortable
  } else {
    humidity_status = HUM_WET; // wet
  }
  Serial.print("<DEBUG DHT> ");
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print("(" + String(humidity_status) + ")");
  Serial.print(", % Temp: ");
  Serial.print(temperature);
  Serial.println(" Celsius");
}

void get_cb_value(int &soil_hum, int &cb) {
  cb = 0;
  if (soil_hum <= 5) {
    cb = 60;
  } else if (soil_hum <= 15) {
    cb = 40;
  } else if (soil_hum <= 30) {
    cb = 20;
  } else if (soil_hum <= 50) {
    cb = 10;
  }
}

void get_soil_hum_sensor_value(int &soil_hum, int &cb) {
  // read the analog in value
  int sensorValue = analogRead(SOIL_HUM_ANALOG_PIN);
  // map it to the range of the PWM out
  soil_hum = map(sensorValue, 0, 1024, 0, 255);
  get_cb_value(soil_hum, cb);
  Serial.print("<DEBUG SOIL> ");
  Serial.print("sensorValue = ");
  Serial.print(sensorValue);
  Serial.print(", Soil Moisture percentage = ");
  Serial.print(soil_hum);
  Serial.print("% , Water Tension = ");
  Serial.print(cb);
  Serial.println("cb");
}

void get_lux_sensor_value(float &lux) {
  // this is a blocking read
  lux_sensor.start();                 //start measurement
  lux = lux_sensor.getLux();   //read the result

  Serial.print("<DEBUG LUX> ");
  Serial.print("sensorValue = ");
  Serial.print(lux);
  Serial.println(" lux");
}
