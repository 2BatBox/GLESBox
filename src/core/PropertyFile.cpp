#include "PropertyFile.h"

#include "io/FIStream.h"
#include "io/ISReader.h"
#include "io/FOStream.h"
#include "io/OSWriter.h"

#include <cstring>
#include <vector>

using namespace std;
using namespace core;

PropertyFile::PropertyFile(const string& fileName) :
		fileName(fileName), MAGIC("CPF.") {
	try {
		update();
	} catch (const IOException& e) {
		// file hasn't created yet or has bad format
	} catch (const EOFException& e) {
		// file hasn't created yet or has bad format
	}
}

PropertyFile::~PropertyFile() {
}

void PropertyFile::update() throw (IOException, EOFException) {
	FIStream stream(fileName);
	ISReader reader(stream);
	reader.open();

	char buffer[strlen(MAGIC)];
	reader.readFully(buffer, strlen(MAGIC));
	if (memcmp(buffer, MAGIC, strlen(MAGIC))) {
		throw IOException("Bad magic numbers");
	}
	RecordSize_t records;
	reader.readLittleEndian(records);

	RecordSize_t size;
	vector<char> key;
	vector<char> value;
	while (records--) {
		// read key
		reader.readLittleEndian(size);
		key.resize(size);
		reader.readFully(&key[0], size);

		// read value
		reader.readLittleEndian(size);
		value.resize(size);
		reader.readFully(&value[0], size);

		string strKey(key.begin(), key.end());
		string strValue(value.begin(), value.end());
		storage[strKey] = strValue;
	}
}

void PropertyFile::commit() throw (IOException) {
	FOStream stream(fileName);
	OSWriter writer(stream);
	writer.open();

	writer.writeFully(MAGIC, strlen(MAGIC)); // magic. Core Property File.
	writer.writeLittleEndian((RecordSize_t) (storage.size()));
	MapType::const_iterator cit = storage.begin();
	while (cit != storage.end()) {
		string key = cit->first;
		string value = cit->second;
		writer.writeLittleEndian((RecordSize_t) key.size());
		writer.writeFully(key.c_str(), key.size());
		writer.writeLittleEndian((RecordSize_t) value.size());
		writer.writeFully(value.c_str(), value.size());
		++cit;
	}
}

void PropertyFile::putBool(const string& key, Bool_t value) {
	putScalar(key, value);
}

void PropertyFile::putInt(const string& key, Int_t value) {
	putScalar(key, value);
}

void PropertyFile::putLong(const string& key, Long_t value) {
	putScalar(key, value);
}

PropertyFile::Bool_t PropertyFile::getBool(const string& key, Bool_t defaultValue) {
	return getScalar(key, defaultValue);
}

PropertyFile::Int_t PropertyFile::getInt(const string& key, Int_t defaultValue) {
	return getScalar(key, defaultValue);
}

PropertyFile::Long_t PropertyFile::getLong(const string& key, Long_t defaultValue) {
	return getScalar(key, defaultValue);
}

void PropertyFile::putString(const string& key, const string& value) {
	storage[key] = value;
}

const string& PropertyFile::getString(const string& key, const string& defaultValue) {
	MapType::const_iterator it = storage.find(key);
	if (it != storage.end()) {
		return it->second;
	}
	return defaultValue;
}
