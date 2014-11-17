#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
char* file_read(const char* filename)
{
	FILE* input;
	errno_t err;
	if ((err = fopen_s(&input, filename, "rt")) != 0){
		printf("File was not opened\n");
		return NULL;
	}
	/*int c;
	while ((c = getc(input)) != EOF)
		putchar(c);*/
	//printf("File was opened\n");
	char nextChar = getc(input);
	long size = 0;

	while (nextChar != EOF) {
		//Do something else, like collect statistics
		size++;
		nextChar = getc(input);
	}
	rewind(input);
	/*if using c-compiler: dont cast malloc's return value*/
	char *content = (char*)malloc((size_t)size + 1);
	if (content == NULL) return NULL;

	fread(content, 1, (size_t)size, input);
	if (ferror(input)) {
		free(content);
		return NULL;
	}

	fclose(input);
	content[size] = '\0';
	return content;
}

/**
* Display compilation errors from the OpenGL shader compiler
*/
void print_log(GLuint object)
{
	GLint log_length = 0;
	if (glIsShader(object))
		glGetShaderiv(object, GL_INFO_LOG_LENGTH, &log_length);
	else if (glIsProgram(object))
		glGetProgramiv(object, GL_INFO_LOG_LENGTH, &log_length);
	else {
		fprintf(stderr, "printlog: Not a shader or a program\n");
		return;
	}

	char* log = (char*)malloc(log_length);

	if (glIsShader(object))
		glGetShaderInfoLog(object, log_length, NULL, log);
	else if (glIsProgram(object))
		glGetProgramInfoLog(object, log_length, NULL, log);

	fprintf(stderr, "%s", log);
	free(log);
}

/**
* Compile the shader from file 'filename', with error handling
*/
GLuint create_shader(const char* filename, GLenum type)
{
	const GLchar* source = file_read(filename);
	if (source == NULL) {
		fprintf(stderr, "Error opening %s: ", filename); perror("");
		return 0;
	}
	GLuint res = glCreateShader(type);
	const GLchar* sources[2] = {
#ifdef GL_ES_VERSION_2_0
		"#version 100\n"
		"#define GLES2\n",
#else
		"#version 120\n",
#endif
		source };
	glShaderSource(res, 2, sources, NULL);
	free((void*)source);

	glCompileShader(res);
	GLint compile_ok = GL_FALSE;
	glGetShaderiv(res, GL_COMPILE_STATUS, &compile_ok);
	if (compile_ok == GL_FALSE) {
		fprintf(stderr, "%s:", filename);
		print_log(res);
		glDeleteShader(res);
		return 0;
	}

	return res;
}