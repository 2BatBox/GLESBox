#ifndef CORE_FIO_FILEWRITER_H_
#define CORE_FIO_FILEWRITER_H_

#include "OutputFile.h"
#include "../utils/endian.h"

namespace core {

class FileWriter {

protected:
	OutputFile* file;

public:
	FileWriter(OutputFile* file);

	virtual ~FileWriter() = default;

	unsigned write(char* buffer, unsigned size) throw (FIOException);

	unsigned writeFully(const char* buffer, unsigned size) throw (FIOException);

	template <typename M>
	unsigned writeLittleEndian(M value) throw(FIOException) {
		unsigned vSize = sizeof(M);
		char array[vSize];
		core::writeLittleEndian(value, array);
		writeFully(array, vSize);
		return vSize;
	}

	template <typename M>
	unsigned writeBigEndian(M value) throw(FIOException) {
		unsigned vSize = sizeof(M);
		char array[vSize];
		core::writeBigEndian(value, array);
		writeFully(array, vSize);
		return vSize;
	}

private:
	FileWriter(const FileWriter& other);
	FileWriter& operator=(const FileWriter&);

};

} /* namespace core */

#endif /* CORE_FIO_FILEWRITER_H_ */
