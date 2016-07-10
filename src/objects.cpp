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
using std::int64_t;
using std::string;
using std::cout;
using std::endl;
using std::time;


// WARNING	Ogni metodo che modifica questo task deve chiamare setModificationTime()


Task::Task(const sqlite3_int64 id, sqlite3* db): __id(id)
{
	 __sqlitedb = db;
}


// GET


sqlite3_stmt*
Task::_getSelectStatement(const string columnName) const
{
	const string	sql = "SELECT " + columnName + " FROM " + dbarch::tables::TASKS + " WHERE id = ?;";
	sqlite3_stmt	*ppStmt;

	sqlite3pp_prepare_v2(__sqlitedb, sql.c_str(), sql.size() + 1, &ppStmt, NULL);
	sqlite3pp_bind_int64(ppStmt, 1, getId());

	return ppStmt;
}


template <typename R>
R
Task::_getColumn(const string columnName, R (*sqlite3ppfunc) (sqlite3_stmt* ppStmt, int iCol, sqlite3* db)) const
{
	sqlite3_stmt *ppStmt = _getSelectStatement(columnName);
	R ret;

	if (sqlite3pp_step(ppStmt) == SQLITE_ROW)
		ret = sqlite3ppfunc(ppStmt, 0, __sqlitedb);
	else
		throw std::runtime_error("Impossibile ottenere la colonna '" + columnName +"'");

	sqlite3_finalize(ppStmt);

	return ret;
}


sqlite3_int64
Task::getId() const
{
	return __id;
}


string
Task::getTitle() const
{
	const char *tmp = (const char*)_getColumn<const unsigned char*>("title", sqlite3pp_column_text);
	string r = string(tmp);
	return r;
}


string
Task::getDescription() const
{
	const char *tmp = (const char*)_getColumn<const unsigned char*>("description", sqlite3pp_column_text);
	string r = string(tmp);
	return r;
}


time_t
Task::getCreationTime() const
{
	return _getColumn<sqlite3_int64>("ctime", sqlite3pp_column_int64);
}


time_t
Task::getModificationTime() const
{
	return _getColumn<sqlite3_int64>("mtime", sqlite3pp_column_int64);
}


bool 
Task::isCompleted() const
{
	return _getColumn<int>("completed", sqlite3pp_column_int);
}


// SET


// Sqlite3 bind sul parametro 1 con il valore
sqlite3_stmt*
Task::_getUpdateStatement(const string columnName)
{
	const string	sql = 	"UPDATE " + dbarch::tables::TASKS + " "
							"SET " + columnName + " = ? "
							"WHERE id = ?;";
	sqlite3_stmt	*ppStmt;


	sqlite3pp_prepare_v2(__sqlitedb, sql.c_str(), sql.size() + 1, &ppStmt, NULL);
	sqlite3pp_bind_int64(ppStmt, 2, getId());

	return ppStmt;
}


void
Task::setTitle(const string title)
{
	sqlite3_stmt *ppStmt = _getUpdateStatement("title");

	sqlite3pp_bind_text(ppStmt, 1, title.c_str(), title.size() + 1, SQLITE_STATIC);
	sqlite3pp_step(ppStmt);
	sqlite3_finalize(ppStmt);

    setModificationTime(time(NULL));
}


void
Task::setDescription(const string description)
{
	sqlite3_stmt *ppStmt = _getUpdateStatement("description");

	sqlite3pp_bind_text(ppStmt, 1, description.c_str(), description.size() + 1, SQLITE_STATIC);
	sqlite3pp_step(ppStmt);
	sqlite3_finalize(ppStmt);
	
    setModificationTime(time(NULL));
}


void
Task::setStatus(const bool isCompleted)
{
	sqlite3_stmt *ppStmt = _getUpdateStatement("completed");

	sqlite3pp_bind_int(ppStmt, 1, isCompleted);
	sqlite3pp_step(ppStmt);
	sqlite3_finalize(ppStmt);
	
    setModificationTime(time(NULL));
}


void
Task::setModificationTime(const time_t time)
{
	sqlite3_stmt *ppStmt = _getUpdateStatement("mtime");

	sqlite3pp_bind_int64(ppStmt, 1, time);
	sqlite3pp_step(ppStmt);
	sqlite3_finalize(ppStmt);
}

void
Task::setCreationTime(const time_t time)
{
    sqlite3_stmt *ppStmt = _getUpdateStatement("ctime");

    sqlite3pp_bind_int64(ppStmt, 1, time);
    sqlite3pp_step(ppStmt);
    sqlite3_finalize(ppStmt);
}



