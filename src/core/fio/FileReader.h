#ifndef CORE_FIO_FILEREADER_H_
#define CORE_FIO_FILEREADER_H_

#include "InputFile.h"
#include "../utils/endian.h"

namespace core {

class FileReader {

protected:
	InputFile* file;

public:
	FileReader(InputFile* file);

	virtual ~FileReader() = default;

	unsigned read(char* buffer, unsigned size) throw (FIOException);

	unsigned readFully(char* buffer, unsigned size) throw (FIOException, EOFException);

	template <typename M>
	unsigned readLittleEndian(M& value) throw(FIOException, EOFException) {
		unsigned vSize = sizeof(M);
		char array[vSize];
		readFully(array, vSize);
		return core::readLittleEndian(value, array);
	}

	template <typename M>
	unsigned readBigEndian(M& value) throw(FIOException, EOFException) {
		unsigned vSize = sizeof(M);
		char array[vSize];
		readFully(array, vSize);
		return core::readBigEndian(value, array);
	}


private:
	FileReader(const FileReader& other);
	FileReader& operator=(const FileReader&);

};

} /* namespace core */

#endif /* CORE_FIO_FILEREADER_H_ */
