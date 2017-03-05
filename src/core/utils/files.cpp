#include "files.h"

#include "../io/FIStream.h"
#include "../io/ISReader.h"
#include "../io/FOStream.h"
#include "../io/OSWriter.h"
#include "../memory.h"

core::Array<char> core::loadFile(const char* fileName) throw (IOException, EOFException) {
	FIStream fistream(fileName);
	ISReader isreader(fistream);
	isreader.open();
	size_t fileSize = fistream.getSize();
	AutoArray<char> array(new char[fileSize], fileSize);
	isreader.readFully(*array, array.size);
	isreader.close();
	return array.takeAway();
}

void core::saveFile(const char* fileName, const Array<char>& array) throw (IOException, EOFException) {
	FOStream fostream(fileName);
	OSWriter writer(fostream);
	writer.open();
	writer.writeFully(*array, array.size);
	writer.close();
}

