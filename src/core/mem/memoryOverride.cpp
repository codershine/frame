#include "stdafx.h"

void* _FrameMalloc(size_t size)
{
	return malloc(size);
}

void* _FrameRealloc(void *p, size_t size)
{
	return realloc(p, size);
}

void _FrameFree(void *p)
{
	free(p);
}

void* _FrameMalloc_Ex(size_t size, const char *file, unsigned int line)
{
	(void)file;
	(void)line;

	return malloc(size);
}

void* _FrameRealloc_Ex(void *p, size_t size, const char *file, unsigned int line)
{
	(void)file;
	(void)line;

	return realloc(p, size);
}

void _FrameFree_Ex(void *p, const char *file, unsigned int line)
{
	(void)file;
	(void)line;

	free(p);
}