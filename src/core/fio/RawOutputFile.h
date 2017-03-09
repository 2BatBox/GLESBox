#ifndef CORE_FIO_RAWOUTPUTFILE_H_
#define CORE_FIO_RAWOUTPUTFILE_H_

#include <cstdio>

#include "OutputFile.h"

namespace core {

class RawOutputFile : public OutputFile {

	FILE* file;

	RawOutputFile(FILE* file);

public:
	virtual ~RawOutputFile();

	static OutputFile* open(const char* fileName) throw (NullPointerException, FIOException);

	virtual void close() noexcept override;

	virtual unsigned write(const char* buffer, unsigned size) throw (FIOException) override;

	virtual void seek(unsigned offset, int whence) throw (FIOException) override;

	virtual unsigned tell() throw (FIOException) override;

private:
	RawOutputFile(const RawOutputFile& other);
	RawOutputFile& operator=(const RawOutputFile&);

};

} /* namespace core */

#endif /* CORE_FIO_RAWOUTPUTFILE_H_ */
