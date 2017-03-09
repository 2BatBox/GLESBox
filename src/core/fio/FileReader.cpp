#include "FileReader.h"

using namespace core;

FileReader::FileReader(InputFile* file) :
		file(file) {
}

unsigned FileReader::read(char* buffer, unsigned size) throw (FIOException) {
	return file->read(buffer, size);
}

unsigned FileReader::readFully(char* buffer, unsigned size) throw (FIOException, EOFException) {
	unsigned readed = 0;
	while (readed < size) {
		unsigned result = file->read(buffer + readed, size - readed);
		readed += result;
		if (result == 0) {
			throw EOFException();
		}
	}
	return readed;
}
