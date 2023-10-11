void Scan(){
  ValorSensorCapacitivo = digitalRead(SensorCapacitivo);  // lê o valor da porta digital
  ValorSensorIndutivo = digitalRead(SensorIndutivo);  // lê o valor da porta digital
  ValorOpticoBaixo = digitalRead(OpticoBaixo);  // lê o valor da porta digital
  ValorOpticoMedio = digitalRead(OpticoMedio);  // lê o valor da porta digital
  ValorOpticoAlto = digitalRead(OpticoAlto);  // lê o valor da porta digital
  ValorEsteira01 = digitalRead(Esteira01);  // lê o valor da porta digital
  ValorEsteira02 = digitalRead(Esteira02);  // lê o valor da porta digital
  ValorEsteira03 = digitalRead(Esteira03);  // lê o valor da porta digital

  Serial.print("");
  Serial.print("Sensor Capacitivo: ");
  Serial.println(ValorSensorCapacitivo);
  Serial.print("Sensor Indutivo: ");
  Serial.println(ValorSensorIndutivo);
  Serial.print("Sensor Optico Baixo: ");
  Serial.println(ValorOpticoBaixo);
  Serial.print("Sensor Optico Medio: ");
  Serial.println(ValorOpticoMedio);
  Serial.print("Sensor Optico Alto: ");
  Serial.println(ValorOpticoAlto);
  Serial.print("Sensor Esteira 01: ");
  Serial.println(ValorEsteira01);
  Serial.print("Sensor Esteira 02: ");
  Serial.println(ValorEsteira02);
  Serial.print("Sensor Esteira 03: ");
  Serial.println(ValorEsteira03);

  Serial.println("----------------------------------------------------");
  Serial.println("----------------------------------------------------");
}
