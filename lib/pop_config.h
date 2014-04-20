#ifndef _POP_CONFIG_H_
#define _POP_CONFIG_H_

#define CFG_KEY_SIZE 20
#define CFG_VALUE_SIZE 256
#define LINE_SIZE 256
#define REGEXP_SIZE 40

typedef struct popCfg{
	char comment_char;  	
	char sep_char;		/* separate char */
	char *key;			/* configure key */
	char *value;		/* key value */
}popCfg_t;
int cfg_searchKey(FILE *fp,popCfg_t config);
int cfg_readValue(FILE *cfg_file,popCfg_t config);
int cfg_writeValue(FILE *cfg_file,popCfg_t config);
#endif
