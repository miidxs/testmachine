## Setting up an iPhone

* **Jailbreak the iPhone**

* **Install Cydia packages**: "SBSettings", "openssh", "syslogd", "coreutils", "mobilesubstrate".

* **Checkpoint**: SSH access to the iPhone should work. The default password is "alpine".

## Setting up a development machine (Mac)

* **Install Xcode**: Get it from the Mac AppStore. Install command line tools (from within Xcode).

* **Install MacPorts**: Download from http://www.macports.org/install.php.

## Deploying the tweak

Note: You don't need a Mac to drive the iPhone, only to deploy the tweak.

* **Set THEOS_DEVICE_IP**: "export THEOS\_DEVICE\_IP=\_\_DEVICE\_IP\_\_".

* **Compile and install**: In "public/IosServer": "make clean", "make package", "make install". The default password is "alpine".

* **Checkpoint**: Dump screen should work. Point a browser (Firefox or Chrome) on the Mac to the "\_\_DEVICE\_IP\_\_:59247". You should see an XML representation of the iPhone GUI.

* **Checkpoint**: Logs should be written to "/var/log/syslog" (on the device) when Preferences app is started and stopped. The device may have to be rebooted before log messages appear.

