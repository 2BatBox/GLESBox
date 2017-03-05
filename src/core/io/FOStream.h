#ifndef CORE_IO_FOSTREAM_H_
#define CORE_IO_FOSTREAM_H_

#include "OStream.h"

#include <string>
#include <cstdio>

class FOStream : public OStream {

public:
	FOStream(const std::string& fileName);
	virtual ~FOStream();
	virtual void open() throw(IOException);
	virtual void close() throw(IOException);
	virtual size_t write(const char* data, size_t size) throw(IOException);

protected:
	std::string fileName;
	FILE* file;

private:
	FOStream(const FOStream& other);
	FOStream& operator=(const FOStream&);

};

#endif /* CORE_IO_FOSTREAM_H_ */
