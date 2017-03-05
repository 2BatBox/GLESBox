#ifndef CORE_IO_ISTREAM_H_
#define CORE_IO_ISTREAM_H_

#include "../exception.h"

class IStream {
public:
	virtual ~IStream(){}
	virtual void open() throw(IOException) = 0;
	virtual void close() throw(IOException) = 0;
	virtual size_t read(char* data, size_t size) throw(IOException) = 0;
};

#endif /* CORE_IO_ISTREAM_H_ */
