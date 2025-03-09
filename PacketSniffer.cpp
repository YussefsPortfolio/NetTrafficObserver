#include "PacketSniffer.h"
#include <iostream>
#include <pcap.h>
#include <netinet/ip.h>  // Für die IP-Header-Struktur
#include <netinet/tcp.h> // Für die TCP-Header-Struktur
#include <arpa/inet.h>   // Für die inet_ntoa-Funktion
#include <cstring>

// Konstruktor
PacketSniffer::PacketSniffer() : handle(nullptr) {}

// Destruktor
PacketSniffer::~PacketSniffer() {
    if (handle) {
        pcap_close(handle);  // Handle schließen, wenn das Sniffen beendet ist
    }
}

// Startet das Sniffen mit einem spezifischen Gerät
void PacketSniffer::startSniffing(const std::string& deviceName) {
    device = deviceName;  // Gerät setzen

    char errbuf[PCAP_ERRBUF_SIZE];

    // Versuch, das Gerät zu öffnen
    handle = pcap_open_live(device.c_str(), BUFSIZ, 1, 1000, errbuf);
    if (handle == nullptr) {
        std::cerr << "Fehler beim Öffnen des Geräts " << device << ": " << errbuf << std::endl;
        return;
    }

    std::cout << "Starte Sniffen auf Gerät: " << device << std::endl;

    // Beginne mit dem Sniffen der Pakete (bis zu 10 Pakete in diesem Beispiel)
    pcap_loop(handle, 10, packetHandler, reinterpret_cast<u_char*>(this));

    pcap_close(handle);
}

// Handler für jedes empfangene Paket
void PacketSniffer::packetHandler(u_char *userData, const struct pcap_pkthdr *pkthdr, const u_char *packet) {
    std::cout << "Paket gefangen mit Länge: " << pkthdr->len << std::endl;

    // Mindestgröße für Ethernet + IP
    if (pkthdr->len < 34) return;

    // Ethernet Header überspringen (14 Bytes)
    struct ip* ipHeader = (struct ip*)(packet + 14);

    // Verarbeite TCP-Pakete
    if (ipHeader->ip_p == IPPROTO_TCP) {
        const u_char *tcpData = packet + 14 + (ipHeader->ip_hl << 2);  // TCP Header überspringen
        struct tcphdr* tcpHeader = (struct tcphdr*) tcpData;

        if (pkthdr->len > 34 + (tcpHeader->th_off << 2)) {  // Prüfe, ob genügend Daten vorhanden sind
            std::string payload((char*)tcpData + (tcpHeader->th_off << 2), pkthdr->len - (34 + (tcpHeader->th_off << 2)));

            if (payload.find("GET") != std::string::npos || payload.find("POST") != std::string::npos) {
                std::cout << "HTTP Request gefunden: " << payload << std::endl;
            }
        }

        // HTTP Traffic Detection für Port "80" (HTTP/Internetseiten)
        if (ntohs(tcpHeader->th_sport) == 80 || ntohs(tcpHeader->th_dport) == 80) {
            std::cout << "HTTP Traffic detected!" << std::endl;
        }

        // TCP-Pakete anzeigen
        std::cout << "TCP Paket von " << inet_ntoa(ipHeader->ip_src) << " nach " << inet_ntoa(ipHeader->ip_dst) << std::endl;
    }
    // Verarbeite UDP-Pakete
    else if (ipHeader->ip_p == IPPROTO_UDP) {
        const u_char *udpData = packet + 14 + (ipHeader->ip_hl << 2);  // UDP Header überspringen
        struct udphdr* udpHeader = (struct udphdr*) udpData;

        // UDP-Pakete anzeigen
        std::cout << "UDP Paket von " << inet_ntoa(ipHeader->ip_src) << " nach " << inet_ntoa(ipHeader->ip_dst) << std::endl;
    }
}
