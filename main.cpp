#include <iostream>
#include <pcap.h>

int main() {
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle;

    // Öffnen des Netzwerk-Interfaces (hier 'en0' für das erste Netzwerkinterface)
    handle = pcap_open_live("en0", BUFSIZ, 1, 1000, errbuf);

    if (handle == NULL) {
        std::cerr << "Error opening device: " << errbuf << std::endl;
        return 1;
    }

    std::cout << "Network interface opened successfully!" << std::endl;

    // Schließen der Verbindung
    pcap_close(handle);
    return 0;
}
