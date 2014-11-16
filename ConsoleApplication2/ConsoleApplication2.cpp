/* Using the standard output for fprintf */
#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
/* Use glew.h instead of gl.h to get all the GL prototypes declared */
#include <GL/glew.h>
/* Using the GLUT library for the base windowing setup */
#include <GL/freeglut.h>
/* ADD GLOBAL VARIABLES HERE LATER */

int init_resources(void)
{
	/* FILLED IN LATER */
	return 1;
}

void onDisplay()
{
	/* FILLED IN LATER */
}

void free_resources()
{
	/* FILLED IN LATER */
}

int main(int argc, char* argv[])
{
	/* Glut-related initialising functions */
	glutInit(&argc, argv);
	glutInitContextVersion(2, 0);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(640, 480);
	glutCreateWindow("My First Triangle");

	/* Extension wrangler initialising */
	GLenum glew_status = glewInit();
	if (glew_status != GLEW_OK)
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(glew_status));
		return EXIT_FAILURE;
	}

	/* When all init functions run without errors,
	the program can initialise the resources */
	if (init_resources())
	{
		/* We can display it if everything goes OK */
		glutDisplayFunc(onDisplay);
		glutMainLoop();
	}

	/* If the program exits in the usual way,
	free resources and exit with a success */
	free_resources();
	return EXIT_SUCCESS;
}