AUX_SOURCE_DIRECTORY(. SOURCE)
ADD_EXECUTABLE(strand ${SOURCE})
TARGET_LINK_LIBRARIES(strand boost_system boost_date_time boost_thread pthread)
