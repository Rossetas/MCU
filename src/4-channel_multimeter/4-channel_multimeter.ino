// Marco Vasquez Ovares
// B17032

#include <PCD8544.h>

static PCD8544 lcd;

constexpr float maxInputVoltage = 24.0;
constexpr float adcMidpoint = 511.5;
constexpr int numChannels = 4;
constexpr int analogPins[numChannels] = {A0, A1, A2, A3};
constexpr int warningPins[numChannels] = {8, 9, 10, 11};

float voltages[numChannels] = {0.0};

void setup() {

    Serial.begin(9600);

    for (int pin : warningPins) {
        pinMode(pin, OUTPUT);
    }

    lcd.begin(84, 48);
    lcd.clear();
    lcd.setCursor(1, 0); lcd.print("Welcome");
    lcd.setCursor(1, 1); lcd.print("To");
    lcd.setCursor(1, 2); lcd.print("4-Channel");
    lcd.setCursor(1, 3); lcd.print("Multimeter");

    attachInterrupt(digitalPinToInterrupt(2), clear_display, CHANGE);

    delay(5000);
}

void clear_display() {
    lcd.clear();
}

void serial_display(const char *mode, const float v[]) {
    if (analogRead(A4) > adcMidpoint) {
        Serial.println(mode);
        for (int i = 0; i < numChannels; ++i) {
            Serial.println(v[i]);
        }
    }
}

void lcd_display_ACMODE(const char *mode, const float v[]) {
    lcd.setCursor(0, 0);
    lcd.print(mode);
    for (int i = 0; i < numChannels; ++i) {
        lcd.setCursor(0, i + 1);
        lcd.print("V"); lcd.print(i + 1); lcd.print(": ");
        lcd.print(v[i]); lcd.print("Vrms");
    }
}

void lcd_display_DCMODE(const char *mode, const float v[]) {
    lcd.setCursor(0, 0);
    lcd.print(mode);
    for (int i = 0; i < numChannels; ++i) {
        lcd.setCursor(0, i + 1);
        lcd.print("V"); lcd.print(i + 1); lcd.print(": ");
        lcd.print(v[i]); lcd.print("V");
    }
}

float get_RMS(int pin) {
    constexpr int samples = 1000;
    float tmax = 0.0;
    for (int i = 0; i < samples; ++i) {
        float t = analogRead(pin);
        if (t > tmax) tmax = t;
    }
    float peakVoltage = (tmax - adcMidpoint) * (maxInputVoltage / adcMidpoint);
    return peakVoltage * 0.7071f; // Aproximación de RMS
}

void AC_mode() {
    for (int i = 0; i < numChannels; ++i) {
        voltages[i] = get_RMS(analogPins[i]);
    }

    float adjusted[numChannels];
    for (int i = 0; i < numChannels; ++i) {
        adjusted[i] = voltages[i] * 1.41f;
    }

    warning_leds(adjusted);
    lcd_display_ACMODE("MODO AC", voltages);
    serial_display("MODO AC", voltages);
}

void DC_mode() {
    for (int i = 0; i < numChannels; ++i) {
        voltages[i] = (analogRead(analogPins[i]) - adcMidpoint) * (maxInputVoltage / adcMidpoint);
    }

    warning_leds(voltages);
    lcd_display_DCMODE("MODO DC", voltages);
    serial_display("MODO DC", voltages);
}

void warning_leds(const float v[]) {
    for (int i = 0; i < numChannels; ++i) {
        digitalWrite(warningPins[i], (v[i] > 20.0 || v[i] < -20.0) ? HIGH : LOW);
    }
}

void Switch_mode() {
    (analogRead(A5) < adcMidpoint) ? AC_mode() : DC_mode();
}

void loop() {
    Switch_mode();
}
