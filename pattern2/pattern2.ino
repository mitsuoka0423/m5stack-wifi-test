#include <M5Atom.h>
#include <WiFi.h>

const char *SSID = "xxxxxxxx";
const char *PASSWORD = "xxxxxxxx";

void setup()
{
  Serial.begin(115200);
  M5.begin(true, false, true);
  delay(200);

  Serial.println("Wifi connecting.");
  WiFi.begin(SSID, PASSWORD);

  uint64_t wifiConnectStartTime = millis();
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);

    if ((int)(millis() - wifiConnectStartTime) > 10000)
    {
      wifiConnectStartTime = millis();
      Serial.println();
      Serial.println("try again");
      WiFi.disconnect();
      WiFi.begin();
      Serial.println("Wifi connecting.");
    }
  }
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

// パターン2: loopでも、再度WiFi.begin()を実行する
// アクセスポイントのON/OFFをほぼリアルタイムに検出できる。オーバーヘッドもほぼなし。
void loop()
{
  uint64_t wifiConnectStartTime = millis();
  WiFi.begin();
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);

    if ((int)(millis() - wifiConnectStartTime) > 10000)
    {
      wifiConnectStartTime = millis();
      Serial.println();
      Serial.println("try again");
      WiFi.disconnect();
      WiFi.begin();
      Serial.println("Wifi connecting.");
    }
  }
  Serial.println("WiFi connected");

  Serial.println(WiFi.status());
  Serial.println(WiFi.localIP());
  delay(1000);
}