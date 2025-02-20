cmake_minimum_required(VERSION 3.16)
project(xml_taha)

set(CMAKE_C_STANDARD 11)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})

add_definitions(${GTK3_CFLAGS_OTHER})

add_executable(xml_taha main.c
        coordonnees.h
        global.h
        dimension.h
        colors.h
        image.h
        icone.h
        window.h
        entry.h
        textview.h
        label.h
        comboBox.h
        menu.h
        btn.macros.h
        button.h
        btn_img.h
        includes_button.h
        fixed.h
        progressBar.h
        dialogue.h
        fileChooser.h
        calendrier.h
        bouton_xml.h
        xml_utility.h
        checkbox_xml.h
        dialog_xml.h
        radio_xml.h
        test.c
        taha_template.h
        box.h
)

target_link_libraries(xml_taha ${GTK3_LIBRARIES})