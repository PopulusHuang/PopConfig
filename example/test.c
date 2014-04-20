#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pop_config.h"
int main(int argc, const char *argv[])
{
		FILE *fp = NULL;
		popCfg_t config;
		char key[CFG_KEY_SIZE];
		char value[CFG_VALUE_SIZE];

		memset(key,0,sizeof(key));
		memset(value,0,sizeof(value));
		if(argc != 2)
		{
				printf("Usage:%s file\n",argv[0]);
				exit(1);
		}
		fp = fopen(argv[1],"r+");
		if(fp == NULL)
		{
				fprintf(stderr,"open %s error!",argv[1]);	
				exit(1);
		}
		config.comment_char = '#';
		config.sep_char = '=';
		config.key = "LISTEN";
		config.value = value;
		if(cfg_readValue(fp,config) < 0)
		{
				fprintf(stderr,"%s not found\n",config.key);
				exit(1);
		}
		printf("%s = %s\n",config.key,config.value);
		fclose(fp);
		return 0;
}
