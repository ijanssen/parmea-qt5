# Add files and directories to ship with the application
# by adapting the examples below.
# file1.source = myfile
# dir1.source = mydir
images.source = images_854x480
#images.source = images_640x360
#images.path = images
sounds.source = sounds
lang.source = lang
DEPLOYMENTFOLDERS = images sounds lang

symbian:TARGET.UID3 = 0xE5D5B060

# Smart Installer package's UID
# This UID is from the protected range
# and therefore the package will fail to install if self-signed
# By default qmake uses the unprotected range value if unprotected UID is defined for the application
# and 0x2002CCCF value if protected UID is given to the application
#symbian:DEPLOYMENT.installer_header = 0x2002CCCF

# Allow network access on Symbian
symbian:TARGET.CAPABILITY += NetworkServices
symbian{
    INCLUDEPATH += MW_LAYER_SYSTEMINCLUDE
    LIBS += -L\\epoc32\\release\\armv5\\lib -lremconcoreapi -lremconinterfacebase -lavkon -lcone
    #ICON = $${TARGET}.svg
}


# If your application uses the Qt Mobility libraries, uncomment
# the following lines and add the respective components to the
# MOBILITY variable.
QT = core widgets gui svg multimedia x11extras
CONFIG += mobility
MOBILITY = multimedia

SOURCES += main.cpp \
    panel.cpp \
    mainpanel.cpp \
    infopanel.cpp \
    hiscores.cpp \
    help.cpp \
    yesno.cpp \
    view.cpp \
    scene.cpp \
    resources.cpp \
    gameover.cpp \
    button.cpp \
    boom.cpp \
    ball.cpp \
    anim.cpp \
    sound.cpp \
    splashscreen.cpp \
    bubble.cpp
HEADERS += \
    panel.h \
    mainpanel.h \
    infopanel.h \
    hiscores.h \
    help.h \
    globals.h \
    yesno.h \
    view.h \
    scene.h \
    resources.h \
    platform.h \
    gameover.h \
    button.h \
    build.h \
    boom.h \
    ball.h \
    anim.h \
    sound.h \
    splashscreen.h \
    bubble.h
FORMS +=
