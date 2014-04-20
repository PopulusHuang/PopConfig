#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pop_config.h"
void cut_char(const char *src,char *dest,char del_char)
{
	int i,j,n;
	n = strlen(src);
	for(i = 0,j = 0;i < n;i++)
	{
		if(src[i] == del_char)
		{
			continue;
		}
		else
		{
			dest[j++] = src[i];
		}
	}
}
/* cut blank character */
void cut_blank(const char *src,char *dest)
{
	cut_char(src,dest,' ');
}
/* read the key value */
int cfg_readValue(FILE *cfg_file,popCfg_t config)
{
	char line[LINE_SIZE];
	char src_value[CFG_VALUE_SIZE];
	char dest_value[CFG_VALUE_SIZE];
	char regexp[REGEXP_SIZE];
	int linenum = 0;
	int offset = 0; 
	memset(line,0,sizeof(line));
	memset(src_value,0,sizeof(src_value));
	memset(dest_value,0,sizeof(dest_value));
	memset(regexp,0,sizeof(regexp));
	sprintf(regexp,"%%*[^%c] %c %%s",config.sep_char,config.sep_char);

	offset = cfg_searchKey(cfg_file,config);
	if(Fseek(cfg_file,offset,SEEK_SET) < 0)
		return -1;
	if(fgets(line,LINE_SIZE,cfg_file))
	{
		sscanf(line,regexp,src_value);
		cut_blank(src_value,dest_value);
		strcpy(config.value,dest_value);
		return 0;
	}
	return -1;
}

int Fseek(FILE *fp,long offset,int whence)
{
	if(offset < 0)
		return -1;
	if(fseek(fp,offset,SEEK_SET) < 0)
	{
		perror("fseek");
		exit(-1);	
	}
	return 0;
}
/* Check out the comment character,return 1 by succeed,or 0 by failed.*/
int is_comment(const char *buf,char comment_char)
{
	int i;
	for (i = 0; i < strlen(buf); i++) {
		if(buf[i] == comment_char)	
			return 1;
	}
	return 0;
}
/* Search a key from the configure file,it return the key's 
 * offset when it was found,or -1 if not found.*/
int cfg_searchKey(FILE *fp,popCfg_t config)
{
	char src_key[CFG_KEY_SIZE];
	char dest_key[CFG_KEY_SIZE];
	char line[CFG_VALUE_SIZE];
	char regexp[REGEXP_SIZE];
	int offset = 0;
	int len = 0;
	
	memset(line,0,sizeof(line));
	memset(src_key,0,sizeof(src_key));
	memset(dest_key,0,sizeof(dest_key));
	memset(regexp,0,sizeof(regexp));

	sprintf(regexp,"%%[^%c]",config.sep_char);
	long curr_offset = 0;
	curr_offset = ftell(fp);

	/* make sure seek from the head of file */
	Fseek(fp,0,SEEK_SET);
	while(fgets(line,LINE_SIZE,fp))
	{
		len = strlen(line);	
		offset += len;
		if(is_comment(line,config.comment_char))
		{
				continue;
		}
		sscanf(line,regexp,src_key);	
		cut_blank(src_key,dest_key);
		if(strcmp(dest_key,config.key) == 0)
		{
			Fseek(fp,curr_offset,SEEK_SET);
			return offset-len;	
		}
	memset(dest_key,0,sizeof(dest_key));
	}
	Fseek(fp,curr_offset,SEEK_SET);
	return -1;
}
