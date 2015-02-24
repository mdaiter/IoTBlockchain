# IoTBlockchain
App for a WiFi router that currently uses Merkle trees to verify that data is being sent from point A to B securely, before sending it off to Wink. Wrote a...spartan...Wink API in C. The plan is to expand this into a blockchain over a widely distributed system, so Wink could have possible backups of data in case of crashes, as well as the ability for IoT to IoT direct transactions over time.

To be compiled with OpenWRT or by itself.

By itself:

```
cd package/secure_transmit/src
make
```

For compiling with OpenWRT: cp the package directory into the OpenWRT package SDK (I'd include it here, but it's >200MB). Then, from root run:

```
make
```

This should handle all compilation. This is a shared library, so you need to link against libsecuretransmit.so when compiling it for support

You WILL need to compile [libsocket](https://github.com/dermesser/libsocket) by itself.
