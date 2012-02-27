
win32:!win32-g++ {
    unixstyle = false
} else:win32-g++:isEmpty(QMAKE_SH) {
    unixstyle = false
} else {
    unixstyle = true
}

QDOC = $$QT.core.bins/qdoc3

ONLINE_CONF = $$PWD/qtsensors.qdocconf
DITA_CONF = $$PWD/qtsensors-dita.qdocconf
QCH_CONF = #nothing yet

$$unixstyle {
} else {
    QDOC = $$replace(QDOC, "qdoc", "qdoc3.exe")
    ONLINE_CONF = $$replace(ONLINE_CONF, "/", "\\")
    DITA_DOCS = $$replace(ONLINE_CONF, "/", "\\")
}

# Build rules
docs.depends = dita_docs online_docs qch_docs

online_docs.commands = $$QDOC $$ONLINE_CONF

dita_docs.commands = $$QDOC $$DITA_CONF

qch_docs.commands = #no commands yet

QMAKE_EXTRA_TARGETS += docs dita_docs online_docs qch_docs
QMAKE_CLEAN += \
               "-r $$PWD/../html" \
               "-r $$PWD/../ditaxml"


OTHER_FILES += \
    doc/src/porting.qdoc \
    doc/src/qmlsensorgestures.qdoc \
    doc/src/qtsensorgestures-cpp.qdoc \
    doc/src/qtsensorgestures-emulator \
    doc/src/qtsensorgestures-plugins \
    doc/src/qtsensors-backend.qdoc \
    doc/src/qtsensors-cpp.qdoc \
    doc/src/imports/qtmobilitysensors1.qdoc \
    doc/src/imports/qtsensors5.qdoc \
    doc/src/qtsensors.qdoc
