#ifndef CONFIG_H
#define CONFIG_H

namespace mini_sqlite {
    static constexpr int PAGE_SIZE = 4096;
    static constexpr int DEFAULT_DB_FILE_CAPACITY = 16;
    static constexpr int ROW_SIZE = sizeof(int) + 32 + 255;
}
#endif
