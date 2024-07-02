#include <backends/files.h>

namespace SealFileManager
{
    File::File(const std::string &path, SealLogger::Logger *logger) : path(path), logger(logger) {}

    File::~File()
    {
        if (fileStream.is_open())
        {
            fileStream.close();
        }
    }

    void File::Open(OpenMode mode)
    {
        if (fileStream.is_open())
        {
            if (logger)
            {
                logger->error("File is already open.");
            }
            return;
        }

        std::ios::openmode openMode = ConvertMode(mode);
        fileStream.open(path, openMode);

        if (!fileStream.is_open())
        {
            if (logger)
            {
                logger->error("Failed to open file: " + path);
            }
            return;
        }
    }

    void File::Close()
    {
        if (!fileStream.is_open())
        {
            if (logger)
            {
                logger->error("File is not open.");
            }
            return;
        }
        fileStream.close();
    }

    long File::GetSize()
    {
        CheckIfOpen();

        std::streampos currentPos = fileStream.tellg();
        fileStream.seekg(0, std::ios::end);
        std::streampos size = fileStream.tellg();
        fileStream.seekg(currentPos, std::ios::beg);

        return static_cast<long>(size);
    }

    std::vector<char> File::ReadAll()
    {
        CheckIfOpen();

        long size = GetSize();
        std::vector<char> buffer(size);

        fileStream.seekg(0, std::ios::beg);
        if (!fileStream.read(buffer.data(), size))
        {
            if (logger)
            {
                logger->error("Failed to read file.");
            }
            return std::vector<char>();
        }

        return buffer;
    }

    void File::WriteAll(const std::vector<char> &data)
    {
        CheckIfOpen();

        fileStream.write(data.data(), data.size());
        if (!fileStream)
        {
            if (logger)
            {
                logger->error("Failed to write file.");
            }
        }
    }

    int File::Read(void *buffer, int size)
    {
        CheckIfOpen();

        if (!fileStream.read(static_cast<char *>(buffer), size))
        {
            return -1;
        }
        return static_cast<int>(fileStream.gcount());
    }

    int File::Write(const void *buffer, int size)
    {
        CheckIfOpen();

        if (!fileStream.write(static_cast<const char *>(buffer), size))
        {
            return -1;
        }
        return size;
    }

    bool File::IsOpen() const
    {
        return fileStream.is_open();
    }

    void File::CheckIfOpen() const
    {
        if (!fileStream.is_open())
        {
            if (logger)
            {
                logger->error("File is not open.");
            }
            throw FileException("File is not open.");
        }
    }

    std::ios::openmode File::ConvertMode(OpenMode mode) const
    {
        switch (mode)
        {
        case READ:
            return std::ios::in | std::ios::binary;
        case WRITE:
            return std::ios::out | std::ios::binary | std::ios::trunc;
        case APPEND:
            return std::ios::out | std::ios::binary | std::ios::app;
        default:
            if (logger)
            {
                logger->error("Unknown open mode.");
            }
            throw FileException("Unknown open mode.");
        }
    }
}