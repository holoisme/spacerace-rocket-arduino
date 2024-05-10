# Team Fox : Spacerace Rocket

<p align="center">
  <a href="https://github.com/holoisme/Fox">
    <img src="https://github.com/holoisme/spacerace-rocket-arduino/assets/77677018/245f3916-8faa-4bf5-9846-6d2dbefd9a1b" width="320">
  </a>
</p>

## Electronics ⚡
We used the following components :
* **Arduino Nano** being the main controlling component.
* **BMP180** for measuring altitude.
* **Micro SD Controller** for keeping all the collected data during the flight.
* **Buzzer** for alerting that the board is in another state than `POWER_OFF`.
* **Button** to pass from `POWER_OFF` to `IDLE` state.

## A State Machine 🤖
We used a finite state machine based Arduino program :
* `POWER_OFF`, for when the Avionics is not in the rocket.
* `IDLE`, for when the Avionics is waiting for the take off.
* `ASCENDING`, for when the rocket is ascending and haven't reached the apogee.
* `DESCENDING_PRE_MAIN`, for when the rocket is descending and hasn't reached yet the altitude to deploy the main parachute.
* `DESCENDING_POST_MAIN`, for when the rocket deployed the main and hasn't reached the ground yet.
* `GROUNDED`, for when the rocket landed.

The transitions are as follows :
* `POWER_OFF -> IDLE`: in the press of the button.
* `IDLE -> ASCENDING`: when the altitude reaches a threshold `IDLE_ALTITUDE_THRESHOLD`.
* `ASCENDING -> DESCENDING_PRE_MAIN`: when the velocity passes below a threshold `ASCTODES_VELOCITY_THRESHOLD`.
* `DESCENDING_PRE_MAIN -> DESCENDING_POST_MAIN`: when the altitude passes below a threshold `DEPLOY_ALTITUDE_THRESHOLD`.
* `DESCENDING_POST_MAIN -> GROUNDED`: when the absolute value of the velocity passes below a threshold `GROUNDED_VELOCITY`. 
