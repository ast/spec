# Spec

This is a work-in-progress spectrum analzyer application for Software Defined Radio (SDR) on Linux.

It's heavily optimzed to run well on the Raspberry Pi and is part of a larger project to buil a shortwave
transciever hat for the Raspberry Pi.

## Using

**Spec** creates an AF_UNIX DGRAM socket at ```/tmp/sdrclient``` and expects FFT data as packets of float32 array of length 2048.
You need to perform the FFT in another process and send the data to ***spec***. This will be incorporeted in the SDR solution I'm building.

## Dependecies

* http://www.glfw.org/

## Bulding

```bash
$ make
```

## Running

```
$ ./spec
```

