With this tweak, you can run automated GUI tests on the device.

For every app (including the "SpringBoard" app), an HTTP server is started that executes test commands like "tap", "swipe", "setText", etc.


## Setup

* Jailbreak the iPhone

* Through Cydia, install "TestMachine iPhone driver"

* Point browser (Firefox or Chrome) on the host machine to the "\_\_DEVICE\_IP\_\_:59247". You should see an XML representation of the iPhone GUI.


## Port numbers

* For the "SpringBoard" app the port number is 50000. The server is always running.

* For the other apps, the port number is generated. It's guaranteed to be the same for every run of the app.