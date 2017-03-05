#ifndef CORE_IO_OSWRITER_H_
#define CORE_IO_OSWRITER_H_

#include "../utils/endian.h"
#include "../utils/leb128.h"
#include "OStream.h"

class OSWriter {

public:
	OSWriter(OStream& oStream);

	virtual ~OSWriter();
	virtual void open() throw(IOException);
	virtual void close() throw(IOException);
	virtual size_t write(const char* data, size_t size) throw(IOException);
	virtual void writeFully(const char* data, size_t size) throw(IOException);
	size_t writeUleb(uint32_t value) throw(IOException);
//	size_t writeSleb(int32_t value) throw(IOException);

	template <typename M>
	size_t writeLittleEndian(M value) throw(IOException) {
		size_t vSize = sizeof(M);
		char array[vSize];
		core::writeLittleEndian(value, array);
		writeFully(array, vSize);
		return vSize;
	}

	template <typename M>
	size_t writeBigEndian(M value) throw(IOException) {
		size_t vSize = sizeof(M);
		char array[vSize];
		core::writeBigEndian(value, array);
		writeFully(array, vSize);
		return vSize;
	}

protected:
	OStream& oStream;

private:
	OSWriter(const OSWriter& other);
	OSWriter& operator=(const OSWriter&);

};

#endif /* CORE_IO_OSWRITER_H_ */
