#pragma once

typedef struct String {
	char 		*data;
	long 		idx;

	int 		(*FindChar)		(struct String *s, const char ch);
	int 		(*CountChar)	(struct String *s, const char ch);
	int 		(*Trim)			(struct String *s, const char ch);

	int			(*AppendString)	(struct String *s, const char *data);
} String;

String NewString(const char *p);
int String__FindChar(String *s, const char ch);
int String__CountChar(String *s, const char ch);
int String__Trim(String *s, const char ch);
void String__ReplaceChar(String *s, const char ch, const char *data);
int String__AppendString(String *s, const char *data);
int String__FindChar(String *s, const char ch);
int String__FindCharAt(String *s, const char ch, int match_count);

