#include <pcap.h>
#include <iostream>
#include <string>

#include "PacketSniffer.h"
#include "DeviceSelector.h"

int main() {
    // Erstelle ein DeviceSelector-Objekt
    DeviceSelector deviceSelector;

    // Zeige die Geräteauswahl an
    deviceSelector.showTopDevices();

    // Hole die Gerätewahl des Benutzers
    std::string selectedDevice = deviceSelector.getDeviceChoice();

    // Erstelle ein PacketSniffer-Objekt und starte das Sniffen mit dem gewählten Gerät
    PacketSniffer sniffer;
    sniffer.startSniffing(selectedDevice);  // Gerät an den Sniffer übergeben

    return 0;
}
