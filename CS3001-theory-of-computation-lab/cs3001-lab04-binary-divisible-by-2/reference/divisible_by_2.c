#include "divisible_by_2.h"
#include <stddef.h>

int is_binary_divisible_by_2(const char *s) {
    if (s == NULL || *s == '\0') {
        return 0;
    }
    
    size_t len = 0;
    while (s[len] != '\0') {
        if (s[len] != '0' && s[len] != '1') {
            return 0;
        }
        len++;
    }
    
    return (s[len - 1] == '0') ? 1 : 0;
}
