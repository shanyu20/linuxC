#ifndef _CHG_SERV_H_
#define _CHG_SERV_H_

typedef char s8;
typedef unsigned char u8;
typedef short s16;
typedef unsigned short u16;
typedef int s32;
typedef unsigned int u32;
typedef long long s64;
typedef char * string;
typedef unsigned char bool;

#define SUCCESS 0
#define FAILURE	(-1)

#define FILE_BUFFER_SIZE	2048

#define TERM_INI_FILE_NAME          "/nand/term.ini"
//#define TERM_INI_FILE_NAME          "term.ini"
#define SERVER_IP_KEY_NAME          "server"
#define SERVER_PORT_KEY_NAME        "port"

#endif
