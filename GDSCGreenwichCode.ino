const int swPin = 2;        // Connect the SW-420 signal pin to digital pin 2
const int signalPin = 11;   // Connect the signal pin to digital pin 11
int16_t thresholdVibration = 1000; // Ngưỡng cảnh báo rung, bạn có thể điều chỉnh giá trị này
int16_t thresholdImpact = 2000;   // Ngưỡng cảnh báo va chạm, bạn có thể điều chỉnh giá trị này
unsigned long lastActivityTime = 0; // Thời điểm cuối cùng có sự thay đổi
bool sw420Active = false; // Trạng thái của SW-420
bool sleepMode = false;  // Trạng thái chế độ ngủ

void setup() {
  Serial.begin(9600);
  pinMode(swPin, INPUT);
  pinMode(signalPin, OUTPUT);
}

void loop() {
  // Đọc giá trị cảm biến rung
  int sensorValue = digitalRead(swPin);

  // Kiểm tra nếu cảm biến rung phát hiện rung động và không có sự thay đổi từ SW-420
  if (sensorValue == HIGH && !sw420Active) {
    Serial.println("Vibration detected!");
    sw420Active = true; // Bật cờ cho biết SW-420 đã kích hoạt
    lastActivityTime = millis(); // Reset thời gian khi có sự thay đổi
  }

  // Kiểm tra nếu cảm biến rung phát hiện rung động và có sự thay đổi từ SW-420
  if (sw420Active && (sensorValue == HIGH)) {
    Serial.println("Impact detected!");
    // Thực hiện các hành động cần thiết khi phát hiện va chạm
    // Ví dụ: Bật cảnh báo, gửi thông báo, hoặc thực hiện một hành động cụ thể
    
    // Gửi tín hiệu ra chân D11
    digitalWrite(signalPin, HIGH);
  } else {
    // Không có sự thay đổi, tắt tín hiệu ra chân D11
    digitalWrite(signalPin, LOW);
  }

  // Kiểm tra inactivity sau mỗi 15 giây nếu không có sự thay đổi từ SW-420
  if (sw420Active && millis() - lastActivityTime > 15000) {
    Serial.println("No activity for 15 seconds. Sending warning!");
    // Thực hiện các hành động cần thiết khi không có sự thay đổi từ SW-420 trong 15 giây
    // Ví dụ: Bật cảnh báo, gửi thông báo, hoặc thực hiện một hành động cụ thể
    
    // Gửi tín hiệu ra chân D11
    digitalWrite(signalPin, HIGH);
    
    sw420Active = false; // Tắt cờ SW-420 đã kích hoạt để chuẩn bị cho lần kích hoạt tiếp theo
  }

  // Đợi một khoảng thời gian trước khi đọc lại dữ liệu
  delay(100);
}
