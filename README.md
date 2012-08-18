With this tweak, you can run automated GUI tests on the iPhone. For every app (including the "SpringBoard" app), an HTTP server is started that executes test commands like "tap", "swipe", "setText", etc.


## Setup

* Jailbreak the iPhone

* Through Cydia, install "TestMachine iPhone driver"

* Point a browser (Firefox or Chrome) on the host machine to "\_\_DEVICE\_IP\_\_:59247". You should see an XML representation of the GUI.


## Port numbers

* For the "SpringBoard" app the port number is 50000. The server is always running.

* For the other apps, the port number is arbitrary but guaranteed to be the same for every run. The server is started when the app becomes active and stopped when it becomes inactive.

## Command set

Please refer to the [JavaDoc](http://www.testmachine.ch/javadoc/ch/sukha/testmachine/client/IosDriver.html).
