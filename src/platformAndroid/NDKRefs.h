#ifndef NDK_NDKREFS_H
#define NDK_NDKREFS_H

#include <stdexcept>
#include <android/asset_manager_jni.h>

class NDKException : public std::logic_error {
public:
	NDKException(const std::string& message) : std::logic_error(message) {}
};

class AutoAssetReference {
	AAsset* reference;
public:
	AutoAssetReference(AAsset* asset) : reference(asset) {
	}
	~AutoAssetReference() {
		if (reference != nullptr) {
			AAsset_close(reference);
		}
	}
	AAsset* operator*() const {
		return reference;
	}

	AAsset* takeAway(){
		AAsset* temp = reference;
		reference = nullptr;
		return temp;
	}

private:
	AutoAssetReference(const AutoAssetReference& copy);
	AutoAssetReference& operator=(const AutoAssetReference& rvalue);
};

#endif //NDK_NDKREFS_H
