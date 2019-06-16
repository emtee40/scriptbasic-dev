/*
MIT License

Copyright (c) 2019 Armando I. Rivera <airr@outlook.com>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "iptools.h"

char *publicIP() {
    struct __res_state res;
    char host_ip[16],ip[16],*hostname="resolver1.mydns.com", *query = "myip.opendns.com";
    int result,i,length;
    struct hostent *he;
    struct in_addr **addr_list, addr;
    ns_msg handle;
    ns_rr rr;
    u_char answer[NS_PACKETSZ];

    he=gethostbyname("resolver1.opendns.com");
    addr_list = (struct in_addr **) he->h_addr_list;
    strcpy(host_ip, inet_ntoa(*addr_list[0]));

    res_ninit( &res);
    inet_aton(host_ip, &addr);
    res.nsaddr_list[0].sin_addr=addr;
    res.nsaddr_list[0].sin_family=AF_INET;;
    res.nsaddr_list[0].sin_port=htons(NS_DEFAULTPORT);;
    res.nscount=1;

    length=res_nquery( &res,query,ns_c_in,ns_t_a,answer,sizeof(answer));
    ns_initparse(answer,length, &handle);
    if(ns_msg_count(handle,ns_s_an)>0) {
        if( ns_parserr( &handle,ns_s_an,0, &rr)==0 )
            strcpy(ip,inet_ntoa(*(struct in_addr*)ns_rr_rdata(rr)));
    }
    return strdup(ip);
}

char* getMac(char* iface) {
	int fd;
	struct ifreq ifr;
	unsigned char *mac;
    char ret[16];
	
	fd = socket(AF_INET, SOCK_DGRAM, 0);

	ifr.ifr_addr.sa_family = AF_INET;
	strncpy(ifr.ifr_name , iface , IFNAMSIZ-1);

	ioctl(fd, SIOCGIFHWADDR, &ifr);

	close(fd);
	
	mac = (unsigned char *)ifr.ifr_hwaddr.sa_data;
	
	//display mac address
	sprintf(ret,"%.2x:%.2x:%.2x:%.2x:%.2x:%.2x" , mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    return strdup(ret);
}

char* localIP(char* iface) {
    int fd;
    struct ifreq ifr;
    char host[16];

    fd = socket(AF_INET, SOCK_DGRAM, 0);

    ifr.ifr_addr.sa_family = AF_INET;

    strncpy(ifr.ifr_name, iface, IFNAMSIZ-1);

    ioctl(fd, SIOCGIFADDR, &ifr);

    close(fd);

    /* display result */
    sprintf(host, "%s", inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));
    return strdup(host);
}
