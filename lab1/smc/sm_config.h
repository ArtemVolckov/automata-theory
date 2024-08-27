#ifndef SM_CONFIG_H
#define SM_CONFIG_H

#define LET let
#define ALNUM ('a'<=LET && LET<='z' || 'A'<=LET && LET<='Z' || '0'<=LET && LET<='9')
#define ALNUM_DOT_SLASH ('a'<=LET && LET<='z' || 'A'<=LET && LET<='Z' || '0'<=LET && LET<='9' || LET=='.' || LET=='/')
#define BLANK (LET=='\t' || LET==' ')
#define HYPHEN (LET=='-')

#endif
