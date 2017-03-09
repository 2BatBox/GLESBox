#include "RawInputFile.h"

//#include <cerrno>
#include <cstring>

using namespace core;

RawInputFile::RawInputFile(FILE* file, unsigned size) :
		file(file), fileSize(size) {
}

RawInputFile::~RawInputFile() {
	close();
}

InputFile* RawInputFile::open(const char* fileName) throw (NullPointerException, FIOException) {
	if (fileName == nullptr) {
		throw NullPointerException();
	}
	FILE* file = fopen(fileName, "r");
	if (file == nullptr) {
		std::string message(std::strerror (errno));
		throw FIOException(message + " : " + fileName);
	}

	if (fseek(file, 0, SEEK_END)) {
		fclose(file);
		std::string message(std::strerror (errno));
		throw FIOException(message + " : " + fileName);
	}

	long size = ftell(file);
	if (size < 0) {
		fclose(file);
		std::string message(std::strerror (errno));
		throw FIOException(message + " : " + fileName);
	}
	if (fseek(file, 0, SEEK_SET)) {
		fclose(file);
		std::string message(std::strerror (errno));
		throw FIOException(message + " : " + fileName);
	}
	return new RawInputFile(file, size);
}

void RawInputFile::close() noexcept {
	if(file != nullptr) {
		fclose(file);
		file = nullptr;
	}
}

unsigned RawInputFile::read(char* buffer, unsigned size) throw (FIOException) {
	unsigned result = fread(buffer, 1, size, file);
	if (result == 0) {
		if (ferror(file)) {
			throw FIOException(std::strerror(errno));
		}
	}
	return result;
}

void RawInputFile::seek(unsigned offset, int whence) throw (FIOException) {
	if (fseek(file, offset, whence)) {
		throw FIOException(std::strerror(errno));
	}
}

unsigned RawInputFile::tell() throw (FIOException) {
	long result = ftell(file);
	if (result < 0) {
		throw FIOException(std::strerror(errno));
	}
	return result;
}
