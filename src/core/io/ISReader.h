#ifndef CORE_IO_ISREADER_H_
#define CORE_IO_ISREADER_H_

#include "../utils/endian.h"
#include "../utils/leb128.h"
#include "IStream.h"

class ISReader {

public:
	ISReader(IStream& iStream);

	virtual ~ISReader();
	virtual void open() throw(IOException);
	virtual void close() throw(IOException);
	virtual size_t read(char* data, size_t size) throw(IOException);
	virtual void readFully(char* data, size_t size) throw(IOException, EOFException);
	size_t readUleb(uint32_t& value) throw(IOException, EOFException, LEBFormatException);
//	size_t readSleb(int32_t& value) throw(IOException, EOFException, LEBFormatException);

	template <typename M>
	size_t readLittleEndian(M& value) throw(IOException, EOFException) {
		size_t vSize = sizeof(M);
		char array[vSize];
		readFully(array, vSize);
		return core::readLittleEndian(value, array);
	}

	template <typename M>
	size_t readBigEndian(M& value) throw(IOException, EOFException) {
		size_t vSize = sizeof(M);
		char array[vSize];
		readFully(array, vSize);
		return core::readBigEndian(value, array);
	}

protected:
	IStream& iStream;

private:
	ISReader(const ISReader& other);
	ISReader& operator=(const ISReader&);

};

#endif /* CORE_IO_ISREADER_H_ */
