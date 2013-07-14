#!/bin/sh

ASGP_VERSION_FILE=./asgp/lib/src/rp/version.hpp
ASGP_VERSION_MAJOR=$(grep '#define RP_MAJOR_VERSION' "$ASGP_VERSION_FILE" \
    | cut -d' ' -f3)
ASGP_VERSION_MINOR=$(grep '#define RP_MINOR_VERSION' "$ASGP_VERSION_FILE" \
    | cut -d' ' -f3)
ASGP_VERSION_PATCH=$(grep '#define RP_PATCH_NUMBER' "$ASGP_VERSION_FILE" \
    | cut -d' ' -f3)

ASGP_VERSION=$ASGP_VERSION_MAJOR.$ASGP_VERSION_MINOR.$ASGP_VERSION_PATCH
