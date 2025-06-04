/*
  Sistema de Alerta Climático em Tempo Real
  Desenvolvido por:
    - Kaua Carvalho (RM566371)
    - Mariana Silva (RM564241)
    - Vitor Tigre (RM561746)

  O sistema monitora variáveis ambientais (nível da água, umidade, luminosidade e vento)
  para detectar riscos de enchentes e chuvas fortes. Utiliza LEDs RGB e buzzer para alertas visuais e sonoros,
  além de um display LCD para informar o status atual.

  Observações importantes:
  - O sensor ultrassônico começa com nível d'água simulado em 400cm (nível seguro).
  - Quando o nível d'água cair para 395cm, já indica enchente (alerta vermelho).
  - Abaixo de 390cm, aumenta o risco.
  - Quando o nível atingir 10cm (ou menos), o buzzer é ativado junto com o LED vermelho piscando (alerta grave).
  - O sistema considera também umidade alta, vento forte e luminosidade baixa para aumentar o risco.
*/

#include <DHT.h>
#include <LiquidCrystal_I2C.h>

// Configuração do sensor de temperatura e umidade DHT22
#define DHTPIN 2
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// Definição dos pinos dos componentes
const int redPin = 3;         // LED RGB - vermelho
const int greenPin = 5;       // LED RGB - verde
const int bluePin = 6;        // LED RGB - azul
const int potVentoPin = A2;   // Potenciômetro para simular intensidade do vento
const int trigPin = 10;       // Sensor ultrassônico HC-SR04 - trig
const int echoPin = 11;       // Sensor ultrassônico HC-SR04 - echo
const int ldrPin = A1;        // LDR para luminosidade (quanto maior valor, mais escuro)
const int buzzerPin = 9;      // Buzzer para alerta sonoro

// Inicialização do display LCD I2C 16x2 no endereço 0x27
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);
  dht.begin();     // Inicializa sensor DHT22
  lcd.init();      // Inicializa LCD
  lcd.backlight(); // Liga backlight do LCD

  // Configura os pinos como saída ou entrada
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // Leitura dos sensores
  float umidade = dht.readHumidity();               // Umidade relativa do ar
  int luminosidade = analogRead(ldrPin);            // Luz ambiente (quanto maior, mais escuro)
  float nivelAgua = lerSensorUltrassonico();        // Nível da água em cm
  int ventoIntensidade = analogRead(potVentoPin);   // Intensidade do vento (potenciômetro)

  // Variável para acumular pontos de risco
  int pontos = 0;

  // Avaliação do nível da água:
  // Quanto mais baixo o nível, maior o risco (água subindo)
  // A partir de 395 cm já é enchente (pontos maiores)
  if (nivelAgua <= 10) {
    pontos += 4;  // Enchente grave - alerta máximo (buzzer e LED piscando)
  } else if (nivelAgua < 50) {
    pontos += 2;  // Água subindo - atenção vermelha
  }

  // Umidade alta contribui para risco de chuva
  if (umidade > 70) pontos += 1;

  // Intensidade do vento: alerta em dois níveis
  if (ventoIntensidade > 350) pontos += 1;   // Vento moderado
  if (ventoIntensidade > 700) pontos += 1;   // Vento forte

  // Condição crítica: céu escuro (luminosidade alta), umidade e vento altos
  // Lembre que luminosidade é maior quando está escuro (valores altos do LDR indicam pouca luz)
  if (luminosidade > 700 && umidade > 70 && ventoIntensidade > 700) pontos += 1;

  // Exibição dos dados no LCD e controle dos alertas (LEDs e buzzer)
  mostrarNoLCD(pontos, nivelAgua, ventoIntensidade);
  controlarLEDeBuzzer(pontos, nivelAgua <= 10);

  delay(500); // Pequena pausa antes da próxima leitura
}

// Função que exibe informações no LCD
void mostrarNoLCD(int risco, float agua, int vento) {
  lcd.clear();

  // Linha 1: mostra pontos de risco e % do vento
  lcd.setCursor(0, 0);
  lcd.print("Risco: ");
  lcd.print(risco);
  lcd.print("pts V:");
  lcd.print(map(vento, 0, 1023, 0, 100));
  lcd.print("%");

  // Linha 2: nível da água e mensagem de status
  lcd.setCursor(0, 1);
  lcd.print("Agua: ");
  lcd.print(agua);
  lcd.print("cm ");

  if (risco >= 4 || agua <= 10) {
    lcd.print("PERIGO!");
  } else if (risco >= 1) {
    lcd.print("CUIDADO");
  } else {
    lcd.print("NORMAL");
  }
}

// Função para controlar LEDs e buzzer conforme nível de risco
void controlarLEDeBuzzer(int pontos, bool enchenteGrave) {
  noTone(buzzerPin); // Desliga buzzer inicialmente

  // Alerta máximo: água em 10cm ou pontos 4 ou mais
  if (pontos >= 4 || enchenteGrave) {
    for (int i = 0; i < 2; i++) {
      setColor(255, 0, 0); // Pisca LED vermelho
      tone(buzzerPin, 1000); // Buzzer ligado
      delay(300);
      setColor(0, 0, 0); // Apaga LED
      noTone(buzzerPin); // Buzzer desligado
      delay(200);
    }
    return;
  }

  // Outros níveis de alerta
  switch (pontos) {
    case 3:
      setColor(255, 0, 0); // Vermelho fixo (risco alto)
      break;
    case 2:
      setColor(255, 50, 0); // Laranja (risco médio)
      break;
    case 1:
      setColor(255, 255, 0); // Amarelo (risco baixo)
      break;
    default:
      setColor(0, 0, 0); // LED apagado (sem risco)
      break;
  }
}

// Função para definir cor do LED RGB
void setColor(int red, int green, int blue) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}

// Função para ler o sensor ultrassônico e calcular distância (nível da água)
float lerSensorUltrassonico() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  float distance = duration * 0.034 / 2;

  // Filtra valores errôneos (fora do alcance do sensor)
  if (distance > 400 || distance < 2) {
    return 400; // Valor padrão seguro (nível normal)
  }

  return distance;
}
