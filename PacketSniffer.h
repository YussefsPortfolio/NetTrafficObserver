//
// Created by Yussef Arsalan on 27.02.25.
//

#ifndef PACKET_SNIFFER_H
#define PACKET_SNIFFER_H

#include <pcap.h>
#include <string>

class PacketSniffer {
public:
    PacketSniffer();  // Konstruktor
    ~PacketSniffer(); // Destruktor

    // Methode, um das Sniffen mit einem spezifischen Gerät zu starten
    void startSniffing(const std::string& deviceName);

private:
    pcap_t *handle;        // Handle für das Sniffer-Interface
    std::string device;    // Gerät, das zum Sniffen verwendet wird

    // Handler für jedes empfangene Paket
    static void packetHandler(u_char *userData, const struct pcap_pkthdr *pkthdr, const u_char *packet);
};

#endif // PACKET_SNIFFER_H
