#include "ovDir.h"
#include <filesystem>
#include <algorithm>
#include <cctype>

std::vector<std::string> ov::Dir::scan(const std::string &dir, const std::vector<std::string> &patterns, bool recurse)
{
    namespace fs = std::filesystem;

    std::error_code error = {};
    if(!fs::exists(dir, error)) {
        return {};
    }

    if(!fs::is_directory(dir, error)) {
        return {};
    }

    fs::recursive_directory_iterator iter = {dir, fs::directory_options::skip_permission_denied, error};
    if(error) {
        return {};
    }

    std::vector<std::string> pathList = {};
    fs::recursive_directory_iterator end = {};
    while(iter != end) {
        error = {};

        const fs::directory_entry& entry = *iter;
        bool isDir = entry.is_directory(error);
        if(error) {
            error = {};
            isDir = false;
        }

        bool isReg = entry.is_regular_file(error);
        if(error) {
            error = {};
            isReg = false;
        }

        if(!recurse) {
            iter.disable_recursion_pending();
        }
        
        if(isReg) {
            auto name = entry.path().filename().string();
            for(auto& ch : name) {
                ch = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
            }

            for(const auto& pattern : patterns) {
                if(name.find(pattern) != std::string::npos) {
                    pathList.push_back(entry.path().string());
                    break;
                }
            }
        }

        iter.increment(error);
        if(error) {
            error = {};
        }
    }

    std::sort(pathList.begin(), pathList.end());

    return pathList;
}