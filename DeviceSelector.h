//
// Created by Yussef Arsalan on 01.03.25.
//

#ifndef DEVICESELECTOR_H
#define DEVICESELECTOR_H

#include <iostream>
#include <vector>
#include <string>

class DeviceSelector {
public:
    DeviceSelector();  // Konstruktor

    // Methode, um die Geräte anzuzeigen
    void showTopDevices();

    // Methode, um eine Geräteauswahl zu treffen
    std::string getDeviceChoice();  // Rückgabe des gewählten Geräts als String

private:
    // Liste von Geräten
    std::vector<std::string> devices;
};

#endif // DEVICESELECTOR_H
