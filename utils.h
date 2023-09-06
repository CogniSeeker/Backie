#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <filesystem>
#include <random>

enum class BackupType {
    NONE,           ///< Represents a default value for the type
    FULL,           ///< Represents a full backup.
    INCREMENTAL     ///< Represents an incremental backup only of the files that have changed since full backup.
    // DIFFERENTIAL  // Future extension
};
namespace fs = std::filesystem;

BackupType typeFromStr(const std::string& string);

const std::string strFromType(const BackupType type);

std::wstring strToWStr(const std::string& s);

std::string generate_uuid_v4();

bool IsRunningAsAdmin();

#endif // UTILS_H
