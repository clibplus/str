#pragma once

typedef struct String {
	char 		*data;
	long 		idx;

	int 		(*FindChar)		(struct String *s, const char ch);
	int 		(*CountChar)	(struct String *s, const char ch);
	int 		(*Trim)			(struct String *s, const char ch);
} String;

String NewString(const char *p);
int String__FindChar(String *s, const char ch);
int String__CountChar(String *s, const char ch);
int String__Trim(String *s, const char ch);
