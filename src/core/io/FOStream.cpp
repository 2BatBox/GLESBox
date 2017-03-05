#include "FOStream.h"

#include <cerrno>
#include <cstring>

FOStream::FOStream(const std::string& fileName) :
		fileName(fileName), file(NULL) {
}

FOStream::~FOStream() {
	try {
		close();
	} catch (const IOException& e) {
		// It doesn't matter anyway.
	}
}

void FOStream::open() throw (IOException) {
	if (file != NULL) {
		throw IOException("File has already opened");
	}
	file = fopen(fileName.c_str(), "w");
	if (file == NULL) {
		std::string message("Can't open file for writing: ");
		throw IOException(message + fileName);
	}
}

void FOStream::close() throw (IOException) {
	if (file == NULL) {
		throw IOException("File hasn't opened yet");
	}
	if (fclose(file) != EXIT_SUCCESS) {
		throw IOException(std::strerror(errno));
	}
	file = NULL;
}

size_t FOStream::write(const char* data, size_t size) throw (IOException) {
	int8_t* dataPrt = (int8_t*) data;
	if (file == NULL) {
		throw IOException("File hasn't opened yet");
	}
	size_t result = fwrite(dataPrt, 1, size, file);
	if (result == 0) {
		if (ferror(file)) {
			throw IOException(std::strerror(errno));
		}
	}
	return result;
}
