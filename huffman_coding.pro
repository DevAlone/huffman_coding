TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    huffman_coding.cpp \
    BitVector.cpp

HEADERS += \
    huffman_coding.h \
    BitVector.h
