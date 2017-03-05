#include "ISReader.h"

ISReader::ISReader(IStream& iStream) :
		iStream(iStream) {
}

ISReader::~ISReader() {
}

void ISReader::open() throw (IOException) {
	iStream.open();
}

void ISReader::close() throw (IOException) {
	iStream.close();
}

size_t ISReader::read(char* data, size_t size) throw (IOException) {
	return iStream.read(data, size);
}

void ISReader::readFully(char* data, size_t size) throw (IOException, EOFException) {
	size_t readed = 0;
	while (readed < size) {
		size_t result = iStream.read(data + readed, size - readed);
		readed += result;
		if (result == 0) {
			throw EOFException();
		}
	}
}

size_t ISReader::readUleb(uint32_t& value) throw (IOException, EOFException, LEBFormatException) {
	char buffer[5];
	size_t index = 0;
	do {
		if (index > 4) {
			throw LEBFormatException();
		}
		read(buffer + index, 1);
	} while (buffer[index++] & 1u << 7);
	return core::readUleb(value, buffer);
}

//size_t ISReader::readSleb(int32_t& value) throw (IOException, EOFException, LEBFormatException) {
//	char buffer[5];
//	size_t index = 0;
//	do {
//		if (index > 4) {
//			throw LEBFormatException();
//		}
//		read(buffer + index, 1);
//	} while (buffer[index++] & 1u << 7);
//	return core::readSleb(value, buffer);
//}
