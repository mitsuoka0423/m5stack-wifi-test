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

// パターン1* loopでは、WiFi.status()で接続状況を確認するだけ
// アクセスポイントをOFFにしても、数十秒～数分は接続状態と判定され、通信に失敗する可能性がある。
void loop()
{
  Serial.println(WiFi.status());
  Serial.println(WiFi.localIP());
  delay(1000);
}