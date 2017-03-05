#ifndef CORE_PROPERTYFILE_H_
#define CORE_PROPERTYFILE_H_

#include "memory.h"
#include "exception.h"
#include "utils/endian.h"

#include <string>
#include <map>

class PropertyFile {

	const std::string fileName;

	typedef uint8_t Bool_t;
	typedef int32_t Int_t;
	typedef int64_t Long_t;

	typedef std::map<std::string, std::string> MapType;
	typedef uint32_t RecordSize_t;
	MapType storage;

	const char* MAGIC;

public:

	PropertyFile(const std::string& fileName);

	virtual ~PropertyFile();

	void update() throw (IOException, EOFException);
	void commit() throw (IOException);

	void putBool(const std::string& key, Bool_t value);
	void putInt(const std::string& key, Int_t value);
	void putLong(const std::string& key, Long_t value);
	void putString(const std::string& key, const std::string& value);

	Bool_t getBool(const std::string& key, Bool_t defaultValue);
	Int_t getInt(const std::string& key, Int_t defaultValue);
	Long_t getLong(const std::string& key, Long_t defaultValue);
	const std::string& getString(const std::string& key, const std::string& defaultValue);

private:

	template <typename T>
	void putScalar(const std::string& key, T value) {
		char buffer[sizeof(value)];
		core::writeLittleEndian(value, buffer);
		storage[key] = std::string(buffer, sizeof(value));
	}

	template <typename T>
	T getScalar(const std::string& key, T defaultValue) {
		MapType::const_iterator it = storage.find(key);
		if(it != storage.end()){
			std::string value = it->second;
			if(value.size() >= sizeof(defaultValue)){
				T result;
				core::readLittleEndian(result, value.c_str());
				return result;
			}
		}
		return defaultValue;
	}

	PropertyFile(const PropertyFile& other);
	PropertyFile& operator=(const PropertyFile&);

};

#endif /* CORE_PROPERTYFILE_H_ */
