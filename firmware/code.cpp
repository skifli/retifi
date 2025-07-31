#include <Wire.h> // Why a wireh? Idk
#include <Adafruit_GFX.h> // GFX? Liek games? Teeheehee
#include <Adafruit_SSD1306.h> // Solid State Drive ofc

// Ze pins
const int SCL_PIN = 0;
const int SDA_PIN = 1;
const int button1Pin = 2;
const int button2Pin = 3;

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

unsigned long startTime = 0;
bool waitingForReaction = false;

void setup() {
	pinMode(button1Pin, INPUT_PULLUP);
	pinMode(button2Pin, INPUT_PULLUP);

	// Start serial for debugging
	Serial.begin(9600);

	// Start display
	Wire.setSCL(SCL_PIN);
	Wire.setSDA(SDA_PIN);

	if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
		Serial.println("SSD1306 not found");
		while (1); // And now, we wait...
	}

	display.clearDisplay();
	display.setTextSize(2);
	display.setTextColor(SSD1306_WHITE);
	display.setCursor(0, 20);
	display.println("Ready...");
	display.display();

	delay(1000);
}

void loop() {
	// Wait random time before showing signal
	display.clearDisplay();
	display.setCursor(0, 20);
	display.println("Wait...");
	display.display();
	delay(random(2000, 5000));

	// Show signal
	display.clearDisplay();
	display.setCursor(0, 20);
	display.println("GO!");
	display.display();

	startTime = millis();
	waitingForReaction = true;

	while (waitingForReaction) {
		if (digitalRead(button1Pin) == LOW || digitalRead(button2Pin) == LOW) {
			unsigned long reactionTime = millis() - startTime;
			
			display.clearDisplay();
			display.setCursor(0, 10);
			display.setTextSize(1);
			display.print("Reaction Time:");
			display.setCursor(0, 30);
			display.setTextSize(2);
			display.print(reactionTime);
			display.println(" ms");
			display.display();
			Serial.print("Reaction time: ");
			Serial.print(reactionTime);
			Serial.println(" ms");
			waitingForReaction = false;
			
			delay(3000);
		}
	}
}
