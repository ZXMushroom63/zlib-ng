#include "../../zbuild.h"
#include "arm_features.h"

Z_INTERNAL int has_neon;
Z_INTERNAL int has_crc32;
Z_INTERNAL int has_simd;

/* AArch64 does not have ARMv6 SIMD. */
#if !defined(__aarch64__) && !defined(_M_ARM64) && !defined(_M_ARM64EC)
static inline int arm_has_simd() {
#if defined(__linux__) && defined(HAVE_SYS_AUXV_H)
    const char *platform = (const char *)getauxval(AT_PLATFORM);
    return strncmp(platform, "v6l", 3) == 0
        || strncmp(platform, "v7l", 3) == 0
        || strncmp(platform, "v8l", 3) == 0;
#elif defined(ARM_NOCHECK_SIMD)
    return 1;
#else
    return 0;
#endif
}
#endif

void Z_INTERNAL arm_check_features(struct arm_cpu_features *features) {
    features->has_simd = 0;
    features->has_neon = 1;
    features->has_crc32 = 0;
}
