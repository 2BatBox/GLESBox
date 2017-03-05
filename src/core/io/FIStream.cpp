#include "FIStream.h"

#include <cerrno>
#include <cstring>

FIStream::FIStream(const std::string& fileName) :
		fileName(fileName), file(NULL), size(0) {
}

FIStream::~FIStream() {
	try {
		close();
	} catch (const IOException& e) {
		// It doesn't matter anyway.
	}
}

void FIStream::open() throw (IOException) {
	if (file != NULL) {
		throw IOException("File has already opened");
	}
	file = fopen(fileName.c_str(), "r");
	if (file == NULL) {
		std::string message("Can't open file for reading: ");
		throw IOException(message + fileName);
	}
	fseek(file, 0, SEEK_END);
	size = ftell(file);
	fseek(file, 0, SEEK_SET);
}

void FIStream::close() throw (IOException) {
	if (file == NULL) {
		throw IOException("File hasn't opened yet");
	}
	if (fclose(file) != EXIT_SUCCESS) {
		throw IOException(std::strerror(errno));
	}
	file = NULL;
}

size_t FIStream::read(char* data, size_t size) throw (IOException) {
	if (file == NULL) {
		throw IOException("File hasn't opened yet");
	}
	size_t result = fread(data, 1, size, file);
	if (result == 0) {
		if (ferror(file)) {
			throw IOException(std::strerror(errno));
		}
	}
	return result;
}

size_t FIStream::getSize() {
	if (file == NULL) {
		throw IOException("File hasn't opened yet");
	}
	return size;
}
