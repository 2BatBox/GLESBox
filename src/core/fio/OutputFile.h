#ifndef CORE_FIO_OUTPUTFILE_H_
#define CORE_FIO_OUTPUTFILE_H_

#include "exception.h"

namespace core {

class OutputFile {

public:

	OutputFile() = default;

	virtual ~OutputFile() = default;

	/**
	 * Close an opened File, freeing any related resources.
	 * All the next calls have no effect.
	 */
	virtual void close() noexcept = 0;

	/**
	 * Attempt to write 'size' bytes of data to the current offset.
	 * Returns the number of bytes write on success.
	 */
	virtual unsigned write(const char* buffer, unsigned size) throw (FIOException) = 0;

	/**
	 * Seek to the specified offset within the file.
	 * whence - uses the same constants as lseek()/fseek().
	 */
	virtual void seek(unsigned offset, int whence) throw (FIOException) = 0;

	/**
	 * Returns current offset in the file.
	 */
	virtual unsigned tell() throw (FIOException) = 0;


private:
	OutputFile(const OutputFile& other);
	OutputFile& operator=(const OutputFile&);

};

} /* namespace core */

#endif /* CORE_FIO_OUTPUTFILE_H_ */
