# Home Server Stats Display

A small project I made that uses **Arduino** with **Python** to monitor resource usage on my home server at a quick glance.
<br>
It can be used as a base for similar projects, to actively display data on a 16x2 LCD.

---

## About

This project was made because I had an Arduino Uno kit lying around that I had no time to tinker with, so while setting my
home server up, I decided to use it as a way to monitor resource usage it.
<br>
<br>
At the moment, it's very basic, but it will be expanded and I will add buttons to allow for more features.

1. **Arduino Sketch** (`stats.ino`)

   * Handles parsing and writing the data to the display.
2. **Python Script** (`stats.py`)

   * Gathers data from the server and sends it to the Arduino via serial.
---

## ⚙️ Requirements

### Arduino

* Arduino IDE
* Compatible board (I have Uno with CH340)

### Python

* Python 3.8+
* Install dependencies:

  ```bash
  pip install psutil
  pip install pyserial
  ```

---

##  Usage

### 1. Flash the Arduino

1. Open `stats.ino` in the Arduino IDE.
2. Select your board and port.
3. Upload the sketch.
4. Nothing else, you're ready!

### 2.1. Run the Python script

```bash
python3 stats.py
```

### 2.2. Make it run on startup
This is what I wanted so I can keep receiving data after a restart or a power outage without having to restart the script again.

```bash
sudo nano /etc/systemd/system/hssd.service
```
```service
[Unit]
Description=Home Server Stats Display
After=multi-user.target

[Service]
ExecStart=/usr/bin/python3 /path/to/script/stats.py
WorkingDirectory=/path/to/script
Restart=always
User=root

[Install]
WantedBy=multi-user.target
```
```bash
sudo systemctl daemon-restart
sudo systemctl start hssd
sudo systemctl enable hssd
```
---

## Demo

![Demo](https://cdn.discordapp.com/attachments/1419347568881700878/1421992670603247646/PXL_20250928_225012654.jpg?ex=68db0d60&is=68d9bbe0&hm=c9161260d874b05080cfb7deb3938f58c0fd70433d7539343d03995ec9da23b8&)

---

## TODO:

* [ ] Add seeing per-process CPU and RAM usage (listing through them with a button)
* [ ] Add seeing per-disk storage usage and R/W stats (listing through them with a button)
* [ ] Add power draw information, CPU speed (per-core) and more. 
* [ ] Add logging
