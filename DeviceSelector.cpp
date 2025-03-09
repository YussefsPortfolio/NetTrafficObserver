#include "DeviceSelector.h"

// Konstruktor - Initialisiert die Geräte
#include "DeviceSelector.h"
DeviceSelector::DeviceSelector() {
    devices.push_back("en0 (WLAN):         Verbunden mit deinem Wi-Fi-Netzwerk.");
    devices.push_back("lo0 (Loopback):     Lokale Verbindung für den Testverkehr.");
    devices.push_back("eth0 (Ethernet):    Drahtgebundene Netzwerkverbindung.");
    devices.push_back("utun0 (VPN):        Virtuelles privates Netzwerk.");
    devices.push_back("bridge0 (Brücke):   Netzwerkbrücke zur Verbindung mehrerer Netzwerke.");
}



// Zeigt die Top 5 Geräte an
void DeviceSelector::showTopDevices() {
    std::cout << "\033[1;32m" << "Top 5 Geräte/Ports:\n" << "\033[0m";  // Grüner Text für Header
    for (size_t i = 0; i < devices.size(); ++i) {
        std::cout << "\033[1;34m" << (i + 1) << ". " << devices[i] << "\033[0m" << std::endl;  // Blau für Geräte
    }
}

// Fragt den Benutzer nach einer Gerätauswahl
std::string DeviceSelector::getDeviceChoice() {
    int choice;
    std::cout << "\nWähle ein Gerät aus (1-5): ";
    std::cin >> choice;

    if (choice < 1 || choice > 5) {
        std::cout << "Ungültige Auswahl. Bitte wähle eine Zahl von 1 bis 5.\n";
        return getDeviceChoice(); // Recursive call to re-prompt the user
    } else {
        return devices[choice - 1];  // Rückgabe des gewählten Geräts
    }
}
