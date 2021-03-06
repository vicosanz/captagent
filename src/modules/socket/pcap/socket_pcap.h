/*
 * $Id$
 *
 *  captagent - Homer capture agent. Modular
 *  Duplicate SIP messages in Homer Encapulate Protocol [HEP] [ipv6 version]
 *
 *  Author: Alexandr Dubovikov <alexandr.dubovikov@gmail.com>
 *  (C) Homer Project 2012-2015 (http://www.sipcapture.org)
 *
 * Homer capture agent is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version
 *
 * Homer capture agent is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
*/


#ifndef _SOCKET_PCAP_H_
#define _SOCKET_PCAP_H_

#include <captagent/xmlread.h>

extern char *usefile;
extern int handler(int value);
extern char *global_config_path;
extern char *global_scripts_path;

int ipv4fragments=0;
int ipv6fragments=0;

/* header offsets */
#define ETHHDR_SIZE 14
#define TOKENRING_SIZE 22
#define PPPHDR_SIZE 4
#define SLIPHDR_SIZE 16
#define RAWHDR_SIZE 0
#define LOOPHDR_SIZE 4
#define FDDIHDR_SIZE 21
#define ISDNHDR_SIZE 16
#define IEEE80211HDR_SIZE 32

#define MAX_SOCKETS 10
profile_socket_t profile_socket[MAX_SOCKETS];

typedef struct socket_pcap_stats {
	uint64_t recieved_packets_total;
	uint64_t recieved_tcp_packets;
	uint64_t recieved_udp_packets;
	uint64_t recieved_sctp_packets;
	uint64_t send_packets;
} socket_pcap_stats_t;

extern FILE* yyin;
extern int yyparse();

//lua_State *LUAScript[MAX_SOCKETS];

int bind_api(socket_module_api_t* api);
int reload_config (char *erbuf, int erlen);
int apply_filter (filter_msg_t *filter);
void free_module_xml_config();
int load_module_xml_config();

/* BIND */
int bind_check_size(msg_t *_m, char *param1, char *param2);
int set_raw_filter(unsigned int loc_idx, char *filter);
pcap_t* get_pcap_handler(unsigned int loc_idx);

int dump_proto_packet(struct pcap_pkthdr *, u_char *, uint8_t, char *, uint32_t, char *,
            char *, uint16_t, uint16_t, uint8_t,uint16_t, uint8_t, uint16_t, uint32_t, uint32_t);


/*IPv4 filter*/
#define BPF_DEFRAGMENTION_FILTER_IPV4 "(ip[6:2] & 0x3fff != 0)"
/*IPv6 filter*/
#define BPF_DEFRAGMENTION_FILTER_IPV6 "(ip6[6]=44 and (ip6[42:2] & 0xfff8 != 0))"

#endif /* _SOCKET_PCAP_H_ */
