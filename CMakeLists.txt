cmake_minimum_required(VERSION 3.5)

project(ChatServer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(PostgreSQL_LIBRARY_DIR /opt/homebrew/Cellar/postgresql@16/16.4/lib)

find_package(PostgreSQL REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(PQXX REQUIRED IMPORTED_TARGET libpqxx)

include_directories (${PostgreSQL_INCLUDE_DIRS})
link_directories(${PostgreSQL_LIBRARY_DIRS})


# target_link_libraries(${PROJECT_NAME}
# PRIVATE libpqxx::pqxx
# PRIVATE PostgreSQL::PostgreSQL)

# PRIVATE (libpqxx::pqxx)
# PRIVATE (PostgreSQL::PostgreSQL)
add_executable(ChatServer main.cpp
    serverconnect.h serverconnect.cpp)
include(GNUInstallDirs)
target_link_libraries(ChatServer

# PRIVATE libpqxx::pqxx
PRIVATE PostgreSQL::PostgreSQL)


install(TARGETS ChatServer
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
