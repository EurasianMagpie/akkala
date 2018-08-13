

//  logd_etc.h

#ifndef _____akkala_logd_etc_h_____
#define _____akkala_logd_etc_h_____

#ifdef __cplusplus
extern "C" {
#endif
    /*
     * Android log priority values, in ascending priority order.
     */
    typedef enum android_LogPriority {
        ANDROID_LOG_UNKNOWN = 0,
        ANDROID_LOG_DEFAULT,    /* only for SetMinPriority() */
        ANDROID_LOG_VERBOSE,
        ANDROID_LOG_DEBUG,
        ANDROID_LOG_INFO,
        ANDROID_LOG_WARN,
        ANDROID_LOG_ERROR,
        ANDROID_LOG_FATAL,
        ANDROID_LOG_SILENT,     /* only for SetMinPriority(); must be last */
    } android_LogPriority;
    
#ifndef __android_log_print
#define __android_log_print(lvl, tag, ...) printf(__VA_ARGS__)
#endif
    
#ifndef __android_log_assert
#define __android_log_assert(...) sizeof(__VA_ARGS__)
#endif
    
#ifdef __cplusplus
}
#endif

#endif//_____akkala_logd_etc_h_____
