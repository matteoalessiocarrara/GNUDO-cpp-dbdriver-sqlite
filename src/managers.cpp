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
# include <iostream>
# include <stdexcept>

# include <sqlite3.h>
# include <sqlite3pp.hpp>

# include "dbdefs.hpp"
# include "managers.hpp"
#include "gnudo.hpp"


using namespace gnudo::abstract::exceptions;
using namespace gnudo::sqlite::exceptions;
using namespace gnudo::sqlite::managers;
using namespace sqlite3pp::functions;
using namespace gnudo::sqlite::dbdefs;
using namespace gnudo::sqlite;

using std::to_string;
using std::int64_t;
using std::string;
using std::vector;
using std::time;


TasksManager::TasksManager(sqlite3 *db, Db *gnudoDb): sqlite3pp::objects::Table(db, tables::tasks), gnudo::abstract::managers::TasksManager(gnudoDb)
{
}


int64_t
TasksManager::_add(const int64_t priority, const string title, const string description, const time_t creationTime, const time_t modificationTime, const bool completed)
{
	const string	sql	=	"INSERT INTO " + tables::tasks + " "
							"("
							+ columns::task::title + ", "
							+ columns::task::description + ", "
							+ columns::task::creationTime + ", "
							+ columns::task::modificationTime + ", "
							+ columns::task::priority + ", "
							+ columns::task::completed +
							")"
							"VALUES (?, ?, ?, ?, ?, ?);";
	sqlite3_stmt	*ppStmt;

	// Se non esiste solleverà un eccezione
	gnudo::abstract::managers::Manager<gnudo::abstract::objects::Task>::getParentDb()->getPriorityLevels()->getPriorityLevel(priority);

	
	sqlite3pp_prepare_v2(sqlite3pp::objects::Table::getParentDb(), sql.c_str(), sql.size() + 1, &ppStmt, NULL);

	sqlite3pp_bind_text(ppStmt, 1, title.c_str(), title.size() + 1, SQLITE_STATIC);
	sqlite3pp_bind_text(ppStmt, 2, description.c_str(), description.size() + 1, SQLITE_STATIC);
	sqlite3pp_bind_int(ppStmt, 3, creationTime);
	sqlite3pp_bind_int(ppStmt, 4, modificationTime);
	sqlite3pp_bind_int(ppStmt, 5, priority);
	sqlite3pp_bind_int(ppStmt, 6, completed);

	sqlite3pp_step(ppStmt);
	sqlite3_finalize(ppStmt);


	sqlite3_int64 taskId = sqlite3_last_insert_rowid(sqlite3pp::objects::Table::getParentDb());
	
	if (taskId == 0)
		throw std::runtime_error("Id dell'ultimo task inserito non trovato");


	return taskId;
}


vector<int64_t>
TasksManager::getIdList(int orderBy, bool ascending) const
{
	vector<sqlite3_int64> tmp;

	switch(orderBy)
	{
		case TITLE:
			tmp = sqlite3pp::objects::Table::getIdList(columns::task::title, ascending);
			break;
		case DESCRIPTION:
			tmp = sqlite3pp::objects::Table::getIdList(columns::task::description, ascending);
			break;
		case CREATION_TIME:
			tmp = sqlite3pp::objects::Table::getIdList(columns::task::creationTime, ascending);
			break;
		case MODIFICATION_TIME:
			tmp = sqlite3pp::objects::Table::getIdList(columns::task::modificationTime, ascending);
			break;
		case PRIORITY:
			tmp = sqlite3pp::objects::Table::getIdList(columns::task::priority, ascending);
			break;
		case COMPLETED:
			tmp = sqlite3pp::objects::Table::getIdList(columns::task::completed, ascending);
			break;
		case ID:
			tmp = sqlite3pp::objects::Table::getIdList(columns::task::id, ascending);
			break;
		// TODO Default?
	}
	
	// Bisogna convertire da sqlite3_int64 a int64_t
	return vector<int64_t>(tmp.begin(), tmp.end());
}



Task*
TasksManager::getObject(const int64_t id) const
{
	if (not isValidId(id))
		throw TaskNotFoundException(to_string(id));

	return new Task(id, sqlite3pp::objects::Table::getParentDb(), this);
}


void
TasksManager::remove(const int64_t id)
{
	sqlite3pp::objects::Table::remove(id);
}


PriorityLevelsManager::PriorityLevelsManager(sqlite3* db, Db *gnudoDb): sqlite3pp::objects::Table(db, tables::priorityLevels), gnudo::abstract::managers::PriorityLevelsManager(gnudoDb)
{
}


int64_t
PriorityLevelsManager::_add(const string name, const int64_t priority, const string color)
{
	const string	sql	=	"INSERT INTO " + tables::priorityLevels + " "
							"("
							+ columns::prioritylevel::name + ", "
							+ columns::prioritylevel::priority + ", "
							+ columns::prioritylevel::color + 
							") "
							"VALUES (?, ?, ?);";
	sqlite3_stmt	*ppStmt;


	sqlite3pp_prepare_v2(sqlite3pp::objects::Table::getParentDb(), sql.c_str(), sql.size() + 1, &ppStmt, NULL);

	sqlite3pp_bind_text(ppStmt, 1, name.c_str(), name.size() + 1, SQLITE_STATIC);
	sqlite3pp_bind_int64(ppStmt, 2, priority);
	sqlite3pp_bind_text(ppStmt, 3, color.c_str(), color.size() + 1, SQLITE_STATIC);

	sqlite3pp_step(ppStmt);
	sqlite3_finalize(ppStmt);

	return priority;
}


vector<int64_t>
PriorityLevelsManager::getIdList(int orderBy, bool ascending) const
{
	vector<sqlite3_int64> tmp;

	switch(orderBy)
	{
		case NAME:
			tmp = sqlite3pp::objects::Table::getIdList(columns::prioritylevel::name, ascending);
			break;
		case PRIORITY:
			tmp = sqlite3pp::objects::Table::getIdList(columns::prioritylevel::priority, ascending);
			break;
		case COLOR:
			tmp = sqlite3pp::objects::Table::getIdList(columns::prioritylevel::color, ascending);
			break;
		// TODO Default?
	}
	
	return vector<int64_t>(tmp.begin(), tmp.end());
}


PriorityLevel *
PriorityLevelsManager::getObject(const int64_t id) const
{
	if (not isValidId(id))
		throw PriorityNotFoundException(to_string(id));
	
	return new PriorityLevel(sqlite3pp::objects::Table::getParentDb(), id, this);
}


void
PriorityLevelsManager::_remove(const int64_t id)
{
	sqlite3pp::objects::Table::remove(id);
}

