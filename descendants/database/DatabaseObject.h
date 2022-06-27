#ifndef DESCENDANTS_DATABASEOBJECT_H
#define DESCENDANTS_DATABASEOBJECT_H

#include "descendants/Types.h"

namespace descendants::database
{
/**
 * This is the interface class for model objects that are stored in the database.
 * Objects of these types are stored as a single entity in the database.
 * This data is handled by a database mapper.
 */
class DatabaseObject
{
public:
    /**
     * This is the getter for the id this object is stored under in the database.
     * If the id is empty, it is most likely because the object is new and is not stored in the database yet.
     *
     * @return The database id of the object.
     */
    [[nodiscard]] const String& getDatabaseId() const;

    /**
     * This is the getter for the timestamp of when the object was first stored in the database.
     * If the time is not set, it is most likely because the object is new and is not stored in the database yet.
     *
     * @return The time when the object was first stored.
     */
    [[nodiscard]] const Optional<TimePoint>& getFirstInserted() const;

    /**
     * This is the getter for the timestamp of when the object was last updated in the database.
     * If the time is not set, it is most likely because the object is new and is not stored in the database yet.
     *
     * @return The time when the object was last stored.
     */
    [[nodiscard]] const Optional<TimePoint>& getLastUpdated() const;

private:
    /**
     * Forbid creation of instances of this type.
     */
    DatabaseObject() = default;

    // Internal properties injected in the object by the database mapper.
    String m_databaseId;
    Optional<TimePoint> m_firstInserted;
    Optional<TimePoint> m_lastUpdated;
};
}    // namespace descendants::database

#endif    // DESCENDANTS_DATABASEOBJECT_H
