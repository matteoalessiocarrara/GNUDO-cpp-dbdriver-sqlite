/*
 * Copyright 2016 Matteo Alessio Carrara <sw.matteoac@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */

# include <ctime>
# include <string>
# include <cstdint>
# include <sstream>
# include <iostream>
# include <stdexcept>

# include <sqlite3pp.hpp>

# include "objects.hpp"
# include "dbdefs.hpp"


using namespace sqlite3pp::functions;
using namespace gnudo::sqlite;
using namespace dbdefs;
using std::int64_t;
using std::string;
using std::cout;
using std::endl;
using std::time;


// WARNING	Ogni metodo che modifica questo task deve chiamare setModificationTime()
// A parte setModificationTime ovviamente XD


Task::Task(const int64_t id, sqlite3* db, TasksManager *parentManager): sqlite3pp::objects::Row(db, tables::tasks, id), gnudo::abstract::Task((gnudo::abstract::TasksManager*)parentManager)
{
}


string
Task::getTitle() const
{
	return (const char*)getColumn<const unsigned char*>(columns::task::title, sqlite3pp_column_text);
}


string
Task::getDescription() const
{
	return (const char*)getColumn<const unsigned char*>(columns::task::description, sqlite3pp_column_text);
}


int
Task::getPriorityLevel() const
{
	return getColumn<int>(columns::task::priority, sqlite3pp_column_int);
}

		class Db;
time_t
Task::getCreationTime() const
{
	return getColumn<sqlite3_int64>(columns::task::creationTime, sqlite3pp_column_int64);
}


time_t
Task::getModificationTime() const
{
	return getColumn<sqlite3_int64>(columns::task::modificationTime, sqlite3pp_column_int64);
}


bool 
Task::isCompleted() const
{
	return getColumn<int>(columns::task::completed, sqlite3pp_column_int);
}


void
Task::setTitle(const string title)
{
	sqlite3_stmt *ppStmt = getUpdateStatement(columns::task::title);

	sqlite3pp_bind_text(ppStmt, 1, title.c_str(), title.size() + 1, SQLITE_STATIC);
	sqlite3pp_step(ppStmt);
	sqlite3_finalize(ppStmt);

	setModificationTime(time(NULL));
}


void
Task::setDescription(const string description)
{
	sqlite3_stmt *ppStmt = getUpdateStatement(columns::task::description);

	sqlite3pp_bind_text(ppStmt, 1, description.c_str(), description.size() + 1, SQLITE_STATIC);
	sqlite3pp_step(ppStmt);
	sqlite3_finalize(ppStmt);
	
	setModificationTime(time(NULL));
}


void
Task::setPriorityLevel(const int level)
{
	sqlite3_stmt *ppStmt = getUpdateStatement(columns::task::priority);

	sqlite3pp_bind_int(ppStmt, 1, level);
	sqlite3pp_step(ppStmt);
	sqlite3_finalize(ppStmt);
	
	setModificationTime(time(NULL));
}


void
Task::setStatus(const bool isCompleted)
{
	sqlite3_stmt *ppStmt = getUpdateStatement(columns::task::completed);

	sqlite3pp_bind_int(ppStmt, 1, isCompleted);
	sqlite3pp_step(ppStmt);
	sqlite3_finalize(ppStmt);
	
	setModificationTime(time(NULL));
}


void
Task::setCreationTime(const time_t time)
{
	sqlite3_stmt *ppStmt = getUpdateStatement(columns::task::creationTime);

	sqlite3pp_bind_int64(ppStmt, 1, time);
	sqlite3pp_step(ppStmt);
	sqlite3_finalize(ppStmt);
}


void
Task::setModificationTime(const time_t time)
{
	sqlite3_stmt *ppStmt = getUpdateStatement(columns::task::modificationTime);

	sqlite3pp_bind_int64(ppStmt, 1, time);
	sqlite3pp_step(ppStmt);
	sqlite3_finalize(ppStmt);
}


PriorityLevel::PriorityLevel(sqlite3* db, const int64_t id, PriorityLevelsManager *parentManager): sqlite3pp::objects::Row(db, tables::priorityLevels, id), gnudo::abstract::PriorityLevel((gnudo::abstract::PriorityLevelsManager*)parentManager)
{
}


string
PriorityLevel::getColor() const
{
	return (const char*)getColumn<const unsigned char*>(columns::prioritylevel::color, sqlite3pp_column_text);
}


int
PriorityLevel::getLevel() const
{
	return getColumn<int>(columns::prioritylevel::priority, sqlite3pp_column_int);
}


string
PriorityLevel::getName() const
{
	return (const char*)getColumn<const unsigned char*>(columns::prioritylevel::name, sqlite3pp_column_text);
}


void
PriorityLevel::setColor(const string color)
{
	sqlite3_stmt *ppStmt = getUpdateStatement(columns::prioritylevel::color);

	sqlite3pp_bind_text(ppStmt, 1, color.c_str(), color.size() + 1, SQLITE_STATIC);
	sqlite3pp_step(ppStmt);
	sqlite3_finalize(ppStmt);
}


void
PriorityLevel::setLevel(const int level)
{
	sqlite3_stmt *ppStmt = getUpdateStatement(columns::prioritylevel::priority);

	sqlite3pp_bind_int(ppStmt, 1, level);
	sqlite3pp_step(ppStmt);
	sqlite3_finalize(ppStmt);
}


void
PriorityLevel::setName(const string name)
{
	sqlite3_stmt *ppStmt = getUpdateStatement(columns::prioritylevel::name);

	sqlite3pp_bind_text(ppStmt, 1, name.c_str(), name.size() + 1, SQLITE_STATIC);
	sqlite3pp_step(ppStmt);
	sqlite3_finalize(ppStmt);
}

