#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <pthread.h>
#include "chgServ.h"

pthread_mutex_t fileSavelock;

s32 OSPrintf(const s8* pFormat, ...)
{
	va_list arg; 
	s32 done = 0; 

	va_start(arg, pFormat); 
	done += vprintf(pFormat, arg); 
	va_end(arg);
	return done;
}

s32 OSSprintf(s8* pBuf,const s8* pFormat, ...)
{
	va_list arg;
	s32 done = 0;

	va_start(arg, pFormat);
	done += vsprintf(pBuf, pFormat, arg);
	va_end(arg);
	return done;
}

s32 MdlFileGetParaAllData(s8* pFile, s8* pV, s32* pVLen)
{
	FILE* pFd;
	s32 size=0;
	if(pFile == NULL || pV == NULL)
		return FAILURE;
	pFd = fopen(pFile, "r+");
	if(pFd == NULL)
		return FAILURE;
	
	size=fread(pV, 1, *pVLen, pFd);
	pV[size]='\0';
	*pVLen = size;
	fclose(pFd);
	
	return SUCCESS;
}

s32 MdlFileSaveTermIni(s8* pFile, s8* pPrm, s32 len)
{
	FILE* pFd;
    s32 nwrite;
    s32 ret;

	if(pFile == NULL || pPrm == NULL)
		return FAILURE;
	pthread_mutex_lock(&fileSavelock);
	pFd = fopen(pFile, "w");
	if(pFd == NULL){
		pthread_mutex_unlock(&fileSavelock);
		return FAILURE;
	}
	nwrite = fwrite(pPrm, 1, len, pFd);
    if (nwrite < len) {
        OSPrintf("%s: write error\n", __FUNCTION__);
    }
	fclose(pFd);
    ret = system("sync");
    if (ret < 0) {
        perror("sync error");
        OSPrintf("%s: sync error\n", __FUNCTION__);
    }
	pthread_mutex_unlock(&fileSavelock);
    
	return SUCCESS;
}

// 保存单个参数
static s32 sysSinglePrmSave(s8* pFile, s8* pKey, s8 *pValue)
{
	s8 prmbuf[FILE_BUFFER_SIZE]={0};//原始数据
	s8 tmpbuf[FILE_BUFFER_SIZE]={0};//将要保存的数据
	s8 linebuf[100]={0};
	s8 *pLineStart = prmbuf;
	s32 prmLen=sizeof(prmbuf);
	if(MdlFileGetParaAllData(pFile, 
					prmbuf, &prmLen) == FAILURE){
		OSPrintf("##Error:Can't Get Para!!! File:%s\n",pFile);
        return FAILURE;
	}

	while((pLineStart=strstr(pLineStart, pKey)) != NULL && 
			*(pLineStart -1) != '\n'){
		if(pLineStart == prmbuf)
			break;
		pLineStart += strlen(pKey);
	}
	
	if(pLineStart == NULL){
		strcpy(tmpbuf, prmbuf);
		//strcat(tmpbuf,"\n");
		OSSprintf(linebuf, "%s=%s\n",pKey,pValue);
		strcat(tmpbuf,linebuf);
	}else{
		memcpy(tmpbuf, prmbuf, (pLineStart - prmbuf));
		OSSprintf(linebuf, "%s=%s\n",pKey,pValue);
		strcat(tmpbuf,linebuf);
		pLineStart = strchr(pLineStart, '\n');
		if(NULL != pLineStart){
			pLineStart += 1;
			strcat(tmpbuf,pLineStart);
		}
	}
	if(MdlFileSaveTermIni(pFile, tmpbuf,strlen(tmpbuf)) == SUCCESS){
		OSPrintf("sysSinglePrmSave SUCCESS key:%s\n",pKey);
	}else{
		OSPrintf("sysSinglePrmSave FAILURE Key:%s\n",pKey);
	}

    return SUCCESS;
}


s32 main(int argc, char *argv[])
{
    s32 ret = FAILURE;
    
    if (argc < 2) {
        printf("usage: %s server_ip server_port\n", argv[0]);
        return -1;
    }
    pthread_mutex_init(&fileSavelock, NULL);
	ret = sysSinglePrmSave(TERM_INI_FILE_NAME, SERVER_IP_KEY_NAME, argv[1]);
    if (ret == FAILURE)
        goto end;
    ret = sysSinglePrmSave(TERM_INI_FILE_NAME, SERVER_PORT_KEY_NAME, argv[2]);
end:
    if (ret == SUCCESS)
        printf("change server ip and port success!\n");
    else
        printf("change server ip and port failure!\n");
    
    return ret;
}
