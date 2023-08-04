#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

DHT dht(0, DHT11); //(sensor pin,sensor type)
BlynkTimer timer;

char auth[] = "EBGjpX7oicqEKzef-0495KyiOrujgCHa"; //Enter the Auth code which was send by Blink
char ssid[] = "Shaz_Sohail";  //Enter your WIFI Name
char pass[] = "Keshwani321";  //Enter your WIFI Password

void weather() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  int r = analogRead(A0);

  r = map(r, 0, 1023, 100, 0);
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Blynk.virtualWrite(V0, t);  //V0 is for Temperature
  Blynk.virtualWrite(V1, h);  //V1 is for Humidity
  Blynk.virtualWrite(V2, r);  //V2 is for Rainfall

  if (h>=80){
    Blynk.logEvent("humidity_alert","Humidity is ", h,"Percent", "Alert! It is going to rain")
  }
  if (t>=40){
    Blynk.logEvent("temperature_alert", "Temperature is ", t, "Degree Celcius", "Alert! It is very hot outside. Heatwaves may affect you")
  }
    if (r>=80){
    Blynk.logEvent("rain_alert", "Rain is ", r, "mm" "Alert!, It is heavyly raining outside.")
  }
}

void setup() {
  Serial.begin(9600); // See the connection status in Serial Monitor
  Blynk.begin(auth, ssid, pass);
  dht.begin();
  // Setup a function to be called every second
  timer.setInterval(10L, weather);
}

void loop() {
  Blynk.run(); // Initiates Blynk
  timer.run(); // Initiates SimpleTimer
}
