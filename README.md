 Smart Streetlight Safety System
An Arduino-based intelligent street lighting solution for public safety, road visibility automation, and energy efficiency — featuring smart sensors, GSM-based emergency alerts, and a manual emergency button.

📌 Aim
To develop an automated street light safety system that improves public safety and road visibility while saving electrical energy using smart sensors and Arduino.

🧰 Components
ComponentPurposeArduino Uno R3Central microcontroller for processing all sensor inputs and controlling outputsLDR SensorDetects ambient light intensity for automatic day/night switchingPIR SensorDetects human or vehicle motion near the streetlightSound SensorDetects loud or abnormal sounds (shouting, alarms, crashes)Active BuzzerProvides audible alert when danger or emergency is detectedGSM Module (SIM900A)Sends emergency SMS alerts to authorities or contactsEmergency Push ButtonManual trigger for instant safety assistanceLED / StreetlightMain lighting output controlled by the systemBreadboard & Jumper WiresCircuit connections and prototyping

⚙️ Working
1. 🔆 Automatic Light Control (LDR Sensor)
The LDR (Light Dependent Resistor) continuously monitors surrounding light intensity. When light falls below a defined threshold (dusk, night, or overcast conditions), the Arduino automatically turns the streetlight ON. It turns OFF again when sufficient daylight is detected — conserving energy.
2. 🚶 Motion-Activated Lighting (PIR Sensor)
The PIR sensor detects movement from humans or vehicles in the vicinity. Upon detection, the system activates or boosts streetlight intensity for improved visibility and safety. In the absence of motion for a set duration, the light may dim or turn off to save power.
3. 🔊 Sound-Based Emergency Alert (Sound Sensor + Buzzer)
The sound sensor listens for abnormal loud sounds such as screaming, collisions, or alarm triggers. When such sounds exceed a threshold, the active buzzer is activated as an immediate alert.
4. 🆘 Emergency Push Button + Buzzer Alert
A physical emergency push button is installed near the streetlight. When pressed by a person in distress:

The active buzzer immediately activates to draw attention
A message is printed to the Serial Monitor for real-time debugging and logging:

  Emergency Button Pressed! Alert Triggered.

This also acts as the trigger point for the GSM alert flow

5. 📲 GSM Emergency SMS (SIM900A)
The SIM900A GSM module is integrated to send an automated SMS to a pre-configured emergency contact number when the emergency button is pressed. This ensures help can be notified even when no one is physically nearby.
System workflow:
<img width="1264" height="1152" alt="image" src="https://github.com/user-attachments/assets/cb1a1ab9-7045-4925-aafc-553fefb8437b" />


👥 Contributors

Project by: Team Ideaforge
            1.C.P.Srivarshini
            2.Jananya A.G
            3.Chethana.M
Institution:Ramaiah University of Applied Sciences,Bengaluru


📄 License
This project is open-source and available under the MIT License.
