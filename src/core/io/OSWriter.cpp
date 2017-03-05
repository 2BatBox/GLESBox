#include "OSWriter.h"

OSWriter::OSWriter(OStream& oStream) :
		oStream(oStream) {
}

OSWriter::~OSWriter() {
}

void OSWriter::open() throw (IOException) {
	oStream.open();
}

void OSWriter::close() throw (IOException) {
	oStream.close();
}

size_t OSWriter::write(const char* data, size_t size) throw (IOException) {
	return oStream.write(data, size);
}

void OSWriter::writeFully(const char* data, size_t size) throw (IOException) {
	size_t writed = 0;
	while (writed < size) {
		size_t result = oStream.write(data + writed, size - writed);
		writed += result;
		if (result == 0) {
			throw IOException("Can't write buffer");
		}
	}
}

size_t OSWriter::writeUleb(uint32_t value) throw (IOException) {
	char buffer[5];
	size_t result = core::writeUleb(value, buffer);
	writeFully(buffer, result);
	return result;
}

//size_t OSWriter::writeSleb(int32_t value) throw (IOException) {
//	char buffer[5];
//	size_t result = core::writeSleb(value, buffer);
//	writeFully(buffer, result);
//	return result;
//}
