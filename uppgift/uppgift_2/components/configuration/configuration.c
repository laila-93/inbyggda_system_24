#include "Configuration.h"
#include <stdio.h>
#include <string.h>
#include "nvs_flash.h"

// Funktion för att initiera konfigurationen
void initConfiguration(Configuration* config) {
    // Nollställ strängar för att undvika skräpdata
    memset(config->deviceName, 0, MAX_STR_LEN);
    memset(config->serialNumber, 0, MAX_STR_LEN);

    // Initiera NVS
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        // Rensa NVS om det är fullt eller föråldrat
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }

    nvs_handle_t nvsHandle;
    // Öppna NVS i läsläge och läs data
    if (nvs_open(NVS_NAMESPACE, NVS_READONLY, &nvsHandle) == ESP_OK) {
        size_t required_size = MAX_STR_LEN;

        // Läs enhetsnamn från NVS eller använd standard
        if (nvs_get_str(nvsHandle, DEVICE_NAME_KEY, config->deviceName, &required_size) != ESP_OK) {
            strcpy(config->deviceName, "DefaultDevice");
        }

        // Läs serienummer från NVS eller använd standard
        required_size = MAX_STR_LEN;
        if (nvs_get_str(nvsHandle, SERIAL_NUMBER_KEY, config->serialNumber, &required_size) != ESP_OK) {
            strcpy(config->serialNumber, "0000000000");
        }

        // Stäng NVS-hanteraren
        nvs_close(nvsHandle);
    }
}

// Funktion för att hämta enhetsnamn
const char* getDeviceName(Configuration* config) {
    return config->deviceName;
}

// Funktion för att hämta serienummer
const char* getSerialNumber(Configuration* config) {
    return config->serialNumber;
}

// Funktion för att ändra enhetsnamn
esp_err_t setDeviceName(Configuration* config, const char* newName) {
    if (!newName) return ESP_ERR_INVALID_ARG; // Kontrollera att namnet är giltigt

    // Kopiera nytt namn till RAM och spara det i NVS
    strncpy(config->deviceName, newName, MAX_STR_LEN - 1);
    config->deviceName[MAX_STR_LEN - 1] = '\0';
    return saveToNVS(DEVICE_NAME_KEY, config->deviceName);
}

// Funktion för att ändra serienummer
esp_err_t setSerialNumber(Configuration* config, const char* newSerial) {
    if (!newSerial) return ESP_ERR_INVALID_ARG; // Kontrollera att serienumret är giltigt

    // Kopiera nytt serienummer till RAM och spara det i NVS
    strncpy(config->serialNumber, newSerial, MAX_STR_LEN - 1);
    config->serialNumber[MAX_STR_LEN - 1] = '\0';
    return saveToNVS(SERIAL_NUMBER_KEY, config->serialNumber);
}

// Funktion för att spara ett värde i NVS
esp_err_t saveToNVS(const char* key, const char* value) {
    nvs_handle_t nvsHandle;
    // Öppna NVS i skrivläge
    esp_err_t err = nvs_open(NVS_NAMESPACE, NVS_READWRITE, &nvsHandle);
    if (err == ESP_OK) {
        // Skriv värde till NVS
        err = nvs_set_str(nvsHandle, key, value);
        if (err == ESP_OK) {
            // Bekräfta ändring
            err = nvs_commit(nvsHandle);
        }
        // Stäng NVS-hanteraren
        nvs_close(nvsHandle);
    } else {
        printf(" Failed to write '%s' to NVS: %s\n", key, esp_err_to_name(err));
    }
    return err;
}
