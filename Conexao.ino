void connectMQTT() {
  client.setServer(MQTT_SERVER, MQTT_PORT);
  while (!client.connected()) {
    Serial.println("Connecting to MQTT server...");
    if (client.connect(DEVICE_ID, MQTT_ACCESS_KEY, MQTT_ACCESS_SECRET)) {
      Serial.println("Connected to WEGNOLOGY platform");
      Serial.println("-------------"); 
    } else {
      Serial.print("Failed to connect to WEGNOLOGY platform, error code: ");
      Serial.print(client.state());
      delay(2000);
    }
  }
}

void connectWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi network");
  Serial.println("-------------"); 
}

void call_pub() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Reconnecting to WiFi");
    connectWiFi();
  }
  if (!client.connected()) {
    Serial.println("Reconnecting to WEGNOLOGY platform");
    connectMQTT();
  }

  client.loop();
  publishData();
  Serial.println("-------------");    
}

void publishData() {
  
  DynamicJsonDocument doc(200);
  doc["data"]["motor"] = 1;
  doc["data"]["alto"] = Palta;
  doc["data"]["medio"] = Pmedia;
  doc["data"]["baixo"] = Pbaixa;

  String payload;
  serializeJson(doc, payload);
  payload.toCharArray(attributes, 200);
  Serial.println(payload);

  if (client.connected()) {
      client.publish(MQTT_TOPIC, attributes);
    }
}
