
find_package(OpenSSL REQUIRED)


add_library(${LIBRARY_NAME} STATIC 
            hash_calculator.cpp
            hash_calculator.h
            logic.cpp
            logic.h
            )

target_link_libraries(${LIBRARY_NAME} PRIVATE OpenSSL::Crypto)