#include "descendants/database/DatabaseObject.h"

namespace descendants::database
{
const String& DatabaseObject::getDatabaseId() const
{
    return m_databaseId;
}

const Optional<TimePoint>& DatabaseObject::getFirstInserted() const
{
    return m_firstInserted;
}

const Optional<TimePoint>& DatabaseObject::getLastUpdated() const
{
    return m_lastUpdated;
}
}    // namespace descendants::database
