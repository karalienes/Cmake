cmake_minimum_required(VERSION 3.16.3...3.19.0)
# minimum ve max cmake versionu yazılır.

project(CMAKE_TUTORIAL VERSION 1.0.0)
#proje ismi ve version numarası

message(STATUS "CMAKE_C_COMPILER: ${CMAKE_C_COMPILER}")
#proje cmake c compıler ekrana yazar.
message(STATUS "CMAKE_PROJECT_VERSION = ${CMAKE_PROJECT_VERSION}")
#proje versionu ekrana yazar

add_executable(${PROJECT_NAME} main.cpp)
#projeye çalışır bir blok ekleme işlemi yapar ilk olarak projenın ısmı ardından blok eklenecektır.

add_subdirectory(Adder)
#Adder dosyasındaki cmake cekmek icin yapılan tanımlamadır.

#target tag kullanılmasının sebebı hangı projeye hıtap etmesıdır bunu kullanmak zorunda degılız dıger turlude yapılabılır.
#target tagsız kullanınca proje ısmını ve ardınan gelen operatoru eklemeye gerek yoktur.(PUBLIC,PRIVATE,INTERFACE)

target_include_directories(${PROJECT_NAME} PUBLIC Adder)
#Bu şekilde tanımlama yaparsak #include<aader.h> şeklinde yazmamıza musade edecektir ama bu tanımlamayı yapmazsak
# #include<Adder/adder.h> şeklinde tanımlama yapmamız gerekmektedir.

target_link_directories(${PROJECT_NAME} PRIVATE Adder)
#Bunun olmasının sebebi bazı dosyaları import ederken bir bir include birde lib kısmının olmasıdır bunun ıcın buna gerek vardır.

target_link_libraries(${PROJECT_NAME} AdderLib)
#Adder içinde tanımlanmış olan lib çekme işlemi yapmaktadır bunun içinde add_subdirectory zaten Adder eklenmiştir.
#Adder içinde add_library tanımlanmıs olan AdderLib yazmak yeterli olacaktır.