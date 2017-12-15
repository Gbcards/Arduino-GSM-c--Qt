#include <SoftwareSerial.h>
SoftwareSerial SIM900(7, 8);

String numG = "";
String msgG = "";

void setup()
{
  SIM900.begin(19200);  //Configura velocidad del puerto serie para el SIM900
  Serial.begin(19200);  //Configura velocidad del puerto serie del Arduino
  Serial.println("OK");
}

void llamar()
{
  Serial.println("Realizando llamada...");
  SIM900.println("ATD" + numG + ";"); //Comando AT para realizar una llamada
  delay(20000);  // Espera 30 segundos mientras realiza la llamada
  SIM900.println("ATH");  // Cuelga la llamada
  Serial.println("Llamada finalizada");
}

void mensaje_sms()
   {
      Serial.println("Enviando SMS...");
      SIM900.print("AT+CMGF=1\r");  //Configura el modo texto para enviar o recibir mensajes
      delay(1000);
      SIM900.println("AT+CMGS=\""+numG+"\"");  //Numero al que vamos a enviar el mensaje
      delay(1000);
      SIM900.println(msgG);  // Texto del SMS
      delay(100);
      SIM900.println((char)26); //Comando de finalización ^Z
      delay(100);
      SIM900.println();
      delay(1000);  // Esperamos un tiempo para que envíe el SMS
      Serial.println("SMS enviado");
   }
   
void loop()
{
  if (Serial.available())
  {
    String input = Serial.readString();

    String  opcion;
    opcion = input.substring(4, 5);

    if (opcion == "l")
    {
      Serial.println("llamar");
      numG = input.substring(5, 14);
      msgG = "";
      Serial.println(numG);
      Serial.println(msgG);
      llamar();
    }
    else if(opcion == "m")
    {
      Serial.println("Enviar mensaje");
      numG = input.substring(5, 14);
      msgG = input.substring(18, input.length());
      Serial.println(numG);
      Serial.println(msgG);
      mensaje_sms();
    }
  }
}