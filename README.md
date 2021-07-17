### Build

To build the `pcap_stats` project run below make command. 

```bash
$ make
```
to generate the `pcap_stats` binary.


NOTE: 
1. This project consist of 3rdparty library `libpcap` which is being 
used for file operation on pcap files.
Location of the library is `lib/`
2. This project will process pcap files generated via tcpdump/wireshark.
Location of SampleCaptures file is `data/`

### Run

To run the application pass a capture file as command line argument.
```bash

./pcap_stats data/sip_call_rtp_g711.pcap 
Filename to be parsed: data/sip_call_rtp_g711.pcap
Complete file has been processed! Number of packets processed: 4269!
# of packets from source ip:

src ip address:    200.57.7.195		# of Packet(s): 71
src ip address:    200.57.7.204		# of Packet(s): 782
src ip address:    200.57.7.206		# of Packet(s): 9
src ip address:    200.57.7.197		# of Packet(s): 285
src ip address:    200.57.7.199		# of Packet(s): 936
src ip address:    200.57.7.194		# of Packet(s): 438
src ip address:    200.57.7.198		# of Packet(s): 17
src ip address:     64.69.76.21		# of Packet(s): 3
src ip address:    200.57.7.205		# of Packet(s): 52
src ip address:    200.57.7.188		# of Packet(s): 2
src ip address:    200.57.7.202		# of Packet(s): 21
src ip address:    200.57.7.196		# of Packet(s): 1457
src ip address:  207.46.106.103		# of Packet(s): 2
src ip address: 216.155.193.154		# of Packet(s): 1
src ip address:  216.136.173.10		# of Packet(s): 9
src ip address:  200.73.183.213		# of Packet(s): 16
src ip address:  207.46.107.165		# of Packet(s): 1
src ip address: 216.155.193.131		# of Packet(s): 1
src ip address:   207.46.106.82		# of Packet(s): 1
src ip address: 216.155.193.159		# of Packet(s): 1


The file provided with this sample code was taken from Wireshark's [capture sample](https://wiki.wireshark.org/SampleCaptures) page.

`sip_call_rtp_g711.pcap` = [SIP_CALL_RTP_G711](https://wiki.wireshark.org/SampleCaptures?action=AttachFile&do=get&target=SIP_CALL_RTP_G711)

## sip_call_rtp_g711

