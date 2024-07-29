#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void dd_0(void *ptr, int c, int length)
{
	int i = 0;
	while(i < length)
	{
		if(sizeof(*ptr) == sizeof(char))
		{
			*((char*)(ptr+(i*sizeof(char)))) = c;
		}else if(sizeof(*ptr) == sizeof(int))
		{
			*((int *)(ptr+(i*sizeof(int)))) = c;	
		}
		i = i +1;
	}
}

long unsigned int strlen(const char *str)
{
	long unsigned int length = 0;
	while(str[length] != '\0')
	{
		length = length +1;
	}
	return length;
}	

const int strcmp(const char *str0, const char *str1)
{
	int i = 0;
	while((str0[i] == str1[i]) & ((str0[i] != '\0') & (str1[i] != '\0')))
	{
		i = i +1;
	}
	if(strlen(str0) != i)
		return 1;
	return 0;
}

char *strdup(const char *str)
{
	char *dupofstr = (char *)malloc((strlen(str)+1)*sizeof(char));
	if(dupofstr == NULL)
		return NULL;
	int length = 0;
	while(str[length] != '\0')
	{
		dupofstr[length] = str[length];
		length = length +1;
	}
	dupofstr[length] = str[length];
	return dupofstr;
}

char *strstrip(const char *s, const char *x)
{
	int i = 0;
	int j = 0;
	char *buffer = (char *)malloc(sizeof(char));
	while(s[j] != '\0')
	{
		if(s[j] != *x)
		{
			buffer[i] = s[j];
			i = i +1;
			buffer = (char *)realloc(buffer, (i+1)*sizeof(char));
		}
		j = j +1;
	}
	buffer[i] = '\0';
	return buffer;
}

const int strcontains(const char *str0, const char *str1)
{
	int i = 0, j = 0;
	while(str0[i+j] != '\0')
	{
		if((str0[i+j] == str1[j]) & (str1[j] != '\0'))
		{
			j = j +1;
		}
		else{
			i = i +1;
			j = 0;
		}
		if(j == strlen(str1))
		{
			return 0;
		}
	}
	return 1;
}

char *strconcatenate(const char *str0, const char *str1)
{
	char *buffer = strdup(str0);	
	const char *str = strdup(str1);	
	int lengh0 = strlen(str0);
	int lengh1 = strlen(str1);
	int i = lengh0;
	buffer = (char *)realloc(buffer, (lengh0+lengh1)*sizeof(char));
	if(buffer == NULL)
		return NULL;
	while((i < (lengh0+lengh1)) & (str[i-lengh0] != '\0'))
	{
		buffer[i] = str[i-lengh0];
		i = i +1;	
	}
	buffer[i] = '\0';
	return buffer;	
}

int find_string_position(char *buffer, char *string, int position)
{
	int i = 0;
	int j = 0;
	int position_found = 0;
	char *str = (char *)malloc(strlen(string)*sizeof(char));
	while(buffer[i] != '\0')
	{
		while(j < strlen(string))
		{	
			str[j] = buffer[i];
			i = i +1;
			j = j +1;
		}
		str[j] = '\0';
		j = 0;
		if(strcmp(string, str) == 0)
		{
			position_found = position_found +1;
			if(position_found == position)
				return i-1;
		}
	}
	return 0;
}

char **get_data_by_key(char *buffer, char *key, int number_of_lines)
{
	char **array = (char **)malloc(sizeof(char *));
	char *cmp = (char *)malloc(strlen(key)*sizeof(char));
	char *data = (char *)malloc(sizeof(char));
	int len = 0;
	int i = 0;
	int c = 0;
	while(buffer[len] != '\0')
	{
		while(i < strlen(key))
		{
			cmp[i] = buffer[len+i];
			i = i +1;	
		}
		i = 0;
		if(strcmp(cmp, key) == 0)
		{
			while(buffer[len] != '\n')
			{
				data[i] = buffer[len];
				i = i +1;
				len = len +1;
				data = (char *)realloc(data, (i+1)*sizeof(char));
			}
			data[i] = '\0';
			i = 0;
			array[c] = strdup(data);
			free(data);
			data = (char *)malloc(sizeof(char));
			c = c +1;
			array = (char **)realloc(array, (c+1)*sizeof(char *));
		}
		len = len +1;
		if((c == number_of_lines)|(number_of_lines != -1))
			break;
	}
	array[c] = '\0';
	free(cmp);
	return array;
}

char **strsplit(char *str, char *spliter)
{
	char **array = (char **)malloc(sizeof(char *));
	char *data = (char *)malloc(strlen(spliter)*sizeof(char));	
	char *buffer = (char *)malloc(sizeof(char));
	int c = 0;
	int i = 0;
	int j = 0;
	int a = 0;
	int spliter_length = strlen(spliter);
	while(str[i] != '\0')
	{
		while(j < spliter_length)
		{
			data[j] = str[i+j];
			buffer[c] = str[i+j];
			j = j +1;
			c = c +1;
			buffer = (char *)realloc(buffer, (c+1)*sizeof(char));
		}
		data[j] = '\0';
		if(strcmp(data, spliter) == 0)
		{
			buffer[c] = '\0';
			buffer = strstrip(buffer, spliter);
			array[a] = strdup(buffer);
			i = i +j;
			j = 0;
			a = a +1;
			c = 0;
			free(buffer);
			array = (char **)realloc(array, (a+1)*sizeof(char *));
			buffer = (char *)malloc(sizeof(char));
		}else if(strcmp(data, spliter) == 1)
		{
			i = i +j;
			j = 0;
		}
		dd_0((void *)data, 0, spliter_length);
	}
	a = a +1;
        array = (char **)realloc(array, (a+1)*sizeof(char *));
        array[a] = (char *)malloc(sizeof(char));
	array[a] = '\0';
	return array;
}

/*char *snprintf(int size, char *string, NULL **variables)
{
	char *s = strsplit(string, strdup("%\0"));
	int counter = 0;
	int i = 0;
	char *result;
	while(s[counter] != '\0')
	{
		if(strlen(s[counter]) != 1)
			result = strconcatenate(strdup(result), strdup(s[counter]));
		else
		{
			if(strcmp(strdup(s[counter]), strdup("d\0")) == 0)
			{
				result = strconcatenate(result, convert_int_to_char(variables[i]));
				i++;
			}else if(strcmp(strdup(s[counter]), strdup("s\0")) == 0)
			{
				result = strconcatenate(result, (char *)variables[i])
				i++;
			}
		}
		counter++;
	}
	return strdup(result);
}
*/
char *get_data_by_key_until_end(const char *restrict buffer, char *key, char *end)
{
	char *cmp = (char *)malloc(strlen(key)*sizeof(char));
	char *data = (char *)malloc(sizeof(char));
	int len = 0;
	int i = 0;
	int j = 0;
	while(buffer[len] != '\0')
	{
		while(i < strlen(key))
		{
			cmp[i] = buffer[len+i];
			i = i +1;	
		}
		cmp[i] = '\0';
		i = 0;
		if(strcmp(cmp, key) == 0)
		{
			while(strcmp(cmp, end) != 0)
			{
				data[j] = buffer[len];
				j = j +1;
				len = len +1;
				data = (char *)realloc(data, (j+1)*sizeof(char));
				while(i < strlen(key))
				{	
					cmp[i] = buffer[len+i]; 
					i = i +1;
				}
				cmp[i] = '\0';
				i = 0;
			}
			break;
		}
		len = len +1;
	}
	data[j] = '\0';	
	return data;
}	

char *read_io()
{
	char *buffer = (char *)malloc(2*sizeof(char));
	char *buffer_buffer_len_content = (char *)malloc(2*sizeof(char));
	char *end_of_line = (char *)malloc(2*sizeof(char));
	int buffer_len = 0;
	*buffer = ' ';
	*(buffer+1) = '\0';
	*end_of_line = '\n';
	*(end_of_line+1) = '\0';
	snprintf(buffer_buffer_len_content, 2*sizeof(char), "%c\0", *(buffer+buffer_len));
	while(strcmp(buffer_buffer_len_content, end_of_line) != 0)
	{
		read(1, &(*(buffer+buffer_len)), sizeof(char));
		snprintf(buffer_buffer_len_content, 2*sizeof(char), "%c\0", *(buffer+buffer_len));
		buffer_len = buffer_len + 1;
		buffer = (char *)realloc(buffer, (buffer_len+2)*sizeof(char));
		*(buffer+buffer_len) = '\0';
	}
	free(buffer_buffer_len_content);
	free(end_of_line);
	return buffer;
}

char *read_file(const char *restrict file_name)
{
	const char *restrict mode = strdup("r\0");
	FILE *restrict fd = fopen(file_name, mode);
	if(fd == NULL)
		return NULL;
	char *buffer = (char *)malloc(sizeof(char));
	int buffer_len = 0;
	do
	{
		buffer_len = buffer_len +1;
		fread(buffer+((buffer_len-1)*sizeof(char)), sizeof(char), 1, fd);
		buffer = (char *)realloc(buffer, (buffer_len+1)*sizeof(char));
	}while(*(buffer+((buffer_len-1)*sizeof(char))) != EOF);
	*(buffer+((buffer_len-1)*sizeof(char))) = '\0';
	return buffer;
}

const int shift_mask_left(const int mask, const int i)
{
	const int mask_shifted = mask << i;
	return mask_shifted;
}

const int and_operation(const int number, const int mask_shifted)
{
	const int result = number & mask_shifted;
	return result;
}

const int shift_result_right(const int number, const int i)
{
	const int result = number >> i;
	return result;
}

void convert_integer_to_binary(int *restrict array, const int number, const int mask, const int length)
{
	int i = 0;
	while(i < length)
	{
		const int mask_shifted = shift_mask_left(mask, i);
		const int and_result = and_operation(number, mask_shifted);
		array[i] = shift_result_right(and_result, i);
		i = i +1;
	}
}

int convert_hexa_to_int(char hexa)
{
	if(hexa == '0')
		return 0;
	if(hexa == '1')
		return 1;
	if(hexa == '2')
		return 2;
	if(hexa == '3')
		return 3;
	if(hexa == '4')
		return 4;
	if(hexa == '5')
		return 5;
	if(hexa == '6')
		return 6;
	if(hexa == '7')
		return 7;
	if(hexa == '8')
		return 8;
	if(hexa == '9')
		return 9;
	if(hexa == 'a')
		return 10;
	if(hexa == 'b')
		return 11;
	if(hexa == 'c')
		return 12;
	if(hexa == 'd')
		return 13;
	if(hexa == 'e')
		return 14;
	if(hexa == 'f')
		return 15;
	return -1;
}

void convert_hexa_to_binary(int *restrict array, char hexa, int mask)
{
	const int number = convert_hexa_to_int(hexa);
	int i = 0;
	while(i < 4)
	{
		const int mask_shifted = shift_mask_left(mask, i);
		const int and_result = and_operation(number, mask_shifted);
		array[i] = shift_result_right(and_result, i); 
		i = i +1;
	}
}

long convert_char_to_int(char str)
{
	return atoi(str);
}

char convert_int_to_char(long n)
{
	return n - 48 + '0';
}

double pow(double x, double y)
{
	if(y == 1)
		return x;
	return pow(x*x, y-1);
}

int convert_binary_to_integer(int *array, int architecture)
{
	int number = 0;
	int i = architecture-1;
	while(i >= 0)
	{
		if(array[i] == 1)
			number = number + pow(2, i+1);
		i = i -1;
	}
	return number;
}

void print(const char *str, const char *type)
{
        char *string = strdup("string\0");
        int buffer_len = 0;
        if(strcmp(type, string) == 0)
        {
                while(str[buffer_len] != '\0')
                {
                        fwrite(str+(buffer_len*sizeof(char)), sizeof(char), 1, stdout);
                        buffer_len = buffer_len +1;
                }
                fwrite(str+(buffer_len*sizeof(char)), sizeof(char), 1, stdout);
        }
}

int *concatenate_int_arrays(int *restrict array0, int length0, int *restrict array1, int length1)
{
	int i = 0;
	int j = 0;
	int length = 0;
	int *array = (int *)malloc((length0+length1)*sizeof(int));
	
	while(i < length0)
	{
		array[i] = array0[i];
		i = i +1;	
	}
	while(i < (length0+length1))
	{
		array[i] = array1[i-length0];
		i = i +1;
	}
	return array;
}

void write_to_file(char *file_name, char *buffer)
{
	FILE *restrict file = fopen(file_name, "w\0");
	int buffer_len = 0;
	while(buffer[buffer_len] != '\0')
	{
		fwrite(buffer+(buffer_len*sizeof(char)), sizeof(char), 1, file);
		buffer_len = buffer_len +1;
	}
}
