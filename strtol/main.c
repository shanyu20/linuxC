#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef int s32;
typedef unsigned char u8;

const char *str1 = "5555";
const char *str2 = "0100";
const char *str3 = "FF";

static s32 pieceKV087SetRtModeCmd(u8 addr, u8 *pCmd, s32 *pLen)
{
    u8 buf[32] = {0};
    s32 idx = 0;
    s32 ret = -1;

    strncpy(&buf[idx], "<AA", sizeof(buf));
    idx += strlen("<AA");
    sprintf(&buf[idx], "%02x", addr);
    idx += 2;
    strncpy(&buf[idx], "0201025555>", sizeof(buf) - idx);
    idx += strlen("0201025555>");
    if (pCmd != NULL && pLen != NULL) {
        if (*pLen > idx) {
            memcpy(pCmd, buf, idx);
            *pLen = idx;
            ret = 0;
        }
    }
    
    return ret;
}

int main(void)
{
	unsigned int val1, val2, val3;
	u8 cmdBuf[32] = {0};
	s32 cmdLen = sizeof(cmdBuf);
	u8 addr = 1;

	val1 = strtol(str1, NULL, 16);
	val2 = strtol(str2, NULL, 10);
	val3 = strtol(str3, NULL, 16);

	printf("val1 = %d, 0x%x\n", val1, val1);
	printf("val2 = %d, 0x%x\n", val2, val2);
	printf("val3 = %d, 0x%x\n", val3, val3);
	
	pieceKV087SetRtModeCmd(addr, cmdBuf, &cmdLen);
	printf("cmdBuf=%s, cmdLen=%d\n", cmdBuf, cmdLen);
	
	printf("bye bye!\n");
}
