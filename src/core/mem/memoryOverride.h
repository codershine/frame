void FRAME_DLL_EXPORT * _FrameMalloc(size_t size);
void FRAME_DLL_EXPORT * _FrameRealloc(void *p, size_t size);
void FRAME_DLL_EXPORT _FrameFree(void *p);
void FRAME_DLL_EXPORT * _FrameMalloc_Ex(size_t size, const char *file, unsigned int line);
void FRAME_DLL_EXPORT * _FrameRealloc_Ex(void *p, size_t size, const char *file, unsigned int line);
void FRAME_DLL_EXPORT _FrameFree_Ex(void *p, const char *file, unsigned int line);