# Google Home Lightstrip Controller
**Make your own smart LED Strips using Google Actions, Firebase Functions, Arduino, and the ESP8266 WiFi chip.**

*This guide is based off [shivasiddarth's](https://github.com/shivasiddharth) [YouTube Tutorial](https://www.youtube.com/watch?v=e1C5WIfZ89s&t=1096s)*


![finishedController](https://github.com/uzairmahmed/ArduinoLightManager/blob/master/Images/finishedBright.JPG)
---

## Google Actions Setup

1. Go to [Google Actions Console](console.actions.google.com)
2. Create a Project
3. Select `Smart Home`
4. Choose a name for the Action
5. Go to `Actions` and add the following fullfillment URL
    - `https://us-central1-PROJECT_ID.cloudfunctions.net/smarthome`
6. Go to `Account Linking` and add a Client ID and Secret
    - ID: `ABC123`
    - Secret `DEF456`
    - `https://us-central1-PROJECT_ID.cloudfunctions.net/fakeauth`
    - `https://us-central1-PROJECT_ID.cloudfunctions.net/faketoken`
7. Click Next
8. Go to Cloud Console and enable the `HomeGraph API` in `APIs and Services`
9. Add Credentials
    - Select `Service Account` and add the `Service Account Token Creator` role.
    - Create a JSON Key

---

## Firebase Setup

### Firebase Directory Setup

1. Clone this repository
2. Save the JSON key file from the previous step to `./Firebase/arduino-nodemcu-control/functions/smart-home-key.json`
3. Download [NodeJS](https://nodejs.org/en/)
4. Open a Powershell Terminal with administrator privileges
5. `cd` into `Firebase\arduino-nodemcu-control\functions`
6. `Set-ExecutionPolicy RemoteSigned` to enable scripts
7. `npm install -g firebase-tools` to install firebase
8. `firebase login`
9. `firebase use PROJECT_ID`
10. `npm i`
11. Go to [Firebase](console.firebase.google.com)
12. Click `Database > Create Database > Enable`, and copy the URL given
13. Click `Settings > Users and permissions > Service Accounts > Database secrets`  and copy the secret given

### Smart Devices Setup

1. For each device you intend to use, add an entry to the devices array inside `Firebase\arduino-nodemcu-control\functions\devices.json`
    - Use the template given in `Firebase\arduino-nodemcu-control\functions\device_template.json` for your entry
2. Customize your device further by referencing to the [Google Smarthome Docs](https://developers.google.com/assistant/smarthome/guides)

### Firebase Deployment

1. In a terminal, `cd` into `Firebase\arduino-nodemcu-control\functions`
2. `firebase deploy`
3. Go to the link specified.
4. Click `Database > Create Database > Enable`, and note down the URL given
5. Click `Realtime Database`
6. Click `Settings > Users and permissions > Service Accounts > Database secrets` and note down the secret given
7. Save your URL and Secret in a file, **you will need it later**.

---

## Hardware Setup

![soldering](https://github.com/uzairmahmed/ArduinoLightManager/blob/master/Images/Soldering.png)

**Note:** The steps outlined above work for any type of device/hardware (lights, fans, motors, etc). The steps below are specifically to control LightStrips with Cloud Functions

### Circuit Building

#### **Components Needed**

- **1x** NodeMCU ESP8266 Development Board
- **1x** WS2812 LED Strip
- **1x** MicroUSB PinBoard (Female)
- **1x** 3-Pin Screw Terminal
- **2x** 15-Pin Headers
- **1x** 5-Pin Headers
- **5x** Jumper Cables
- **1x** 10x24-Hole Perfboard
- **1x** Micro USB Cable
- **1x** USB Power Supply

#### **Power Requirements**

The ESP8266 board operates at 3.3V, however the WS2812 operates at 5V. Additionally, the maximum current that can be drawn from each GPIO pin is 12mA. For this reason we need to power the board independently from the lightstrip, and with a larger power supply.

To choose an adequate power supply, we need to calculate the maximum current drawn from the arduino and the lights.

ESP8266 Board Max Current Draw: 400mA

WS2812 Strip Max Current Draw (all pixels are bright white): 3.6A

- Each LED draws a maximum of 60mA (Red, Green, Blue)
- 60 LED strip = 3.6 Amps required.

Therefore we need a 5V / 4A Power Supply.

![Circuit](https://github.com/uzairmahmed/ArduinoLightManager/blob/master/Images/Circuit.png)

#### **Breadboard Testing**

1. Open `Wiring\Breadboard_Wiring.png`, and create the circuit shown.
2. To test the circuit, open `Arduino\OfflineLightManager\OfflineLightManager.ino` in Arduino.
3. If you have not already, setup your ESP8266 Board to work with Arduino IDE, Steps shown below in `Setup Arduino/NodeMCU Setup with Arduino IDE`.
4. Go to `Tools > Library Manager` and get
    - `FastLED` by `Daniel Garcia`
5. Connect the circuit to your computer using the microUSB port **on the ESP8266 board**
Click Upload
6. Confirm that the light strip turns on.
7. Reconnect the ciruit to your computer, but this time, use the microUSB port **on the external pinboard**
8. Confirm that the light strip turns on (but brighter).

#### **Perfboard Testing**

1. Open `Wiring\Perfboard_Wiring.png`, and solder the circuit shown.
2. Repeat steps 5-8 from the previous section to confirm your circuit board works.

### Arduino Setup

#### Configure NodeMCU with Arduino IDE

1. Open Arduino
2. Go to `File > Preferences`, under `Additional Boards Manager URLS` paste the following URL: `http://arduino.esp8266.com/stable/package_esp8266com_index.json`
3. Go to `Tools > Board > Boards Manager` and get `esp8266` by ESP8266 Community
4. Go to `Tools > Board` and select `NodeMCU 1.0 (ESP-12E)`

#### Upload LightManager Code

1. Download the git repository at [FirebaseExtended/firebase-arduino](https://github.com/FirebaseExtended/firebase-arduino)
2. Open `Arduino\LightManager\LightManager.ino` in Arduino.
3. Go to `Sketch > Include Library > Add ZIP Library`
4. Go to `Tools > Library Manager` and get

    - `ArduinoJSON` **v5.13** by `Benoit Blanchon`,
    - `WiFiManager` by `Tzapu, Tablatronix`,
    - `Adafruit_Neopixel` by `Adafruit`

5. Make the following changes to the code:
    - Replace `FIREBASE_URL` with the Firebase URL **saved earlier**.
    - Replace `FIREBASE_KEY` with the Firebase Secret **saved earlier**.
    - For each device you make:
        - Edit `LED_Count` variable to match the number of LEDs in your strip.
        - Edit `STRMDEVID` variable to match the ID of the device you created in `Firebase\arduino-nodemcu-control\functions\devices.json`.

6. Verify your code
7. Upload your code
8. Connect to the WiFi Network created by your ESP8266
9. Click `Configure Wifi` and connect to your home WiFi address (2.4GHz only)

---

## Google Home Setup

### Setup

1. Open your [Google Actions](console.actions.google.com) project
2. Go to `Google Actions Console > Test`
3. Invoke a test in the simulator, you will get an error, and then the Action will activate.
4. Open the Google Home app on a mobile device.
5. Go to `'+' > Set up Device > Have something already setup? > '[Test] Device Name'`
6. Add the [Test] Devices to a room and test the lights.
7. Refer to `Debugging` Below if something isn't working correctly.
8. **Congratulations! You've made your own smart Light Strips!**

![Finished](https://github.com/uzairmahmed/ArduinoLightManager/blob/master/Images/Finished.png)

---

---

## Debugging

If your lights aren't working properly, follow these steps to find the root of the issue.

1. Click the reset button on your ESP8266 Board (**this solves most issues**)
2. Firebase Debugging
    - Go to [Firebase Console](console.firebase.google.com) and open Realtime Database.
    - Change the color of your lights and make sure the values are changing in the database. 
        - If the database is unresponsive:
            - Confirm that Google Actions is setup properly with Firebase
            - Clear the Database and try changing colors again
            - Redeploy your Firebase Functions
        - If the database changes values properly, go to `External USB Debugging`.
3. External USB Debugging
    - Disconnect your circuit from the light strip and connect it to your computer using the microUSB port **on the ESP8266 board**.
    - Change the color of your lights and check if the lights change colors properly.
        - If they change properly, your external microUSB wiring isn't properly connected.
        - If they dont change, go to `Arduino WiFi Debugging`
4. Arduino WiFi Debugging
    - With your circuit connected to your computer, open Arduino,
    - Go to `Tools > Serial Monitor`.
    - If the serial monitor is sending `Streaming Error` indefinitely, check that your WiFi works properly.
    - OR If the serial monitor is sending instructions to connect to a WiFi network connect to the WiFi Network created by your ESP8266 and reconfigure your board.
    - OR Change the color of your lights and confirm that the serial monitor sends `patch` with the function you just activated.
        - If nothing shows up, confirm that Firebase is setup properly with Arduino
        - If the right output shows up, go to `Arduino Offline Debugging`
    - If none of the above worked/applied to you, go to `Arduino Offline Debugging`
5. Arduino Offline Debugging
    - Open `Arduino\OfflineLightManager\OfflineLightManager.ino` in Arduino.
    - If you don't have it already, go to `Tools > Library Manager` and get `FastLED` by `Daniel Garcia`
    - Upload the code and make sure that the LED strip turns on.
        - If the LED strip doesn't turn on, check your wiring, and make sure there are no short circuits anywhere.
        - If the LED strip does turn on properly, **something is wrong with your Google Actions / Firebase / LightController.ino setup**