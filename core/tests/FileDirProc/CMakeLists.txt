#Tests for FileDirProc Classes

add_executable(FileFilter_T FileFilter_T.cpp)
target_link_libraries(FileFilter_T gnsstk)
add_test(NAME FileDirProc_FileFilter COMMAND $<TARGET_FILE:FileFilter_T>)

add_executable(FileSpecFind_T FileSpecFind_T.cpp)
if( ${CMAKE_SYSTEM_NAME} MATCHES "Windows" )
  target_link_libraries(FileSpecFind_T gnsstk shlwapi)
else()
  target_link_libraries(FileSpecFind_T gnsstk)
endif()
add_test(NAME FileDirProc_FileSpecFind
  COMMAND FileSpecFind_T
  WORKING_DIRECTORY ${GNSSTK_TEST_DATA_DIR})

add_executable(FileSpec_T FileSpec_T.cpp)
target_link_libraries(FileSpec_T gnsstk)
add_test(NAME FileDirProc_FileSpec COMMAND $<TARGET_FILE:FileSpec_T>)

add_executable(FileStore_T FileStore_T.cpp)
target_link_libraries(FileStore_T gnsstk)
add_test(NAME FileDirProc_FileStore COMMAND $<TARGET_FILE:FileStore_T>)

add_executable(FileUtils_T FileUtils_T.cpp)
target_link_libraries(FileUtils_T gnsstk)
add_test(NAME FileDirProc_FileUtils COMMAND $<TARGET_FILE:FileUtils_T>)

#add_executable(RTFileFrame_T RTFileFrame_T.cpp)
#target_link_libraries(RTFileFrame_T gnsstk)
#add_test(NAME FileDirProc_RTFileFrame COMMAND $<TARGET_FILE:RTFileFrame_T>)
