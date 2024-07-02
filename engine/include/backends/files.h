#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <string>
#include <fstream>
#include <vector>
#include <stdexcept>

#include "../utilities/logger.h"

namespace SealFileManager
{
    class FileException : public std::runtime_error
    {
    public:
        explicit FileException(const std::string &message) : std::runtime_error(message) {}
    };

    class File
    {
    public:
        enum OpenMode
        {
            READ,
            WRITE,
            APPEND
        };

        File(const std::string &path, SealLogger::Logger *logger = nullptr);
        ~File();

        void Open(OpenMode mode);
        void Close();
        long GetSize();
        std::vector<char> ReadAll();
        void WriteAll(const std::vector<char> &data);

        int Read(void *buffer, int size);
        int Write(const void *buffer, int size);

        bool IsOpen() const;

        std::string GetPath() const
        {
            return path;
        }

    private:
        std::string path;
        std::fstream fileStream;
        SealLogger::Logger *logger;

        void CheckIfOpen() const;
        std::ios::openmode ConvertMode(OpenMode mode) const;
    };
}

#endif // FILE_MANAGER_H
