#ifndef LOG_H_
#define LOG_H_

#ifdef __ANDROID_API__

#ifndef NATIVE_LOG_TAG
#define NATIVE_LOG_TAG "core.lib"
#endif

#include <android/log.h>
#define LOGI(...) {__android_log_print(ANDROID_LOG_INFO, NATIVE_LOG_TAG, __VA_ARGS__)}
#define LOGW(...) {__android_log_print(ANDROID_LOG_WARN, NATIVE_LOG_TAG, __VA_ARGS__)}
#define LOGE(...) {
	((void)__android_log_print(ANDROID_LOG_ERROR, NATIVE_LOG_TAG, "**** ERROR **** ")); \
	((void)__android_log_print(ANDROID_LOG_ERROR, NATIVE_LOG_TAG, __VA_ARGS__));\
}

#else

#include <stdio.h>
#define LOGI(...) printf(__VA_ARGS__); printf("\n");
#define LOGW(...) printf(__VA_ARGS__); printf("\n");
#define LOGE(...) { \
	((void)printf("**** ERROR **** IN %s: %s() : line %d\n\t", __FILE__, __FUNCTION__, __LINE__)); \
	((void)printf(__VA_ARGS__));\
	printf("\n"); \
}
#endif

#endif /* LOG_H_ */
