# Include the CPack
include(InstallRequiredSystemLibraries)

# Set all the variable
set(CPACK_GENERATOR "ZIP")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Lilith common elements")
set(CPACK_PACKAGE_VENDOR "astrihale")
set(CPACK_PACKAGE_VERSION_MAJOR ${LILITH_MAJOR_VERSION})
set(CPACK_PACKAGE_VERSION_MINOR ${LILITH_MINOR_VERSION})
set(CPACK_PACKAGE_VERSION_PATCH ${LILITH_PATCH_VERSION})

# And include CPack
include(CPack)
