#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "str.h"

String NewString(const char *p) {
	if(!p)
		return (String){ .data = (char *)malloc(1), .idx = 0 };

	String s = {
		.data 			= (!p ? NULL : strdup(p)),
		.idx 			= (!p ? 0 : strlen(p)),

		.FindChar		= String__FindChar,
		.FindCharAt		= String__FindCharAt,
		.CountChar		= String__CountChar,
		.Trim			= String__Trim,
		.TrimAt			= String__TrimAt,
		.Strip			= String__Strip,
		.StripFrom2End 	= String__StripPos2End,

		.isEmpty		= String__IsEmpty,
		.isNumber		= String__isNumber,
		.AppendStr 		= String__AppendStr,
		.AppendString	= String__AppendString,
		.AppendNum 		= String__AppendInt,
		.AppendArray 	= String__AppendArray,
		.AppendiArray	= String__AppendIntArray,
		.FindString 	= String__FindString,
		.FindStringAt	= String__FindStringAt,
		.GetSubstr		= String__GetSubstr,
		.Join			= String__Join,
		.Replace		= String__Replace,
		.IsUppercase	= String__IsUppercase,
		.IsLowercase	= String__IsLowercase,
		.StartsWith		= String__StartsWith,
		.EndsWith 		= String__EndsWith,
		.Split			= String__Split,
		.SplitAlt		= String__SplitAlt,
		.Destruct		= DestroyString
	};

	return s;
}

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
	s->idx = strlen(new);

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
	s->idx = strlen(new);

	return found;
}

int String__Strip(String *s) {
	if(!s || !s->data) return 0;

	int start = 0;
	while(isspace(s->data[start])) start++;

	int end = strlen(s->data) - 1;
	while(isspace(s->data[end])) end--;

	int new_len = end - start + 2;
	char *new = (char *)malloc(new_len);
	if(!new)
		return 0;

	memset(new, '\0', new_len);
	for(int i = 0; i < new_len; i++)
		new[i] = s->data[start + i];


	new[strlen(new) - 1] = '\0';
	free(s->data);
	s->data = strdup(new);
	s->idx = strlen(new);

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
		if(!isdigit(s->data[i]))
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

int StartsWith(String *s, const char *data) {
	if(!s || !data)
		return 0;

	if(strlen(data) >= s->idx)
		return 0;

	for(int i = 0; i < strlen(data); i++)
		if(s->data[i] != data[i])
			return 0;

	return 1;
}

int EndsWith(String *s, const char *data) {
	if(!s || !data)
		return 0;

	if(strlen(data) >= s->idx)
		return 0;

	for(int i = s->idx; i > s->idx; i--)
		if(s->data[i] != data[i])
			return 0;

	return 1;
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
			for(int chr = 0; chr < (int)strlen(data); chr++) {
				new[idx] = data[chr];
				idx++;
				if((i + chr) > s->idx)
					new = (char *)realloc(new, idx + 1);
			}
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
	while(!data[i])
		String__AppendString(s, data[i]);

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

	char *BUFF = (char *)malloc(20);
	memset(BUFF, '\0', 20);
	sprintf(BUFF, "%d\0", num);

	String__AppendString(s, BUFF);
	free(BUFF);
	return 1;
}

int String__FindString(String *s, const char *data) {
	if(!s || !s->data || !data)
		return -1;

	if((long)strlen(data) < s->idx)
		return -1;

	for(int i = 0; i < s->idx; i++) {
		if(s->data[i] == data[0] && s->data[i + strlen(data) - 1] == data[strlen(data) - 1]) {
			for(int ch = 0; ch < (int)strlen(data); ch++) {
				if(s->data[i + ch] == data[ch] && ch == ((int)strlen(data)-1)) {
					return i;
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

	for(int i = 0; i < s->idx; i++)
		if(i >= start && i < end) {
			strncat(new, &s->data[i], sizeof(char));
			idx++;
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

	int start = String__FindStringAt(s, find, 0) == -1 ? 0 : 0;
	int end = 0, idx = 1;
	char *new = (char *)malloc(1);

	while(end != -1) {
		end = String__FindStringAt(s, find, idx);
		char *substr = String__GetSubstr(s, start, (end == -1 ? (int)(s->idx - strlen(find) - 1) : end) );

		idx += strlen(substr) + strlen(replace);
		new = (char *)realloc(new, idx);

		strncat(new, substr, strlen(substr));
		strncat(new, replace, strlen(replace));

		free(substr);
		start = end + strlen(find);
	}

	free(s->data);
	s->data = new;
	s->idx = strlen(new);

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

int String__StartsWith(String *s, const char *data) {
	if(!s || !s->data)
		return -1;

	if((long)strlen(data) < s->idx)
		return -1;

	for(int i = 0; i < (int)strlen(data); i++)
		if(s->data[i] != data[i])
			return 0;

	return 1;
}

int String__EndsWith(String *s, const char *data) {
	if(!s || !s->data)
		return -1;

	if((long)strlen(data) < s->idx)
		return -1;

	int start = s->idx - strlen(data);
	for(int i = start; start < s->idx; i++)
		if(s->data[i] != data[i])
			return 0;

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
