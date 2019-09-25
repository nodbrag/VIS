/*
* trace.h
*
*  Created on: Nov 02, 2017
*      Author: gyz
*/

#ifndef DEF_H_
#define DEF_H_

#ifndef _WIN32
#define LT_API
#else
#ifdef LT_EXPORTS	
#define LT_API __declspec(dllexport)
#else
#define LT_API
#endif
#endif

#endif /* DEF_H_ */