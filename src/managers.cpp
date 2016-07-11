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

# include <sqlite3pp.hpp>

# include "dbdefs.hpp"
# include "managers.hpp"


using namespace sqlite3pp::functions;
using namespace gnudo::sqlite;
using std::int64_t;
using std::string;
using std::time;


TasksManager::TasksManager(sqlite3 *db)
{
	__sqlitedb = db;
}


sqlite3_int64
TasksManager::add(const string title, const string description, const time_t creationTime, const time_t modificationTime, const bool completed)
{
	const string	sql	=	"INSERT INTO " + dbarch::tables::TASKS + " (title, description, ctime, mtime, completed) "
                            "VALUES (?, ?, ?, ?, ?);";
	sqlite3_stmt	*ppStmt;


	sqlite3pp_prepare_v2(__sqlitedb, sql.c_str(), sql.size() + 1, &ppStmt, NULL);

	sqlite3pp_bind_text(ppStmt, 1, title.c_str(), title.size() + 1, SQLITE_STATIC);
    sqlite3pp_bind_text(ppStmt, 2, description.c_str(), description.size() + 1, SQLITE_STATIC);
    sqlite3pp_bind_int(ppStmt, 3, creationTime);
    sqlite3pp_bind_int(ppStmt, 4, modificationTime);
    sqlite3pp_bind_int(ppStmt, 5, completed);

	sqlite3pp_step(ppStmt);
	sqlite3_finalize(ppStmt);


	sqlite3_int64 taskId = sqlite3_last_insert_rowid(__sqlitedb);
	
	if (taskId == 0)
		throw std::runtime_error("Id dell'ultimo task inserito non trovato");


	return taskId;
}



void
TasksManager::remove(const gnudo::abstract::Task* task)
{
	const string	sql = "DELETE FROM " + dbarch::tables::TASKS + " WHERE id = ?;";
	sqlite3_stmt	*ppStmt;

	sqlite3pp_prepare_v2(__sqlitedb, sql.c_str(), sql.size() + 1, &ppStmt, NULL);
	sqlite3pp_bind_int64(ppStmt, 1, ((gnudo::sqlite::Task*)task)->getId());
	sqlite3pp_step(ppStmt);
	sqlite3_finalize(ppStmt);
}


Task*
TasksManager::getTask(const sqlite3_int64 id)
{
	return new Task(id, __sqlitedb);
}


vector<sqlite3_int64>
TasksManager::getIdList(Order order, bool asc) const
{
	const string			columns[] = {"title", "description", "ctime", "mtime", "completed"};
	const string			sql = "SELECT id FROM " + dbarch::tables::TASKS + " ORDER BY " + columns[order] + (asc? " ASC" : " DESC") + ";";
	sqlite3_stmt			*ppStmt;
	vector<sqlite3_int64>	ret;

	sqlite3pp_prepare_v2(__sqlitedb, sql.c_str(), sql.size() + 1, &ppStmt, NULL);

	while(sqlite3pp_step(ppStmt) == SQLITE_ROW)
		ret.insert(ret.end(), sqlite3pp_column_int64(ppStmt, 0, __sqlitedb));

	sqlite3_finalize(ppStmt);

	return ret;
}

