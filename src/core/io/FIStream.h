#ifndef CORE_IO_FISTREAM_H_
#define CORE_IO_FISTREAM_H_

#include "IStream.h"

#include <string>
#include <cstdio>

class FIStream : public IStream {

public:
	FIStream(const std::string& fileName);
	virtual ~FIStream();
	virtual void open() throw(IOException);
	virtual void close() throw(IOException);
	virtual size_t read(char* data, size_t size) throw(IOException);
	size_t getSize();

protected:
	std::string fileName;
	FILE* file;
	size_t size;

private:
	FIStream(const FIStream& other);
	FIStream& operator=(const FIStream&);

};

#endif /* CORE_IO_FISTREAM_H_ */
