#ifndef NDK_ASSETINPUTFILE_H
#define NDK_ASSETINPUTFILE_H

#include <cstdio>

#include <android/asset_manager_jni.h>

#include "../core/fio/InputFile.h"
#include "NDKRefs.h"

class AssetInputFile : public core::InputFile {

	AAsset* file;
	unsigned fileSize;

	AssetInputFile(AAsset* file, unsigned size);

public:
	virtual ~AssetInputFile();

	static core::InputFile* open(AAssetManager* manager, const char* fileName) throw(NDKException);

	virtual void close() noexcept override;

	virtual unsigned read(char* buffer, unsigned size) throw(core::FIOException) override;

	virtual void seek(unsigned offset, int whence) throw(core::FIOException) override;

	virtual unsigned tell() throw(core::FIOException) override;

	virtual inline unsigned getSize() noexcept override {
		return fileSize;
	}

private:
	AssetInputFile(const AssetInputFile& other);

	AssetInputFile& operator=(const AssetInputFile&);
};


#endif //NDK_ASSETINPUTFILE_H
