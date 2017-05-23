# pymedioex
A Python extension for using MedIOEx card properly.


## Installation

Here are the steps of installation:

- Be sure you have `bcm2835` library installed. Here is the [install link](https://github.com/pe2a/MedIOEx/blob/master/bcm2835-1.50.tar.gz).

  Steps to install `bcm2835`:

  ```
  pi@raspberrypi:~ $ sudo su
  root@raspberrypi:/home/pi# tar zxvf bcm2835-1.50.tar.gz
  root@raspberrypi:/home/pi# cd bcm2835-1.50
  root@raspberrypi:/home/pi/bcm2835-1.50# ./configure
  root@raspberrypi:/home/pi/bcm2835-1.50# make
  root@raspberrypi:/home/pi/bcm2835-1.50# make check
  root@raspberrypi:/home/pi/bcm2835-1.50# make install
  ```
  This will install the C dependencies for `bcm2835`.

- Download a proper release
- Unzip it.
- Go to library directory and open a terminal
- Check your python version to use
- Open a terminal and write `sudo python3 setup.py install`

Then you can open a shell and use library like this
(Note that you might need to be superuser before opening the shell.)

```
>>> import medioex
>>> medioex.do_di_init()  # Need for using Digital Inputs/Digital Outputs initialization
>>> medioex.do_write(3, 1)  # Sets Digital Output 3 HIGH
>>> a = medioex.di_read(5)  # Reads from Digital Input 5
>>> medioex.ro_write(13, 1)  # Sets Relay Output 13 HIGH
>>> medioex.ai_init()  # Need for reading from Analog Inputs initialization
>>> b = medioex.ai_read(4)  # Reads from Analog Input 4
>>> mediex.ao_init()  # Need for writing to Analog Inputs initialization
>>> medioex.ao_write(3, 4095)  # Writes 4095 to Analog Output 3
```


## Maintainers: 

[Ulku Bayraktar](https://github.com/bayraktarulku)

[Nejdet Çağdaş Yücesoy](https://github.com/nejdetckenobi)
