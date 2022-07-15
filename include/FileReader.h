#ifndef FILEREADER_H
#define FILEREADER_H

#include <fstream>
#include <string>

class FileReader {
private:
    std::fstream m_handler;

    FileReader () = delete;
    FileReader(const FileReader&) = delete;
    FileReader(FileReader&&) = delete;

public : 
    FileReader(std::string_view fname);
    ~FileReader();

    /**
     * @brief returns the content of `fname`
     * 
     * @return std::string 
     */
    auto content() -> std::string;
};


#endif // FILEREADER_H