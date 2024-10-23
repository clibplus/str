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

	int			(*isNumber)		(struct String *s);
	int 		(*StartsWith)	(struct String *s, const char *data);
	int			(*EndsWith)		(struct String *s, const char *data);
	int			(*AppendString)	(struct String *s, const char *data);
	int			(*FindString)	(struct String *s, const char *data);
	int 		(*FindStringAt)	(struct String *s, const char *data, int idx);
	char		*(*GetSubstr)	(struct String *s, int start, int end);
	int			(*Join)			(struct String *s, const char **arr, const char delim);
	int			(*Replace)		(struct String *s, const char *find, const char *replace);
	int			(*IsUppercase)	(struct String *s);
	int 		(*IsLowercase)	(struct String *s);
	char 		**(*Split)		(struct String *s, const char *delim);
	char 		**(*SplitAlt)	(struct String *s, const char *delim);
	int			(*Destruct)		(struct String *s);
} String;

//
//			| - > Create a new intanse of String
//			| - > Returns the new instanse upon success or NULL upon failures
//
String		NewString(const char *p);

//
//			| - > Find a char's position in string
//			| - > Returns the character position or -1 upon failure
//
int			String__FindChar(String *s, const char ch);

//
//			| - > Find a character's position matching the amount of matches found of the character
//			| - > Return the character's position or -1 upon failures
//
int 		String__FindCharAt(String *s, const char ch, int match_count);

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
//			| - > Check if a string is a number
//			| - > Returns 1 upon success or 0 upon failure
//
int 		isNumber(String *s);

//
//			| - > Check if the current string starts with the string provided
//			| - > Returns 1 upon success or 0 upon failure
//
int 		StartsWith(String *s, const char *data);

//
//			| - > Check if the current string ends with the string provided
//			| - > Returns 1 upon success or 0 upon failure
//
int 		EndsWith(String *s, const char *data);

//
//			| - > Find a substr in the current string
//			| - > Return the substr position or -1 upon failures
//
int 		String__FindString(String *s, const char *data);


//
//			| - > Find a substr at the matching the provided match count in the current string
//			| - > Return the substr position or -1 upon failures
//
int 		String__FindStringAt(String *s, const char *data, int match_count);

//
//			| - > Get a substr from start to end position of the string
//			| - > Returns a pointer to the string upon success or NULL upon failure
//
char 		*String__GetSubstr(String *s, int start, int end);

//
//			| - > Replace a string
//			| - > Returns 1 upon success and 0 on failure
//
int 		String__Replace(String *s, const char *find, const char *replace);

//
//			| - > Add an array of elements to the string with a delim between each element
//			| - > Returns 1 upon success or 0 upon failures
//
int 		String__Join(String *s, const char **arr, const char delim);

//
//			| - > Split a string with the delim provided
//			| - > Returns an array upon success or NULL upon failure
//
char 		**String__Split(String *s, const char *delim);

//
//			| - > Split string with the delim provided
//			| - > Returns an array upon success or NULL upon failure
//
char 		**String__SplitAlt(String *s, const char *delim);

//
//			| - > Validate if a starts with the provided string
//			| - > Returns -1 upon failure, 0 upon not found, and 1 upon true
//
int 		String__StartsWith(String *s, const char *data);

//
//			| - > Validate if a ends with the provided string
//			| - > Returns -1 upon failure, 0 upon not found, and 1 upon true
//
int 		String__EndsWith(String *s, const char *data);

//
//			| - > Check if the string is all lowercase
//			| - > Returns 1 upon success or 0 upon failure
//
int 		String__IsLowercase(String *s);

//
//			| - > Check if the string is all uppercase
//			| - > Returns 1 upon success or 0 upon failure
//
int 		String__IsUppercase(String *s);

//
//			| - > Destruct the String struct
//
int 		DestroyString(String *s);
