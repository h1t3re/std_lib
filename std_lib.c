#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int strncmp(const char *str1, const char *str2)
{
	int i = 0;
	while((*(str1+i) != '\0') & (*(str2+i) != '\0'))
	{
		if(*(str1+i) != *(str2+i))
			return 1;
		i = i +1;
	}
	if(((*(str1+i) != '\0') & (*(str2+i) == '\0')) | ((*(str1+i) == '\0') & (*(str2+i) != '\0')))
	       return 1;	
	return 0;
}

unsigned int strlen(const char *str)
{
	unsigned int len = 0;
	while(*(str+len) != '\0')
		len = len +1;
	return len +1;
}

char *strdup(const char *str)
{
	int len = 0;
	int i = 0;
	while(*(str+len) != '\0')
		len = len +1;
	len = len +1;

	char *duplicat_of_str = (char *)malloc(len*sizeof(char));
	
	while(i < len)
	{
		duplicat_of_str[i] = str[i];
		i = i +1;
	}
	duplicat_of_str[len] = str[len];
	return duplicat_of_str;
}

char *read_input()
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
	while(strncmp(buffer_buffer_len_content, end_of_line) != 0)
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

char *read_file(char *file_name)
{
	int fd = open(file_name, 'r');
	if(fd == -1)
		return NULL;
	char *buffer;
	int buffer_len = 0;
	buffer = (char *)malloc(sizeof(char));
	if(buffer == NULL)
		return NULL;
	while(read(fd, &(*(buffer+buffer_len)), sizeof(char)) > 0)
	{
		buffer_len = buffer_len + 1;
		buffer = (char *)realloc(buffer, (buffer_len+1)*sizeof(char));
		if(buffer == NULL)
			return NULL;
	}
	*(buffer+buffer_len) = '\0';
	close(fd);
	return buffer;
}

int strcontains(const char *str1, const char *str2)
{
	int i = 0;
	int j = 0;
	int strlen_array1 = 0;
	int strlen_array2 = 0;
	char *array1;
	char *array2;
	char *tmp;
	int tmp0 = 0;
	while(strlen_array1 < strlen(str1))
		strlen_array1 = strlen_array1 +1;
	while(strlen_array2 < strlen(str2))
		strlen_array2 = strlen_array2 +1;
	
       	array1 = (char *)malloc(strlen_array1*sizeof(char));
       	array2 = (char *)malloc(strlen_array2*sizeof(char));
	
	while(i < strlen_array1)
	{
		*(array1 + i)	= *(str1 + i);
		i = i +1;
	}
	i = 0;
	while(i < strlen_array2)
	{
		*(array2 + i)	= *(str2 + i);
		i = i +1;
	}
	if(strlen_array1 < strlen_array2)
	{
		tmp = strdup(array1);
		array1 = strdup(array2);
		array2 = tmp;
		tmp0 = strlen_array1;
		strlen_array1 = strlen_array2;
		strlen_array2 = tmp0;
	}
	i = 0;
	while(*(array1 + i) != '\0')
	{
		j = 0;
		while((*(array1 + i + j) == (*(array2 + j))) & (*(array2 + j) != '\0'))
			j = j + 1;
		if(j == strlen_array2)
			return 0;
		i = i +1;
	}
	return 1;
}

char **s(char *buffer, char *spliter)
{
	char **array = (char **)malloc(sizeof(char *));
	int i = 0;
	int j = 0;
	int k = 0;
	int v = 0;
	char *str0 = (char *)malloc(sizeof(char));
	char *str1 = (char *)malloc(strlen(spliter)*sizeof(char));
	array[k] = (char *)malloc(sizeof(char));
	while(i <= strlen(spliter))
	{
		str0[i] = spliter[i];
		i = i +1;
		str0 = (char *)realloc(str0, (i+1)*sizeof(char));
	}
	str0[i] = '\0';
	i = 0;
	while(i <= strlen(buffer))
	{
		v = 0;
		while(v < strlen(spliter))
		{
			str1[v] = buffer[i+v];
			v = v +1;
		}
		while((strncmp(str0, str1) == 0) & (buffer[i] != '\0'))
		{
			i = i +1;
		}
		if((strncmp(str0, str1) != 0) & (buffer[i] != '\0'))
		{
			array[k][j] = buffer[i];
			j = j +1;
			array[k] = (char *)realloc(array[k], (j+1)*sizeof(char));
		}else{
			if(j >= 1)
			{
				array[k][j] = '\0';
				k = k +1;
				array = (char **)realloc(array, (k+1)*sizeof(char *));
				array[k] = (char *)malloc(sizeof(char));
			}
			j = 0;
		}
		i = i +1;
	}
	array[k][0] = '\0';
	return array;
}

char **split(char *buffer, char *spliter)
{
	char **array = (char **)malloc(sizeof(char *));
	int i = 0;
	int j = 0;
	int k = 0;
	int v = 0;
	char *str0 = (char *)malloc(sizeof(char));
	char *str1 = (char *)malloc(2*sizeof(char));
	array[k] = (char *)malloc(sizeof(char));
	while(i <= strlen(spliter))
	{
		str0[i] = spliter[i];
		i = i +1;
		str0 = (char *)realloc(str0, (i+1)*sizeof(char));
	}
	str0[i] = '\0';
	i = 0;
	while(i <= strlen(buffer))
	{
		while((buffer[i] == spliter) & (buffer[i] != '\0'))
		{
			i = i +1;
		}
		str1[0] = buffer[i];
		str1[1] = '\0';
		if((strncmp(str0, str1) != 0) & (buffer[i] != '\0'))
		{
			array[k][j] = buffer[i];
			j = j +1;
			array[k] = (char *)realloc(array[k], (j+1)*sizeof(char));
		}else{
			if(j >= 1)
			{
				array[k][j] = '\0';
				k = k +1;
				array = (char **)realloc(array, (k+1)*sizeof(char *));
				array[k] = (char *)malloc(sizeof(char));
			}
			j = 0;
		}
		i = i +1;
	}
	array[k][0] = '\0';
	return array;
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

void *convert_integer_to_binary(int *array, int mask, const int number)
{
	int i = 0;
	while(i < 32)
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

void convert_hexa_to_binary(int *array, int mask, char hexa)
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
