#pragma once

typedef struct String {
	char 		*data;
	long 		idx;

	int 		(*FindChar)		(struct String *s, const char ch);
	int 		(*FindCharAt)	(struct String *s, const char ch, int match_count);
	int 		(*CountChar)	(struct String *s, const char ch);
	int 		(*Trim)			(struct String *s, const char ch);
	int			(*Strip)		(struct String *s);
	int 		(*StripFrom2End)(struct String *s, int idx);

	int			(*AppendString)	(struct String *s, const char *data);
	int			(*FindString)	(struct String *s, const char *data);
} String;

String NewString(const char *p);
int String__FindChar(String *s, const char ch);
int String__CountChar(String *s, const char ch);
int String__Trim(String *s, const char ch);
void String__ReplaceChar(String *s, const char ch, const char *data);
int String__AppendString(String *s, const char *data);
int String__FindChar(String *s, const char ch);
int String__FindCharAt(String *s, const char ch, int match_count);
int String__Strip(String *s);
int String__StripPos2End(String *s, int idx);
int String__FindString(String *s, const char *data);
