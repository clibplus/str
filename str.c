#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "str.h"

String ConstructMethods(String *s);

String NewStringAlt(const char **arr) {
	String n = NewString(NULL);
	for(int i = 1; arr[i] != NULL; i++) {
		n.AppendString(&n, arr[i]);
	}

	return n;
}

String NewString(const char *p) {
	if(!p)
		return ConstructMethods(&(String){ .data = (char *)malloc(1), .idx = 0 });

	String s = {
		.data 			= (!p ? NULL : strdup(p)),
		.idx 			= (!p ? 0 : strlen(p)),
	};

	s = ConstructMethods(&s);

	return s;
}

String ConstructMethods(String *s) {
	s->Set 				= String__Set;
	s->Get				= String__Get;
	s->FindChar			= String__FindChar;
	s->FindCharAt		= String__FindCharAt;
	s->CountChar		= String__CountChar;
	s->Trim				= String__Trim;
	s->TrimAt			= String__TrimAt;
	s->Strip			= String__Strip;
	s->StripFrom2End 	= String__StripPos2End;

	s->Clear			= String__Clear;
	s->InsertAtIdx		= String__InsertCharAtIdx;
	s->InsertAfterCh 	= String__InsertCharAt;
	s->Is 				= String__Is;
	s->Contains			= String__Contains;
	s->isEmpty			= String__IsEmpty;
	s->isNumber			= String__isNumber;
	s->AppendStr 		= String__AppendStr;
	s->AppendString		= String__AppendString;
	s->AppendNum 		= String__AppendInt;
	s->AppendArray 		= String__AppendArray;
	s->AppendiArray		= String__AppendIntArray;
	s->FindString 		= String__FindString;
	s->FindStringAt		= String__FindStringAt;
	s->IsASCII			= String__IsASCII;
	s->GetSubstr		= String__GetSubstr;
	s->Join				= String__Join;
	s->Replace			= String__Replace;
	s->IsUppercase		= String__IsUppercase;
	s->IsLowercase		= String__IsLowercase;
	s->StartsWith		= String__StartsWith;
	s->EndsWith 		= String__EndsWith;
	s->Split			= String__Split;
	s->SplitAlt			= String__SplitAlt;
	s->RmSubstr 		= String__RemoveSubstr;

	s->Utils 			= String__Utils;
	s->Destruct			= DestroyString;

	return *s;
}

String *String__Set(String *s, const char *data) {
	if(!s || !data)
		return NULL;

	String__Clear(s);
	String__AppendString(s, data);
	return s;
}

char *String__Get(String *s) { if(!s) return 0; return s->data; }

int String__Clear(String *s) {
	if(!s || !s->data)
		return 0;

	if(s->data) {
		/* Since freeing doesn't clear the data, memset is needed! */
		memset(s->data, '\0', s->idx);
		free(s->data);
	}

	s->data = (char *)malloc(1);
	memset(s->data, '\0', 1);
	s->idx = 0;

	return 1;
}

int String__InsertCharAtIdx(String *s, int pos, char new_ch) {
	if(!s || !s->data) 
		return 0;

	char *BUFF = (char *)malloc(s->idx - 1);
	int idx = 0;

	for(int i = 0; i < s->idx; i++) {
		BUFF[idx] = s->data[i];
		idx++;
		BUFF = (char *)realloc(BUFF, idx + 1);

		
		if(i == pos) {
			BUFF[idx] = new_ch;
			idx++;
			BUFF = (char *)realloc(BUFF, idx + 1);
		}
	}

	free(s->data);
	s->data = BUFF;
	s->idx = idx;

	return 1;
}

int String__InsertCharAt(String *s, char find_ch, char new_ch) {
	if(!s || !s->data) 
		return 0;

	char *BUFF = (char *)malloc(1);
	int idx = 0;

	for(int i = 0; i < s->idx; i++) {
		BUFF[idx] = s->data[i];
		idx++;
		BUFF = (char *)realloc(BUFF, idx + 1);

		if(s->data[i] == find_ch) {
			BUFF[idx] = new_ch;
			idx++;
			BUFF = (char *)realloc(BUFF, idx + 1);
		}
	}

	free(s->data);
	s->data = BUFF;
	s->idx = idx;

	return 1;
}

// int String__InsertAt(String *s, int pos, char *data) {
// 	if(!s || !s->data || !data)
// 		return 0;

// 	char *BUFF = (char *)malloc(1);
// 	int idx = 0;

// 	for(int i = 0; i < s->data; i++) {
// 		if(i == pos) {
// 			strncat(BUFF, )
// 		}
// 	}

// 	return 1;
// }

int String__FindChar(String *s, const char ch) {
	if(!s || !s->data)
		return -1;

	for(int i = 0; i < s->idx; i++) {
		if(!s->data[i])
			break;

		if(s->data[i] == ch)
			return i;
	}

	return -1;
}

int String__FindCharAt(String *s, const char ch, int match_count) {
	if(!s || !s->data)
		return -1;

	int count = 0;
	for(int i = 0; i < s->idx; i++) {
		if(!s->data[i])
			break;

		if(s->data[i] == ch)
			count++;

		if(s->data[i] == ch && match_count == i)
			return i;
	}

	return -1;
}

int String__CountChar(String *s, const char ch) {
	if(!s || !s->data)
		return -1;

	int count = 0;
	for(int i = 0; i < s->idx; i++) {
		if(!s->data[i])
			break;

		if(s->data[i] == ch)
			count++;

	}

	return count;
}

int String__Trim(String *s, const char ch) {
	if(!s || !s->data)
		return 0;

	int found = 0, idx = 0;
	char *new = (char *)malloc(1);

	for(int i = 0; i < s->idx; i++) {
		if(!s->data[i])
			break;

		if(s->data[i] == ch) {
			found = 1;
			continue;
		}

		new[idx] = s->data[i];
		idx++;
		new = (char *)realloc(new, idx + 1);
	}

	new[idx] = '\0';
	free(s->data);
	s->data = new;
	s->idx = idx;

	return found;
}



int String__TrimAt(String *s, int pos) {
	if(!s || !s->data)
		return 0;

	int found = 0, idx = 0;
	char *new = (char *)malloc(1);

	for(int i = 0; i < s->idx; i++) {
		if(!s->data[i])
			break;

		if(i == pos) {
			found = 1;
			continue;
		}

		new[idx] = s->data[i];
		idx++;
		new = (char *)realloc(new, idx + 1);
	}

	new[idx] = '\0';
	free(s->data);
	s->data = new;
	s->idx = idx;

	return found;
}

int String__IsASCII(String *s) {
	if(!s || !s->data)
		return 0;

	for(int i = 0; s->data[i] != '\0'; i++)
    	if((s->data[i] < 'A' || s->data[i] > 'Z') && s->data[i] != 10)
			return 0;

	return 1;
}

int String__Strip(String *s) {
	if(!s || !s->data)
		return 0;

	char *BUFF = (char *)malloc(1);
	int idx = 0;
	for(int i = 0; i < s->idx; i++) {
		if(s->data[i] == ' ' || s->data[i] == '\t')
			continue;

		BUFF[idx] = s->data[i];
		idx++;
		BUFF = (char *)realloc(BUFF, idx + 1);
	}
	
	return 1;
}

int String__StripPos2End(String *s, int idx) {
	if(!s || !s->data)
		return 0;

	int new_len = s->idx - (s->idx - idx);
	char *new = (char *)malloc(new_len);
	memset(new, '\0', new_len);

	for(int i = 0; i < new_len; i++)
		new[i] = s->data[i];

	free(s->data);
	s->data = new;
	s->idx = new_len;
	return 1;
}

int String__IsEmpty(String *s) {
	if(!s)
		return 0;

	for(int i = 0; i < s->idx; i++) {
		if((s->data[i] > 'A' && s->data[i] < 'Z' || s->data[i] > 'a' && s->data[i] < 'z') && s->data[i] != 10)
			return 0;
	}

	return 1;
}

int String__isNumber(String *s) {
	for(int i = 0; i < s->idx; i++)
		if(!s->data[i])
			return 0;

	return 1;
}

int String__Is(String *s, const char *data) {
	if(!s || !data)
		return 0;

	return (!strcmp(s->data, data));
}

int String__Contains(String *s, const char *data) {
	if(!s || !data)
		return 0;

	return (strstr(s->data, data) != 0 ? 1 : 0);
}

int String__StartsWith(String *s, const char *data) {
	if(!s || !data)
		return 0;

	if(strlen(data) >= s->idx)
		return 0;

	for(int i = 0; i < strlen(data); i++) {
		if(s->data[i] != data[i])
			return 0;

		if(i == strlen(data) - 1)
			return 1;
	}

	return 0;
}

int String__EndsWith(String *s, const char *data) {
	if(!s || !data)
		return 0;

	if(strlen(data) >= s->idx)
		return 0;

	int ch = 0;
	for(int i = s->idx - strlen(data); i < s->idx; i++) {
		if(s->data[i] != data[ch])
			return 0;

		if(i == (s->idx - 1))
			return 1;

		ch++;
	}

	return 0;
}

int String__ReplaceChar(String *s, const char ch, const char *data) {
	if(!s || !s->data)
		return 0;

	char *new = (char *)malloc(s->idx);
	int idx = 0, found = 0;

	for(int i = 0; i < s->idx; i++) {
		if(!s->data[i])
			break;

		if(s->data[i] == ch) {
			int len = strlen(data);
			for(int chr = 0; chr < len; chr++) {
				new[idx] = data[chr];
				idx++;
				if((i + chr) >= s->idx)
					new = (char *)realloc(new, idx + 1);
			}
			continue;
		}

		new[idx] = s->data[i];
		idx++;
		if(i > s->idx)
			new = (char *)realloc(new, idx + 1);
	}

	new[idx] = '\0';
	free(s->data);
	s->data = new;
	s->idx = strlen(new);
	return found;
}

int String__AppendStr(String *s, String *new) {
	if(!s || !new)
		return 0;

	String__AppendString(s, new->data);
	new->Destruct(new);
	
	return 1;
}

int String__AppendArray(String *s, const char **data) {
	if(!s || !data)
		return 0;

	int i = 0;
	while(data[i] != NULL) {
		String__AppendString(s, data[i]);
		i++;
	}

	return 1;
}

int String__AppendString(String *s, const char *data) {
	if(!s || !s->data || !data)
		return 0;

	for(int i = 0; i < (int)strlen(data); i++) {
		s->data[s->idx] = data[i];
		s->idx++;
		s->data = (char *)realloc(s->data, s->idx + 1);
	}
	return 1;
}

int String__AppendIntArray(String *s, int *arr) {
	if(!s || !s->data)
		return 0;

	int i = 0;
	while(arr[i] != '\0')
		String__AppendInt(s, arr[i]);

	return 1;
}

int String__AppendInt(String *s, int num) {
	if(!s || !s->data)
		return 0;

	char *BUFF = (char *)malloc(100);
	memset(BUFF, '\0', 100);
	
	sprintf(BUFF, "%d", num);

	String__AppendString(s, BUFF);
	free(BUFF);
	return 1;
}

int String__FindString(String *s, const char *data) {
	if(!s || !s->data || !data)
		return -1;

	if((long)strlen(data) > s->idx)
		return -1;

	for(int i = 0; i < s->idx; i++) {
		if(s->data[i] == data[0] && s->data[i + strlen(data) - 1] == data[strlen(data) - 1]) {
			for(int ch = 0; ch < (int)strlen(data); ch++) {
				if(s->data[i + ch] == data[ch] && ch == ((int)strlen(data)-1)) {
					return i;
				} else if(s->data[i + ch] != data[ch]) {
					break;
				}
			}
		}
	}
	return -1;
}

int String__FindStringAt(String *s, const char *data, int match_count) {
	if(!s || !s->data || !data)
		return -1;

	int matches = 0;
	for(int i = 0; i < s->idx; i++) {
		if(s->data[i] == data[0] && s->data[i + strlen(data) - 1] == data[strlen(data) - 1]) {
			for(int ch = 0; ch < (int)strlen(data); ch++) {
				if(s->data[i + ch] == data[ch] && ch == ((int)strlen(data)-1)) {
					matches++;
				}
			}

			if(matches == match_count)
				return i;
		}
	}

	return -1;
}

char *String__GetSubstr(String *s, int start, int end) {
	if(!s || !s->data)
		return NULL;

	int new_len = s->idx + (end - start) + 1;
	char *new = (char *)malloc(new_len);
	memset(new, '\0', new_len);
	int idx = 0;

	for(int i = 0; i < s->idx; i++) {
		if(i >= start && i < end) {
			strncat(new, &s->data[i], sizeof(char));
			idx++;
		}
	}
	
	new[strlen(new)] = '\0';
	return (strlen(new) > 0 ? new : NULL);
}

int String__RemoveSubstr(String *s, int start, int end) {
	if(!s || !s->data)
		return -0;

	char *new = (char *)malloc(1);
	int idx = 0;
	for(int i = 0; i < s->idx; i++) {
		if(i > start || i < end)
			continue;

		if(!s->data[i])
			break;

		new[idx] = s->data[i];
		idx++;
		new = (char *)realloc(new, idx + 1);
	}

	new[idx] = '\0';

	free(s->data);
	s->data = new;
	s->idx = idx;

	return 1;
}

int String__Replace(String *s, const char *find, const char *replace) {
	if(!s || !s->data || !find || !replace)
		return 0;

	String new_str = NewString(NULL);
	int start = (String__FindStringAt(s, find, 0) == -1 ? 0 : 0), end = 0, idx = 1;

	while ((end = String__FindStringAt(s, find, idx)) != -1) {
		char *substr = String__GetSubstr(s, start, (end == -1 ? (int)(s->idx) : end));
		String__AppendString(&new_str, substr);

		if(!substr)
			break;

		String__AppendString(&new_str, replace);

		free(substr);
		start = end + strlen(find);
	}
	
	char *substr = String__GetSubstr(s, start, s->idx);
	String__AppendString(&new_str, substr);
	free(substr);

	free(s->data);
	new_str.data[new_str.idx] = '\0';
	s->data = new_str.data;
	s->idx = new_str.idx;

	return 1;
}

int String__Join(String *s, const char **arr, const char delim) {
	if(!s || !s->data || !arr)
		return 0;

	int i = 0;
	while(arr[i] != NULL) {
		s->data = (char *)realloc(s->data, s->idx + (strlen(arr[i]) + 1));
		strncat(s->data, arr[i], strlen(arr[i]));
		if(arr[i + 1] != NULL)
			strncat(s->data, &delim, sizeof(char));

		i++;
		s->idx += strlen((const char *)&arr[i])  + 1;
	}

	s->idx = strlen(s->data) + 1;
	s->data[s->idx - 1] = '\0';
	return 1;
}

int String__IsLowercase(String *s) {
	for(int i = 0; i < s->idx; i++) {
		if(!s->data[i])
			break;

		if(!islower(s->data[i]))
			return 0;
	}

	return 1;
}

int String__IsUppercase(String *s) {
	for(int i = 0; i < s->idx; i++) {
		if(!s->data[i])
			break;

		if(!isupper(s->data[i]))
			return 0;
	}

	return 1;
}

char **String__Split(String *s, const char *delim) {
	char **arr = (char **)malloc(sizeof(char *) * 1);
	int idx = 0;

	char *copy = strdup(s->data);
	char *token = strtok(copy, delim);
	while(token != NULL) {
		arr[idx] = strdup(token);
		idx++;
		arr = (char **)realloc(arr, sizeof(char *) * (idx + 1));
		token = strtok(NULL, delim);
	}

	arr[idx] = NULL;
	free(copy);
	return arr;
}

char **String__SplitAlt(String *s, const char *delim) {
	if(!s || !s->data || !delim)
		return (char **)NULL;

	char **arr = (char **)malloc(sizeof(char *) * 1);
	int last = 0;
	int i = 1;
	while(last != -1) {
		int pos = String__FindStringAt(s, delim, i);
		char *sub = String__GetSubstr(s, last, pos == -1 ? s->idx : pos);
		arr[i] = sub;
		i++;
		arr = (char **)realloc(arr, sizeof(char *) * (i + 1));
		last = pos + strlen(delim);

		if(pos == -1) break;
	}

	return arr;
}

int DestroyString(String *s) {
	if(s->data)
		return 0;

	free(s->data);
	s->data = NULL;
	return 1;
}
