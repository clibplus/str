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

//
//			| - > Create a new intanse of String
//			| - > Returns the new instanse upon success or NULL upon failures
//
String 		NewString(const char *p);

//
//			| - > Find a char's position in string
//			| - > Returns the character position or -1 upon failure
//
int			String__FindChar(String *s, const char ch);

//
//			| - > Find a character's position matching the amount of matches found of the character
//			| - > Return the character's position or -1 upon failures
//
int String__FindCharAt(String *s, const char ch, int match_count);

//
//			| - > Count the amount of matches, matching character provided
//			| - > Returns the count upon success or -1 upon failures
//
int 		String__CountChar(String *s, const char ch);

//
//			| - > Trim a character from string
//			| - > Returns 1 upon success or 0 upon failures
//
int 		String__Trim(String *s, const char ch);

//
//			| - > Replace character with a string
//			| - > Returns 1 upon success or 0 upon failures
//
int 		String__ReplaceChar(String *s, const char ch, const char *data);

//
//			| - > Append a string to the current string
//			| - > Returns 1 upon success or 0 upon failures
//
int 		String__AppendString(String *s, const char *data);

//
//			| - > Strip the whitespaces in a string
//			| - > Returns 1 upon success or 0 upon failures
//
int 		String__Strip(String *s);

//
//			| - > Strip from a position in string to the end of string
//			| - > Returns 1 upon sucess or 0 upon failures
//
int 		String__StripPos2End(String *s, int idx);

//
//			| - > Find a substr in the current string
//			| - > Returns 1 upon sucess or -1 upon failures
//
int 		String__FindString(String *s, const char *data);
