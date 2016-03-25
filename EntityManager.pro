TEMPLATE = subdirs

SUBDIRS = src

android {
} else {
    SUBDIRS += tests samples
}

CONFIG += ordered
CONFIG += c++14

tests.depends = src
samples.depends = tests
