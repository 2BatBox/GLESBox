#ifndef CORE_FIO_RAWINPUTFILE_H_
#define CORE_FIO_RAWINPUTFILE_H_

#include <cstdio>

#include "InputFile.h"

namespace core {

class RawInputFile: public InputFile {

	FILE* file;
	unsigned fileSize;

	RawInputFile(FILE* file, unsigned size);

public:
	virtual ~RawInputFile();

	static InputFile* open(const char* fileName) throw (NullPointerException, FIOException);

	virtual void close() noexcept override;

	virtual unsigned read(char* buffer, unsigned size) throw (FIOException) override;

	virtual void seek(unsigned offset, int whence) throw (FIOException) override;

	virtual unsigned tell() throw (FIOException) override;

	virtual inline unsigned getSize() noexcept override {
		return fileSize;
	}

private:
	RawInputFile(const RawInputFile& other);
	RawInputFile& operator=(const RawInputFile&);

};

} /* namespace core */

#endif /* CORE_FIO_RAWINPUTFILE_H_ */
