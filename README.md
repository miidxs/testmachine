## Setup

* Jailbreak the iPhone

* Through Cydia, install "TestMachine iPhone driver"

* Point browser (Firefox or Chrome) on the host machine to the "\_\_DEVICE\_IP\_\_:59247". You should see an XML representation of the iPhone GUI.


## Port numbers

* For every app, a HTTP server is started that executes the test commands.

* For the "SpringBoard" app the port number is 50000. The server is always running.

* For the other apps, the port number is generated. It's guaranteed to be the same for every run of the app.
The server is started when the app becomes active and stopped when it becomes inactive.

