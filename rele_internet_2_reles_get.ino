#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0x90, 0xA2, 0xDA, 0x00, 0x9B, 0x36 }; //MAC ADRESS UNIVERSAL PARA PLACAS GENÉRICAS
byte ip[] = { 192, 168, 10, 99 }; // ENDEREÇO DE IP - DEFINIDO PELO USUÁRIO
byte gateway[] = { 192, 168, 10, 1 }; // ENDEREÇO GATEWAY DO ROTEADOR
byte subnet[] = { 255, 255, 255, 0 }; //SUBMASCARA DO ROTEADOR
EthernetServer server(8081); //PORTA QUE SERÁ ABERTA

String readString;

int rele[2];
char* nome_rele[2];
int estado_rele[2];
int tipo_rele[2];

//////////////////////

void setup() {

  //CONFIGURACAO DAS PORTAS EM QUE OS RELES ESTAO CONECTADOS:
  rele[0] = 2;
  rele[1] = 9;

  //NOME DOS RELÊS
  nome_rele[0] = "Sala";
  nome_rele[1] = "Quarto";

  //ESTADO DOS RELêS
  estado_rele[0] = 0;
  estado_rele[1] = 0;

  //TIPO DOS BOTOES 0-> toggle, 1-> pulse
  tipo_rele[0] = 0;
  tipo_rele[1] = 0;

  pinMode(rele[0], OUTPUT);
  pinMode(rele[1], OUTPUT);

  Ethernet.begin(mac, ip, gateway, subnet); //COMEÇAR O ETHERNET SHIELD, COM OS DADOS ACIMA
  server.begin(); //COMECAR O WEBSERVER
  Serial.begin(9600);  //HABILITAR O SERIAL
  Serial.println("Arduino + Ethernet Shield + Relês V2.0"); //IMPRIMIR NO SERIAL
}

void loop() {
  // CRIAR A CONEXÃO COM O CLIENTE
  EthernetClient client = server.available();
  if (client) {
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();

        //read char by char HTTP request
        if (readString.length() < 100) {

          //store characters to string
          readString += c;
          Serial.print(c);
        }

        //if HTTP request has ended
        if (c == '\n') {

          ///////////////////// control arduino pin
          Serial.println(readString); //print to serial monitor for debuging

          char pesquisa[] = "?xx";
          for (int i = 2; i <= 3; i++) {
            pesquisa[2] = i + 48;

            pesquisa[1] = 'l';
            if (readString.indexOf(pesquisa) > 0) {
              if (tipo_rele[i - 2] == 1) {
                digitalWrite(rele[i - 2], HIGH);  // LIGA O RELE - HIGH
                Serial.println("Rele");
                Serial.println(i);
                Serial.println("On");
                digitalWrite(rele[i - 2], LOW);
                Serial.print("Rele");
                Serial.print(i);
                Serial.println("Off");
              } else {
                digitalWrite(rele[i - 2], HIGH);
                Serial.print("Rele");
                Serial.print(i);
                Serial.println("On");
                estado_rele[i - 2] = 1;
              }
            }
            pesquisa[1] = 'd';
            if (readString.indexOf(pesquisa) > 0) {
              digitalWrite(rele[i - 2], LOW);
              Serial.print("Rele");
              Serial.print(i);
              Serial.println("Off");
              estado_rele[i - 2] = 0;
            }

          }



          //clearing string for next read
          readString = "";


          /////////////// PAGINA HTML //////////////////////////

          client.println("HTTP/1.1 200 OK"); //send new page
          client.println("Content-Type: text/html");
          client.println();

          client.println("<html>");
          client.println("<head>");
          client.println("<title>Arduino + Ethernet Shield + Relê</title>");
          client.println("<meta charset=utf-8'>");
          client.println("<meta name='viewport' content='width=device-width, initial-scale=1, user-scalable=no'>");
          client.println("<meta name='apple-mobile-web-app-capable' content='yes' />");
          client.println("<meta name='apple-mobile-web-app-status-bar-style' content='white'>");
          client.println("<link rel='stylesheet' href='http://maxcdn.bootstrapcdn.com/bootstrap/3.3.5/css/bootstrap.min.css'>");
          client.println("<link rel='icon' href='http://www.blocodochapolin.com.br/arduino_rele/img/icone.png' type='image/x-icon' />");
          client.println("<script type='text/javascript' src='https://ajax.googleapis.com/ajax/libs/jquery/1.11.3/jquery.min.js'></script>");
          client.println("<script type='text/javascript' src='http://maxcdn.bootstrapcdn.com/bootstrap/3.3.5/js/bootstrap.min.js'></script>");
          client.println("<script type='text/javascript' src='http://www.blocodochapolin.com.br/arduino/rele_internet_2_reles_get/2reles_get.js'></script>");
          client.println("</head>");
          client.println("<body>");
          client.println("<div id='container' align='center'>");
          client.println("<h2>Arduino + Ethernet Shield + Relês v2.0</h2>");
          client.println("<hr><br>");
          for (int i = 0; i <= 1; i++) {
            client.print("<div id='porta");
            client.print(i + 2);
            client.print("_estado' style='display: none'>");
            client.print(estado_rele[i]);
            client.println("</div>");
            client.print("<div id='porta");
            client.print(i + 2);
            client.print("_titulo' style='display: none'>");
            client.print(nome_rele[i]);
            client.println("</div>");
            client.print("<div id='porta");
            client.print(i + 2);
            client.println("_botao' style='position: relative;'></div><br>");
          }
          client.println("</div>");
          client.println("<script>VerificaEstado();</script>");
          client.println("</body>");
          client.println("</head>");
          client.println("</html>");

          delay(1);
          //stopping client
          client.stop();
        }
      }
    }
  }
}

