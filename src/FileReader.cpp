#include "../include/FileReader.h"

FileReader::FileReader(std::string_view fname) {
  m_handler.open(static_cast<std::string>(fname), std::fstream::in);
}

FileReader::~FileReader(void) { m_handler.close(); }

auto FileReader::content(void) -> std::string {
  return {std::istreambuf_iterator<char>(m_handler),
          std::istreambuf_iterator<char>()};
}