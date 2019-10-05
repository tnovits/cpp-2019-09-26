cmake_minimum_required(VERSION 3.12)
project(cpp_2019_09_26 VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

set(CMAKE_CXX_STANDARD 17)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

configure_file(version.h.in ${PROJECT_SOURCE_DIR}/version.h)

add_executable(helloworld_cli)
target_sources(helloworld_cli PRIVATE
        main.cpp
        )

add_library(helloworld lib.h lib.cpp)
target_sources(helloworld PRIVATE
        lib.cpp
        )

add_executable(test_version)
target_sources(test_version PRIVATE
        test_version.cpp
        )

set_target_properties(helloworld_cli helloworld test_version PROPERTIES
        CXX_STANDARD_REQUIRED ON
        COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
        )

set_target_properties(test_version PROPERTIES
        COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
        INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
        )

target_link_libraries(helloworld_cli
        helloworld
        )

message("BOOST:" ${Boost_LIBRARIES})

target_link_libraries(test_version
        ${Boost_LIBRARIES}
        helloworld
        )

install(TARGETS helloworld_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT tnovits@yandex.ru)

set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)

include(CPack)

enable_testing()

add_test(helloworld_tests test_version)