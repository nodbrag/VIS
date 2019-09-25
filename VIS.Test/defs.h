#ifndef __DEF_H__
#define __DEF_H__

#ifndef _WIN32
#define LT_API
#else
#ifdef LT_EXPORTS	
#define LT_API __declspec(dllexport)
#else
#define LT_API __declspec(dllimport)
#endif
#endif

#endif //__DEFS_H__