include(FetchContent)

set(QCUSTOMPLOT_VERSION "2.1.1")
set(QCUSTOMPLOT_URL "https://www.qcustomplot.com/release/${QCUSTOMPLOT_VERSION}/QCustomPlot.tar.gz")
FetchContent_Declare(
    QCustomPlot
    URL ${QCUSTOMPLOT_URL}
    # URL_HASH  ${QCUSTOMPLOT_HASH}
    DOWNLOAD_EXTRACT_TIMESTAMP ON
)

FetchContent_MakeAvailable(QCustomPlot)

# Check that files exist (good practice)
if(NOT EXISTS "${qcustomplot_SOURCE_DIR}/qcustomplot.h")
    message(FATAL_ERROR "qcustomplot.h not found after extraction. Check tarball structure.")
endif()

if(NOT EXISTS "${qcustomplot_SOURCE_DIR}/qcustomplot.cpp")
    message(FATAL_ERROR "qcustomplot.cpp not found in ${qcustomplot_SOURCE_DIR}")
endif()

add_library(qcustomplot STATIC
    "${qcustomplot_SOURCE_DIR}/qcustomplot.cpp"
    "${qcustomplot_SOURCE_DIR}/qcustomplot.h"
)

add_library(QCustomPlot::QCustomPlot ALIAS qcustomplot)

# Expose the headers to consumers
target_include_directories(qcustomplot PUBLIC
    $<BUILD_INTERFACE:${qcustomplot_SOURCE_DIR}>
)

# Qt dependencies (Qt5 or Qt6 — matches whatever the parent project uses)
target_link_libraries(qcustomplot PUBLIC
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::PrintSupport
)
