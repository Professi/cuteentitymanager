TEMPLATE = subdirs

SUBDIRS = src

android {
} else {
    SUBDIRS += tests samples
}

CONFIG += ordered

tests.depends = src
samples.depends = tests
