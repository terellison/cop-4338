#include"find.h"
//this function finds an occurrence of needle in haystack
//needle must be matched with a whole word in haystack...
static char *strstr_fully_matched(char *haystack, char *needle) {
  char *rv;
  char padded_needle[strlen(needle) + 3];
  padded_needle[0] = ' ';
  strcpy(padded_needle + 1, needle);
  padded_needle[strlen(needle) + 1] = ' ';
  padded_needle[strlen(needle) + 2] = '\0';//pad the needle w/ spaces before and after
  if(!strcmp(needle, haystack))
	  return haystack;// needle matches the whole haystack
  if (!strncmp(haystack, padded_needle + 1, strlen(needle) + 1)) {
    return haystack; // needle is at the beginning of haystack
  }
  if ((rv = strstr(haystack, padded_needle)) != NULL) {
    return rv + 1; // needle is at the middle of haystack.
  }
  padded_needle[strlen(needle) + 1] = '\0';//remove the last space
  if ((rv = strstr(haystack, padded_needle)) != NULL &&
      rv[strlen(padded_needle)] == '\0') {
    return rv + 1; // needle is at the end of haystack.
  }
  return NULL;
}
//lowers the case of each character in its input string
static void to_lower(char* input){
	for(int i = 0;i < strlen(input);i++)
		input[i] = tolower(input[i]);
}
//this function finds an occurrence of needle in haystack
//option specify case-sensitivity of search and whether needle should match a whole word
char* strstr_w_option(char* haystack, char* needle, flags option){
	if(option & CASE){
		to_lower(haystack = strdup(haystack));
		to_lower(needle = strdup(needle));
		if(option & MATCHED)
			return strstr_fully_matched(haystack, needle);
		else
			return strstr(haystack, needle);
	}else if(option & MATCHED)
		return strstr_fully_matched(haystack, needle);
	else
		return strstr(haystack, needle);
}
//subroutine used in qsort
static void swap(void** v, int i, int j){
  void* temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}
//quick sort on array of strings
void quicksort(char*str[], int left, int right){
  int i, last;
  if(left >= right)
    return;
  swap(str, left, left + (right-left)/2);
  last = left;
  for(i = left + 1; i <= right;i++)
    if(strcmp(str[i],str[left]) < 0)
      swap(str, ++last, i);
  swap(str, left, last);
  quicksort(str, left, last-1);
  quicksort(str, last+1, right);
}

/// @brief Returns the index of the first occurrence of a given substring within a string
/// @param str String to search
/// @param subStr Substring to find within str
/// @return First index of the first occurrence of subStr in str, 
/// or -1 if subStr is not found
int find(const char* str, const char* subStr, const flags option)
{
  if(!strstr_w_option(str, subStr, option))
  {
    return -1;
  }

  int len1 = strlen(str), len2 = strlen(subStr), 
  i = 0, j = 0, matched = 0, rVal = 0;

  while(i < len1 && j < len2 && matched < len2)
  {
    char a = str[i], b = subStr[j];

    if(option & CASE)
    {
      if(a >= 'A' && a <= 'Z')
        {
            a = a + ('a' - 'A');
        }

        if(b >= 'A' && b <= 'Z')
        {
            b = b + ('a' - 'A');
        }
    }

    if(a == b)
    {
      if(matched == 0)
      {
        rVal = i;
      }
      ++matched;
      ++j;

      if((option & MATCHED) && matched == len2)
      {
        // Reset matched if not fully matched
        int goodFront = (str[rVal-1] == ' ') || (rVal == 0);
        int goodBack = (str[i+1] == ' ') || (str[i+1] == '\0');

        if(!(goodFront && goodBack))
        {
          matched = 0;
          j = 0;
        }
        
      }
    }
    else
    {
      matched = 0;
      j = 0;
    }

    ++i;
  }

  return rVal;
}