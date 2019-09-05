AUX_SOURCE_DIRECTORY(. SOURCE)
ADD_EXECUTABLE(main ${SOURCE})
TARGET_LINK_LIBRARIES(main boost_system boost_date_time boost_thread pthread)
