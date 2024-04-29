#include <Servo.h>
#define RAIN_SENSOR_PIN A0
#define SERVO_PIN 9

Servo servo;
int angle = 0;
int prev_rain_state = 0;
int rain_value;
int rain_threshold = 300;

void setup() {
    Serial.begin(9600);
    pinMode(RAIN_SENSOR_PIN, INPUT);
    servo.attach(SERVO_PIN);
    servo.write(angle);
}

void loop() {
    rain_value = analogRead(RAIN_SENSOR_PIN);

    if (rain_value > rain_threshold && prev_rain_state == 0) {
        // Rain detected
        Serial.println("Rain detected!");
        gradualRotate(90);
        prev_rain_state = 1;
    } else if (rain_value <= rain_threshold && prev_rain_state == 1) {
        // Rain stopped
        Serial.println("Rain stopped!");
        gradualRotate(0);
        prev_rain_state = 0;
    }
}

void gradualRotate(int targetAngle) {
    int currentAngle = servo.read();
    int step = 1;  // Adjust this value for desired speed (smaller = slower)
    while (currentAngle != targetAngle) {
        if (currentAngle < targetAngle) {
            currentAngle += step;
        } else {
            currentAngle -= step;
        }
        servo.write(currentAngle);
        delay(20);  // Delay for smoother movement (adjust as needed)
    }
}
