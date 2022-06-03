CRGB ledsChannel1[16];
CorsairLightingFirmwareStorageEEPROM firmwareStorage;
CorsairLightingFirmware firmware(CORSAIR_LIGHTING_NODE_PRO, &firmwareStorage);
FastLEDControllerStorageEEPROM storage;
FastLEDController ledController(&storage);
CorsairLightingProtocolController cLP(&ledController, &firmware);
CorsairLightingProtocolHID cHID(&cLP);

void corsair_setup() {
	FastLED.addLeds<WS2812B, 0, GRB>(ledsChannel1, 16);
	ledController.addLEDs(0, ledsChannel1, 16);
}

void corsair_loop() {
	cHID.update();

	if (ledController.updateLEDs()) {
		FastLED.show();
	}
}