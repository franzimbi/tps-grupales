#include <hash.h>
#include <stdint.h>
#include <string.h>

uint32_t jenkins_one_at_a_time_hash(const char *key)
{
    uint32_t hash, i;
    size_t len = strlen(key);
    for(hash = i = 0; i < len; ++i)
    {
        hash += key[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash;
}

