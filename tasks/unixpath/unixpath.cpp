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
                while (cur.back() != '/') {
                    cur.pop_back();
                }
                if (cur.size() != 1) {
                    cur.pop_back();
                }
            }
        } else if (path[i] != '/') {
            if (i > 0 && path[i - 1] == '/' && cur.back() != '/') {
                cur.push_back('/');
            }
            cur.push_back(path[i]);
        }
    }
    return cur;
}
