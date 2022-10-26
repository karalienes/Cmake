cmake_minimum_required(VERSION 3.16.3...3.19.0)
# minimum ve max cmake versionu yazılır.

project(CMAKE_TUTORIAL VERSION 1.2.2)
#proje ismi ve version numarası


option(USE_ADDER "A simple library for adding 2 floats" ON)
#Burada eklediğim yeni option ile USE_ADDER on of durumuna göre lib açıp kapatma işlemi yapabiliriz.
if(USE_ADDER)   
    add_subdirectory(Adder)
    
    list(APPEND EXTRA_LIB_DIRS Adder)
    list(APPEND EXTRA_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/Adder")
    list(APPEND EXTRA_LINKS AdderLib)
    #Burada opsiyon olarak eklenen Adder list içerisinde tutuyoruz ardından gerekli durumda ekleme işlemi yapıyoruz.
endif()

configure_file(CMAKE_TUTORIAL_Config.h.in CMAKE_TUTORIAL_Config.h)
#Burda bir confugire oluşturuyoruz. buradaki amac proje ismi ile aynı isimde olması gerekmektedir.


add_executable(${PROJECT_NAME} main.cpp)
#projeye çalışır bir blok ekleme işlemi yapar ilk olarak projenın ısmı ardından blok eklenecektır.

find_library(myglewlib glew NAMES glew2 GLEW GLEW2 DOC "glew library")
#Burada ilk değişken verdiğimiz isimdir ikinci gerçek adıdır.
#NAMES olarak adlandırılan 3 adet örnek isimlerdir. Yani onlar olmazsa onda bulabilecektir.
#Doc ile belgelendirme işlemi yapılabilir.

if(${myglewlib} STREQUAL myglewlib-NOTFOUND)
    message(FATAL_ERROR "no glew, sad day")
else()
    message(STATUS "glew found! as ${myglewlib}")
endif()
# Buradan libin olup olmadığını bile getirebiliriz. Yani kontrol edebiliriz.




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


add_subdirectory(external/glfw)
#Adder dosyasındaki cmake cekmek icin yapılan tanımlamadır.
#Burda amaç yolu verilen libi çekme işlemidir.

#target tag kullanılmasının sebebı hangı projeye hıtap etmesıdır bunu kullanmak zorunda degılız dıger turlude yapılabılır.
#target tagsız kullanınca proje ısmını ve ardınan gelen operatoru eklemeye gerek yoktur.(PUBLIC,PRIVATE,INTERFACE)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_BINARY_DIR})
#Version source code için gerekli target_include_directories işlemidir.


target_include_directories(${PROJECT_NAME} 
    #PUBLIC Adder 
    PUBLIC external/glfw/include/GLFW
    ${EXTRA_INCLUDE_DIRS}
    )
#Bu şekilde tanımlama yaparsak #include<aader.h> şeklinde yazmamıza musade edecektir ama bu tanımlamayı yapmazsak
# #include<Adder/adder.h> şeklinde tanımlama yapmamız gerekmektedir.

target_link_directories(${PROJECT_NAME} 
    #PRIVATE Adder
    PRIVATE external/glfw/src
    ${EXTRA_LIB_DIRS}
    )
#Bunun olmasının sebebi bazı dosyaları import ederken bir bir include birde lib kısmının olmasıdır bunun ıcın buna gerek vardır.
#Bunlar tamamen source kodda olacaktır.


target_link_libraries(${PROJECT_NAME} ${EXTRA_LINKS} glfw ${myglewlib})
#Adder içinde tanımlanmış olan lib çekme işlemi yapmaktadır bunun içinde add_subdirectory zaten Adder eklenmiştir.
#Adder içinde add_library tanımlanmıs olan AdderLib yazmak yeterli olacaktır.
#add_library() içinde yazanlar yazılmalıdır burda yoksa hata verecektır :)


install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/CMAKE_TUTORIAL_Config.h" DESTINATION include)
#installarını oluşturuyoruz her library'nın bir adet lib bir adette include dosyaları bulunmak zorundadır.


include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set(CPACK_PACKAGE_VERSION_MAJOR "${Tutorial_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${Tutorial_VERSION_MINOR}")
include(CPack)

# Bu eklediğimiz satırlar ile projenin mac ve windowsta kurulmasına sebeb olacaktır. 



