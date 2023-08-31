#include "helper.h"

struct ipheader {
  unsigned char  iph_ihl:4, iph_ver:4;
  unsigned char  iph_tos;
  unsigned short int iph_len;
  unsigned short int iph_ident;
  unsigned char  iph_flag;
  unsigned short int iph_offset;
  unsigned char  iph_ttl;
  unsigned char  iph_protocol; 
  unsigned short int iph_chksum;
  unsigned int iph_sourceip;
  unsigned int iph_destip;
};


struct tcpheader {
  unsigned short int tcph_srcport; // Source port
  unsigned short int tcph_destport; // Destination port
  unsigned int tcph_seqnum; // Sequence number
  unsigned int tcph_acknum; // Acknowledgment number
  unsigned char  tcph_reserved:4, tcph_offset:4; // Data offset, reserved
  // TCP flags
  unsigned int
       tcp_res1:4,  /*little-endian*/
       tcph_hlen:4,  /*length of tcp header in 32-bit words*/
       tcph_fin:1,   /*Finish flag "fin"*/
       tcph_syn:1,   /*Synchronize sequence numbers to start a connection*/
       tcph_rst:1,   /*Reset flag */
       tcph_psh:1,   /*Push, sends data to the application*/
       tcph_ack:1,   /*acknowledge*/
       tcph_urg:1,   /*urgent pointer*/
       tcph_res2:2;
  unsigned short int tcph_win; // Window
  unsigned short int tcph_chksum; // Checksum
  unsigned short int tcph_urgptr; // Urgent pointer
};


struct arpheader {
  unsigned short int hardware_type;
  unsigned short int protocol_type;
  unsigned char hardware_len;
  unsigned char protocol_len;
  unsigned short int opcode;
  unsigned char sender_mac[6];
  unsigned char sender_ip[4];
  unsigned char target_mac[6];
  unsigned char target_ip[4];
};

