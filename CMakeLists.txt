# minimum cmake required
cmake_minimum_required(VERSION 3.20)
# project name, version, and description
project(HeroesVSVillainsBOT VERSION 1.1 DESCRIPTION "A Discord bot written in C++ using the DPP Discord Library" LANGUAGES CXX)
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)
# add DPP as a dependency


#create an executable
add_executable(${PROJECT_NAME} 
	src/main.cpp
	src/initialization.cpp
	src/management.cpp
	)

# linking libraries
target_link_libraries(${PROJECT_NAME}
	/usr/local/lib/libdpp.so.10.0.7
	/usr/local/lib/libdpp.so
	Threads::Threads
	)

# specify includes
target_include_directories(${PROJECT_NAME} PRIVATE
	include
	/usr/include
	/usr/local/include
	)

# set C++ version
set_target_properties(${PROJECT_NAME} PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
	)
		
