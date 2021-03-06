#pragma once
class CameraWrapper
{
public:
	static CameraWrapper& getInstance()
	{
		static CameraWrapper    instance; // Guaranteed to be destroyed.
							  // Instantiated on first use.
		return instance;
	}
private:
	CameraWrapper() {}                    // Constructor? (the {} brackets) are needed here.

	// C++ 03
	// ========
	// Dont forget to declare these two. You want to make sure they
	// are unacceptable otherwise you may accidentally get copies of
	// your singleton appearing.
	//CameraWrapper(CameraWrapper const&);            // Don't Implement
	//void operator=(CameraWrapper const&);			// Don't implement

	// C++ 11
	// =======
	// We can use the better technique of deleting the methods
	// we don't want.
public:
	CameraWrapper(CameraWrapper const&) = delete;
	void operator=(CameraWrapper const&) = delete;

	// Note: Scott Meyers mentions in his Effective Modern
	//       C++ book, that deleted functions should generally
	//       be public as it results in better error messages
	//       due to the compilers behavior to check accessibility
	//       before deleted status
};

