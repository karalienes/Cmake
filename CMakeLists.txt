cmake_minimum_required(VERSION 3.16.3...3.19.0)
# minimum ve max cmake versionu yazılır.

project(CMAKE_TUTORIAL VERSION 1.2.2)
#proje ismi ve version numarası

configure_file(CMAKE_TUTORIAL_Config.h.in CMAKE_TUTORIAL_Config.h)
#Burda bir confugire oluşturuyoruz. buradaki amac proje ismi ile aynı isimde olması gerekmektedir.

#### DOWNLOAD ALL THE SUBMODULES

find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJEECT_SOURCE_DIR}/.git")
#Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT SUBMOD RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()



message(STATUS "CMAKE_C_COMPILER: ${CMAKE_C_COMPILER}")
#proje cmake c compıler ekrana yazar.
message(STATUS "CMAKE_PROJECT_VERSION = ${CMAKE_PROJECT_VERSION}")
#proje versionu ekrana yazar

add_executable(${PROJECT_NAME} main.cpp)
#projeye çalışır bir blok ekleme işlemi yapar ilk olarak projenın ısmı ardından blok eklenecektır.

add_subdirectory(Adder)
add_subdirectory(external/glfw)
#Adder dosyasındaki cmake cekmek icin yapılan tanımlamadır.
#Burda amaç yolu verilen libi çekme işlemidir.

#target tag kullanılmasının sebebı hangı projeye hıtap etmesıdır bunu kullanmak zorunda degılız dıger turlude yapılabılır.
#target tagsız kullanınca proje ısmını ve ardınan gelen operatoru eklemeye gerek yoktur.(PUBLIC,PRIVATE,INTERFACE)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_BINARY_DIR})
#Version source code için gerekli target_include_directories işlemidir.


target_include_directories(${PROJECT_NAME} 
    PUBLIC Adder 
    PUBLIC external/glfw/include/GLFW
    )
#Bu şekilde tanımlama yaparsak #include<aader.h> şeklinde yazmamıza musade edecektir ama bu tanımlamayı yapmazsak
# #include<Adder/adder.h> şeklinde tanımlama yapmamız gerekmektedir.

target_link_directories(${PROJECT_NAME} 
    PRIVATE Adder
    PRIVATE external/glfw/src
    )
#Bunun olmasının sebebi bazı dosyaları import ederken bir bir include birde lib kısmının olmasıdır bunun ıcın buna gerek vardır.
#Bunlar tamamen source kodda olacaktır.


target_link_libraries(${PROJECT_NAME} AdderLib glfw)
#Adder içinde tanımlanmış olan lib çekme işlemi yapmaktadır bunun içinde add_subdirectory zaten Adder eklenmiştir.
#Adder içinde add_library tanımlanmıs olan AdderLib yazmak yeterli olacaktır.
#add_library() içinde yazanlar yazılmalıdır burda yoksa hata verecektır :)