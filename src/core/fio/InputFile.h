#ifndef CORE_FIO_INPUTFILE_H_
#define CORE_FIO_INPUTFILE_H_

#include "exception.h"

namespace core {

class InputFile {

public:

	InputFile() = default;

	virtual ~InputFile() = default;

	/**
	 * Close an opened File, freeing any related resources.
	 * All the next calls have no effect.
	 */
	virtual void close() noexcept = 0;

	/**
	 * Attempt to read 'size' bytes of data from the current offset.
	 * Returns the number of bytes read on success.
	 */
	virtual unsigned read(char* buffer, unsigned size) throw (FIOException) = 0;

	/**
	 * Seek to the specified offset within the file.
	 * whence - uses the same constants as lseek()/fseek().
	 */
	virtual void seek(unsigned offset, int whence) throw (FIOException) = 0;

	/**
	 * Returns current offset in the file.
	 */
	virtual unsigned tell() throw (FIOException) = 0;

	/**
	 * Returns size of the input file.
	 */
	virtual unsigned getSize() noexcept = 0;

private:
	InputFile(const InputFile& other);
	InputFile& operator=(const InputFile&);

};

} /* namespace core */

#endif /* CORE_FIO_INPUTFILE_H_ */
