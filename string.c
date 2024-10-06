#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "String.h"

String NewString(const char *p) {
	if(!p)
		return (String){ .data = (char *)malloc(1), .idx = 0 };

	String s = {
		.data 			= (char *)p,
		.idx 			= strlen(p),

		.FindChar		= String__FindChar,
		.CountChar		= String__CountChar,
		.Trim			= String__Trim
	};

	return s;
}

int String__FindChar(String *s, const char ch) {
	for(int i = 0; i < s->idx; i++) {
		if(!s->data[i])
			break;

		if(s->data[i] == ch)
			return i;
	}

	return -1;
}

int String__CountChar(String *s, const char ch) {
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
	if(!s)
		return 0;

	int found = 0, idx = 0;
	char *new = (char *)malloc(1);

	for(int i = 0; i < s->idx; i++) {
		if(!s->data[i])
			break;

		if(s->data[i] == ch)
			continue;

		new[idx] = s->data[i];
		idx++;
		new = (char *)realloc(new, idx + 1);
	}

	new[idx] = '\0';
	free(s->data);
	s->data = new;
	s->idx = strlen(new);

	return 1;
}
