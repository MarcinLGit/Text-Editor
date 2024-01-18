
find_package(OpenSSL REQUIRED)


add_library(${LIBRARY_NAME} SHARED
	    lcs.h
            lcs.cpp
            leven.h
            leven.cpp
            logic4.h
            logic4.cpp
            )

target_link_libraries(${LIBRARY_NAME} PRIVATE OpenSSL::Crypto)

