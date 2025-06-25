#include "sensors/microphoneSensor/microphoneSensor.h"
#include "loRa/loRaInstance/loRaInstance.h"

const float MicrophoneSensor::CALIBRATION_OFFSET = 120.0f;
const int MicrophoneSensor::BITS_SHIFT_SPH0645 = 8;

MicrophoneSensor::MicrophoneSensor()
{
    initialized = false;
    lastSoundLevel = 0.0f;
}

void MicrophoneSensor::setup()
{
    if (!initializeI2S())
    {
        Serial.println("❌ Initialisation I2S échouée !");
        while (1)
            ;
    }
    Serial.println("✅ I2S initialisé");
}

void MicrophoneSensor::printSensorData(SensorData data)
{
    Serial.print("📡 ");
    Serial.print(data.name);
    Serial.print(" = ");
    Serial.print(data.value);
    Serial.print(" ");
    Serial.print(data.unit);
    Serial.print(" @ ");
    Serial.println(data.timestamp);
}

void MicrophoneSensor::readSensorData()
{
    if (!initialized)
        return;

    float amplitude = readAmplitude();
    float soundLevel = convertToDecibels(amplitude);
    long timestamp = millis();

    // Validation simple
    if (soundLevel < 20.0f || soundLevel > 120.0f)
    {
        soundLevel = lastSoundLevel; // Utilise la dernière valeur valide
    }
    else
    {
        lastSoundLevel = soundLevel;
    }

    SensorData soundData = {"sound", soundLevel, "dB", timestamp};

    // Envoi LoRa
    loRaTransmitter.addData(soundData);

    // Optionnel : affichage
    // printSensorData(soundData);
}
bool MicrophoneSensor::initializeI2S() {
    i2s_config_t i2s_config = {
        .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),
        .sample_rate = 44100,  // Fréquence standard
        .bits_per_sample = I2S_BITS_PER_SAMPLE_32BIT,
        .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,  // Mono gauche
        .communication_format = I2S_COMM_FORMAT_STAND_I2S,  // ⚠️ Format standard
        .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
        .dma_buf_count = 4,
        .dma_buf_len = 1024,
        .use_apll = false,
        .tx_desc_auto_clear = false,
        .fixed_mclk = 0
    };

    i2s_pin_config_t pin_config = {
        .bck_io_num = I2S_BCLK_PIN,
        .ws_io_num = I2S_LRC_PIN,
        .data_out_num = I2S_PIN_NO_CHANGE,
        .data_in_num = I2S_DOUT_PIN
    };

    esp_err_t ret = i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL);
    if (ret != ESP_OK) {
        Serial.printf("❌ Erreur installation I2S: %s\n", esp_err_to_name(ret));
        return false;
    }

    ret = i2s_set_pin(I2S_NUM_0, &pin_config);
    if (ret != ESP_OK) {
        Serial.printf("❌ Erreur pins I2S: %s\n", esp_err_to_name(ret));
        return false;
    }

    // Démarrer I2S explicitement
    i2s_start(I2S_NUM_0);
    
    Serial.println("✅ I2S configuré et démarré");
    return true;
}

float MicrophoneSensor::readAmplitude()
{
    if (!initialized)
        return 0.0f;

    int32_t samples[I2S_BUFFER_SIZE];
    size_t bytesRead = 0; // ✅ Variable

    // ✅ Passer l'adresse de bytesRead
    esp_err_t result = i2s_read(I2S_NUM_MIC, samples, sizeof(samples), &bytesRead, 1000);

    if (result != ESP_OK || bytesRead == 0)
    {
        return 0.0f;
    }

    int samplesCount = bytesRead / sizeof(int32_t);
    float rms = calculateRMS(samples, samplesCount);

    return rms;
}

float MicrophoneSensor::convertToDecibels(float amplitude)
{
    if (amplitude <= 0)
        return 20.0f;

    // Conversion en dB pour SPH0645
    float db = 20.0f * log10(amplitude / 8388608.0f) + CALIBRATION_OFFSET;

    // Limitation des valeurs
    if (db < 20.0f)
        db = 20.0f;
    if (db > 120.0f)
        db = 120.0f;

    return db;
}

float MicrophoneSensor::calculateRMS(int32_t *samples, int count)
{
    if (count == 0)
        return 0.0f;

    float sum = 0.0f;
    int validSamples = 0;

    for (int i = 0; i < count; i++)
    {
        // SPH0645: données 24 bits dans les bits de poids fort
        int32_t processedSample = samples[i] >> BITS_SHIFT_SPH0645;

        if (processedSample != 0)
        {
            sum += (float)(processedSample * processedSample);
            validSamples++;
        }
    }

    if (validSamples == 0)
        return 0.0f;

    return sqrt(sum / validSamples);
}
