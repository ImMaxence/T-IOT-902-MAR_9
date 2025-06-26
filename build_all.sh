#!/bin/bash

echo "Compilation des projets IoT LoRa..."

# Projet 1 - Gateway
echo -e "Compilation Gateway WiFi LoRa 32 V2..."
cd gateway || exit 1
pio run -e heltec_wifi_lora_32_V2

if [ $? -eq 0 ]; then
    echo -e "Gateway: Compilation réussie"
    echo "Binaire: .pio/build/heltec_wifi_lora_32_V2/firmware.bin"
else
    echo -e "Gateway: Erreur de compilation"
    exit 1
fi

cd ..

# Projet 2 - IoT
echo -e "Compilation IoT..."
cd iot || exit 1
pio run -e ttgo-t-beam

if [ $? -eq 0 ]; then
    echo -e "IoT: Compilation réussie"
    echo "Binaire: .pio/build/ttgo-t-beam/firmware.bin"
else
    echo -e "IoT: Erreur de compilation"
    exit 1
fi

cd ..

echo -e "Tous les binaires sont compliés"

mkdir -p release

DATE=$(date +%Y%m%d_%H%M%S)

cp "gateway/.pio/build/heltec_wifi_lora_32_V2/firmware.bin" \
    "release/gateway_${DATE}.bin"
echo "Gateway binaire copié"

    cp "iot/.pio/build/ttgo-t-beam/firmware.bin" \
    "release/iot_${DATE}.bin"
echo "IoT binaire copié"
