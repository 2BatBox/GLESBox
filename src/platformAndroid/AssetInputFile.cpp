#include "AssetInputFile.h"

using namespace core;

AssetInputFile::AssetInputFile(AAsset* file, unsigned size) :
		file(file), fileSize(size) {
}

AssetInputFile::~AssetInputFile() {
	close();
}

InputFile* AssetInputFile::open(AAssetManager* manager, const char* fileName) throw (NDKException) {
	if (fileName == nullptr) {
		throw NullPointerException();
	}
	AutoAssetReference asset(AAssetManager_open(manager, fileName, AASSET_MODE_STREAMING));
	if(*asset == NULL){
		throw NDKException("Can't open AAsset file");
	}
	unsigned size = AAsset_getLength(*asset);
	return new AssetInputFile(asset.takeAway(), size);
}

void AssetInputFile::close() noexcept {
	if(file != nullptr) {
		AAsset_close(file);
		file = nullptr;
	}
}

unsigned AssetInputFile::read(char* buffer, unsigned size) throw (FIOException) {
	int result = AAsset_read(file, buffer, size);
	if (result < 0) {
			throw FIOException("Can't read AAsset file");
	}
	return result;
}

void AssetInputFile::seek(unsigned offset, int whence) throw (FIOException) {
	if (AAsset_seek(file, offset, whence) < 0) {
		throw FIOException("Can't set the position in AAsset file");
	}
}

unsigned AssetInputFile::tell() throw (FIOException) {
	int remaining = AAsset_getRemainingLength(file);
	if (remaining < 0 || remaining > fileSize) {
		throw FIOException("Can't get current position in AAsset file");
	}
	return fileSize - remaining;
}
