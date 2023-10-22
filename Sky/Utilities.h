#pragma once

#if SK_DEBUG==2
	#define SK_ERROR(x) std::cout<<x<<std::endl;	
	#define SK_LOG(x) std::cout<<x<<std::endl;	
#elif SK_DEBUG==1 
	#define SK_ERROR(x) std::cout<<x<<std::endl;	
	#define SK_LOG(x) 
#else 
	#define SK_ERROR(x)
	#define SK_LOG(x)
#endif

#ifdef SKY_MSCPP
	#ifdef SKY_LIB
		#define SKY_API __declspec(dllexport)
	#else 
		#define SKY_API __declspec(dllimport)
	#endif
#else 
	#define SKY_API 
#endif

#define SKY_APPLICATION_START(ClassName)\
int main()\
{\
	ClassName::Init();\
	ClassName::RunInterface(); \
	return(0);\
}