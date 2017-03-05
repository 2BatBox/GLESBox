#ifndef CORE_IO_OSTREAM_H_
#define CORE_IO_OSTREAM_H_

#include "../exception.h"

class OStream {
public:
	virtual ~OStream(){}
	virtual void open() throw(IOException) = 0;
	virtual void close() throw(IOException) = 0;
	virtual size_t write(const char* data, size_t size) throw(IOException) = 0;
};

#endif /* CORE_IO_OSTREAM_H_ */
