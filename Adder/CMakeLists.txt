add_library(AdderLib 
adder.cpp
adder.h
)
#Yeni bir lib bu lib için gerekli olan cpp eklenmesidir.

install(TARGETS AdderLib DESTINATION lib)
install(FILES adder.h DESTINATION include)
#installarını oluşturuyoruz her library'nın bir adet lib bir adette include dosyaları bulunmak zorundadır.
