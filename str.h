#pragma once

typedef struct String {
	char 		*data;
	long 		idx;

	void 		(*Set) 			(struct String *s, const char *data);
	char 		*(*Get)			(struct String *s);
	/* Char Checking Operations */
	int 		(*FindChar)		(struct String *s, const char ch);							// Find a char in string
	int 		(*FindCharAt)	(struct String *s, const char ch, int match_count);			// Find a char in string at the matching match count position
	int 		(*CountChar)	(struct String *s, const char ch);							// Count the amount of time a char in string matches the provided char

	/* Char Moodifying Operation */
	int 		(*Trim)			(struct String *s, const char ch);							// Trim a char from string
	int 		(*TrimAt)		(struct String *s, int pos);								// Trim a char from string at the poistion provided in string
	int			(*Strip)		(struct String *s);											// Strip whitespaces from string
	int 		(*StripFrom2End)(struct String *s, int idx);

	/* String Checking Operation */
	int 		(*Clear)		(struct String *s);											// Clear the current string
	int 		(*InsertAtIdx) 	(struct String *s, int pos, char new_ch);											// Insert a char at a string's position
	int 		(*InsertAfterCh)(struct String *s, char find_ch, char new_ch);											// Insert a char after a char's position in the current string
	int 		(*Is)			(struct String *s, const char *data);						// Compare the current string with a substr
	int 		(*Contains)		(struct String *s, const char *data);						// Check if the current string contains a substr
	int			(*isEmpty)		(struct String *s); 										// Checks if string is empty
	int			(*isNumber)		(struct String *s);											// Checks if string is a number
	int			(*IsUppercase)	(struct String *s);											// Checks if string is all uppercase
	int 		(*IsLowercase)	(struct String *s);											// Checks if string is all lowercase
	int 		(*StartsWith)	(struct String *s, const char *data);						// Checks if string starts with a substring
	int			(*EndsWith)		(struct String *s, const char *data);						// Checks if string ends with a substring
	int			(*FindString)	(struct String *s, const char *data);						// Checks if string contains a substring
	int 		(*FindStringAt)	(struct String *s, const char *data, int idx);				// Checks if string contains a substring matching the match count position provided

	/* String Getters */
	char		*(*GetSubstr)	(struct String *s, int start, int end);						// Get a substring from start to end position in the string
	char 		**(*Split)		(struct String *s, const char *delim);						// Split the current string with delim
	char 		**(*SplitAlt)	(struct String *s, const char *delim);						// Backup function for Split (TESTING STAGES)
	
	/* String Modifying Operations */
	int 		(*AppendStr)	(struct String *s, struct String *new);						// Append a substring using another String struct into the current string
	int			(*AppendString)	(struct String *s, const char *data);						// Append a substring to the current string
	int			(*AppendArray)	(struct String *s, const char **data);						// Append a substring to the current string
	int 		(*AppendiArray)	(struct String *s, int *arr);								// Append elements from a int array to the current string
	int			(*AppendNum)	(struct String *s, int num);								// Append a number int type to the current string
	int			(*RmSubstr)		(struct String *s, int start, int end);						// Remove a substring from the current string
	int			(*Join)			(struct String *s, const char **arr, const char delim);		// Append an array of elements to the current string
	int			(*Replace)		(struct String *s, const char *find, const char *replace);	// Replace a substring in string with a new string
	int			(*Destruct)		(struct String *s);											// Destruct the string structure
} String;

//
//			| - > Create a new intanse of String
//			| - > Returns the new instanse upon success or NULL upon failures
//
String		NewString(const char *p);

//
//			| - > Clear string
//			| - > Returns 1 upon success or 0 upon failure
//
int 		String__Clear(String *s);

//
//
//
//
String 		*String__Set(String *s, const char *data);

//
//
//
//
char 		*String__Get(String *s);

//
//
//
//
int 		String__InsertCharAtIdx(String *s, int pos, char replacement);

//
//
//
//
int 		String__InsertCharAt(String *s, char find_ch, char replacement);

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
//			| - > Trim a char from string at a position in string
//			| - > Returns 1 upon success or 0 upon failure
//
int 		String__TrimAt(String *s, int idx);

//
//			| - > Replace character with a string
//			| - > Returns 1 upon success or 0 upon failures
//
int 		String__ReplaceChar(String *s, const char ch, const char *data);

//
//			| - > Append an array of ints to the current string
//			| - > Returns 1 upon success or 0 upon failure
//
int 		String__AppendIntArray(String *s, int *arr);

//
//			| - > Append a string to the current string
//			| - > Returns 1 upon success or 0 upon failures
//
int 		String__AppendStr(String *s, String *new);

//
//			| - > Append a string to the current string
//			| - > Returns 1 upon success or 0 upon failures
//
int 		String__AppendString(String *s, const char *data);

//
//			| - > Append an array of strings to the current string
//			| - > Returns 1 upon success or 0 upon failure
//
int 		String__AppendArray(String *s, const char **data);

//
//			| - > Append an int to the current string
//			| - > Returns 1 upon success or 0 upon failure
//
int 		String__AppendInt(String *s, int num);

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
//			| - > Check if the current string is empty
//			| - > Returns 1 upon success or 0 on failure
//
int	 		String__IsEmpty(String *s);

//
//			| - > Check if string matches the string provided
//			| - > Returns >1 upon success or 0 upon failure
//
int 		String__Is(String *s, const char *data);

//
//			| - > Check if the current string contains a substr
//			| - > Returns >1 upon success or 0 upon failure
//
int 		String__Contains(String *s, const char *data);

//
//			| - > Check if a string is a number
//			| - > Returns 1 upon success or 0 upon failure
//
int 		String__isNumber(String *s);

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
//			| - > Remove a substr from the current string
//			| - > Returns 1 upon success or 0 upon failure
//
int 		String__RemoveSubstr(String *s, int start, int end);

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
