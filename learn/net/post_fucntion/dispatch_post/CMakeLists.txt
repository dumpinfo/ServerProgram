AUX_SOURCE_DIRECTORY(. SOURCE)
ADD_EXECUTABLE(dispatch_post ${SOURCE})
TARGET_LINK_LIBRARIES(dispatch_post boost_system boost_date_time boost_thread pthread)
