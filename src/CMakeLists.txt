cmake_minimum_required(VERSION 3.13)

target_sources(pico-hid
	PRIVATE
	${CMAKE_CURRENT_LIST_DIR}/pico-hid.cpp
	)
#add_subdirectory(...)
