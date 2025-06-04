// #include "globals.h"
// // WiFiClientSecure client;

// void setup()
// {
//   Serial.begin(UART_DEFAUT_BAUDRATE, SERIAL_8N1);
//   initRFID();
//   Serial.println("Log:");
//   delay(2000);
//   connect_init();
//   Serial.println("Ready to scan RFID cards...");
// }

// void loop()
// {
//   String uid = readUID();
//   if (uid != "")
//   {
//     Serial.println("Scanned UID: " + uid);
//     checkUIDWithGoogleSheet(uid);
//   }
//   delay(2000);
// }

#include "globals.h"
MFRC522 rfid(SDA, RST);
String uidString;
const char *ssid = "22-08";
const char *password = "414414a2";
// Google script Web_App_URL.
String Web_App_URL = "https://script.google.com/macros/s/AKfycbyhdSBnSCtKOrLOUFU5dcPTf3vYwEDrB7_AfBr39yJNQKmI4brm7lD9bTH4avFGC-0j/exec";
#define On_Board_LED_PIN 2
#define MAX_STUDENTS 10
struct Student
{
  String id;
  char code[10];
  char name[30];
};
Student students[MAX_STUDENTS];
int studentCount = 0;
int runMode = 2;
const int btnIO = 15;
bool btnIOState = HIGH;
unsigned long timeDelay = millis();
unsigned long timeDelay2 = millis();
bool InOutState = 0; // 0: vào, 1:ra
const int ledIO = 4;

char *getStudentNameById(char *uid);
void readDataSheet(void *pvParams);
void writeUIDSheet();
void writeLogSheet();
int countElements(const char *data, char delimiter);

void readUID()
{
  // Prepare key - all keys are set to FFFFFFFFFFFFh at chip delivery from the factory.
  MFRC522::MIFARE_Key key;
  for (byte i = 0; i < 6; i++)
  {
    key.keyByte[i] = 0xFF;
  }
  // Look for new cards
  if (!rfid.PICC_IsNewCardPresent())
  {
    return;
  }

  // Select one of the cards
  if (!rfid.PICC_ReadCardSerial())
  {
    return;
  }
  // Now a card is selected. The UID and SAK is in mfrc522.uid.

  uidString = "";
  for (byte i = 0; i < rfid.uid.size; i++)
  {
    uidString.concat(String(rfid.uid.uidByte[i] < 0x10 ? "0" : ""));
    uidString.concat(String(rfid.uid.uidByte[i], HEX));
  }
  uidString.toUpperCase();
  Serial.println("Card UID: " + uidString);
  if (runMode == 1)
    writeUIDSheet();
  else if (runMode == 2)
    writeLogSheet();
  // Dump PICC type
  byte piccType = rfid.PICC_GetType(rfid.uid.sak);
  //    Serial.print("PICC type: ");
  // Serial.println(mfrc522.PICC_GetTypeName(piccType));
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI && piccType != MFRC522::PICC_TYPE_MIFARE_1K && piccType != MFRC522::PICC_TYPE_MIFARE_4K)
  {
    // Serial.println("This sample only works with MIFARE Classic cards.");
    return;
  }
}
void readDataSheet(void *pvParams)
{
  while (1)
  {

    if (WiFi.status() == WL_CONNECTED)
    {
      digitalWrite(On_Board_LED_PIN, HIGH);

      // Create a URL for reading or getting data from Google Sheets.
      String Read_Data_URL = Web_App_URL + "?sts=read";

      Serial.println();
      Serial.println("-------------");
      Serial.println("Read data from Google Spreadsheet...");
      Serial.print("URL : ");
      Serial.println(Read_Data_URL);

      //::::::::::::::::::The process of reading or getting data from Google Sheets.
      // Initialize HTTPClient as "http".
      HTTPClient http;

      // HTTP GET Request.
      http.begin(Read_Data_URL.c_str());
      http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);

      // Gets the HTTP status code.
      int httpCode = http.GET();
      Serial.print("HTTP Status Code : ");
      Serial.println(httpCode);

      // Getting response from google sheet.
      String payload;
      studentCount = 0;
      if (httpCode > 0)
      {
        payload = http.getString();
        Serial.println("Payload : " + payload);

        // Tách dữ liệu
        char charArray[payload.length() + 1];
        payload.toCharArray(charArray, payload.length() + 1);
        // Đếm số phần tử
        int numberOfElements = countElements(charArray, ',');
        Serial.println("Number of elements: " + String(numberOfElements));
        char *token = strtok(charArray, ",");
        while (token != NULL && studentCount < numberOfElements / 3)
        {
          students[studentCount].id = atoi(token); // Chuyển đổi ID từ chuỗi sang số nguyên
          token = strtok(NULL, ",");
          strcpy(students[studentCount].code, token); // Sao chép mã học sinh
          token = strtok(NULL, ",");
          strcpy(students[studentCount].name, token); // Sao chép tên học sinh

          studentCount++;
          token = strtok(NULL, ",");
        }

        // In ra danh sách học sinh
        for (int i = 0; i < studentCount; i++)
        {
          Serial.print("ID: ");
          Serial.println(students[i].id);
          Serial.print("Code: ");
          Serial.println(students[i].code);
          Serial.print("Name: ");
          Serial.println(students[i].name);
        }
      }

      http.end();
      //::::::::::::::::::

      digitalWrite(On_Board_LED_PIN, LOW);
      Serial.println("-------------");
      // if (studentCount > 0)
      //   return;
      // else
      //   return;
    }
    delay(20000);
  }
}

void writeUIDSheet()
{
  String Send_Data_URL = Web_App_URL + "?sts=writeuid";
  Send_Data_URL += "&uid=" + uidString;
  Serial.println();
  Serial.println("-------------");
  Serial.println("Send data to Google Spreadsheet...");
  Serial.print("URL : ");
  Serial.println(Send_Data_URL);
  // Initialize HTTPClient as "http".
  HTTPClient http;

  // HTTP GET Request.
  http.begin(Send_Data_URL.c_str());
  http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);

  // Gets the HTTP status code.
  int httpCode = http.GET();
  Serial.print("HTTP Status Code : ");
  Serial.println(httpCode);

  // Getting response from google sheets.
  String payload;
  if (httpCode > 0)
  {
    payload = http.getString();
    Serial.println("Payload : " + payload);
  }

  http.end();
}
String urlencode(String str);
void writeLogSheet()
{
  char charArray[uidString.length() + 1];
  uidString.toCharArray(charArray, uidString.length() + 1);
  char *studentName = getStudentNameById(charArray);
  if (studentName != nullptr)
  {
    Serial.print("Tên học sinh với ID ");
    Serial.print(uidString);
    Serial.print(" là: ");
    Serial.println(studentName);

    String Send_Data_URL = Web_App_URL + "?sts=writelog";
    Send_Data_URL += "&uid=" + uidString;
    Send_Data_URL += "&name=" + urlencode(String(studentName));
    if (InOutState == 0)
    {
      Send_Data_URL += "&inout=" + urlencode("VÀO");
    }
    else
    {
      Send_Data_URL += "&inout=" + urlencode("RA");
    }

    Serial.println();
    Serial.println("-------------");
    Serial.println("Send data to Google Spreadsheet...");
    Serial.print("URL : ");
    Serial.println(Send_Data_URL);
    // Initialize HTTPClient as "http".
    HTTPClient http;

    // HTTP GET Request.
    http.begin(Send_Data_URL.c_str());
    http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);

    // Gets the HTTP status code.
    int httpCode = http.GET();
    Serial.print("HTTP Status Code : ");
    Serial.println(httpCode);

    // Getting response from google sheets.
    String payload;
    if (httpCode > 0)
    {
      payload = http.getString();
      Serial.println("Payload : " + payload);
    }

    http.end();
  }
  else
  {
    Serial.print("Không tìm thấy học sinh với ID ");
    Serial.println(uidString);
  }
}
String urlencode(String str)
{
  String encodedString = "";
  char c;
  char code0;
  char code1;
  char code2;
  for (int i = 0; i < str.length(); i++)
  {
    c = str.charAt(i);
    if (c == ' ')
    {
      encodedString += '+';
    }
    else if (isalnum(c))
    {
      encodedString += c;
    }
    else
    {
      code1 = (c & 0xf) + '0';
      if ((c & 0xf) > 9)
      {
        code1 = (c & 0xf) - 10 + 'A';
      }
      c = (c >> 4) & 0xf;
      code0 = c + '0';
      if (c > 9)
      {
        code0 = c - 10 + 'A';
      }
      code2 = '\0';
      encodedString += '%';
      encodedString += code0;
      encodedString += code1;
    }
    yield();
  }
  return encodedString;
}
char *getStudentNameById(char *uid)
{
  for (int i = 0; i < studentCount; i++)
  {
    if (strcmp(students[i].code, uid) == 0)
    {
      return students[i].name;
    }
  }
  return nullptr; // Trả về nullptr nếu không tìm thấy
}
int countElements(const char *data, char delimiter)
{
  // Tạo một bản sao của chuỗi dữ liệu để tránh thay đổi chuỗi gốc
  char dataCopy[strlen(data) + 1];
  strcpy(dataCopy, data);

  int count = 0;
  char *token = strtok(dataCopy, &delimiter);
  while (token != NULL)
  {
    count++;
    token = strtok(NULL, &delimiter);
  }
  return count;
}

void rfid_func(void *pr)
{
  while (1)
  {
    if (millis() - timeDelay2 > 500)
    {
      readUID();
      timeDelay2 = millis();
    }
    if (digitalRead(btnIO) == LOW)
    {
      if (btnIOState == HIGH)
      {
        if (millis() - timeDelay > 500)
        {
          // Thực hiện lệnh
          InOutState = !InOutState;
          digitalWrite(ledIO, InOutState);
          timeDelay = millis();
        }
        btnIOState = LOW;
      }
    }
    else
    {
      btnIOState = HIGH;
    }
    delay(500);
  }
}
void setup()
{
  Serial.begin(9600);
  pinMode(btnIO, INPUT_PULLUP);
  pinMode(ledIO, OUTPUT);
  pinMode(On_Board_LED_PIN, OUTPUT);
  Serial.println();
  Serial.println("-------------");
  Serial.println("WIFI mode : STA");
  Serial.println("-------------");
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  SPI.begin();     // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(1000);
  }
  xTaskCreate(readDataSheet, "read", 1024 * 20, nullptr, 10, nullptr);
  xTaskCreate(rfid_func, "rfid", 1024 * 10, nullptr, 1, nullptr);
  // if (!readDataSheet())
  //   Serial.println("Can't read data from google sheet!");
}

void loop()
{
}