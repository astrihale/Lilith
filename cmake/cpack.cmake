# Include the CPack
include(InstallRequiredSystemLibraries)

# Set all the variable
set(CPACK_GENERATOR "ZIP")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Descendants common elements")
set(CPACK_PACKAGE_VENDOR "astrihale")
set(CPACK_PACKAGE_VERSION_MAJOR ${DESCENDANTS_MAJOR_VERSION})
set(CPACK_PACKAGE_VERSION_MINOR ${DESCENDANTS_MINOR_VERSION})
set(CPACK_PACKAGE_VERSION_PATCH ${DESCENDANTS_PATCH_VERSION})

# And include CPack
include(CPack)
