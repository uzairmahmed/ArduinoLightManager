# Light Strip Controller
May 19 2020 - Switching to IoT

Steps Followed:


## Setup Google Actions
1. Go to [Google Actions Console](console.actions.google.com)
1. Create a Project
1. Select `Smart Home`
1. Choose a name for the Action --> (called "Test Device Name" throughout this README)
1. Go to `Actions` and add the following fullfillment URL
 - `https://us-central1-PROJECT_ID.cloudfunctions.net/smarthome`
1. Go to `Account Linking` and add a Client ID and Secret
    - ID: `ABC123`
    - Secret `DEF456`
    - `https://us-central1-PROJECT_ID.cloudfunctions.net/fakeauth`
    - `https://us-central1-PROJECT_ID.cloudfunctions.net/faketoken`
1. Click Next
1. Go to Cloud Console and enable the `HomeGraph API` in `APIs and Services`
1. Add Credentials
    - Select `Service Account` and add the `Service Account Token Creator` role.
    - Create a JSON Key


# Setup Directory
1. Rename the JSON key fil from the previous step to `smart-home-key.json`
2. Clone this Repo
1. Move `smart-home-key.json` to `/smarthome-control/functions/`
1. Download [NodeJS](https://nodejs.org/en/)
1. In a terminal, `cd` into `/smarthome-control/functions/`
1. `npm install -g firebase-tools` to install firebase
1. `Set-ExecutionPolicy RemoteSigned` to enable scripts
1. `firebase login`
1. `firebase use PROJECT_ID`
1. `npm i`
1. Go to [Firebase](console.firebase.google.com)
1. Click `Database > Create Database > Enable`, and copy the URL given
1. Click `Settings > Users and permissions > Service Accounts > Database secrets` Copy the Secret Given

# Setup Devices
1. Head to `/smarthome-control/functions/devices.json` 
1. Add and edit devices from template. [Docs](https://developers.google.com/assistant/smarthome/guides)

# Deploy Database
1. In a terminal, `cd` into `/smarthome-control/functions/`
1. `firebase deploy`
1. Go to the link specified.
1. Click `Database > Create Database > Enable`, and copy the URL given
1. Click `Realtime Database`
1. Click `Settings > Users and permissions > Service Accounts > Database secrets` and copy the secret given

# Deploy NodeMCU
1. Download the git repository at [FirebaseExtended/firebase-arduino](https://github.com/FirebaseExtended/firebase-arduino )
1. Start Arduino
1. go to (ARDUINO FILE)
1. Go to `Tools > Library Manager` and get `ArduinoJSON v5.13`, `WiFiManager`, `Adafruit_Neopixel`
1. Go to `Sketch > Include Library > Add ZIP Library`
1. replace `FIREBASE_URL` with the Firebase URL from the previous step
1. replace `FIREBASE_KEY` with the Firebase key from the previous step
1. Edit `LED_Count` variable
1. Verify your code
1. Upload your code
1. Connect to your ESP device from your computer
1. Click `Configure Wifi` and connect to your home WiFi Address

# Setup Google Home
1. Go to `Google Actions Console > Test`
1. Invoke a test in the simulator, you will get an error, and then the Action will activate.
1. Open the Google Home app on a mobile device.
1. Go to `'+' > Set up Device > Have something already setup? > [Test Device Name]`


https://www.youtube.com/watch?v=e1C5WIfZ89s&feature=youtu.be 9:54
