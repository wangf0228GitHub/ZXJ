#include "HardwareProfile.h"

/*   É¾³ý×ó±ßµÄ¿Õ¸ñ   */
char * l_trim(char * szOutput, const char *szInput)
{
	assert(szInput != NULL);
	assert(szOutput != NULL);
	assert(szOutput != szInput);
	for(NULL; *szInput != '\0' && isspace(*szInput); ++szInput)
	{
		;
	}
	return strcpy(szOutput, szInput);
}

/*   É¾³ýÓÒ±ßµÄ¿Õ¸ñ   */
char *r_trim(char *szOutput, const char *szInput)
{
	char *p = NULL;
	assert(szInput != NULL);
	assert(szOutput != NULL);
	assert(szOutput != szInput);
	strcpy(szOutput, szInput);
	for(p = szOutput + strlen(szOutput) - 1; p >= szOutput && isspace(*p); --p)
	{
		;
	}
	*(++p) = '\0';
	return szOutput;
}
/*   É¾³ýÁ½±ßµÄ¿Õ¸ñ   */
char * a_trim(char * szOutput, const char * szInput)
{
	char *p = NULL;
	assert(szInput != NULL);
	assert(szOutput != NULL);
	l_trim(szOutput, szInput);
	for   (p = szOutput + strlen(szOutput) - 1;p >= szOutput && isspace(*p); --p)
	{
		;
	}
	*(++p) = '\0';
	return szOutput;
}
