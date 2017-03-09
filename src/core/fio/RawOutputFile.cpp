#include "RawOutputFile.h"

#include <cstring>

using namespace core;

RawOutputFile::RawOutputFile(FILE* file) :
		file(file) {
}

RawOutputFile::~RawOutputFile() {
	close();
}

OutputFile* RawOutputFile::open(const char* fileName) throw (NullPointerException, FIOException) {
	if (fileName == nullptr) {
		throw NullPointerException();
	}
	FILE* file = fopen(fileName, "w");
	if (file == nullptr) {
		std::string message(std::strerror(errno));
		throw FIOException(message + " : " + fileName);
	}

	return new RawOutputFile(file);
}

void RawOutputFile::close() noexcept {
	if (file != nullptr) {
		fclose(file);
		file = nullptr;
	}
}

unsigned RawOutputFile::write(const char* buffer, unsigned size) throw (FIOException) {
	unsigned result = fwrite(buffer, 1, size, file);
	if (result == 0) {
		if (ferror(file)) {
			throw FIOException(std::strerror(errno));
		}
	}
	return result;
}

void RawOutputFile::seek(unsigned offset, int whence) throw (FIOException) {
	if (fseek(file, offset, whence)) {
		throw FIOException(std::strerror(errno));
	}
}

unsigned RawOutputFile::tell() throw (FIOException) {
	long result = ftell(file);
	if (result < 0) {
		throw FIOException(std::strerror(errno));
	}
	return result;
}
