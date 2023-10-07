#include "unixpath.h"

std::string NormalizePath(std::string_view current_working_dir, std::string_view path) {
    std::string cur;
    if (path[0] != '/') {
        for (size_t i = 0; i < current_working_dir.size(); ++i) {
            cur.append(1, current_working_dir[i]);
        }
    } else {
        cur = "/";
    }
    for (size_t i = 0; i < path.size(); ++i) {
        if (path[i] == '.') {
            if (i + 1 != path.size() && path[i + 1] == '.') {
                while (cur[cur.size() - 1] != '/') {
                    cur.erase(cur.size() - 1);
                }
            }
            if (path.size() != 1) {
                cur.erase(cur.size() - 1);
            }
        } else if (path[i] != '/') {
            if (i > 0 && path[i - 1] == '/' && cur[cur.size() - 1] != '/') {
                cur.append(1, '/');
            }
            cur.append(1, path[i]);
        }
    }
    return cur;
}
