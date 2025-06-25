#!/bin/bash

# start iot
cd iot/
pio run --target upload
cd ..

# start gateway
cd gateway/
pio run --target upload
